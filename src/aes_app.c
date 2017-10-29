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
 *		 - AES in software:
 *			*  duration:  	~ 37 ms
 *			*    energy: 	~ 285 µJ
 *			* code size: 	~ 42 kB
 *		 - AES in hardware:
 *			*  duration:   	~ 7 ms
 *			*    energy:  	~ 60 µJ
 *			* code size: 	~ 40 kB
 *
*  	 	Try reducing the number of readings. What can you conclude?
 */

#if defined(APP_TYPE) && (APP_TYPE == AES_APP)

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
#include "LoRaMacCrypto.h"


#define APP_ENCRYPT_DUTYCYCLE   100		// Milliseconds between two encryptions

#define APP_PORT                1		// Application port
#define NR_TEMP_READINGS        64		// Size of user data buffer max = PHY_MAX_PAYLOAD_SIZE/2
#define PHY_MAX_PAYLOAD_SIZE	255

#ifndef LORAWAN_DEVICE_ADDRESS
#define LORAWAN_DEVICE_ADDRESS                      ( uint32_t )0xB105F00D
#endif
#ifndef LORAWAN_NWKSKEY
#define LORAWAN_NWKSKEY                             { 0x44, 0x52, 0x41, 0x4d, 0x43, 0x4f, 0x69, 0x73, 0x74, 0x68, 0x65, 0x62, 0x65, 0x73, 0x74, 0x21 }
#endif
#ifndef LORAWAN_APPSKEY
#define LORAWAN_APPSKEY                             { 0x2d, 0x47, 0x65, 0x6f, 0x66, 0x66, 0x72, 0x65, 0x79, 0x20, 0x4f, 0x74, 0x74, 0x6f, 0x79, 0x2d }
#endif

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
    //GpioWrite(&Led0, 0);
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
	OMuxToggleLed();
}

#endif /* AES_APP */
