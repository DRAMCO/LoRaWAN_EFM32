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
 *         File: main.c
 *      Created: 2017-09-20
 *       Author: Geoffrey Ottoy
 *
 *  Description: Main function running on the EFM32.
 *  	The type of application can be selected (see app_select.h)
 */


#include "app_select.h"
#ifdef EXAMPLE_APP
#include "example_app.h"
#endif
#ifdef AES_APP
#include "aes_app.h"
#endif
#ifdef DEEP_SLEEP_APP
#include "deep_sleep_app.h"
#endif

int main(void){
#ifdef AES_APP
	main_aes();
#endif
#ifdef EXAMPLE_APP
	main_example();
#endif
	while(1);
}
