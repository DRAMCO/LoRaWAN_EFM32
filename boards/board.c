/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: Target board general functions implementation

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
#include "board.h"
#include "gpio.h"
#include "em_device.h"

/*!
 * Unique Devices IDs register set ( EFM32GG )
 */
#define         ID1                                 0x0FE081F0
#define         ID2                                 0x0FE081F4

Gpio_t Led0;
Gpio_t Led1;

Gpio_t Pb0;
Gpio_t Pb1;

Gpio_t Si7021_Enable;
Gpio_t Adps9200_Int;

Adc_t Adc;
I2c_t I2c;

/*!
 * Initializes the unused GPIO to a know status
 */
static void BoardUnusedIoInit( void );

/*!
 * System Clock Configuration
 */
static void SystemClockConfig( void );

/*!
 * Used to measure and calibrate the system wake-up time from STOP mode
 */
static void CalibrateSystemWakeupTime( void );

/*!
 * System Clock Re-Configuration when waking up from STOP mode
 */
static void SystemClockReConfig( void );

/*!
 * Timer used at first boot to calibrate the SystemWakeupTime
 */
static TimerEvent_t CalibrateSystemWakeupTimeTimer;

/*!
 * Flag to indicate if the MCU is Initialized
 */
static bool McuInitialized = false;

/*!
 * Flag to indicate if the SystemWakeupTime is Calibrated
 */
static bool SystemWakeupTimeCalibrated = false;

/*!
 * Callback indicating the end of the system wake-up time calibration
 */
static void OnCalibrateSystemWakeupTimeTimerEvent( void )
{
    SystemWakeupTimeCalibrated = true;
}

/*!
 * Nested interrupt counter.
 *
 * \remark Interrupt should only be fully disabled once the value is 0
 */
static uint8_t IrqNestLevel = 0;

void BoardReadRegVersion(uint8_t * data){
	SX1272ReadBuffer(0x42, data, 1);
}

void BoardDisableIrq( void )
{
    __disable_irq( );
    IrqNestLevel++;
}

void BoardEnableIrq( void )
{
    IrqNestLevel--;
    if( IrqNestLevel == 0 )
    {
        __enable_irq( );
    }
}

void BoardInitPeriph( void )
{
	/* Initialize LEDs */
	GpioInit( &Led0, LED_0, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0 );
	GpioInit( &Led1, LED_1, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0 );

	// Switch LED 0 and 1 OFF
	GpioWrite( &Led0, 0 );
	GpioWrite( &Led1, 0 );

	/* Initialize push buttons */
	GpioInit( &Pb0, BUTTON_0, PIN_INPUT, PIN_PUSH_PULL, PIN_PULL_UP, 1 );
	GpioInit( &Pb1, BUTTON_1, PIN_INPUT, PIN_PUSH_PULL, PIN_PULL_UP, 1 );
	GpioSetInterrupt(&Pb0, IRQ_FALLING_EDGE, IRQ_LOW_PRIORITY, &Button_0_ISR );
	GpioSetInterrupt(&Pb1, IRQ_FALLING_EDGE, IRQ_LOW_PRIORITY, &Button_1_ISR );

#ifdef HW_VERSION_3
	/* Enable Si7021 temperature and humidity sensor */
	GpioInit( &Si7021_Enable, SI7021_ENABLE, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 1);
	GpioWrite( &Si7021_Enable, 1 ); // enable

	/* Setup interrupt for ADPS 9200 light sensor */
	GpioInit( &Adps9200_Int, ADPS9200_INT, PIN_INPUT, PIN_PUSH_PULL, PIN_NO_PULL, 1 );
	GpioSetInterrupt(&Adps9200_Int, IRQ_FALLING_EDGE, IRQ_LOW_PRIORITY, &Adps9200_ISR );

	/* Init I2c */
    I2cInit(&I2c, I2C_SCL, I2C_SDA);
#endif
}

void BoardInitMcu( void )
{
    if( McuInitialized == false )
    {
    	RtcInit();
    }

    SpiInit( &SX1272.Spi, RADIO_MOSI, RADIO_MISO, RADIO_SCLK, RADIO_NSS );
    SX1272IoInit( );

    //UartInit(&Uart1, UART_1, PE_0, PE_1);
    //UartConfig(&Uart1, RX_TX, 115200, UART_8_BIT, UART_1_STOP_BIT, NO_PARITY, NO_FLOW_CTRL);

    if( McuInitialized == false )
    {
        McuInitialized = true;
        if( GetBoardPowerSource( ) == BATTERY_POWER )
        {
            CalibrateSystemWakeupTime( );
        }
    }
}

void BoardDeInitMcu( void )
{
	assert_param( FAIL );
}

uint32_t BoardGetRandomSeed( void )
{
    return ( ( *( uint32_t* )ID1 ) ^ ( *( uint32_t* )ID2 ) );
}

void BoardGetUniqueId( uint8_t *id )
{
	id[7] = ( ( *( uint32_t* )ID1 ) ) >> 24;
    id[6] = ( ( *( uint32_t* )ID1 ) ) >> 16;
    id[5] = ( ( *( uint32_t* )ID1 ) ) >> 8;
    id[4] = ( ( *( uint32_t* )ID1 ) );
    id[3] = ( ( *( uint32_t* )ID2 ) ) >> 24;
    id[2] = ( ( *( uint32_t* )ID2 ) ) >> 16;
    id[1] = ( ( *( uint32_t* )ID2 ) ) >> 8;
    id[0] = ( ( *( uint32_t* )ID2 ) );
}

uint8_t BoardGetBatteryLevel( void )
{
	assert_param( FAIL );
	return 0; // never reached
}

static void BoardUnusedIoInit( void )
{
	assert_param( FAIL );
}

void SystemClockConfig( void )
{
	assert_param( FAIL );
}

void CalibrateSystemWakeupTime( void )
{
    if( SystemWakeupTimeCalibrated == false )
    {
        TimerInit( &CalibrateSystemWakeupTimeTimer, OnCalibrateSystemWakeupTimeTimerEvent );
        TimerSetValue( &CalibrateSystemWakeupTimeTimer, 1000 );
        TimerStart( &CalibrateSystemWakeupTimeTimer );
        while( SystemWakeupTimeCalibrated == false )
        {
            TimerLowPowerHandler( );
        }
    }
}

void SystemClockReConfig( void )
{
	assert_param(FAIL);
}

void SysTick_Handler( void )
{
	assert_param(FAIL);
}

uint8_t GetBoardPowerSource( void )
{
#if defined( USE_USB_CDC )
    if( UartUsbIsUsbCableConnected( ) == 0 )
    {
        return BATTERY_POWER;
    }
    else
    {
        return USB_POWER;
    }
#else
    return BATTERY_POWER;
#endif
}

#ifdef USE_FULL_ASSERT
/*
 * Function Name  : assert_failed
 * Description    : Reports the name of the source file and the source line number
 *                  where the assert_param error has occurred.
 * Input          : - file: pointer to the source file name
 *                  - line: assert_param error line source number
 * Output         : None
 * Return         : None
 */
void assert_failed( uint8_t* file, uint32_t line )
{
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while( 1 )
    {
    }
}
#endif
