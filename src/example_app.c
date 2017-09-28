/*  ____  ____      _    __  __  ____ ___
 * |  _ \|  _ \    / \  |  \/  |/ ___/ _ \
 * | | | | |_) |  / _ \ | |\/| | |  | | | |
 * | |_| |  _ <  / ___ \| |  | | |__| |_| |
 * |____/|_| \_\/_/   \_\_|  |_|\____\___/
 *                           research group
 *                             dramco.be/
 *
 *   KU Leuven - Technology Campus Gent,
 *   Gebroeders De Smetstraat 1,
 *   B-9000 Gent, Belgium
 *
 *         File: example_app.c
 *      Created: 2017-09-20
 *       Author: Geoffrey Ottoy
 *
 *  Description: Example application. Measure and accumulate temperature
 *  	and relative humidity. Periodically send accumulated data.
 */

#if defined(APP_TYPE) && (APP_TYPE == EXAMPLE_APP)

// Standard C libraries
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

// "commissioning_mydev.h" contains keys & IDs associated to your LoRaWAN network application and device.
#include "Comissioning_mydev.h"
// "board.h" contains functionality to initialize and interface with the EFM32 and its peripherals
#include "board.h"
// "omux-board.h" contains functionality to interface with several lines (outputs) of the expansion board,
// through the use of the I2C output MUX on the expansion board.
#include "omux-board.h"
// "si7021-board.h" offers functionality to interface with the Happy Gecko on-board temperature and
// humidity sensor.
#include "si7021-board.h"
// "LoRaMac.h" provides access to the LoRaWAN MAC layer functions.
#include "LoRaMac.h"


#define APP_SENSE_DUTYCYCLE					5000	// Milliseconds between two sensor readings
#define APP_SENSE_DUTYCYCLE_RND				1000	// Random delay [ms]
#define APP_DEFAULT_DATARATE				DR_5	// SF7 - BW125
#define APP_PORT_TEMP						1		// Application port for temperature readings
#define APP_PORT_RH							2		// Application port for relative humidity
#define APP_PORT_BTN						3		// Application port for button action
#define APP_PORT_MIXED						4		// Application port for mixed payloads
#define APP_TEMP_SIZE						2		// Number of bytes in a temperature reading
#define APP_RH_SIZE							2		// Number of bytes in a relative humidity reading
#define APP_DATA_TEMP_MAX_SIZE				8		// Size of temperature data buffer
#define APP_DATA_RH_MAX_SIZE				8		// Size of humidity data buffer
#define APP_DATA_MIXED_MAX_SIZE				18		// Size of mixed data buffer
#define APP_ADR_ON                          1		// Whether we use Adaptive Data Rate or not
#define APP_CONFIRMED_MSG_ON                1		// Whether this example will transmit confirmed or unconfirmed packets

#if (OVER_THE_AIR_ACTIVATION == 0)
    static uint8_t  NwkSKey[] = LORAWAN_NWKSKEY;
    static uint8_t  AppSKey[] = LORAWAN_APPSKEY;
    static uint32_t DevAddr   = LORAWAN_DEVICE_ADDRESS;
#else
    static uint8_t DevEui[] = LORAWAN_DEVICE_EUI;
    static uint8_t AppEui[] = LORAWAN_APPLICATION_EUI;
    static uint8_t AppKey[] = LORAWAN_APPLICATION_KEY;
#endif


typedef enum DeviceState
{
    DEVICE_STATE_INIT,
    DEVICE_STATE_JOIN,
    DEVICE_STATE_SENSE,
    DEVICE_STATE_SLEEP
} DeviceState_t;

DeviceState_t devState;

static uint32_t     TxDutyCycleTime;            // Defines the application data transmission duty cycle
static TimerEvent_t TxNextPacketTimer;          // Timer to handle the application data transmission duty cycle
static bool         NextTx = true;              // Indicates if a new packet can be sent

static uint8_t tDataBuffer[APP_DATA_TEMP_MAX_SIZE]; // User application data
static uint8_t rhDataBuffer[APP_DATA_RH_MAX_SIZE]; // User application data
static uint8_t mixedDataBuffer[APP_DATA_MIXED_MAX_SIZE]; // User application data

