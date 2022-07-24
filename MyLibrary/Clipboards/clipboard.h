/**
  ******************************************************************************
  * @file    clipboards_conf.h
  * @author  Reiter Roman
  * @version 1.0
  * @date Created on: 24.12.2021
  * @brief   Header file of GPIO HAL module.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CLIPBOARDS_CLIPBOARDS_DEF_H_
#define CLIPBOARDS_CLIPBOARDS_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx.h"

/** @addtogroup MyLibrary
  * @{
  */

/** @defgroup CLIPBOARDS Clipboards
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup CLIPBOARDS_Exported_Types CLIPBOARDS Exported Types
  * @{
  */

/**
  * @brief  TIM Time base Configuration Structure definition
  */
 typedef struct
  {
 	 GPIO_TypeDef* GPIO_MOSI_Port;	/*!< MOSI-Port des Clipboards */

  	 uint16_t GPIO_MOSI_Pin;       	/*!< MOSI-Pin des Clipboards */

 	 GPIO_TypeDef* GPIO_SCK_Port;	/*!< SCK-Port des Clipboards */

 	 uint16_t GPIO_SCK_Pin;			/*!< SCK-Pin des Clipboards */

 	 GPIO_TypeDef* GPIO_CS_Port;	/*!< CS-Port des Clipboards */

 	 uint16_t GPIO_CS_Pin;       	/*!< CS-Pin des Clipboards */

  } CLIPBOARD_SPI_TypeDef;
  /**
    * @}
    */

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
  void MY_CLIPBOARD_Init(CLIPBOARD_SPI_TypeDef * hclipboard,GPIO_TypeDef* GPIO_MOSI_Port, uint16_t GPIO_MOSI_Pin,GPIO_TypeDef* GPIO_SCK_Port, uint16_t GPIO_SCK_Pin,GPIO_TypeDef* GPIO_CS_Port, uint16_t GPIO_CS_Pin);
  /**
    * @}
    */

  /** @addtogroup CLIPBOARDS_Exported_Functions_Group2 CLIPBOARDS SPI-Transfer functions
    *  @brief   CLIPBOARDS SPI-Transfer functions
    * @{
    */
  void MY_CLIPBOARD_SPI_TX(CLIPBOARD_SPI_TypeDef * hclipboard, uint8_t * value);
  uint16_t get_value_bitpositions(uint16_t zahl, uint16_t stelle);

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

#endif /* CLIPBOARDS_CLIPBOARDS_DEF_H_ */
