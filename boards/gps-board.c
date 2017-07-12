/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: Generic low level driver for GPS receiver

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
#include "board.h"

/*!
 * FIFO buffers size
 */
//#define FIFO_TX_SIZE                                128
#define FIFO_RX_SIZE                                128

//uint8_t TxBuffer[FIFO_TX_SIZE];
uint8_t RxBuffer[FIFO_RX_SIZE];

/*!
 * \brief Buffer holding the  raw data received from the gps
 */
uint8_t NmeaString[128];

/*!
 * \brief Maximum number of data byte that we will accept from the GPS
 */
uint8_t NmeaStringSize = 0;


PpsTrigger_t PpsTrigger;


void GpsMcuOnPpsSignal( void )
{
	assert_param(FAIL);
}

void GpsMcuInvertPpsTrigger( void )
{
	assert_param(FAIL);
}

uint8_t GpsMcuGetPpsTrigger( void )
{
    return( PpsTrigger );
}

void GpsMcuInit( void )
{
	assert_param(FAIL);
}

void GpsMcuStart( void )
{
	assert_param(FAIL);
}

void GpsMcuStop( void )
{
	assert_param(FAIL);
}

void GpsMcuProcess( void )
{

}

void GpsMcuIrqNotify( UartNotifyId_t id )
{
	assert_param( FAIL );
}
