/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: MCU RTC timer and low power modes management

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
#include <math.h>
#include "board.h"
#include "rtc-board.h"
#include "em_rtc.h"
#include "em_cmu.h"
#include "em_emu.h"

#define RTC_TICKS_PER_S			32768
#define RTC_TICKS_PER_MS		32.768
#define RTC_TICK_DURATION_MS	0.030517578

// EFM32 temperature sensor gradient
#define THERMOMETER_GRADIENT  (-6.3)

// RTC variables. Used for converting RTC counter to system time
static uint32_t   rtcOverflowCounter    = 0;
static uint32_t   rtcOverflowInterval   = 0;
static uint32_t   rtcOverflowIntervalR  = 0;

// Thermometer calibration variables
static uint8_t    thermCalTemp;
static uint16_t   thermCalValue;

// Temperature compensation variables
static int32_t    tempCompAccumulator   = 0;
static int32_t    tempCompInterval      = 0;

static uint32_t      rtcFreq;               /**< RTC Frequence. 32.768 kHz */
static TimerTime_t   previousTime = 0;

/*!
 * Flag used to indicates a the MCU has waken-up from an external IRQ
 */
volatile bool NonScheduledWakeUp = false;

/*!
 * \brief Flag to indicate if the timestamps until the next event is long enough
 * to set the MCU into low power mode
 */
static bool RtcTimerEventAllowsLowPower = false;

/*!
 * \brief Flag to disable the LowPower Mode even if the timestamps until the
 * next event is long enough to allow Low Power mode
 */
static bool LowPowerDisableDuringTask = false;

/*!
 * \brief Indicates if the RTC is already Initialized or not
 */
static bool RtcInitalized = false;

/*!
 * \brief Hold the Wake-up time duration in ms
 */
volatile uint32_t McuWakeUpTime = 0;

/*!
 * \brief Hold the cumulated error in micro-second to compensate the timing errors
 */
static int32_t TimeoutValueError = 0;


void RtcInit( void )
{
	if( RtcInitalized == false )
	{
		// Reset overflow counter
		rtcOverflowCounter = 0;

		// Calculate overflow interval based on RTC counter width and frequency
		rtcOverflowInterval   = ((0x00FFFFFF+1) / RTC_TICKS_PER_MS);
		rtcOverflowIntervalR  = ((0x00FFFFFF+1) - (rtcOverflowInterval * RTC_TICKS_PER_MS)); // remainder

		RtcInitalized = true;

		// Ensure LE modules are accessible
		CMU_ClockEnable(cmuClock_CORELE, true);

		// Enable LFACLK in CMU (will also enable oscillator if not enabled)
		CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFXO);

		// Use the prescaler to reduce power consumption.
		CMU_ClockDivSet(cmuClock_RTC, cmuClkDiv_1);

		rtcFreq = CMU_ClockFreqGet(cmuClock_RTC);

		// Enable clock to RTC module
		CMU_ClockEnable(cmuClock_RTC, true);

		RTC_Init_TypeDef init = RTC_INIT_DEFAULT;
		init.enable   = false;
		init.debugRun = false;
		init.comp0Top = false;
		RTC_Init(&init);

		// Disable all rtc interrupts
		RTC_IntDisable(RTC_IEN_OF | RTC_IEN_COMP0);
		RTC_IntClear(RTC_IFC_OF | RTC_IFC_COMP0);

		RTC_CounterReset();

		// Enable interrupt on overflow
		RTC_IntEnable(RTC_IF_OF);

		// Enable interrupts
		NVIC_SetPriority(RTC_IRQn, 4);
		NVIC_ClearPendingIRQ(RTC_IRQn);
		NVIC_EnableIRQ(RTC_IRQn);

		// Enable RTC
		RTC_Enable(true);
	}
}

void RtcSetTimeout( uint32_t timeout )
{
	RTC_IntClear(RTC_IEN_COMP0);

	previousTime = RtcGetTimerValue();

	if (timeout < 1)
		timeout = 1;

	// timeoutValue is used for complete computation
	double timeoutValue = round( timeout * RTC_TICKS_PER_MS );

	// timeoutValueTemp is used to compensate the cumulating errors in timing far in the future
	double timeoutValueTemp =  ( double )timeout * RTC_TICKS_PER_MS;

	// Compute timeoutValue error
	double error = timeoutValue - timeoutValueTemp;

	// Add new error value to the cumulated value in uS
	TimeoutValueError += ( error * 1000 );

	// Correct cumulated error if greater than ( RTC_ALARM_TICK_DURATION * 1000 )
	if( TimeoutValueError >= ( int32_t )( RTC_TICK_DURATION_MS * 1000 ) )
	{
		TimeoutValueError = TimeoutValueError - ( uint32_t )( RTC_TICK_DURATION_MS * 1000 );
		timeoutValue = timeoutValue + 1;
	}

	// Rounding errors should not cause us to set the number behind the current time
	uint32_t value = (previousTime * RTC_TICKS_PER_MS) + timeoutValue;
	if (RTC->CNT > value && value + RTC_TICKS_PER_MS > RTC->CNT)
		RTC_CompareSet(0, RTC->CNT + 1);
	else
		RTC_CompareSet(0, value);

	RTC_IntEnable(RTC_IF_COMP0);
}

