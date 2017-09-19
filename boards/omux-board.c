/*  ____  ____      _    __  __  ____ ___
 * |  _ \|  _ \    / \  |  \/  |/ ___/ _ \
 * | | | | |_) |  / _ \ | |\/| | |  | | | |
 * | |_| |  _ <  / ___ \| |  | | |__| |_| |
 * |____/|_| \_\/_/   \_\_|  |_|\____\___/
 *                           research group
 *                             dramco.be/
 *
 *   KU Leuven - Technology Campus Gent,
 *   Gebroeders De Smetstraat 1,
 *   B-9000 Gent, Belgium
 *
 *         File: omux-board.c
 *      Created: 2017-09-19
 *       Author: Geoffrey Ottoy
 *
 *  Description: Functions to control the EFM32 Wonder Gecko
 *  	LoRa Extension Board I2C output mux.
 */


#include <stddef.h>
#include "board.h"
#include "i2c.h"
#include "i2cspm.h"
#include "omux-board.h"

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

#define OMUX_ADDR		0x65

#define ALL_OFF			0x00
#define ALL_ON			0xFF
#define LED_ON			0x01
#define EWE				0x02
#define TX_SWITCH_ON	0x04
#define RX_SWITCH_ON	0x08

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

uint8_t prevValue = 0x00;

/* Toggle the LED on the extension board.
 */
bool OMuxToggleLed(I2c_t *obj){
	prevValue ^= LED_ON;
	return OMuxSetValue(obj, OMUX_ADDR, prevValue);
}

/* Set RF-LORA module in default state
 */
bool OMuxAntInit(I2c_t * obj){
	return OMuxAntSetRX(obj);
}

/* Set RF-LORA module in transmit mode
 */
bool OMuxAntSetTX(I2c_t * obj){
	prevValue &= !(RX_SWITCH_ON);
	prevValue |= TX_SWITCH_ON;
	return OMuxSetValue(obj, OMUX_ADDR, prevValue);
}

/* Set RF-LORA module in receive mode
 */
bool OMuxAntSetRX(I2c_t * obj){
	prevValue &= !(TX_SWITCH_ON);
	prevValue |= RX_SWITCH_ON;
	return OMuxSetValue(obj, OMUX_ADDR, prevValue);
}

/* Set new value on the output mux
 */
bool OMuxSetValue(I2c_t *obj, uint8_t addr, uint8_t value){
	I2cWrite(obj, addr, 0, value);
	return true;
}
