/**
  @page I2C_TwoBoards_MasterRx_SlaveTx_IT I2C example (IT Mode)
  
  @verbatim
  ******************** (C) COPYRIGHT 2016 STMicroelectronics *******************
  * @file    Examples_LL/I2C/I2C_TwoBoards_MasterRx_SlaveTx_IT/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the I2C_TwoBoards_MasterRx_SlaveTx_IT I2C example (IT Mode).
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
  
How to handle the reception of one data byte from an I2C slave device 
by an I2C master device. Both devices operate in interrupt mode. The peripheral is initialized 
with LL unitary service functions to  optimize for performance and size.


This example guides you through the different configuration steps by mean of LL API
to configure GPIO and I2C peripherals using two STM32L073RZ-Nucleo Rev C.

Boards: STM32L073RZ-Nucleo Rev C (embeds a STM32L073RZ device)
SCL Pin: PC.0 (CN7, pin 38)
SDA Pin: PC.1 (CN7, pin 36)

   ______BOARD SLAVE_____                       _____BOARD MASTER_____
  |        ______________|                     |______________        |
  |       |I2C3          |                     |          I2C3|       |
  |       |              |                     |              |       |
  |       |          SCL |_____________________| SCL          |       |
  |       |              |                     |              |       |
  |       |              |                     |              |       |
  |       |          SDA |_____________________| SDA          |       |
  |       |______________|                     |______________|       |
  |         __           |                     |             __       |
  |        |__|          |                     |            |__|      |
  |        USER       GND|_____________________|GND         USER      |
  |___STM32L0xx_Nucleo___|                     |___STM32L0xx_Nucleo___|

The project is splitted in two parts the Master Board and the Slave Board
- Master Board
  I2C3 Peripheral is configured in Master mode with EXTI (Standard Mode @100kHz).
And GPIO associated to User push-button is linked with EXTI. 
- Slave Board
  I2C3 Peripheral is configured in Slave mode with EXTI (Standard Mode @100kHz, Own address 7-bit enabled).

The user can choose between Master and Slave through "#define SLAVE_BOARD"
in the "main.h" file:
- Comment "#define SLAVE_BOARD" to select Master board.
- Uncomment "#define SLAVE_BOARD" to select Slave board.

LED2 blinks quickly on BOARD MASTER to wait for user-button press. 

Example execution:
Press the User push-button on BOARD MASTER to initiate a read request by Master.
This action will generate an I2C start condition with the Slave address and a read bit condition.
When address Slave match code is received on I2C3 of BOARD SLAVE, an ADDR interrupt occurs.
I2C3 Slave IRQ Handler routine is then checking Address Match Code and direction Read.
This will allow Slave to enter in transmitter mode and then send a byte when TXIS interrupt occurs.
When byte is received on I2C3 of BOARD MASTER, an RXNE interrupt occurs.
When RXDR register is read, Master auto-generate a NACK and STOP condition
to inform the Slave that the transfer is finished.
The NACK condition generate a NACK interrupt in Slave side treated in the I2C3 Slave IRQ handler routine by a clear of NACK flag.
The STOP condition generate a STOP interrupt in both side (Slave and Master). Both I2C3 IRQ handler routine are then
clearing the STOP flag in both side.

LED2 is On :
- Slave side if transfer sequence is completed.
- Master side if data is well received.

In case of errors, LED2 is blinking.

@par Directory contents 

  - I2C/I2C_TwoBoards_MasterRx_SlaveTx_IT/Inc/stm32l0xx_it.h          Interrupt handlers header file
  - I2C/I2C_TwoBoards_MasterRx_SlaveTx_IT/Inc/main.h                  Header for main.c module
  - I2C/I2C_TwoBoards_MasterRx_SlaveTx_IT/Inc/stm32_assert.h          Template file to include assert_failed function
  - I2C/I2C_TwoBoards_MasterRx_SlaveTx_IT/Src/stm32l0xx_it.c          Interrupt handlers
  - I2C/I2C_TwoBoards_MasterRx_SlaveTx_IT/Src/main.c                  Main program
  - I2C/I2C_TwoBoards_MasterRx_SlaveTx_IT/Src/system_stm32l0xx.c      STM32L0xx system source file

@par Hardware and Software environment

  - This example runs on STM32L073xx devices.
    
  - This example has been tested with STM32L073RZ-Nucleo Rev C board and can be
    easily tailored to any other supported device and development board.

  - STM32L073RZ-Nucleo Rev C Set-up
    - Connect GPIOs connected to Board Slave I2C3 SCL/SDA (PC.0 and PC.1)
    to respectively Board Master SCL and SDA pins of I2C3 (PC.0 and PC.1).
      - I2C3_SCL  PC.0 (CN7, pin 38) : connected to I2C3_SCL PC.0 (CN7, pin 38) 
      - I2C3_SDA  PC.1 (CN7, pin 36) : connected to I2C3_SDA PC.1 (CN7, pin 36)
    - Connect Master board GND to Slave Board GND

  - Launch the program. Press User push-button to initiate a read request by Master 
      then Slave send a byte.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory (The user can choose between Master 
   and Slave target through "#define SLAVE_BOARD" in the "main.h" file)
    o Comment "#define SLAVE_BOARD" and load the project in Master Board
    o Uncomment "#define SLAVE_BOARD" and load the project in Slave Board
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