TimerTime_t RtcGetAdjustedTimeoutValue( uint32_t timeout )
{
    if( timeout > McuWakeUpTime )
    {   // we have waken up from a GPIO and we have lost "McuWakeUpTime" that we need to compensate on next event
        if( NonScheduledWakeUp == true )
        {
            NonScheduledWakeUp = false;
            timeout -= McuWakeUpTime;
        }
    }

    if( timeout > McuWakeUpTime )
    {
    	RtcTimerEventAllowsLowPower = true;
    	/*
    	// we don't go in Low Power mode for delay below 50ms (needed for LEDs)
    	if (timeout < 50)
        {
            RtcTimerEventAllowsLowPower = false;
        }
        else
        {
            RtcTimerEventAllowsLowPower = true;
            timeout -= McuWakeUpTime;
        }*/
    }
    return  timeout;
}

TimerTime_t RtcGetTimerValue( void )
{
	TimerTime_t t = 0;

	// Add time based on number of counter overflows
//	t += rtcOverflowCounter * rtcOverflowInterval;

	// Add remainder if the overflow interval is not an integer
//	if ( rtcOverflowIntervalR != 0 )
//	{
//		t += (rtcOverflowCounter * rtcOverflowIntervalR) / RTC_TICKS_PER_MS;
//	}

	// Add the number of milliseconds for RTC
	t += ( RTC->CNT / RTC_TICKS_PER_MS );

	// Add compensation for crystal temperature drift
	t += tempCompAccumulator;

	return t;
}

TimerTime_t RtcGetElapsedAlarmTime( void )
{
    TimerTime_t currentTime = RtcGetTimerValue();
    if( currentTime < previousTime )
    {
        return( currentTime + ( rtcOverflowInterval - previousTime ) );
    }
    else
    {
        return( currentTime - previousTime );
    }
}

TimerTime_t RtcComputeFutureEventTime( TimerTime_t futureEventInTime )
{
    return( RtcGetTimerValue( ) + futureEventInTime );
}

TimerTime_t RtcComputeElapsedTime( TimerTime_t eventInTime )
{
    TimerTime_t elapsedTime = 0;

    // Needed at boot, cannot compute with 0 or elapsed time will be equal to current time
    if( eventInTime == 0 )
    {
        return 0;
    }

    elapsedTime = RtcGetTimerValue();
    if( elapsedTime < eventInTime )
    { // roll over of the counter
        return( elapsedTime + ( rtcOverflowInterval - eventInTime ) );
    }
    else
    {
        return( elapsedTime - eventInTime );
    }
}

void BlockLowPowerDuringTask ( bool status )
{
    LowPowerDisableDuringTask = status;
}

void RtcEnterLowPowerStopMode( void )
{
	if( ( LowPowerDisableDuringTask == false ) && ( RtcTimerEventAllowsLowPower == true ) )
	{
		//EMU_EnterEM1();

		if (Radio.GetStatus() == RF_IDLE)
			EMU_EnterEM2(true);
		else
			EMU_EnterEM1();
	}
}

void RtcRecoverMcuStatus( void )
{
	assert_param( FAIL );
}


/***************************************************************************//**
 * @brief RTC Interrupt Handler
 ******************************************************************************/
void RTC_IRQHandler(void)
{
	uint32_t flags = RTC_IntGetEnabled();
	RTC_IntClear(RTC_IFC_OF | RTC_IFC_COMP0);

	// Check for overflow
	if (flags & RTC_IF_OF)
		rtcOverflowCounter++;

	// Check if timer expired
	if (flags & RTC_IF_COMP0)
	{
		RTC_IntDisable(RTC_IEN_COMP0);
		TimerIrqHandler();
	}
}

TimerTime_t RtcTempCompensation( TimerTime_t period, float temperature )
{
	// stub function
	return period;
}

void HAL_Delay (uint32_t ms)
{
	uint32_t startTime = RtcGetTimerValue();
	while((RtcGetTimerValue() - startTime) < ms); // busy wait until at least ms ticks have passed
}
