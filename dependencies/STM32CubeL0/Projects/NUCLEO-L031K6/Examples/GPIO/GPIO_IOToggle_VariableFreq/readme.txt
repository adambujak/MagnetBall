/**
  @page GPIO_IOToggle_VariableFreq GPIO IO Toggle Variable Freq example
  
  @verbatim
  ******************** (C) COPYRIGHT 2016 STMicroelectronics *******************
  * @file    GPIO/GPIO_IOToggle_VariableFreq/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the GPIO IO example with variable toggeling frequency .
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
  @endverbatim

@par Example Description
How to configure and use GPIOs to toggle the on-board user LEDs at different
frequencies. This example is based on the STM32L0xx LL API. The peripheral
is initialized with LL initialization function to demonstrate LL init usage. 

The LED3 (IO PB.03) toggles at 1s when IO PA.12 (Arduino D2) is connected to GND with a jumper
and LED3 toggles at 100ms when IO PA.12 is not connected. 

In this example, HCLK is configured with HSI at 16 MHz.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The example needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - GPIO/GPIO_IOToggle_VariableFreq/Inc/stm32l0xx_hal_conf.h    HAL configuration file
  - GPIO/GPIO_IOToggle_VariableFreq/Inc/stm32l0xx_it.h          Interrupt handlers header file
  - GPIO/GPIO_IOToggle_VariableFreq/Inc/main.h                  Header for main.c module  
  - GPIO/GPIO_IOToggle_VariableFreq/Src/stm32l0xx_it.c          Interrupt handlers
  - GPIO/GPIO_IOToggle_VariableFreq/Src/main.c                  Main program
  - GPIO/GPIO_IOToggle_VariableFreq/Src/system_stm32l0xx.c      STM32L0xx system source file


@par Hardware and Software environment

  - This example runs on STM32L031xx devices.
    
  - This example has been tested with STM32L031K6-Nucleo board and can be
    easily tailored to any other supported device and development board.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example


 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
