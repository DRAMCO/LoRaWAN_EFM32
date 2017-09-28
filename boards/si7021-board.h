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
 *         File: si7021-board.h
 *      Created: 2017-09-19
 *       Author: Geoffrey Ottoy
 *
 *  Description: Header for si7021-board.c
 */

#ifndef BOARDS_SI7021_BOARD_H_
#define BOARDS_SI7021_BOARD_H_

#include "em_device.h"
#include <stdbool.h>

/* Reads relative humidity and temperature from a Si7021 sensor.
 *   Returns zero on OK, non-zero otherwise.
 */
int32_t Si7021_MeasureRHAndTemp(uint32_t *rhData, uint32_t *tData);

#endif /* BOARDS_SI7021_BOARD_H_ */
