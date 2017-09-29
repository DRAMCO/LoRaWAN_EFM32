/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: Target board general functions implementation

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
#ifndef __BOARD_H__
#define __BOARD_H__

#include "em_device.h"
#include "em_assert.h"

typedef struct
{
  ADC_TypeDef* Instance;
}ADC_HandleTypeDef;

typedef struct
{
  I2C_TypeDef* Instance;
}I2C_HandleTypeDef;

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "utilities.h"
#include "timer.h"
#include "delay.h"
#include "gpio.h"
#include "adc.h"
#include "spi.h"
#include "i2c.h"
#include "radio.h"
#include "sx1272.h"
#include "rtc-board.h"
#include "sx1272-board.h"

#define assert_param(expr) (EFM_ASSERT( expr ))

/*!
 * Generic definition
 */
#ifndef SUCCESS
#define SUCCESS                                     1
#endif

#ifndef FAIL
#define FAIL                                        0
#endif


/*!
 * Board MCU pins definitions
 */

#ifdef HW_VERSION_3
// RF LORA 868 connections
#define RADIO_MOSI                                  PE_11
#define RADIO_MISO                                  PE_10
#define RADIO_SCLK                                  PE_12
#define RADIO_NSS                                   PE_13
#define RADIO_RESET                                 PA_2

#define RADIO_DIO_0                                 PC_0
#define RADIO_DIO_1                                 PC_1
#define RADIO_DIO_2                                 PB_11
#define RADIO_DIO_3                                 PD_4
#define RADIO_DIO_4                                 PD_5
#define RADIO_DIO_5                                 PA_1

// Happy Gecko LEDs
#define LED_0                                       PF_4
#define LED_1                                       PF_5

// Happy Gecko push buttons
#define BUTTON_0									PC_9
#define BUTTON_1									PC_10

// I²C pins
#define I2C_SCL                                     PD_7
#define I2C_SDA                                     PD_6

// Happy Gecko temperature and humidity sensor enable
#define SI7021_ENABLE								PC_8

// Extension board light sensor interrupt line
#define ADPS9200_INT								PC_2

#else /*HW_VERSION_1 or HW_VERSION_2 */
// RF LORA 868 connections
#define RADIO_MOSI                                  PE_11
#define RADIO_MISO                                  PE_10
#define RADIO_SCLK                                  PE_12
#define RADIO_NSS                                   PE_13
#define RADIO_RESET                                 PA_2

#define RADIO_DIO_0                                 PC_0
#define RADIO_DIO_1                                 PD_7
#define RADIO_DIO_2                                 PC_1
#define RADIO_DIO_3                                 PD_6
#define RADIO_DIO_4                                 PA_5
#define RADIO_DIO_5                                 PA_1

#define RADIO_ANT_SWITCH_TX							PB_11
#define RADIO_ANT_SWITCH_RX							PD_4

// Happy Gecko LEDs
#define LED_0                                       PF_4
#define LED_1                                       PF_5

// Happy Gecko push buttons
#define BUTTON_0									PC_9
#define BUTTON_1									PC_10

#define I2C_SCL                                     NC
#define I2C_SDA                                     NC

#endif /* HW_VERSION_3 */



/*!
 * LED GPIO pins objects
 */
/*
extern Gpio_t IrqMpl3115;
extern Gpio_t IrqMag3110;
extern Gpio_t GpsPowerEn;
extern Gpio_t NcIoe3;
extern Gpio_t NcIoe4;
extern Gpio_t NcIoe5;
extern Gpio_t NcIoe6;
extern Gpio_t NcIoe7;
extern Gpio_t NIrqSX9500;
extern Gpio_t Irq1Mma8451;
extern Gpio_t Irq2Mma8451;
extern Gpio_t TxEnSX9500;
*/
extern Gpio_t Led0;
extern Gpio_t Led1;
extern Gpio_t Pb0;
extern Gpio_t Pb1;
extern Gpio_t Si7021_Enable;

extern void Button_0_ISR(void);
extern void Button_1_ISR(void);
/*!
 * Debug GPIO pins objects
 */
/*
#if defined( USE_DEBUG_PINS )
extern Gpio_t DbgPin1;
extern Gpio_t DbgPin2;
extern Gpio_t DbgPin3;
extern Gpio_t DbgPin4;
extern Gpio_t DbgPin5;
#endif
*/

/*!
 * MCU objects
 */
extern Adc_t Adc;
extern I2c_t I2c;

/*
extern Gpio_t GpsPps;
extern Gpio_t GpsRx;
extern Gpio_t GpsTx;
*/
enum BoardPowerSource
{
    USB_POWER = 0,
    BATTERY_POWER
};

void BoardReadRegVersion(uint8_t * data);

/*!
 * \brief Disbale interrupts
 *
 * \remark IRQ nesting is managed
 */
void BoardDisableIrq( void );

/*!
 * \brief Enable interrupts
 *
 * \remark IRQ nesting is managed
 */
void BoardEnableIrq( void );

/*!
 * \brief Initializes the target board peripherals.
 */
void BoardInitMcu( void );

/*!
 * \brief Initializes the boards peripherals.
 */
void BoardInitPeriph( void );

/*!
 * \brief De-initializes the target board peripherals to decrease power
 *        consumption.
 */
void BoardDeInitMcu( void );

/*!
 * \brief Get the current battery level
 *
 * \retval value  battery level ( 0: very low, 254: fully charged )
 */
uint8_t BoardGetBatteryLevel( void );

/*!
 * Returns a pseudo random seed generated using the MCU Unique ID
 *
 * \retval seed Generated pseudo random seed
 */
uint32_t BoardGetRandomSeed( void );

/*!
 * \brief Gets the board 64 bits unique ID
 *
 * \param [IN] id Pointer to an array that will contain the Unique ID
 */
void BoardGetUniqueId( uint8_t *id );

/*!
 * \brief Get the board power source
 *
 * \retval value  power source ( 0: USB_POWER,  1: BATTERY_POWER )
 */
uint8_t GetBoardPowerSource( void );

void Button_0_ISR() __attribute__ ((weak));
void Button_1_ISR() __attribute__ ((weak));
void Adps9200_ISR() __attribute__ ((weak));

#endif // __BOARD_H__
