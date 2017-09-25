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
 *         File: app_select.h
 *      Created: 2017-09-21
 *       Author: Geoffrey Ottoy
 *
 *  Description: This header file contains macro's that regulate
 *  	which application is being compiled.
 */

#ifndef SRC_APP_SELECT_H_
#define SRC_APP_SELECT_H_

// define either AES_APP, EXAMPLE_APP or DEEP_SLEEP_APP as global symbols
#if defined(APP_TYPE)
 #if (APP_TYPE != EXAMPLE_APP)
  #if (APP_TYPE != AES_APP)
   #if (APP_TYPE != DEEP_SLEEP_APP)
    #error "No app type was specified."
   #endif
  #else //AES_APP is defined
   #if (APP_TYPE == DEEP_SLEEP_APP)
    #error "Only one app type may be specified."
   #endif
  #endif
 #else
  #if (APP_TYPE == AES_APP)
   #error "Only one app type may be specified."
  #endif
  #if (APP_TYPE == DEEP_SLEEP_APP)
   #error "Only one app type may be specified."
  #endif
 #endif
#endif

#endif /* SRC_APP_SELECT_H_ */