uint8_t tBufferPointer;
uint8_t rhBufferPointer;
uint8_t senseCounter;
uint8_t payloadSize;
uint8_t *payload;

static void AccumulateT(uint32_t tData){
	if(!(tBufferPointer>APP_DATA_TEMP_MAX_SIZE-APP_TEMP_SIZE)){
		int16_t temp = (uint16_t)(tData);
		*(tDataBuffer+tBufferPointer) = (uint8_t)(temp >> 8);
		*(tDataBuffer+tBufferPointer+1) = (uint8_t)(temp & 0xFF);
		tBufferPointer += APP_TEMP_SIZE;
	}
}

static void AccumulateRH(uint32_t rhData){
	if(!(rhBufferPointer>APP_DATA_RH_MAX_SIZE-APP_RH_SIZE)){
		int16_t rh = (uint16_t)(rhData);
		*(rhDataBuffer+rhBufferPointer) = (uint8_t)(rh >> 8);
		*(rhDataBuffer+rhBufferPointer+1) = (uint8_t)(rh & 0xFF);
		rhBufferPointer += APP_RH_SIZE;
	}
}

static void PrepareTxFrame(uint8_t port){
	switch(port){
		case APP_PORT_TEMP: {
			payload = tDataBuffer;
			payloadSize = APP_DATA_TEMP_MAX_SIZE;
			tBufferPointer = 0;
		} break;
		case APP_PORT_RH: {
			payload = rhDataBuffer;
			payloadSize = APP_DATA_RH_MAX_SIZE;
			rhBufferPointer = 0;
		} break;
		default: {
			uint8_t mdbPtr = 0;
			// copy t data
			mixedDataBuffer[mdbPtr++] = tBufferPointer;
			memcpy(mixedDataBuffer+mdbPtr, tDataBuffer, tBufferPointer);
			mdbPtr+=tBufferPointer;
			// copy rh data
			mixedDataBuffer[mdbPtr++] = rhBufferPointer;
			memcpy(mixedDataBuffer+mdbPtr, rhDataBuffer, rhBufferPointer);
			//
			payload = mixedDataBuffer;
			payloadSize = APP_DATA_MIXED_MAX_SIZE;
			rhBufferPointer = 0;
			tBufferPointer = 0;
		} break;
	}
}

static bool SendFrame(uint8_t port)
{
    McpsReq_t mcpsReq;
    LoRaMacTxInfo_t txInfo;

    if (LoRaMacQueryTxPossible(payloadSize, &txInfo) != LORAMAC_STATUS_OK)
    {
        // Send empty frame in order to flush MAC commands
        mcpsReq.Type = MCPS_UNCONFIRMED;
        mcpsReq.Req.Unconfirmed.fBuffer = NULL;
        mcpsReq.Req.Unconfirmed.fBufferSize = 0;
        mcpsReq.Req.Unconfirmed.Datarate = APP_DEFAULT_DATARATE;
    }
    else // Send the data
    {
        if (APP_CONFIRMED_MSG_ON)
        {
            // Send a confirmed packet
            mcpsReq.Type = MCPS_CONFIRMED;
            mcpsReq.Req.Confirmed.fPort = port;
            mcpsReq.Req.Confirmed.fBuffer = payload;
            mcpsReq.Req.Confirmed.fBufferSize = payloadSize;
            mcpsReq.Req.Confirmed.NbTrials = 8;
            mcpsReq.Req.Confirmed.Datarate = APP_DEFAULT_DATARATE;
        }
        else
        {
            // Send an unconfirmed packet
            mcpsReq.Type = MCPS_UNCONFIRMED;
            mcpsReq.Req.Unconfirmed.fPort = port;
            mcpsReq.Req.Unconfirmed.fBuffer = payload;
            mcpsReq.Req.Unconfirmed.fBufferSize = payloadSize;
            mcpsReq.Req.Unconfirmed.Datarate = APP_DEFAULT_DATARATE;
        }
    }

    if (LoRaMacMcpsRequest(&mcpsReq) == LORAMAC_STATUS_OK)
        return false;

    return true;
}

