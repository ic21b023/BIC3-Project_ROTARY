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
#include "StdLib/mystdlib.h"

/** @addtogroup MyLibrary
  * @{
  */

/** @defgroup MYSTDLIB MyStdLib
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

 void MY_STDLIB_Delay(TIM_HandleTypeDef *htim ,uint16_t us){
 	  	//  uint32_t d = HAL_GetTickFreq();
 	  	//__HAL_TIM_SET_PRESCALER(&htim6, 16-1);
 	  	__HAL_TIM_SET_COUNTER(htim,0);  // set the counter value a 0
 	  	while (__HAL_TIM_GET_COUNTER(htim) < us);  // wait for the counter to reach the us input in the parameter

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
