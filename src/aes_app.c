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
 *         File: aes_app.c
 *      Created: 2017-09-21
 *       Author: Geoffrey Ottoy
 *
 *  Description: This example application shows how using hardware acceleration,
 *  	saves energy. By off-loading the AES encryption to the EFM32 AES core,
 *  	the encryption is performed faster than when it is done in software. This
 *  	will allow the processor to go to sleep faster (saving energy every time).
 *
 *  	This application will periodically encrypt a buffer of 128 bytes (and
 *  	compute the MIC). Using the global symbol USE_AES_HW (project settings),
 *  	one can enable hardware encryption.
 *
 *  	Observations you should be able to make (in energy monitor):
 *  	 - AES in software:
 *  	 	 duration:  ~ 35 ms
 *  	 	   energy: ~ 445 µJ
 *  	 	code size: 	~ 42 kB
 *  	 - AES in hardware:
 *  	 	 duration:   ~ 7 ms
 *  	 	   energy:  ~ 91 µJ
 *  	 	code size: 	~ 40 kB
 *
*  	 	Try reducing the number of readings. What can you conclude?
 */

#if defined(APP_TYPE) && (APP_TYPE == AES_APP)

#include <string.h>
#include <math.h>

#include <Comissioning_mydev.h>
#include "board.h"
#include "omux-board.h"

#include "LoRaMac.h"
#include "LoRaMacCrypto.h"

#include <time.h>
#include <stdlib.h>

#define APP_ENCRYPT_DUTYCYCLE   100		// Milliseconds between two encryptions

#define APP_PORT                1		// Application port
#define NR_TEMP_READINGS        64		// Size of user data buffer
#define PHY_MAX_PAYLOAD_SIZE	255

#if defined(USE_AES_HW)
#if (USE_AES_HW == 1)
#pragma message("Running AES in hardware.")
#else
#pragma message("Running AES in software.")
#endif
#endif

typedef enum DeviceState
{
    DEVICE_STATE_INIT,
	DEVICE_STATE_ENCRYPT,
    DEVICE_STATE_SLEEP
} DeviceState_t;

static TimerEvent_t EncryptNextPacketTimer;          // Timer to handle the application data transmission duty cycle

DeviceState_t devState;

static void OnEncryptNextPacketTimerEvent(void)
{
    TimerStop(&EncryptNextPacketTimer);
    devState = DEVICE_STATE_ENCRYPT;
}

int main_aes( void )
{
    BoardInitMcu();
    BoardInitPeriph();

    srand(time(NULL));   // should only be called once

    uint8_t payload[NR_TEMP_READINGS*2];
    uint8_t LoRaMacBuffer[NR_TEMP_READINGS*2];
    uint16_t LoRaMacTxPayloadLen = NR_TEMP_READINGS*2;
    uint8_t LoRaMacAppSKey[] = LORAWAN_APPSKEY;
    uint8_t LoRaMacNwkSKey[] = LORAWAN_NWKSKEY;
    uint32_t LoRaMacDevAddr = LORAWAN_DEVICE_ADDRESS;
    uint32_t UpLinkCounter = 0;
    uint8_t LoRaMacPayload[PHY_MAX_PAYLOAD_SIZE];
    uint32_t mic;

    devState = DEVICE_STATE_INIT;
    while (true)
    {
        switch (devState)
        {
            case DEVICE_STATE_INIT:
            {
                TimerInit(&EncryptNextPacketTimer, OnEncryptNextPacketTimerEvent);

                // Fill the payload with 64 temperature readings (all 21.000 °C)
                uint8_t i;
                for(i=0; i<NR_TEMP_READINGS; i++){
                	*(payload+i*2) = 0x52;
                	*(payload+1+i*2) = 0x08;
                }

                devState = DEVICE_STATE_ENCRYPT;
                break;
            }
            case DEVICE_STATE_ENCRYPT:
            {
            	TimerSetValue(&EncryptNextPacketTimer, APP_ENCRYPT_DUTYCYCLE);
            	TimerStart(&EncryptNextPacketTimer);
            	//GpioToggle(&Led1);

            	// Example: we want to send 64 temperature readings (uplink)
            	// payload = 128 bytes
            	// First, the MAC layer will encrypt the payload
            	LoRaMacPayloadEncrypt( (uint8_t* ) payload, LoRaMacTxPayloadLen, LoRaMacAppSKey, LoRaMacDevAddr, UP_LINK, UpLinkCounter, LoRaMacPayload );
            	// Then it will compute message integrity code (MIC)
            	LoRaMacComputeMic( LoRaMacBuffer, LoRaMacTxPayloadLen+10, LoRaMacNwkSKey, LoRaMacDevAddr, UP_LINK, UpLinkCounter, &mic );
            	UpLinkCounter++;

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
	OMuxToggleLed(&I2c);
}

#endif /* AES_APP */
