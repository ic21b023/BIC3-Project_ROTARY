/**
  ******************************************************************************
  * @file    clipboards_conf.c
  * @author  Reiter Roman
  * @version 1.0
  * @date Created on: 24.12.2021
  * @brief   GPIO HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the General Purpose Input/Output (GPIO) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *
  @verbatim
  ==============================================================================
                    ##### GPIO Peripheral features #####
  ==============================================================================
  [..]
    (+) Each port bit of the general-purpose I/O (GPIO) ports can be individually
        configured by software in several modes:
        (++) Input mode
        (++) Analog mode
        (++) Output mode
        (++) Alternate function mode
        (++) External interrupt/event lines

    (+) During and just after reset, the alternate functions and external interrupt
        lines are not active and the I/O ports are configured in input floating mode.

    (+) All GPIO pins have weak internal pull-up and pull-down resistors, which can be
        activated or not.

    (+) In Output or Alternate mode, each IO can be configured on open-drain or push-pull
        type and the IO speed can be selected depending on the VDD value.

    (+) The microcontroller IO pins are connected to onboard peripherals/modules through a
        multiplexer that allows only one peripheral alternate function (AF) connected
       to an IO pin at a time. In this way, there can be no conflict between peripherals
       sharing the same IO pin.

    (+) All ports have external interrupt/event capability. To use external interrupt
        lines, the port must be configured in input mode. All available GPIO pins are
        connected to the 16 external interrupt/event lines from EXTI0 to EXTI15.

    (+) The external interrupt/event controller consists of up to 39 edge detectors
        (16 lines are connected to GPIO) for generating event/interrupt requests (each
        input line can be independently configured to select the type (interrupt or event)
        and the corresponding trigger event (rising or falling or both). Each line can
        also be masked independently.

                     ##### How to use this driver #####
  ==============================================================================
  [..]
    (#) Enable the GPIO AHB clock using the following function: __HAL_RCC_GPIOx_CLK_ENABLE().

    (#) Configure the GPIO pin(s) using HAL_GPIO_Init().
        (++) Configure the IO mode using "Mode" member from GPIO_InitTypeDef structure
        (++) Activate Pull-up, Pull-down resistor using "Pull" member from GPIO_InitTypeDef
             structure.
        (++) In case of Output or alternate function mode selection: the speed is
             configured through "Speed" member from GPIO_InitTypeDef structure.
        (++) In alternate mode is selection, the alternate function connected to the IO
             is configured through "Alternate" member from GPIO_InitTypeDef structure.
        (++) Analog mode is required when a pin is to be used as ADC channel
             or DAC output.
        (++) In case of external interrupt/event selection the "Mode" member from
             GPIO_InitTypeDef structure select the type (interrupt or event) and
             the corresponding trigger event (rising or falling or both).

    (#) In case of external interrupt/event mode selection, configure NVIC IRQ priority
        mapped to the EXTI line using HAL_NVIC_SetPriority() and enable it using
        HAL_NVIC_EnableIRQ().

    (#) To get the level of a pin configured in input mode use HAL_GPIO_ReadPin().

    (#) To set/reset the level of a pin configured in output mode use
        HAL_GPIO_WritePin()/HAL_GPIO_TogglePin().

   (#) To lock pin configuration until next reset use HAL_GPIO_LockPin().

    (#) During and just after reset, the alternate functions are not
        active and the GPIO pins are configured in input floating mode (except JTAG
        pins).

    (#) The LSE oscillator pins OSC32_IN and OSC32_OUT can be used as general purpose
        (PC14 and PC15, respectively) when the LSE oscillator is off. The LSE has
        priority over the GPIO function.

    (#) The HSE oscillator pins OSC_IN/OSC_OUT can be used as
        general purpose PH0 and PH1, respectively, when the HSE oscillator is off.
        The HSE has priority over the GPIO function.

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <Clipboards/clipboard.h>

/** @addtogroup MyLibrary
  * @{
  */

/** @defgroup CLIPBOARDS Clipboards
  * @brief TIM HAL module driver
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup CLIPBOARDS_Exported_Functions CLIPBOARDS Exported Functions
  * @{
  */

