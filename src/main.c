#include <string.h>
#include <math.h>

#include "Comissioning.h"
#include "board.h"

#include "LoRaMac.h"

#define APP_TX_DUTYCYCLE                    15000   // Milliseconds between two transmissions
#define APP_TX_DUTYCYCLE_RND                1000    // Random delay for application data transmission duty cycle [ms]
#define APP_DEFAULT_DATARATE                DR_5    // SF7 - BW125
#define APP_PORT                            2       // Application port
#define APP_DATA_SIZE                       16      // Size of packets to transmit in this example
#define APP_DATA_MAX_SIZE                   64      // Size of user data buffer
#define APP_ADR_ON                          1       // Whether we use Adaptive Data Rate or not
#define APP_CONFIRMED_MSG_ON                1       // Whether this example will transmit confirmed or unconfirmed packets

#if (OVER_THE_AIR_ACTIVATION == 0)
    static uint8_t  NwkSKey[] = LORAWAN_NWKSKEY;
    static uint8_t  AppSKey[] = LORAWAN_APPSKEY;
    static uint32_t DevAddr   = LORAWAN_DEVICE_ADDRESS;
#else
    static uint8_t DevEui[] = LORAWAN_DEVICE_EUI;
    static uint8_t AppEui[] = LORAWAN_APPLICATION_EUI;
    static uint8_t AppKey[] = LORAWAN_APPLICATION_KEY;
#endif


static enum eDevicState
{
    DEVICE_STATE_INIT,
    DEVICE_STATE_JOIN,
    DEVICE_STATE_SEND,
    DEVICE_STATE_SLEEP
} DeviceState;

static uint8_t      AppData[APP_DATA_MAX_SIZE]; // User application data
static uint32_t     TxDutyCycleTime;            // Defines the application data transmission duty cycle
static TimerEvent_t TxNextPacketTimer;          // Timer to handle the application data transmission duty cycle
static bool         NextTx = true;              // Indicates if a new packet can be sent

static void PrepareTxFrame(uint8_t port)
{
    for (unsigned int i = 0; i < APP_DATA_SIZE; ++i)
        AppData[i] = i;
}

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
            DeviceState = DEVICE_STATE_SEND;
            NextTx = true;
        }
        else // We need to join before we can send data
            DeviceState = DEVICE_STATE_JOIN;
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
            DeviceState = DEVICE_STATE_SEND;
    }

    NextTx = true;
}

//static void MlmeIndication(MlmeIndication_t *mlmeIndication)
//{
//}

int main( void )
{
    LoRaMacPrimitives_t LoRaMacPrimitives;
    LoRaMacCallback_t LoRaMacCallbacks;
    MibRequestConfirm_t mibReq;

    BoardInitMcu();
    BoardInitPeriph();

    DeviceState = DEVICE_STATE_INIT;
    while (true)
    {
        switch (DeviceState)
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

                DeviceState = DEVICE_STATE_JOIN;
                break;
            }
            case DEVICE_STATE_JOIN:
            {
#if (OVER_THE_AIR_ACTIVATION != 0)
                MlmeReq_t mlmeReq;

                // Initialize LoRaMac device unique ID
                //BoardGetUniqueId(DevEui);

                mlmeReq.Type = MLME_JOIN;
                mlmeReq.Req.Join.DevEui = DevEui;
                mlmeReq.Req.Join.AppEui = AppEui;
                mlmeReq.Req.Join.AppKey = AppKey;

                if (NextTx == true)
                    LoRaMacMlmeRequest(&mlmeReq);

                DeviceState = DEVICE_STATE_SLEEP;
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

                DeviceState = DEVICE_STATE_SEND;
#endif
                break;
            }
            case DEVICE_STATE_SEND:
            {
                if (NextTx)
                {
                    PrepareTxFrame(APP_PORT);
                    GpioWrite(&Led1, 1);
                    NextTx = SendFrame();
                    GpioWrite(&Led1, 0);
                }

                // Schedule next packet transmission
                TxDutyCycleTime = APP_TX_DUTYCYCLE + randr(-APP_TX_DUTYCYCLE_RND, APP_TX_DUTYCYCLE_RND);
                TimerSetValue(&TxNextPacketTimer, TxDutyCycleTime);
                TimerStart(&TxNextPacketTimer);

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

// This function is called when PB0 is pressed
void Button_0_ISR(void){
	GpioToggle(&Led0);
}

// This function is called when PB1 is pressed
void Button_1_ISR(void){
	//
}
