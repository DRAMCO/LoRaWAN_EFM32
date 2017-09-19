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
#include "i2cspm.h"

/*!
 *  The value of the maximal timeout for I2C waiting loops
 */
#define TIMEOUT_MAX                                 0x8000

I2cAddrSize I2cInternalAddrSize = I2C_ADDR_SIZE_8;
I2CSPM_Init_TypeDef i2cInit = I2CSPM_INIT_DEFAULT;

void I2cMcuInit( I2c_t *obj, PinNames scl, PinNames sda )
{
	// EFM32-specific simple poll-based I2C master init
	I2CSPM_Init(&i2cInit);

	// Link to stack
	obj->I2c.Instance = i2cInit.port;
}

void I2cMcuFormat( I2c_t *obj, I2cMode mode, I2cDutyCycle dutyCycle, bool I2cAckEnable, I2cAckAddrMode AckAddrMode, uint32_t I2cFrequency )
{
	//assert_param(FAIL);
	return;
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
	I2C_TransferSeq_TypeDef    seq;
	I2C_TransferReturn_TypeDef ret;

	seq.addr  = deviceAddr<<1;
	seq.flags = I2C_FLAG_WRITE;
	seq.buf[0].data   = buffer;
	seq.buf[0].len    = size;

	ret = I2CSPM_Transfer(obj->I2c.Instance, &seq);
	if (ret != i2cTransferDone){
		return FAIL;
	}

	return SUCCESS;
}

uint8_t I2cMcuReadBuffer( I2c_t *obj, uint8_t deviceAddr, uint16_t regAddr, uint8_t *buffer, uint16_t size )
{
	I2C_TransferSeq_TypeDef    seq;
	I2C_TransferReturn_TypeDef ret;
	uint8_t                    i2c_write_data[1];

	seq.addr  = deviceAddr;
	seq.flags = I2C_FLAG_WRITE_READ;
	/* Select command to issue */
	i2c_write_data[0] = (uint8_t) regAddr;
	seq.buf[0].data   = i2c_write_data;
	seq.buf[0].len    = 1;
	/* Select location/length of data to be read */
	seq.buf[1].data = buffer;
	seq.buf[1].len  = size;

	ret = I2CSPM_Transfer(obj->I2c.Instance, &seq);

	if (ret != i2cTransferDone)
	{
		*buffer = 0;
		return FAIL;
	}

	return SUCCESS;
}

uint8_t I2cMcuWaitStandbyState( I2c_t *obj, uint8_t deviceAddr )
{
	assert_param(FAIL);
	return FAIL;
}
