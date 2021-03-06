/**
  @page DAC_SimpleConversion DAC Simple Conversion example
  
  @verbatim
  ******************** (C) COPYRIGHT 2016 STMicroelectronics *******************
  * @file    DAC/DAC_SimpleConversion/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the DAC Simple Conversion example.
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

How to use the DAC peripheral to do a simple conversion.

STM32L073RZ-Nucleo Rev C board's LED can be used to monitor the process status:
  - LED2 is slowly blinking (1 sec. period) and example is stopped (using infinite loop)
  when there is an error during process.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The example needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - DAC/DAC_SimpleConversion/Inc/stm32l0xx_hal_conf.h    HAL configuration file
  - DAC/DAC_SimpleConversion/Inc/stm32l0xx_it.h          DMA interrupt handlers header file
  - DAC/DAC_SimpleConversion/Inc/main.h                  Header for main.c module  
  - DAC/DAC_SimpleConversion/Src/stm32l0xx_it.c          DMA interrupt handlers
  - DAC/DAC_SimpleConversion/Src/main.c                  Main program
  - DAC/DAC_SimpleConversion/Src/stm32l0xx_hal_msp.c     HAL MSP file
  - DAC/DAC_SimpleConversion/Src/system_stm32l0xx.c      STM32L0xx system source file
  

@par Hardware and Software environment  
  - This example runs on STM32L07xx and STM32L08xx devices.
    
  - This example has been tested with STM32L073RZ-Nucleo Rev C board and can be
    easily tailored to any other supported device and development board.

  - STM32L073RZ-Nucleo Rev C Set-up 	
    - Connect PA4 (pin 32 in CN7 connector)(DAC Channel1) pin to an oscilloscope.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example
  
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */

