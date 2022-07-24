/**
  ******************************************************************************
  * @file    bargraph.h
  * @author  reite
  * @version 1.0
  * @date Created on: Jan 23, 2022
  * @brief   Header file of GPIO HAL module.
  ******************************************************************************
  */

#ifndef CLIPBOARDS_BARGRAPH_BARGRAPH_H_
#define CLIPBOARDS_BARGRAPH_BARGRAPH_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "Clipboards/clipboard.h"



/** @addtogroup GLOBAL_MAIN_Driver
  * @{
  */

/** @addtogroup XXX
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup XXX_Exported_Types XXX Exported Types
  * @{
  */

/**
  * @brief  XXX Configuration Structure definition
  */
typedef enum
{
	MY_BARGRAPH_BRITHNESSMODE_PULSED = 0,
	MY_BARGRAPH_BRITHNESSMODE_STROBED  = 1

} MY_BARGRAPH_BrightnessMode;




/**
  * @brief  XXX Configuration Structure definition
  */
typedef struct
 {
	CLIPBOARD_SPI_TypeDef hclipboardR;

	TIM_HandleTypeDef * htimR;

	MY_BARGRAPH_BrightnessMode BrightnessMode;

 } MY_BARGRAPH_HandleTypeDef;
/**
  * @}
  */
/* Exported constants --------------------------------------------------------*/
/** @defgroup XXX_Exported_Constants XXX Exported Constants
  * @{
  */

/** @defgroup XXX_CONST_ANT XXX Const Ant
  * @{
  */
	//	Inser First EXPORTED CONSTANT
/**
  * @}
  */

/** @defgroup XXX_CONST_ANT XXX Const Ant
  * @{
  */
	//	Inser Secound EXPORTED CONSTANT
/**
  * @}
  */
/**
  * @}
  */
/* Exported macro ------------------------------------------------------------*/
/** @defgroup XXX_Exported_Macros XXX Exported Macros
  * @{
  */

/** @brief  Reset DMA handle state.
  * @param  __HANDLE__ XXX handle
  * @retval None
  */

	//	Inser First Exported Macros

/**
  * @brief  Enable the specified DMA Channel.
  * @param  __HANDLE__ DMA handle
  * @retval None
  */

	//	Inser Secound Exported Macros
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup XXX_Exported_Functions
  * @{
  */

/** @addtogroup XXX_Exported_Functions_Group1
  * @{
  */
/* Initialization and de-initialization functions *****************************/
		void MY_BARGRAPH_Init_Strobed(MY_BARGRAPH_HandleTypeDef * hbargraph ,TIM_HandleTypeDef * htim,GPIO_TypeDef* GPIO_MOSI_Port, uint16_t GPIO_MOSI_Pin,GPIO_TypeDef* GPIO_SCK_Port, uint16_t GPIO_SCK_Pin,GPIO_TypeDef* GPIO_CS_Port, uint16_t GPIO_CS_Pin);
		void MY_BARGRAPH_Init_Pulsed(MY_BARGRAPH_HandleTypeDef * hbargraph ,TIM_HandleTypeDef * htim, uint32_t channel, GPIO_TypeDef* GPIO_MOSI_Port, uint16_t GPIO_MOSI_Pin,GPIO_TypeDef* GPIO_SCK_Port, uint16_t GPIO_SCK_Pin,GPIO_TypeDef* GPIO_CS_Port, uint16_t GPIO_CS_Pin);

/**
  * @}
  */

/** @addtogroup XXX_Exported_Functions_Group2
  * @{
  */
/* IO operation functions *****************************************************/
		void MY_BARGRAPH_SET_BITS(MY_BARGRAPH_HandleTypeDef * hbargraph,uint16_t * number,uint8_t * brightness);
			void MY_BARGRAPH_SET_BITS_PULSED(MY_BARGRAPH_HandleTypeDef * hbargraph,uint16_t * number,uint8_t * brightness);
			void MY_BARGRAPH_SET_BITS_PWM(MY_BARGRAPH_HandleTypeDef * hbargraph, uint16_t * number);

/**
  * @}
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup DMA_Private_Macros DMA Private Macros
  * @{
  */
	//Inser All Private_Macros
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

#endif /* CLIPBOARDS_BARGRAPH_BARGRAPH_H_ */