static void OnTxNextPacketTimerEvent(void)
{
    TimerStop(&TxNextPacketTimer);

    // Check if we have already joined a network
    MibRequestConfirm_t mibReq;
    mibReq.Type = MIB_NETWORK_JOINED;
    LoRaMacStatus_t status = LoRaMacMibGetRequestConfirm(&mibReq);
    if (status == LORAMAC_STATUS_OK)
    {
        // If we already joined then transmit data
        if (mibReq.Param.IsNetworkJoined == true)
        {
        	devState = DEVICE_STATE_SENSE;
            NextTx = true;
        }
        else // We need to join before we can send data
        	devState = DEVICE_STATE_JOIN;
    }
}

static void McpsConfirm(McpsConfirm_t *mcpsConfirm)
{
    // Packet was send (and we have waited for replies)
    NextTx = true;
}

static void McpsIndication(McpsIndication_t *mcpsIndication)
{
    if (mcpsIndication->Status == LORAMAC_EVENT_INFO_STATUS_OK)
    {
        // Packet received
    }
}

static void MlmeConfirm(MlmeConfirm_t *mlmeConfirm)
{
    if (mlmeConfirm->Status == LORAMAC_EVENT_INFO_STATUS_OK)
    {
        // Check if the node has joined the network
        if (mlmeConfirm->MlmeRequest == MLME_JOIN)
        	devState = DEVICE_STATE_SENSE;
    }

    NextTx = true;
}

//static void MlmeIndication(MlmeIndication_t *mlmeIndication)
//{
//}

