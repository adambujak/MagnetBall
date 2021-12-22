/**
  @page RTC_Tamper RTC Tamper Example
  
  @verbatim
  ******************** (C) COPYRIGHT 2016 STMicroelectronics *******************
  * @file    RTC/RTC_Tamper/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the RTC Tamper example.
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

Configuration of the RTC HAL API to write/read data to/from RTC Backup registers. 
It also demonstrates the tamper detection feature.

- At the beginning of the main program the HAL_Init() function is called to reset 
  all the peripherals, initialize the Flash interface and the systick.
  Then the SystemClock_Config() function is used to configure the system
  clock (SYSCLK) to run at 2 MHz.

- The RTC peripheral configuration is ensured by the HAL_RTC_Init() function.
  This later is calling the HAL_RTC_MspInit() function which core is implementing
  the configuration of the needed RTC resources according to the used hardware (CLOCK, 
  PWR, RTC clock source and BackUp). You may update this function to change RTC configuration.

- LSE oscillator clock is used as RTC clock source by default.
  The user can use also LSI as RTC clock source. The user uncomment the adequate 
  define on the main.h file.

- HAL_RTCEx_SetTamper_IT() function is then called to initialize the Tamper with 
  interrupt mode. This function allows to erase or not the backup data registers
  after a Tamper detection through the NoErase and MaskFlag fields in the Tamper
  configuration.
  In this example the Backup registers should be erased.

The associated firmware performs the following:
1. It configures the Tamper pin to be falling edge, and enables the Tamper 
   interrupt.
2. It writes the data to all RTC Backup data registers, then check whether the 
   data were correctly written.
3. Applying a low level on the TAMPER1 pin (PC.13) by pressing Tamper push button,
   the RTC backup data registers are reset and the Tamper interrupt is generated. 
4. The corresponding ISR then checks whether the RTC Backup data registers are cleared. 
   If yes LED2 turns ON.
   
- LED2 is toggling : This indicates that the system generates an error.

@note Care must be taken when using HAL_Delay(), this function provides accurate
      delay (in milliseconds) based on variable incremented in SysTick ISR. This
      implies that if HAL_Delay() is called from a peripheral ISR process, then 
      the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The example needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents  

  - RTC/RTC_Tamper/Inc/stm32l0xx_hal_conf.h    HAL configuration file
  - RTC/RTC_Tamper/Inc/stm32l0xx_it.h          Interrupt handlers header file
  - RTC/RTC_Tamper/Inc/main.h                  Header for main.c module  
  - RTC/RTC_Tamper/Src/stm32l0xx_it.c          Interrupt handlers handlers
  - RTC/RTC_Tamper/Src/main.c                  Main program
  - RTC/RTC_Tamper/Src/stm32l0xx_hal_msp.c     HAL MSP module
  - RTC/RTC_Tamper/Src/system_stm32l0xx.c      STM32L0xx system source file


@par Hardware and Software environment

  - This example runs on STM32L051xx, STM32L052xx, STM32L053xx STM32L062xx and 
    STM32L063xx device lines RevZ

  - This example has been tested with STM32L053R8-Nucleo RevC  board and can be
    easily tailored to any other supported device and development board.

  - STM32L053R8-Nucleo Set-up
    - Use LED2 connected to PA.05 pin
    - Use KEY push button connected to PC.13 pin


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example


 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
 