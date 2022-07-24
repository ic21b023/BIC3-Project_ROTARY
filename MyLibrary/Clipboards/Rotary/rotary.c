/*
 * rotary.c
 *
 *  Created on: 25.12.2021
 *      Author: reiter
 */

/* Includes ------------------------------------------------------------------*/
#include "rotary.h"

/* Private variables ---------------------------------------------------------*/
/** @addtogroup SERIALPROT_Private_Variables
  * @{
  */
static GPIO_TypeDef* GPIO_ENCA_Portx;
static uint16_t GPIO_ENCA_Pinx;
static GPIO_TypeDef* GPIO_ENCB_Portx;
static uint16_t GPIO_ENCB_Pinx;
static GPIO_TypeDef* GPIO_SWITCH_Portx;
static uint16_t GPIO_SWITCH_Pinx;

static uint8_t encA_now;
static uint8_t encB_now;
static uint8_t enc_last;
static uint8_t swi_now;

static uint8_t ring_rot[17][16]={
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}};
  /**
    * @}
    */


/**
  * @brief  Funktion 			Initialisiert Encoder
  * @param  hrotary 			rotary handle
  * @param  htim 				htim handle
  * @param  GPIO_MOSI_Port		MOSI-Port des Clipboards
  * @param  GPIO_MOSI_Pin		MOSI-Pin des Clipboards
  * @param  GPIO_SCK_Port 		SCK-Port des Clipboards
  * @param  GPIO_SCK_Pin		SCK-Pin des Clipboards
  * @param  GPIO_CS_Port		MOSI-Port des Clipboards
  * @param  GPIO_CS_Pin			SCK-Pin des Clipboards
  * @param  GPIO_ENCA_Port		ENCA-Port des Clipboards
  * @param  GPIO_ENCA_Pin		ENCA-Pin des Clipboards
  * @param  GPIO_ENCB_Port		ENCB-Port des Clipboards
  * @param  GPIO_ENCB_Pin		ENCB-Pin des Clipboards
  * @param  GPIO_SWITCH_Port	SWITCH-Port des Clipboards
  * @param  GPIO_SWITCH_Pin		SWITCH-Pin des Clipboards
  */
void MY_ROTARY_Init_Strobed(MY_ROTARY_HandleTypeDef * hrotary ,TIM_HandleTypeDef * htim,GPIO_TypeDef* GPIO_MOSI_Port, uint16_t GPIO_MOSI_Pin,GPIO_TypeDef* GPIO_SCK_Port, uint16_t GPIO_SCK_Pin,GPIO_TypeDef* GPIO_CS_Port, uint16_t GPIO_CS_Pin,GPIO_TypeDef* GPIO_ENCA_Port, uint16_t GPIO_ENCA_Pin,GPIO_TypeDef* GPIO_ENCB_Port, uint16_t GPIO_ENCB_Pin,GPIO_TypeDef* GPIO_SWITCH_Port, uint16_t GPIO_SWITCH_Pin){
	MY_CLIPBOARD_Init(&hrotary->hclipboard,GPIO_MOSI_Port, GPIO_MOSI_Pin, GPIO_SCK_Port, GPIO_SCK_Pin, GPIO_CS_Port, GPIO_CS_Pin);
	hrotary->htim = htim;
	HAL_TIM_Base_Start(htim);
	GPIO_ENCA_Portx =GPIO_ENCA_Port;
	GPIO_ENCA_Pinx = GPIO_ENCA_Pin;
	GPIO_ENCB_Portx=GPIO_ENCB_Port;
	GPIO_ENCB_Pinx=GPIO_ENCB_Pin;
	GPIO_SWITCH_Portx=GPIO_SWITCH_Port;
	GPIO_SWITCH_Pinx=GPIO_SWITCH_Pin;
	/* prüfen ob Encoderlevel High oder Low */
	enc_last=HAL_GPIO_ReadPin (GPIO_ENCA_Port, GPIO_ENCA_Pin);

}

/**
  * @brief  Funktion 	Liefert das Encoderevent
  * @retval Liefert 1 für rechtsdreh, 2 für linksdreh und 3 für taster gedrückt
  */
uint8_t MY_ROTARY_GetEncoderEvent(){
	uint8_t retval=0;
	encA_now = HAL_GPIO_ReadPin (GPIO_ENCA_Portx, GPIO_ENCA_Pinx);
	encB_now = HAL_GPIO_ReadPin (GPIO_ENCB_Portx, GPIO_ENCB_Pinx);
	swi_now = HAL_GPIO_ReadPin (GPIO_SWITCH_Portx, GPIO_SWITCH_Pinx);

	if(encA_now != encB_now){
		if(encB_now == enc_last){
			retval= 1;
		}else if(encA_now == enc_last){
			retval= 2;
		}
	}else if(swi_now){
			retval= 3;
	}
		return retval;
}