int main_example( void )
{
    LoRaMacPrimitives_t LoRaMacPrimitives;
    LoRaMacCallback_t LoRaMacCallbacks;
    MibRequestConfirm_t mibReq;

    BoardInitMcu();
    BoardInitPeriph();
    OMuxLedOff();

    srand(time(NULL));   // should only be called once

    senseCounter = 0;
    devState = DEVICE_STATE_INIT;
    while (true)
    {
        switch (devState)
        {
            case DEVICE_STATE_INIT:
            {
                LoRaMacPrimitives.MacMcpsConfirm = McpsConfirm;
                LoRaMacPrimitives.MacMcpsIndication = McpsIndication;
                LoRaMacPrimitives.MacMlmeConfirm = MlmeConfirm;
                //LoRaMacPrimitives.MacMlmeIndication = MlmeIndication;
                //LoRaMacCallbacks.GetBatteryLevel = BoardGetBatteryLevel;
                //LoRaMacCallbacks.GetTemperatureLevel = NULL;
                LoRaMacInitialization(&LoRaMacPrimitives, &LoRaMacCallbacks);

                TimerInit(&TxNextPacketTimer, OnTxNextPacketTimerEvent);

                // Enable or disable Adaptive Data Rate
                mibReq.Type = MIB_ADR;
                mibReq.Param.AdrEnable = APP_ADR_ON;
                LoRaMacMibSetRequestConfirm(&mibReq);

                // Set whether this is a public or private network
                mibReq.Type = MIB_PUBLIC_NETWORK;
                mibReq.Param.EnablePublicNetwork = LORAWAN_PUBLIC_NETWORK;
               // mibReq.Param.UpLinkCounter
                LoRaMacMibSetRequestConfirm( &mibReq );

                // Add some channels other than the default 3 channels
                // Channel = { Frequency [Hz], { ( ( DrMax << 4 ) | DrMin ) }, Band }
                LoRaMacChannelAdd(3, (ChannelParams_t){867100000, {((DR_5 << 4) | DR_0)}, 0});
                LoRaMacChannelAdd(4, (ChannelParams_t){867300000, {((DR_5 << 4) | DR_0)}, 0});
                LoRaMacChannelAdd(5, (ChannelParams_t){867500000, {((DR_5 << 4) | DR_0)}, 0});

                // Set which channel to use for RX2
                mibReq.Type = MIB_RX2_CHANNEL;
                mibReq.Param.Rx2Channel = (Rx2ChannelParams_t){869525000, DR_3};
                LoRaMacMibSetRequestConfirm(&mibReq);

                devState = DEVICE_STATE_JOIN;
                break;
            }
            case DEVICE_STATE_JOIN:
            {
#if (OVER_THE_AIR_ACTIVATION != 0)
                MlmeReq_t mlmeReq;

                // Initialize LoRaMac device unique ID
                mlmeReq.Type = MLME_JOIN;
                mlmeReq.Req.Join.DevEui = DevEui;
                mlmeReq.Req.Join.AppEui = AppEui;
                mlmeReq.Req.Join.AppKey = AppKey;

                if (NextTx == true)
                    LoRaMacMlmeRequest(&mlmeReq);

                devState = DEVICE_STATE_SLEEP;
#else
                // Choose a random device address if not already defined in Comissioning.h
                if (DevAddr == 0)
                {
                    srand1(BoardGetRandomSeed());
                    DevAddr = randr(0, 0x01FFFFFF);
                }

                mibReq.Type = MIB_NET_ID;
                mibReq.Param.NetID = LORAWAN_NETWORK_ID;
                LoRaMacMibSetRequestConfirm(&mibReq);

                mibReq.Type = MIB_DEV_ADDR;
                mibReq.Param.DevAddr = DevAddr;
                LoRaMacMibSetRequestConfirm(&mibReq);

                mibReq.Type = MIB_NWK_SKEY;
                mibReq.Param.NwkSKey = NwkSKey;
                LoRaMacMibSetRequestConfirm(&mibReq);

                mibReq.Type = MIB_APP_SKEY;
                mibReq.Param.AppSKey = AppSKey;
                LoRaMacMibSetRequestConfirm(&mibReq);

                mibReq.Type = MIB_NETWORK_JOINED;
                mibReq.Param.IsNetworkJoined = true;
                LoRaMacMibSetRequestConfirm(&mibReq);

                devState = DEVICE_STATE_SENSE;
#endif
                break;
            }
            case DEVICE_STATE_SENSE:
            {
            	uint32_t tData;
            	uint32_t rhData;
            	uint8_t appPort;
            	Si7021_MeasureRHAndTemp(&rhData, &tData);

            	// Measure temperature every time the device gets in the state "DEVICE_STATE_SENSE"
            	AccumulateT(tData);
            	if(senseCounter == 2){ // Measure relative humidity every three times
            		AccumulateRH(rhData);
            		senseCounter = 0;
            	}
            	else{
            		senseCounter++;
            	}

            	if((tBufferPointer+rhBufferPointer) >= APP_DATA_MIXED_MAX_SIZE-APP_RH_SIZE-APP_TEMP_SIZE){
            		// send mixed data packet
            		NextTx = true;
            		appPort = APP_PORT_MIXED;
            	}
            	else{
            		if(tBufferPointer == APP_DATA_TEMP_MAX_SIZE){
            			// send temp data packet
						NextTx = true;
						appPort = APP_PORT_TEMP;
            		}
            		else{
            			if(rhBufferPointer == APP_DATA_RH_MAX_SIZE){
            				// send temp data packet
							NextTx = true;
							appPort = APP_PORT_RH;
            			}
            			else{
            				NextTx = false; // don't transmit yet.
            			}
            		}
            	}

                if(NextTx){
                    PrepareTxFrame(appPort);
                    GpioWrite(&Led1, 1);
                    SendFrame(appPort);
                    GpioWrite(&Led1, 0);
                }

                // Schedule next sensor reading
                TxDutyCycleTime = APP_SENSE_DUTYCYCLE + randr(-APP_SENSE_DUTYCYCLE_RND, APP_SENSE_DUTYCYCLE_RND);
                TimerSetValue(&TxNextPacketTimer, TxDutyCycleTime);
                TimerStart(&TxNextPacketTimer);

                devState = DEVICE_STATE_SLEEP;
                break;
            }
            case DEVICE_STATE_SLEEP:
            {
                // Wake up through events
                TimerLowPowerHandler();
                break;
            }
        }
    }
}

// This function is called when PB0 is pressed
void Button_0_ISR(void){
	GpioToggle(&Led0);
}

// This function is called when PB1 is pressed
void Button_1_ISR(void){
	OMuxToggleLed();
}

#endif /* EXAMPLE_APP */
