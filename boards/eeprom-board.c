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
*/
#include "board.h"

#include "i2c-board.h"
#include "eeprom-board.h"

//#define DEVICE_I2C_ADDRESS                          0xA8

static uint8_t I2cDeviceAddr;// = DEVICE_I2C_ADDRESS;

uint8_t EepromMcuWriteBuffer( uint16_t addr, uint8_t *buffer, uint16_t size )
{
	assert_param(FAIL);
    return FAIL;
}

uint8_t EepromMcuReadBuffer( uint16_t addr, uint8_t *buffer, uint16_t size )
{
	assert_param(FAIL);
	return FAIL;
}

void EepromMcuSetDeviceAddr( uint8_t addr )
{
    I2cDeviceAddr = addr;
}

uint8_t EepromMcuGetDeviceAddr( void )
{
    return I2cDeviceAddr;
}
