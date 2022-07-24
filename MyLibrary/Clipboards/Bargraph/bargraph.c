/*
 * bargraph.c
 *
 *  Created on: 25.12.2021
 *      Author: reite
 */

//#include "Clipboards/clipboards_conf.h"
#include "bargraph.h"

 static void MY_BARGRAPH_SET_BRITGHTNESS_PWM(TIM_HandleTypeDef *htim, uint8_t * percent);


 static uint8_t bar_rot[11][16]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0}};



void MY_BARGRAPH_Init_Strobed(MY_BARGRAPH_HandleTypeDef * hbargraph ,TIM_HandleTypeDef * htim,GPIO_TypeDef* GPIO_MOSI_Port, uint16_t GPIO_MOSI_Pin,GPIO_TypeDef* GPIO_SCK_Port, uint16_t GPIO_SCK_Pin,GPIO_TypeDef* GPIO_CS_Port, uint16_t GPIO_CS_Pin){
	MY_CLIPBOARD_Init(&hbargraph->hclipboardR,GPIO_MOSI_Port, GPIO_MOSI_Pin, GPIO_SCK_Port, GPIO_SCK_Pin, GPIO_CS_Port, GPIO_CS_Pin);
	hbargraph->htimR = htim;
	HAL_TIM_Base_Start(htim);
	hbargraph->BrightnessMode = MY_BARGRAPH_BRITHNESSMODE_STROBED;
}

void MY_BARGRAPH_Init_Pulsed(MY_BARGRAPH_HandleTypeDef * hbargraph ,TIM_HandleTypeDef * htim, uint32_t channel, GPIO_TypeDef* GPIO_MOSI_Port, uint16_t GPIO_MOSI_Pin,GPIO_TypeDef* GPIO_SCK_Port, uint16_t GPIO_SCK_Pin,GPIO_TypeDef* GPIO_CS_Port, uint16_t GPIO_CS_Pin){
	MY_CLIPBOARD_Init(&hbargraph->hclipboardR,GPIO_MOSI_Port, GPIO_MOSI_Pin, GPIO_SCK_Port, GPIO_SCK_Pin, GPIO_CS_Port, GPIO_CS_Pin);
	hbargraph->htimR = htim;
	HAL_TIMEx_PWMN_Start(htim,channel);
  	HAL_TIM_PWM_Start(htim,channel);
  	hbargraph->BrightnessMode = MY_BARGRAPH_BRITHNESSMODE_PULSED;
}

void MY_BARGRAPH_SET_BITS(MY_BARGRAPH_HandleTypeDef * hbargraph,uint16_t * number,uint8_t * brightness ){

	if(hbargraph->BrightnessMode){
		MY_BARGRAPH_SET_BITS_PULSED(hbargraph,number, brightness );
	}else{
		MY_BARGRAPH_SET_BITS_PWM(hbargraph,number);
		MY_BARGRAPH_SET_BRITGHTNESS_PWM(hbargraph->htimR,brightness );
	}
}