/** @defgroup CLIPBOARDS_Exported_Functions_Group1 CLIPBOARDS Initialization/de-initialization functions
 *  @brief    Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the CLIPBOARDx peripheral according to the specified parameters in the GPIO_Init.
  * @param  GPIOx where x can be (A..H) to select the GPIO peripheral for STM32L4 family
  * @param  GPIO_Init pointer to a GPIO_InitTypeDef structure that contains
  *         the configuration information for the specified GPIO peripheral.
  * @retval None
  */
 void MY_CLIPBOARD_Init(CLIPBOARD_SPI_TypeDef * hclipboard,GPIO_TypeDef* GPIO_MOSI_Port, uint16_t GPIO_MOSI_Pin,GPIO_TypeDef* GPIO_SCK_Port, uint16_t GPIO_SCK_Pin,GPIO_TypeDef* GPIO_CS_Port, uint16_t GPIO_CS_Pin){

	hclipboard->GPIO_MOSI_Port=GPIO_MOSI_Port;
	hclipboard->GPIO_MOSI_Pin=GPIO_MOSI_Pin;

	hclipboard->GPIO_SCK_Port=GPIO_SCK_Port;
	hclipboard->GPIO_SCK_Pin=GPIO_SCK_Pin;

	hclipboard->GPIO_CS_Port=GPIO_MOSI_Port;
	hclipboard->GPIO_CS_Pin=GPIO_CS_Pin;


 }

 /**
   * @}
   */

 /** @defgroup CLIPBOARDS_Exported_Functions_Group2 CLIPBOARDS SPI-Transfer functions
  *  @brief CLIPBOARDS SPI-Transfer functions
  *
 @verbatim
  ===============================================================================
                        ##### IO operation functions #####
  ===============================================================================

 @endverbatim
   * @{
   */

 /**
   * @brief  Read the specified input port pin.
   * @param  GPIOx where x can be (A..H) to select the GPIO peripheral for STM32L4 family
   * @param  GPIO_Pin specifies the port bit to read.
   *         This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
   * @retval The input port pin value.
   */
 void MY_CLIPBOARD_SPI_TX(CLIPBOARD_SPI_TypeDef * hclipboard, uint8_t * value){

 	HAL_GPIO_WritePin(hclipboard->GPIO_CS_Port, hclipboard->GPIO_CS_Pin, GPIO_PIN_RESET);

 	for(int i=15;i>=0;i--){
 		HAL_GPIO_WritePin(hclipboard->GPIO_MOSI_Port, hclipboard->GPIO_MOSI_Pin, value[i]);
 		HAL_GPIO_WritePin(hclipboard->GPIO_SCK_Port, hclipboard->GPIO_SCK_Pin, GPIO_PIN_SET);
 		HAL_GPIO_WritePin(hclipboard->GPIO_SCK_Port, hclipboard->GPIO_SCK_Pin, GPIO_PIN_RESET);
 	}

 	HAL_GPIO_WritePin(hclipboard->GPIO_CS_Port, hclipboard->GPIO_CS_Pin, GPIO_PIN_SET);

 }

 /**
   * @brief  Set or clear the selected data port bit.
   *
   * @note   This function uses GPIOx_BSRR and GPIOx_BRR registers to allow atomic read/modify
   *         accesses. In this way, there is no risk of an IRQ occurring between
   *         the read and the modify access.
   *
   * @param  GPIOx where x can be (A..H) to select the GPIO peripheral for STM32L4 family
   * @param  GPIO_Pin specifies the port bit to be written.
   *         This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
   * @param  PinState specifies the value to be written to the selected bit.
   *         This parameter can be one of the GPIO_PinState enum values:
   *            @arg GPIO_PIN_RESET: to clear the port pin
   *            @arg GPIO_PIN_SET: to set the port pin
   * @retval None
   */
uint16_t get_value_bitpositions(uint16_t zahl, uint16_t stelle){
 	     return (((zahl& ( 0b0000000000000001<<stelle))>>stelle)+(stelle*((zahl& ( 0b0000000000000001<<stelle))>>stelle)));

 }

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
