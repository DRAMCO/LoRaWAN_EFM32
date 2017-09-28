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
 *         File: omux-board.h
 *      Created: 2017-09-19
 *       Author: Geoffrey Ottoy
 *
 *  Description: Header for omux-board.c
 */

#ifndef BOARDS_OMUX_BOARD_H_
#define BOARDS_OMUX_BOARD_H_

/* Toggle the LED on the extension board.
 */
bool OMuxToggleLed(void);

/* Set the LED on the extension board.
 */
bool OMuxLedOn(void);

/* Clear the LED on the extension board.
 */
bool OMuxLedOff(void);

/* Set RF-LORA module in default state
 */
bool OMuxAntInit(void);

/* Set RF-LORA module in transmit mode
 */
bool OMuxAntSetTX(void);

/* Set RF-LORA module in receive mode
 */
bool OMuxAntSetRX(void);

/* Set new value on the output mux
 */
bool OMuxSetValue(uint8_t addr, uint8_t value);

#endif /* BOARDS_OMUX_BOARD_H_ */
