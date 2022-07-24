/**
  ******************************************************************************
  * @file    mystdlib.h
  * @author  Reiter Roman
  * @version 1.0
  * @date Created on: 24.12.2021
  * @brief   Header file of GPIO HAL module.
  ******************************************************************************
  */
#ifndef STDLIB_MYSTDLIB_H_
#define STDLIB_MYSTDLIB_H_


#ifdef __cplusplus
 extern "C" {
#endif


 /* Includes ------------------------------------------------------------------*/
#include "stm32l4xx.h"

 /** @addtogroup MyLibrary
   * @{
   */

 /** @defgroup MYSTDLIB MyStdLib
   * @{
   */

 /* Exported types ------------------------------------------------------------*/
 /* Exported constants --------------------------------------------------------*/
 /* Exported macro ------------------------------------------------------------*/
 /* Private macros ------------------------------------------------------------*/
 /* Exported functions --------------------------------------------------------*/

 /** @addtogroup CLIPBOARDS_Exported_Functions CLIPBOARDS Exported Functions
   * @{
   */

 /** @addtogroup CLIPBOARDS_Exported_Functions_Group1 CLIPBOARDS Initialization/de-initialization functions
   * @brief    Initialization and Configuration functions
   * @{
   */
 void MY_STDLIB_Delay(TIM_HandleTypeDef *htim ,uint16_t us);

 /**
     * @}
     */

   /**
     * @}
     */

   /**
     * @}
     */

   /**
     * @}
     */

#ifdef __cplusplus
}
#endif

#endif /* STDLIB_MYSTDLIB_H_ */
