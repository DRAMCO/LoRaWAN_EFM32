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
 *         File: si7021-board.c
 *      Created: 2017-09-19
 *       Author: Geoffrey Ottoy
 *
 *  Description: Functions to read the EFM32 Wonder Gecko
 *  	on-board si7021 temperature and humidity sensor.
 */

#include <stddef.h>
#include "board.h"
#include "i2c.h"
#include "i2cspm.h"
#include "si7021-board.h"

/** I2C device address for Si7021 */
#define SI7021_ADDR      0x80

/** Si7021 Read Temperature Command */
#define SI7021_READ_TEMP       0xE0  /* Read previous T data from RH measurement
                                      * command*/
/** Si7021 Read RH Command */
#define SI7021_READ_RH         0xE5  /* Perform RH (and T) measurement. */

/* Reads data from the Si7021 sensor.
 *   Returns number of bytes read on success. Otherwise returns error codes
 *   based on the I2CDRV.
 */
static int32_t Si7021_Measure(uint8_t addr, uint32_t *data, uint8_t command){
	uint8_t rdBuffer[2];

	I2cReadBuffer(&I2c, addr, (uint16_t)command, rdBuffer, 2 );
	*data = ((uint32_t) rdBuffer[0] << 8) + (rdBuffer[1] & 0xfc);

	return((int) 2);
}

/* Reads relative humidity and temperature from a Si7021 sensor.
 *   Returns zero on OK, non-zero otherwise.
 */
int32_t Si7021_MeasureRHAndTemp(uint32_t *rhData, uint32_t *tData){
#ifdef HW_VERSION_3
	int ret = Si7021_Measure(SI7021_ADDR, rhData, SI7021_READ_RH);

	if (ret == 2){
		/* convert to percent * 1000 */
		*rhData = (((*rhData) * 15625L) >> 13) - 6000;
	}
	else{
		return -1;
	}

	ret = Si7021_Measure(SI7021_ADDR, (uint32_t *) tData, SI7021_READ_TEMP);

	if (ret == 2){
		*tData = (((*tData) * 21965L) >> 13) - 46850; /* convert to °C * 1000 */
	}
	else{
		return -1;
	}

	return 0;
#else
	assert_param(FAIL);
	return -2;
#endif
}

