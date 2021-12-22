/**
  ******************************************************************************
  * @file    COMP/COMP_PulseWidthMeasurement/Src/stm32l0xx_it.c
  * @author  MCD Application Team
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l0xx_it.h"

/** @addtogroup STM32L0xx_HAL_Examples
  * @{
  */

/** @addtogroup COMP_PulseWidthMeasurement
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern COMP_HandleTypeDef   Comp2Handle;
extern TIM_HandleTypeDef    TimHandle;
extern DAC_HandleTypeDef    DacHandle;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0+ Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
}

/******************************************************************************/
/*                 STM32L0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32l0xx.s).                                               */
/******************************************************************************/

/**
 * @brief  This function handles COMP interrupt request.
 * @param  None
 * @retval None
 */
void COMPx_IRQHandler(void)
{
 HAL_COMP_IRQHandler(&Comp2Handle);
}

/**
* @brief  This function handles TIM interrupt request.
* @param  None
* @retval None
*/
void TIMx_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&TimHandle);
}

/**
* @brief  This function handles DAC interrupt request.
* @param  None
* @retval None
*/
void DACx_IRQHandler(void)
{
  HAL_DAC_IRQHandler(&DacHandle);
}

/**
* @brief  This function handles DMA interrupt request.
* @param  None
* @retval None
*/
void DMA1_Channel4_5_6_7_IRQHandler(void)
{
  HAL_DMA_IRQHandler(DacHandle.DMA_Handle1);
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