void MY_BARGRAPH_SET_BITS_PULSED(MY_BARGRAPH_HandleTypeDef * hbargraph,uint16_t * number,uint8_t * brightness){
/*
	uint32_t gg = HAL_GetTick();

	for(uint8_t i =0;i<10;i++){
		MY_CLIPBOARD_SPI_TX(&hbargraph->hclipboardR,bar_rot[i]);
		MY_STDLIB_Delay(hbargraph->htimR,(100-brightness[i])*10);
		MY_CLIPBOARD_SPI_TX(&hbargraph->hclipboardR,bar_rot[get_value_bitpositions(number,(uint16_t)i)]);
		MY_STDLIB_Delay(hbargraph->htimR,10*brightness[i]);
	}

	uint32_t ggg = gg-HAL_GetTick();
	uint32_t dggg = gg-HAL_GetTick();
*/
    MY_CLIPBOARD_SPI_TX(&hbargraph->hclipboardR,bar_rot[0]);
  	MY_STDLIB_Delay(hbargraph->htimR,(100-brightness[0])*10);
  	MY_CLIPBOARD_SPI_TX(&hbargraph->hclipboardR,bar_rot[get_value_bitpositions(number,0)]);
  	MY_STDLIB_Delay(hbargraph->htimR,10*brightness[0]);

  	MY_CLIPBOARD_SPI_TX(&hbargraph->hclipboardR,bar_rot[0]);
  	MY_STDLIB_Delay(hbargraph->htimR,(100-brightness[1])*10);
  	MY_CLIPBOARD_SPI_TX(&hbargraph->hclipboardR,bar_rot[get_value_bitpositions(number,1)]);
  	MY_STDLIB_Delay(hbargraph->htimR,10*brightness[1]);

  	MY_CLIPBOARD_SPI_TX(&hbargraph->hclipboardR,bar_rot[0]);
  	MY_STDLIB_Delay(hbargraph->htimR,(100-brightness[2])*10);
  	MY_CLIPBOARD_SPI_TX(&hbargraph->hclipboardR,bar_rot[get_value_bitpositions(number,(uint32_t)2)]);
  	MY_STDLIB_Delay(hbargraph->htimR,10*brightness[2]);

  	MY_CLIPBOARD_SPI_TX(&hbargraph->hclipboardR,bar_rot[0]);
  	MY_STDLIB_Delay(hbargraph->htimR,(100-brightness[3])*10);
  	MY_CLIPBOARD_SPI_TX(&hbargraph->hclipboardR,bar_rot[get_value_bitpositions(number,3)]);
  	MY_STDLIB_Delay(hbargraph->htimR,10*brightness[3]);

  	MY_CLIPBOARD_SPI_TX(&hbargraph->hclipboardR,bar_rot[0]);
  	MY_STDLIB_Delay(hbargraph->htimR,(100-brightness[4])*10);
  	MY_CLIPBOARD_SPI_TX(&hbargraph->hclipboardR,bar_rot[get_value_bitpositions(number,4)]);
  	MY_STDLIB_Delay(hbargraph->htimR,10*brightness[4]);

  	MY_CLIPBOARD_SPI_TX(&hbargraph->hclipboardR,bar_rot[0]);
  	MY_STDLIB_Delay(hbargraph->htimR,(100-brightness[5])*10);
  	MY_CLIPBOARD_SPI_TX(&hbargraph->hclipboardR,bar_rot[get_value_bitpositions(number,5)]);
  	MY_STDLIB_Delay(hbargraph->htimR,10*brightness[5]);

  	MY_CLIPBOARD_SPI_TX(&hbargraph->hclipboardR,bar_rot[0]);
  	MY_STDLIB_Delay(hbargraph->htimR,(100-brightness[6])*10);
  	MY_CLIPBOARD_SPI_TX(&hbargraph->hclipboardR,bar_rot[get_value_bitpositions(number,6)]);
  	MY_STDLIB_Delay(hbargraph->htimR,10*brightness[6]);

  	MY_CLIPBOARD_SPI_TX(&hbargraph->hclipboardR,bar_rot[0]);
  	MY_STDLIB_Delay(hbargraph->htimR,(100-brightness[7])*10);
  	MY_CLIPBOARD_SPI_TX(&hbargraph->hclipboardR,bar_rot[get_value_bitpositions(number,7)]);
  	MY_STDLIB_Delay(hbargraph->htimR,10*brightness[7]);

  	MY_CLIPBOARD_SPI_TX(&hbargraph->hclipboardR,bar_rot[0]);
  	MY_STDLIB_Delay(hbargraph->htimR,(100-brightness[8])*10);
  	MY_CLIPBOARD_SPI_TX(&hbargraph->hclipboardR,bar_rot[get_value_bitpositions(number,8)]);
  	MY_STDLIB_Delay(hbargraph->htimR,10*brightness[8]);

  	MY_CLIPBOARD_SPI_TX(&hbargraph->hclipboardR,bar_rot[0]);
  	MY_STDLIB_Delay(hbargraph->htimR,(100-brightness[9])*10);
  	MY_CLIPBOARD_SPI_TX(&hbargraph->hclipboardR,bar_rot[get_value_bitpositions(number,9)]);
  	MY_STDLIB_Delay(hbargraph->htimR,10*brightness[9]);

}

 void MY_BARGRAPH_SET_BITS_PWM(MY_BARGRAPH_HandleTypeDef * hbargraph, uint16_t * number){

	uint8_t bar_rotz[16]={0};

	for(uint8_t i=0; i<10;i++){
		if(get_value_bitpositions(number,i)>0){
			bar_rotz[get_value_bitpositions(number,i)-1]=1;
		}
	}

	MY_CLIPBOARD_SPI_TX(&hbargraph->hclipboardR,bar_rotz);

}


static void MY_BARGRAPH_SET_BRITGHTNESS_PWM(TIM_HandleTypeDef *htim, uint8_t * percent){

	  htim->Instance->CCR3= (htim->Init.Period/100) * (uint32_t) percent;
}
