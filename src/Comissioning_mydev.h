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
 * IEEE Organizationally Unique Identifier ( OUI ) (big endian)
 */
//#define IEEE_OUI                                    0x00, 0x00, 0x00

/*!
 * 64 bit end-device identifier, EUI-64 (unique)
 * The EUIs are used to identify all of the (virtual) parts of the LoRaWAN inside the backend server.
 *
 */
#define LORAWAN_DEVICE_EUI                          { 0x00, 0xE6, 0xB1, 0x39, 0xE9, 0xD3, 0x4E, 0x30 }

/*!
 * 64 bit eapplication identifier, EUI-64 (unique)
 */
#define LORAWAN_APPLICATION_EUI                     { 0x70, 0xB3, 0xD5, 0x7E, 0xF0, 0x00, 0x63, 0x66 }

/*!
 * AES encryption/decryption cipher application key
 */
#define LORAWAN_APPLICATION_KEY                     { 0xC7, 0x83, 0xFE, 0x54, 0xD4, 0x25, 0x0D, 0xCF, 0xF3, 0xEC, 0x02, 0x52, 0xF1, 0x6D, 0xED, 0x4B }
/*!
 * Current network ID
 */
#define LORAWAN_NETWORK_ID                          ( uint32_t )0x13

/*!
 * Device address on the network (big endian)
 * This device address is a non-unique 32-bit adres
 * If OTA is enabled this device will receive DevAddr from the network
 * When APB is selected, this value is hard-coded
 */
#define LORAWAN_DEVICE_ADDRESS                      ( uint32_t )0x26011E47

/*!
 * AES encryption/decryption cipher network session key
 * he NwkSKey is known by the network and the device and is used to validate the integrity of each message by its Message Integrity Code (MIC) (AES-CMAC)
 */
#define LORAWAN_NWKSKEY                             { 0xD8, 0x4B, 0x2B, 0x20, 0x84, 0x07, 0x60, 0x69, 0xCD, 0x88, 0x5E, 0xFF, 0x5E, 0xBD, 0x7A, 0x02 }
/*!
 * AES encryption/decryption cipher application session key
 * The AppSKey is used for end-to-end encryption of the frame payload.  (AES-128)
 */
#define LORAWAN_APPSKEY                             { 0xB7, 0xF8, 0x93, 0x10, 0xEE, 0x55, 0x29, 0xE3, 0x63, 0x37, 0x8D, 0xCD, 0x88, 0x32, 0x7B, 0x39 }

#endif // __LORA_COMMISSIONING_H__
