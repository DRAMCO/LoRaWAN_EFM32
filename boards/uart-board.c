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
#include "uart-board.h"
#include "em_cmu.h"
#include "em_leuart.h"

/** LEUART Rx/Tx Port/Pin Location */
#define LEUART_LOCATION    0
#define LEUART_TXPORT      gpioPortD        /* LEUART transmission port */
#define LEUART_TXPIN       4                /* LEUART transmission pin  */
#define LEUART_RXPORT      gpioPortD        /* LEUART reception port    */
#define LEUART_RXPIN       5                /* LEUART reception pin     */

uint8_t RxData = 0;

void UartMcuInit( Uart_t *obj, uint8_t uartId, PinNames tx, PinNames rx )
{
    obj->UartId = uartId;

    GpioInit(&obj->Tx, tx, PIN_OUTPUT, PIN_PUSH_PULL, PIN_PULL_UP, 0);
    GpioInit(&obj->Rx, rx, PIN_INPUT, PIN_PUSH_PULL, PIN_PULL_UP, 0);
}

void UartMcuConfig( Uart_t *obj, UartMode_t mode, uint32_t baudrate, WordLength_t wordLength, StopBits_t stopBits, Parity_t parity, FlowCtrl_t flowCtrl )
{
	CMU_ClockEnable(cmuClock_LEUART0, true);

	int dataBitsValue;
	if (wordLength == UART_9_BIT)
		dataBitsValue = usartDatabits9;
	else
		dataBitsValue = usartDatabits8;

	int stopBitsValue;
	if (stopBits == UART_2_STOP_BIT)
		stopBitsValue = usartStopbits2;
	else if (stopBits == UART_1_5_STOP_BIT)
		stopBitsValue = usartStopbits1p5;
	else if (stopBits == UART_0_5_STOP_BIT)
		stopBitsValue = usartStopbits0p5;
	else
		stopBitsValue = usartStopbits1;

	int parityValue;
	if (parity == EVEN_PARITY)
		parityValue = usartEvenParity;
	else if (parity == ODD_PARITY)
		parityValue = usartOddParity;
	else
		parityValue = usartNoParity;

	int enableValue;
	if (mode == TX_ONLY)
		enableValue = usartEnableTx;
	else if (mode == RX_ONLY)
		enableValue = usartEnableRx;
	else
		enableValue = usartEnable;

	LEUART_Init_TypeDef uartInit = {
	    .enable       = leuartDisable,   // wait to enable the transceiver
	    .refFreq      = 0,              // setting refFreq to 0 will invoke the CMU_ClockFreqGet() function and measure the HFPER clock
	    .baudrate     = baudrate,       // desired baud rate
	    .databits     = dataBitsValue,
	    .parity       = parityValue,
	    .stopbits     = stopBitsValue,
	};

	LEUART_Init(LEUART0, &uartInit);

	// clear RX/TX buffers and shift regs, enable transmitter and receiver pins
	LEUART0->ROUTE = LEUART_ROUTE_RXPEN | LEUART_ROUTE_TXPEN | LEUART_LOCATION;

	// Enable interrupts
	USART_IntClear(LEUART0, _LEUART_IF_MASK);
	USART_IntEnable(LEUART0, LEUART_IF_RXDATAV);
	NVIC_ClearPendingIRQ(LEUART0_IRQn);
	//NVIC_ClearPendingIRQ(LEUART0_RX_IRQn);
	NVIC_EnableIRQ(LEUART0_IRQn);

	LEUART_Enable(LEUART0, enableValue);
}

void UartMcuDeInit( Uart_t *obj )
{
	LEUART0->ROUTE = _LEUART_ROUTE_RESETVALUE;

	USART_Enable(LEUART0, usartDisable);
	CMU_ClockEnable(cmuClock_LEUART0, false);
}

uint8_t UartMcuPutChar( Uart_t *obj, uint8_t data )
{
	// Wait until we can send the next byte
	while ((LEUART0->STATUS & LEUART_STATUS_TXBL) == 0)
		;

	LEUART0->TXDATA = (uint32_t)data;
	return 0; // OK
}

uint8_t UartMcuGetChar( Uart_t *obj, uint8_t *data )
{
	if (LEUART0->STATUS & LEUART_STATUS_RXDATAV)
	{
		*data = (uint8_t)LEUART0->RXDATA;
		return 0;
	}
	else
		return 1;
}

void UART0_RX_IRQHandler(void)
{
	if (LEUART0->STATUS & LEUART_STATUS_RXDATAV)
	{
		Uart1.IrqNotify(UART_NOTIFY_RX);
		USART_IntClear(LEUART0, LEUART_IF_RXDATAV);
	}
}
/*
void UART0_TX_IRQHandler(void)
{
	if (UART0->STATUS & UART_STATUS_TXBL)
	{
		Uart1.IrqNotify(UART_NOTIFY_TX);
		USART_IntClear(UART0, UART_IF_TXBL);
	}
}
*/
