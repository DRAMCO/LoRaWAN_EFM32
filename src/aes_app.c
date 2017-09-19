#include <string.h>
#include <math.h>

#include "Comissioning_geoff.h"
#include "board.h"

#include "LoRaMac.h"

#include <time.h>
#include <stdlib.h>

#define APP_ENCRYPT_DUTYCYCLE                    1000   // Milliseconds between two transmissions

#define APP_DEFAULT_DATARATE                DR_5    // SF7 - BW125
#define APP_PORT                            1       // Application port
#define APP_DATA_SIZE                       2      // Size of packets to transmit in this example
#define APP_DATA_MAX_SIZE                   64      // Size of user data buffer
#define APP_ADR_ON                          1       // Whether we use Adaptive Data Rate or not
#define APP_CONFIRMED_MSG_ON                1       // Whether this example will transmit confirmed or unconfirmed packets

static uint8_t DevEui[] = LORAWAN_DEVICE_EUI;
static uint8_t AppEui[] = LORAWAN_APPLICATION_EUI;
static uint8_t AppKey[] = LORAWAN_APPLICATION_KEY;


static enum eDevicState
{
    DEVICE_STATE_INIT,
	DEVICE_STATE_ENCRYPT,
    DEVICE_STATE_SLEEP
} DeviceState;

static uint8_t     AppData[APP_DATA_MAX_SIZE]; // User application data
static TimerEvent_t EncryptNextPacketTimer;          // Timer to handle the application data transmission duty cycle


static bool SendFrame(void)
{
    McpsReq_t mcpsReq;
    LoRaMacTxInfo_t txInfo;

    if (LoRaMacQueryTxPossible(APP_DATA_SIZE, &txInfo) != LORAMAC_STATUS_OK)
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
            mcpsReq.Req.Confirmed.fPort = APP_PORT;
            mcpsReq.Req.Confirmed.fBuffer = AppData;
            mcpsReq.Req.Confirmed.fBufferSize = APP_DATA_SIZE;
            mcpsReq.Req.Confirmed.NbTrials = 8;
            mcpsReq.Req.Confirmed.Datarate = APP_DEFAULT_DATARATE;
        }
        else
        {
            // Send an unconfirmed packet
            mcpsReq.Type = MCPS_UNCONFIRMED;
            mcpsReq.Req.Unconfirmed.fPort = APP_PORT;
            mcpsReq.Req.Unconfirmed.fBuffer = AppData;
            mcpsReq.Req.Unconfirmed.fBufferSize = APP_DATA_SIZE;
            mcpsReq.Req.Unconfirmed.Datarate = APP_DEFAULT_DATARATE;
        }
    }

    if (LoRaMacMcpsRequest(&mcpsReq) == LORAMAC_STATUS_OK)
        return false;

    return true;
}

static void OnEncryptNextPacketTimerEvent(void)
{
    TimerStop(&EncryptNextPacketTimer);
    DeviceState = DEVICE_STATE_ENCRYPT;
}


int main_aes( void )
{
    LoRaMacPrimitives_t LoRaMacPrimitives;
    LoRaMacCallback_t LoRaMacCallbacks;
    MibRequestConfirm_t mibReq;

    BoardInitMcu();
    BoardInitPeriph();

    srand(time(NULL));   // should only be called once


    DeviceState = DEVICE_STATE_INIT;
    while (true)
    {
        switch (DeviceState)
        {
            case DEVICE_STATE_INIT:
            {
                LoRaMacPrimitives.MacMcpsConfirm = NULL;
                LoRaMacPrimitives.MacMcpsIndication = NULL;
                LoRaMacPrimitives.MacMlmeConfirm = NULL;
                LoRaMacInitialization(&LoRaMacPrimitives, &LoRaMacCallbacks);

                TimerInit(&EncryptNextPacketTimer, OnEncryptNextPacketTimerEvent);

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

                DeviceState = DEVICE_STATE_ENCRYPT;
                break;
            }
            case DEVICE_STATE_ENCRYPT:
            {
            	TimerSetValue(&EncryptNextPacketTimer, APP_ENCRYPT_DUTYCYCLE);
            	TimerStart(&EncryptNextPacketTimer);
            	GpioToggle(&Led1);
            	SendFrame();

                DeviceState = DEVICE_STATE_SLEEP;
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