/**
  * @brief  Funktion 					Setzt die LED's des Encoders
  * @param  hrotary 					rotary handle
  * @param  bit_array_of_leds 			Jedes Bit steht für eine LED / 0=aus, 1=ein
  * @param  bit_array_of_brightness		Helligkeit jeder LED 0-100%
  */
void MY_ROTARY_SET_LEDS(MY_ROTARY_HandleTypeDef * hrotary, uint16_t * bit_array_of_leds, uint8_t * bit_array_of_brightness){
 //16000 MAX


	for(int i=0;i<16;i++){

		MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[0]);
		MY_STDLIB_Delay(hrotary->htim,(100-bit_array_of_brightness[i])*10);
		MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[get_value_bitpositions(bit_array_of_leds,i)]);
		MY_STDLIB_Delay(hrotary->htim,10*bit_array_of_brightness[i]);
	}

	/*

    MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[0]);
  	MY_STDLIB_Delay(hrotary->htim,(100-brightness[0])*10);
  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[get_value_bitpositions(number,0)]);
  	MY_STDLIB_Delay(hrotary->htim,10*brightness[0]);

  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[0]);
  	MY_STDLIB_Delay(hrotary->htim,(100-brightness[1])*10);
  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[get_value_bitpositions(number,1)]);
  	MY_STDLIB_Delay(hrotary->htim,10*brightness[1]);

  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[0]);
  	MY_STDLIB_Delay(hrotary->htim,(100-brightness[2])*10);
  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[get_value_bitpositions(number,2)]);
  	MY_STDLIB_Delay(hrotary->htim,10*brightness[2]);

  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[0]);
  	MY_STDLIB_Delay(hrotary->htim,(100-brightness[3])*10);
  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[get_value_bitpositions(number,3)]);
  	MY_STDLIB_Delay(hrotary->htim,10*brightness[3]);

  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[0]);
  	MY_STDLIB_Delay(hrotary->htim,(100-brightness[4])*10);
  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[get_value_bitpositions(number,4)]);
  	MY_STDLIB_Delay(hrotary->htim,10*brightness[4]);

  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[0]);
  	MY_STDLIB_Delay(hrotary->htim,(100-brightness[5])*10);
  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[get_value_bitpositions(number,5)]);
  	MY_STDLIB_Delay(hrotary->htim,10*brightness[5]);

  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[0]);
  	MY_STDLIB_Delay(hrotary->htim,(100-brightness[6])*10);
  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[get_value_bitpositions(number,6)]);
  	MY_STDLIB_Delay(hrotary->htim,10*brightness[6]);

  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[0]);
  	MY_STDLIB_Delay(hrotary->htim,(100-brightness[7])*10);
  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[get_value_bitpositions(number,7)]);
  	MY_STDLIB_Delay(hrotary->htim,10*brightness[7]);

  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[0]);
  	MY_STDLIB_Delay(hrotary->htim,(100-brightness[8])*10);
  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[get_value_bitpositions(number,8)]);
  	MY_STDLIB_Delay(hrotary->htim,10*brightness[8]);

  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[0]);
  	MY_STDLIB_Delay(hrotary->htim,(100-brightness[9])*10);
  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[get_value_bitpositions(number,9)]);
  	MY_STDLIB_Delay(hrotary->htim,10*brightness[9]);

  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[0]);
  	MY_STDLIB_Delay(hrotary->htim,(100-brightness[10])*10);
  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[get_value_bitpositions(number,10)]);
  	MY_STDLIB_Delay(hrotary->htim,10*brightness[10]);

  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[0]);
  	MY_STDLIB_Delay(hrotary->htim,(100-brightness[11])*10);
  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[get_value_bitpositions(number,11)]);
  	MY_STDLIB_Delay(hrotary->htim,10*brightness[11]);

  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[0]);
  	MY_STDLIB_Delay(hrotary->htim,(100-brightness[12])*10);
  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[get_value_bitpositions(number,12)]);
  	MY_STDLIB_Delay(hrotary->htim,10*brightness[12]);

  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[0]);
  	MY_STDLIB_Delay(hrotary->htim,(100-brightness[13])*10);
  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[get_value_bitpositions(number,13)]);
  	MY_STDLIB_Delay(hrotary->htim,10*brightness[13]);

  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[0]);
  	MY_STDLIB_Delay(hrotary->htim,(100-brightness[14])*10);
  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[get_value_bitpositions(number,14)]);
  	MY_STDLIB_Delay(hrotary->htim,10*brightness[14]);

  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[0]);
  	MY_STDLIB_Delay(hrotary->htim,(100-brightness[15])*10);
  	MY_CLIPBOARD_SPI_TX(&hrotary->hclipboard,ring_rot[get_value_bitpositions(number,15)]);
  	MY_STDLIB_Delay(hrotary->htim,10*bit_array_of_brightness[15]);
 */
  	/* prüfen ob Encoderlevel High oder Low */
  	enc_last = HAL_GPIO_ReadPin (GPIO_ENCA_Portx, GPIO_ENCA_Pinx);
}
