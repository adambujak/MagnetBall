/**
  @page LPUART_WakeUpFromStop LPUART example
  
  @verbatim
  ******************** (C) COPYRIGHT 2016 STMicroelectronics *******************
  * @file    Examples_LL/LPUART/LPUART_WakeUpFromStop/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the LPUART_WakeUpFromStop LPUART example.
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
  
Configuration of GPIO and LPUART peripherals to allow characters 
received on LPUART_RX pin to wake up the MCU from low-power mode. This example is based 
on the LPUART LL API. The peripheral initialization uses LL unitary 
service functions for optimization purposes (performance and size).

LPUART Peripheral is configured in asynchronous mode (9600 bauds, 8 data bit, 1 start bit, 1 stop bit, no parity).
No HW flow control is used.
LPUART Clock is based on HSI.

Example execution:
After startup from reset and system configuration, LED2 is blinking quickly during 3 sec,
then MCU  enters Stop mode (LED2 off).
On first  character reception by the LPUART from PC Com port (ex: using HyperTerminal)
after Stop Mode period, MCU wakes up from Stop Mode.
Received character value is checked :
- On a specific value ('S' or 's'), LED2 is turned On and program ends.
- If different from 'S' or 's', program performs a quick LED2 blinks during 3 sec and 
  enters again Stop mode, waiting for next character to wake up.

In case of errors, LED2 is slowly blinking (1 sec period).

@par Directory contents 

  - LPUART/LPUART_WakeUpFromStop/Inc/stm32l0xx_it.h          Interrupt handlers header file
  - LPUART/LPUART_WakeUpFromStop/Inc/main.h                  Header for main.c module
  - LPUART/LPUART_WakeUpFromStop/Inc/stm32_assert.h          Template file to include assert_failed function
  - LPUART/LPUART_WakeUpFromStop/Src/stm32l0xx_it.c          Interrupt handlers
  - LPUART/LPUART_WakeUpFromStop/Src/main.c                  Main program
  - LPUART/LPUART_WakeUpFromStop/Src/system_stm32l0xx.c      STM32L0xx system source file

@par Hardware and Software environment

  - This example runs on STM32L073xx devices.

  - This example has been tested with STM32L073RZ-Nucleo Rev C board and can be
    easily tailored to any other supported device and development board.

  - STM32L073RZ-Nucleo Rev C Set-up
    - Connect STM32 MCU board LPUART1 TX pin (GPIO PC1 connected to pin 36 of CN7 connector)
      to PC COM port RX signal
    - Connect STM32 MCU board LPUART1 RX pin (GPIO PC0 connected to pin 38 of CN7 connector)
      to PC COM port TX signal
    - Connect STM32 MCU board GND to PC COM port GND signal

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
