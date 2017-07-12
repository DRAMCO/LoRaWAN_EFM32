/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: Bleeper board I2C driver implementation

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
#include "board.h"
#include "i2c-board.h"

/*!
 *  The value of the maximal timeout for I2C waiting loops
 */
#define TIMEOUT_MAX                                 0x8000

I2cAddrSize I2cInternalAddrSize = I2C_ADDR_SIZE_8;

/*!
 * MCU I2C peripherals enumeration
 */
/*
typedef enum {
    I2C_1 = ( uint32_t )I2C1_BASE,
    I2C_2 = ( uint32_t )I2C2_BASE,
} I2cName;
*/

void I2cMcuInit( I2c_t *obj, PinNames scl, PinNames sda )
{
	assert_param(FAIL);
}

void I2cMcuFormat( I2c_t *obj, I2cMode mode, I2cDutyCycle dutyCycle, bool I2cAckEnable, I2cAckAddrMode AckAddrMode, uint32_t I2cFrequency )
{
	assert_param(FAIL);
}

void I2cMcuDeInit( I2c_t *obj )
{
	assert_param(FAIL);
}

void I2cSetAddrSize( I2c_t *obj, I2cAddrSize addrSize )
{
    I2cInternalAddrSize = addrSize;
}

uint8_t I2cMcuWriteBuffer( I2c_t *obj, uint8_t deviceAddr, uint16_t addr, uint8_t *buffer, uint16_t size )
{
	assert_param(FAIL);
	return FAIL;
}

uint8_t I2cMcuReadBuffer( I2c_t *obj, uint8_t deviceAddr, uint16_t addr, uint8_t *buffer, uint16_t size )
{
	assert_param(FAIL);
	return FAIL;
}

uint8_t I2cMcuWaitStandbyState( I2c_t *obj, uint8_t deviceAddr )
{
	assert_param(FAIL);
	return FAIL;
}
