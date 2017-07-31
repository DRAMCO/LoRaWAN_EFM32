/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: Bleeper board SPI driver implementation

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
#include "board.h"
#include "spi-board.h"
#include "em_cmu.h"
#include "em_gpio.h"

#define USART_USED          USART0
#define USART_LOCATION      USART_ROUTE_LOCATION_DEFAULT
#define USART_CLK           cmuClock_USART0

typedef enum
{
  RESET = 0,
  SET = !RESET
} FlagStatus;

void SpiInit( Spi_t *obj, PinNames mosi, PinNames miso, PinNames sclk, PinNames nss )
{
	BoardDisableIrq( );

	USART_InitSync_TypeDef init = USART_INITSYNC_DEFAULT;
	obj->Spi.Init = init;
	obj->Spi.Instance = (void*)USART0_BASE;

    // Enable module clocks
	CMU_ClockEnable(cmuClock_HFPER, true);
	CMU_ClockEnable(USART_CLK, true);
	CMU_ClockEnable(cmuClock_GPIO, true);

    GpioInit( &obj->Mosi, mosi, PIN_ALTERNATE_FCT, PIN_PUSH_PULL, PIN_PULL_DOWN, 0 );
    GpioInit( &obj->Miso, miso, PIN_ALTERNATE_FCT, PIN_PUSH_PULL, PIN_PULL_DOWN, 0 );
    GpioInit( &obj->Sclk, sclk, PIN_ALTERNATE_FCT, PIN_PUSH_PULL, PIN_PULL_DOWN, 0 );
    GpioInit( &obj->Nss, nss, PIN_ALTERNATE_FCT, PIN_PUSH_PULL, PIN_PULL_UP, 1 );

    // Reset USART just in case
	USART_Reset(USART_USED);

    SpiFormat( obj, USART_FRAME_DATABITS_EIGHT, usartClockMode0, 0, 0);
    SpiFrequency( obj, 1000000 );

    USART_InitSync(USART_USED, &obj->Spi.Init);

    USART_USED->ROUTE = USART_ROUTE_TXPEN | USART_ROUTE_RXPEN | USART_ROUTE_CLKPEN | USART_LOCATION;

    BoardEnableIrq( );
}

void SpiDeInit( Spi_t *obj )
{
	assert_param( FAIL );
}

void SpiFormat( Spi_t *obj, int8_t bits, int8_t cpol, int8_t cpha, int8_t slave )
{
	(void)cpha; // Falling vs rising edge is already part of cpol

    obj->Spi.Init.databits = bits;

    obj->Spi.Init.clockMode = cpol;
    obj->Spi.Init.msbf = true;
    obj->Spi.Init.refFreq = 0;

    obj->Spi.Init.master = !slave;
}

void SpiFrequency( Spi_t *obj, uint32_t hz )
{
	obj->Spi.Init.baudrate = hz;
}

FlagStatus SpiGetFlag( Spi_t *obj, uint16_t flag )
{
	assert_param( FAIL );
	return 0; // never reached
}

uint16_t SpiInOut( Spi_t *obj, uint16_t outData )
{
	uint8_t data;
	data = USART_SpiTransfer(USART_USED, outData);
	return (uint16_t)data;

	// For every byte sent, one is received
	USART_Tx(USART_USED, outData);
	return USART_Rx(USART_USED);
}

