/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: Bleeper board UART driver implementation

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
#include "board.h"
/*
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"
#include "uart-usb-board.h"
*/
/* USB handler declaration */
/* Handle for USB Full Speed IP */
//USBD_HandleTypeDef  *hUsbDevice_0;
/*
USBD_HandleTypeDef hUsbDeviceFS;
extern PCD_HandleTypeDef hpcd_USB_FS;
*/
void UartUsbInit( Uart_t *obj, uint8_t uartId, PinNames tx, PinNames rx )
{
	assert_param(FAIL);
}

void UartUsbConfig( Uart_t *obj, UartMode_t mode, uint32_t baudrate, WordLength_t wordLength, StopBits_t stopBits, Parity_t parity, FlowCtrl_t flowCtrl )
{

}

void UartUsbDeInit( Uart_t *obj )
{

}

uint8_t UartUsbIsUsbCableConnected( void )
{
	assert_param(FAIL);
    return 0;
}

uint8_t UartUsbPutBuffer( Uart_t *obj, uint8_t *buffer, uint16_t size )
{
	assert_param(FAIL);
    return FAIL;
}

uint8_t UartUsbPutChar( Uart_t *obj, uint8_t data )
{
	assert_param(FAIL);
	return FAIL;
}

uint8_t UartUsbGetChar( Uart_t *obj, uint8_t *data )
{
	assert_param(FAIL);
	return FAIL;
}

void USB_LP_IRQHandler( void )
{
	assert_param(FAIL);
}
