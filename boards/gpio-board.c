/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: Bleeper board GPIO driver implementation

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
#include "board.h"
#include "gpio-board.h"
#include "em_gpio.h"
#include "em_cmu.h"

#define PIN_DIO_0		0
#define PIN_DIO_1   	7
#define PIN_DIO_2   	1
#define PIN_DIO_3   	6
#define PIN_DIO_4   	5

#define PIN_BUTTON_0   	9
#define PIN_BUTTON_1   	10

#define PIN_LIGHT_SENSE	2 // Future use

static GpioIrqHandler *GpioIrq[16];

void GpioMcuInit( Gpio_t *obj, PinNames pin, PinModes mode, PinConfigs config, PinTypes type, uint32_t value )
{
    if( pin == NC )
    {
        return;
    }
    obj->pin = pin;
    obj->pinIndex = (0x01 << (obj->pin & 0x0F));
    obj->portIndex = ((obj->pin >> 4) & 0x0F);

    // We don't use the port variable on this board
    obj->port = NULL;

    if (mode == PIN_INPUT)
        GPIO_PinModeSet(obj->portIndex, obj->pin & 0x0F, gpioModeInput, value);
    else
        GPIO_PinModeSet(obj->portIndex, obj->pin & 0x0F, gpioModePushPull, value);

    // Sets initial output value
    if( mode == PIN_OUTPUT )
        GpioMcuWrite( obj, value );
}

void GpioMcuSetInterrupt( Gpio_t *obj, IrqModes irqMode, IrqPriorities irqPriority, GpioIrqHandler *irqHandler )
{
	if (irqHandler == NULL)
		return;

	bool risingEdge = false;
	bool fallingEdge = false;
	switch( irqMode )
	{
		case NO_IRQ:
			break;
		case IRQ_RISING_EDGE:
			risingEdge = true;
			break;
		case IRQ_FALLING_EDGE:
			fallingEdge = true;
			break;
		case IRQ_RISING_FALLING_EDGE:
			risingEdge = true;
			fallingEdge = true;
			break;
	}

	uint32_t priority = 0;
	switch( irqPriority )
	{
	case IRQ_VERY_LOW_PRIORITY:
	case IRQ_LOW_PRIORITY:
		priority = 3;
		break;
	case IRQ_MEDIUM_PRIORITY:
		priority = 2;
		break;
	case IRQ_HIGH_PRIORITY:
		priority = 1;
		break;
	case IRQ_VERY_HIGH_PRIORITY:
	default:
		priority = 0;
		break;
	}

	GPIO_IntConfig(obj->portIndex, obj->pin & 0x0F, risingEdge, fallingEdge, true);

	NVIC_SetPriority(GPIO_ODD_IRQn , priority);
	NVIC_SetPriority(GPIO_EVEN_IRQn , priority);

	NVIC_EnableIRQ(GPIO_ODD_IRQn);
	NVIC_EnableIRQ(GPIO_EVEN_IRQn);

	GpioIrq[(obj->pin) & 0x0F] = irqHandler;
}

void GpioMcuRemoveInterrupt( Gpio_t *obj )
{
	assert_param( FAIL );
	/*
    GPIO_InitTypeDef   GPIO_InitStructure;

    GPIO_InitStructure.Pin =  obj->pinIndex ;
    GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init( obj->port, &GPIO_InitStructure );*/
}

void GpioMcuWrite( Gpio_t *obj, uint32_t value )
{
	if( obj == NULL )
	{
		assert_param( FAIL );
	}
    // Check if pin is not connected
    if( obj->pin == NC )
    {
        return;
    }

    if (value)
    	GPIO_PinOutSet(obj->portIndex, obj->pin & 0x0F);
    else
    	GPIO_PinOutClear(obj->portIndex, obj->pin & 0x0F);
}

void GpioMcuToggle( Gpio_t *obj )
{
	assert_param(obj != NULL);
    if( obj == NULL )
    {
        assert_param( FAIL );
    }

    // Check if pin is not connected
    if( obj->pin == NC )
    {
        return;
    }

    GPIO_PinOutToggle(obj->portIndex, obj->pin & 0x0F);
}

uint32_t GpioMcuRead( Gpio_t *obj )
{
    if( obj == NULL )
    {
        assert_param( FAIL );
    }
    // Check if pin is not connected
    if( obj->pin == NC )
    {
        return 0;
    }

    return GPIO_PinOutGet(obj->portIndex, obj->pin & 0x0F);
}

void GPIO_ODD_IRQHandler(void)
{
	uint32_t i = GPIO_IntGet();
	GPIO_IntClear(0xAAAA);

	if (i & (1 << PIN_DIO_1))
	{
		if (GpioIrq[PIN_DIO_1] != NULL)
			GpioIrq[PIN_DIO_1]();
	}

	if (i & (1 << PIN_DIO_2))
	{
		if (GpioIrq[PIN_DIO_2] != NULL)
			GpioIrq[PIN_DIO_2]();
	}

	if (i & (1 << PIN_DIO_4))
	{
		if (GpioIrq[PIN_DIO_4] != NULL)
			GpioIrq[PIN_DIO_4]();
	}

	if (i & (1 << PIN_BUTTON_0))
	{
		if (GpioIrq[PIN_BUTTON_0] != NULL)
			GpioIrq[PIN_BUTTON_0]();
	}
 }

void GPIO_EVEN_IRQHandler(void)
 {
	uint32_t i = GPIO_IntGet();
	GPIO_IntClear(0x5555);

	if (i & (1 << PIN_DIO_0))
	{
		if (GpioIrq[PIN_DIO_0] != NULL)
			GpioIrq[PIN_DIO_0]();
	}

	if (i & (1 << PIN_DIO_3))
	{
		if (GpioIrq[PIN_DIO_3] != NULL)
			GpioIrq[PIN_DIO_3]();
	}

	if (i & (1 << PIN_BUTTON_1))
	{
		if (GpioIrq[PIN_BUTTON_1] != NULL)
			GpioIrq[PIN_BUTTON_1]();
	}

	if (i & (1 << PIN_LIGHT_SENSE))
	{
		if (GpioIrq[PIN_LIGHT_SENSE] != NULL)
			GpioIrq[PIN_LIGHT_SENSE]();
	}
}
