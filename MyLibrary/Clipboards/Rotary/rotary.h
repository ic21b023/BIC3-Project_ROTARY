/*
 * rotary.h
 *
 *  Created on: 24.12.2021
 *      Author: reiter
 */

#ifndef CLIPBOARDS_ROTARY_ROTARY_H_
#define CLIPBOARDS_ROTARY_ROTARY_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <Clipboards/clipboard.h>

 /**
   * @brief  ROTARY Handle
   */
 typedef struct
  {
 	CLIPBOARD_SPI_TypeDef hclipboard; 	/*!< Nachricht OK */

 	TIM_HandleTypeDef * htim;			/*!< Nachricht OK */

  } MY_ROTARY_HandleTypeDef;




  /* Exported functions --------------------------------------------------------*/
  void MY_ROTARY_Init_Strobed(MY_ROTARY_HandleTypeDef * hrotary ,TIM_HandleTypeDef * htim,GPIO_TypeDef* GPIO_MOSI_Port, uint16_t GPIO_MOSI_Pin,GPIO_TypeDef* GPIO_SCK_Port, uint16_t GPIO_SCK_Pin,GPIO_TypeDef* GPIO_CS_Port, uint16_t GPIO_CS_Pin,GPIO_TypeDef* GPIO_ENCA_Port, uint16_t GPIO_ENCA_Pin,GPIO_TypeDef* GPIO_ENCB_Port, uint16_t GPIO_ENCB_Pin,GPIO_TypeDef* GPIO_SWITCH_Port, uint16_t GPIO_SWITCH_Pin);
  void MY_ROTARY_SET_LEDS(MY_ROTARY_HandleTypeDef * hrotary,uint16_t * number,uint8_t * brightness);
  uint8_t MY_ROTARY_GetEncoderEvent();


#ifdef __cplusplus
}
#endif


#endif /* CLIPBOARDS_ROTARY_ROTARY_H_ */
