/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: Timer objects and scheduling management

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian

Modified by: Geoffrey Ottoy - KU Leuven for use with external M24C02 EEPROM
by ST Micro-electronics on the LoRA extension board.
*/
#include "board.h"

#include "i2c.h"
#include "eeprom-board.h"

#define DEVICE_I2C_ADDRESS		0x50
#define EEPROM_SIZE				256 // bytes
#define EEPROM_PAGE_SIZE		16 // bytes

static uint8_t I2cDeviceAddr = DEVICE_I2C_ADDRESS;

/* Write a byte buffer to the specified address in EEPROM memory.
 */
uint8_t EepromMcuWriteBuffer( uint16_t addr, uint8_t *buffer, uint16_t size )
{
#ifdef HW_VERSION_3 /* Please note that EEPROM memory will only work on v3.2.
					   Lower versions (v3.0 & v3.1) require hardware rewiring*/
	uint8_t wBuf[size+1];
	uint8_t i;

	if((size > EEPROM_PAGE_SIZE) || ((addr + EEPROM_PAGE_SIZE) > EEPROM_SIZE)){
		return FAIL;
	}

	for(i=0; i<size; i++){
		wBuf[i+1] = buffer[i];
	}
	wBuf[0] = (uint8_t) addr;

	return I2cWriteBuffer( &I2c, I2cDeviceAddr, 0, wBuf, size+1 );
#else
	return FAIL;
#endif
}

/* Read a byte buffer from the specified address in EEPROM memory.
 */
uint8_t EepromMcuReadBuffer( uint16_t addr, uint8_t *buffer, uint16_t size ){
#ifdef HW_VERSION_3 /* Please note that EEPROM memory will only work on v3.2.
					   Lower versions (v3.0 & v3.1) require hardware rewiring*/
	if((size > EEPROM_PAGE_SIZE) || ((addr + EEPROM_PAGE_SIZE) > EEPROM_SIZE)){
		return FAIL;
	}

	return I2cReadBuffer( &I2c, I2cDeviceAddr<<1, addr, buffer, size );
#else
	return FAIL;
#endif
}

/* Set the EEPROM I2C address (not supported, because fixed in hardware).
 */
void EepromMcuSetDeviceAddr( uint8_t addr )
{
    //I2cDeviceAddr = addr; (not supported)
}

/* Returns the EEPROM I2C device address.
 */
uint8_t EepromMcuGetDeviceAddr( void )
{
    return I2cDeviceAddr;
}
