/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2015 Semtech

Description: End device commissioning parameters

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
#ifndef __LORA_COMMISSIONING_H__
#define __LORA_COMMISSIONING_H__

/*!
 * When set to 1 the application uses the Over-the-Air activation procedure
 * When set to 0 the application uses the Personalization activation procedure
 */
#define OVER_THE_AIR_ACTIVATION                     1

/*!
 * Indicates if the end-device is to be connected to a private or public network
 */
#define LORAWAN_PUBLIC_NETWORK                      true

/*!
 * 64 bit end-device identifier, EUI-64 (unique)
 * The EUIs are used to identify all of the (virtual) parts of the LoRaWAN inside the backend server.
 * 
 */
#define LORAWAN_DEVICE_EUI                          { 0x00, 0x76, 0xFB, 0xB5, 0x1B, 0x91, 0xA7, 0x92 }
/*!
 * 64 bit eapplication identifier, EUI-64 (unique)
 */
#define LORAWAN_APPLICATION_EUI                     { 0x70, 0xB3, 0xD5, 0x7E, 0xF0, 0x00, 0x63, 0x66 }


#if OVER_THE_AIR_ACTIVATION == 0
/*!
 * Device address on the network (big endian)
 * This device address is a non-unique 32-bit adres
 * If OTA is enabled this device will receive DevAddr from the network
 * When APB is selected, this value is hard-coded
 */
#define LORAWAN_DEVICE_ADDRESS                      ( uint32_t )0x2601195F

/*!
 * Network Session Key
 * AES encryption/decryption cipher network session key
 * he NwkSKey is known by the network and the device and is used to validate the integrity of each message by its Message Integrity Code (MIC) (AES-CMAC)
 */
#define LORAWAN_NWKSKEY                             { 0x75, 0x44, 0x5D, 0xCB, 0x6B, 0xD8, 0xA1, 0xD4, 0xC5, 0x25, 0x72, 0xC1, 0x46, 0xC4, 0x73, 0x3C }
/*!
 * Application Session Key
 * AES encryption/decryption cipher application session key
 * The AppSKey is used for end-to-end encryption of the frame payload.  (AES-128)
 */
#define LORAWAN_APPSKEY                             { 0xA3, 0xC7, 0x8F, 0x27, 0x2A, 0x26, 0xF3, 0x9D, 0xD2, 0x59, 0x5D, 0x3A, 0x1F, 0x6D, 0xFE, 0x25 }

#endif

/*!
 * AES encryption/decryption cipher application key
 */
#define LORAWAN_APPLICATION_KEY                     { 0x19, 0x54, 0x4D, 0xB9, 0x89, 0x33, 0x75, 0xC0, 0xCB, 0x4C, 0x1E, 0xEE, 0xB6, 0xAA, 0x76, 0x65 }
/*!
 * Current network ID
 */
#define LORAWAN_NETWORK_ID                          ( uint32_t )0x13

#endif // __LORA_COMMISSIONING_H__
