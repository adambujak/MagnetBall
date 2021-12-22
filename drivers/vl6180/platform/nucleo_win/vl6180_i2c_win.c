/*******************************************************************************
 ################################################################################
 #                             (C) STMicroelectronics 2014
 #
 # This program is free software; you can redistribute it and/or modify it under
 # the terms of the GNU General Public License version 2 and only version 2 as
 # published by the Free Software Foundation.
 #
 # This program is distributed in the hope that it will be useful, but WITHOUT
 # ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 # FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 # details.
 #
 # You should have received a copy of the GNU General Public License along with
 # this program; if not, write to the Free Software Foundation, Inc.,
 # 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 #
 #------------------------------------------------------------------------------
 #                             Imaging Division
 ################################################################################
 ********************************************************************************/

/**
 * @file vl6180_i2c.c
 *
 * Copyright (C) 2014 ST MicroElectronics
 *
 * provide variable word size byte/Word/dword VL6180 register access via i2c
 *
 */
#include "vl6180_platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "SERIAL_COMMS.h"

#if I2C_BUFFER_CONFIG == 0
/* GLOBAL config buffer */
uint8_t i2c_global_buffer[VL6180_MAX_I2C_XFER_SIZE];

    #define DECL_I2C_BUFFER
    #define VL6180_GetI2cBuffer(dev, n_byte)    i2c_global_buffer

#elif I2C_BUFFER_CONFIG == 1
/* ON STACK */
    #define DECL_I2C_BUFFER                     uint8_t LocBuffer[VL6180_MAX_I2C_XFER_SIZE];
    #define VL6180_GetI2cBuffer(dev, n_byte)    LocBuffer
#elif I2C_BUFFER_CONFIG == 2
/* user define buffer type declare DECL_I2C_BUFFER  as access  via VL6180_GetI2cBuffer */
    #define DECL_I2C_BUFFER
#else
#error "invalid I2C_BUFFER_CONFIG "
#endif

#define VL6180_MAX_STR_SIZE    255
#define VL6180_MAX_MSG_SIZE    100
#define VL6180_MAX_DEVICES     4
#define VL6180X_STATUS_OK      0
#define VL6180X_STATUS_FAIL    1

FILE *log_file = NULL;
int logging = 0;

int VL6180_i2c_fini(VL6180Dev_t dev);
void outputWriteMsg(unsigned int reg, unsigned char *byteArray, int length);
void outputReadMsg(unsigned int reg, unsigned char *byteArray, int length);
void array2HexCString(unsigned char *byteArray, int length, char *str, int strLenMax);

static HANDLE ghMutex;

static unsigned char _dataBytes[VL6180_MAX_MSG_SIZE];
static char _argv[7][VL6180_MAX_STR_SIZE];

int VL6180_i2c_init(VL6180Dev_t dev, char *comPortStr, unsigned int baudRate)
{
  const int cArgc = 7;
  int argc = cArgc;
  unsigned int deviceCount = 0;
  unsigned int comPortId = 0;
  char errorText[VL6180_MAX_STR_SIZE];
  unsigned char devIds[VL6180_MAX_DEVICES];
  unsigned int status = VL6180X_STATUS_FAIL;
  char comPortTmpStr[VL6180_MAX_STR_SIZE] = "";
  char baudRateTmpStr[VL6180_MAX_STR_SIZE] = "";
  char tmpStr[VL6180_MAX_STR_SIZE] = "";
  //static char argv[7][VL6180_MAX_STR_SIZE];
  int i = 0;
  DWORD dwWaitResult;
  char **argv = NULL;
  int ownsMutex = 0;


  if (ghMutex == NULL) {
    ghMutex = CreateMutex(NULL, FALSE, NULL);
  }

  dwWaitResult = WaitForSingleObject(ghMutex, INFINITE);

  if (dwWaitResult == WAIT_OBJECT_0) {
    ownsMutex = 1;
    argv = (char **) malloc(cArgc * sizeof(char *));
    for (i = 0; i < cArgc; i++) {
      argv[i] = (char *) malloc(VL6180_MAX_STR_SIZE);
      argv[i][0] = (char) '\0';
    }

    sscanf_s(comPortStr, "COM%d", &comPortId);


    status = SERIAL_COMMS_Enum_Devices(VL6180_MAX_DEVICES, devIds, &deviceCount);
    if (status != VL6180X_STATUS_OK) {
      SERIAL_COMMS_Get_Error_Text(errorText);
    }
    else{
      sprintf_s(comPortTmpStr, VL6180_MAX_STR_SIZE, "COM_PORT=%d", comPortId);
      sprintf_s(baudRateTmpStr, VL6180_MAX_STR_SIZE, "BAUD_RATE=%d", baudRate);

      strncpy_s(argv[0], VL6180_MAX_STR_SIZE, comPortTmpStr, VL6180_MAX_STR_SIZE);
      strncpy_s(argv[1], VL6180_MAX_STR_SIZE, baudRateTmpStr, VL6180_MAX_STR_SIZE);
      strncpy_s(argv[2], VL6180_MAX_STR_SIZE, "READ_TIMEOUT_PER_BYTE_MS=10", VL6180_MAX_STR_SIZE);
      strncpy_s(argv[3], VL6180_MAX_STR_SIZE, "REPLY_TIMEOUT_MS=100", VL6180_MAX_STR_SIZE);
      strncpy_s(argv[4], VL6180_MAX_STR_SIZE, "REPLY_TERMINATOR=u-boot> ", VL6180_MAX_STR_SIZE);
      strncpy_s(argv[5], VL6180_MAX_STR_SIZE, "ALIGN_STRICT=0", VL6180_MAX_STR_SIZE);
      strncpy_s(argv[6], VL6180_MAX_STR_SIZE, "FLUSH_ON_ERROR=1", VL6180_MAX_STR_SIZE);

      status = SERIAL_COMMS_Init_UBOOT((unsigned int) devIds[0], argc, argv);
      if (status != VL6180X_STATUS_OK) {
        SERIAL_COMMS_Get_Error_Text(errorText);
        ReleaseMutex(ghMutex);
        ownsMutex = 0;
        VL6180_i2c_fini(dev);
      }
    }

    for (i = 0; i < cArgc; i++) {
      free(argv[i]);
    }
    free(argv);
  }
  else{
    status = VL6180X_STATUS_FAIL;
  }

  if (ownsMutex) {
    ReleaseMutex(ghMutex);
  }

  return status;
}

int VL6180_GetErrorText(char *errorText)
{
  unsigned int status = VL6180X_STATUS_OK;

  status = SERIAL_COMMS_Get_Error_Text(errorText);
  return status;
}

int VL6180_i2c_fini(VL6180Dev_t dev)
{
  DWORD dwWaitResult;
  unsigned int status = VL6180X_STATUS_FAIL;
  char errorText[VL6180_MAX_STR_SIZE];

  dwWaitResult = WaitForSingleObject(ghMutex, INFINITE);
  if (dwWaitResult == WAIT_OBJECT_0) {
    status = SERIAL_COMMS_Fini_UBOOT();
    if (status != VL6180X_STATUS_OK) {
      SERIAL_COMMS_Get_Error_Text(errorText);
    }
    ReleaseMutex(ghMutex);
  }

  CloseHandle(ghMutex);
  ghMutex = NULL;

  return status;
}

int VL6180_i2c_startLogging(VL6180Dev_t dev, char *logFile)
{
  unsigned int retVal = 0;

  fopen_s(&log_file, logFile, "w");
  if (log_file != NULL) {
    logging = 1;
  }
  return retVal;
}

int VL6180_i2c_stopLogging(VL6180Dev_t dev)
{
  unsigned int retVal = 0;

  if (log_file != NULL) {
    fclose(log_file);
    log_file = NULL;
    logging = 0;
  }
  return retVal;
}

int VL6180_I2cWrite(VL6180Dev_t dev, unsigned int reg, unsigned char *data, unsigned int length)
{
  unsigned int retries = 3;
  unsigned int retVal;
  DWORD dwWaitResult;
  char errorText[VL6180_MAX_STR_SIZE];

  dwWaitResult = WaitForSingleObject(ghMutex, INFINITE);
  if (dwWaitResult == WAIT_OBJECT_0) {
    do{
      retVal = SERIAL_COMMS_Write_UBOOT(dev->i2c_addr, 0, reg, data, length);
      // note : the field dwIndexHi is ignored. dwIndexLo will
      // contain the entire index (bits 0..15).
      if (retVal != VL6180X_STATUS_OK) {
        SERIAL_COMMS_Get_Error_Text(errorText);
        if (logging) {
          fprintf_s(log_file, "Write Reg %#06x Failed : %s\n", reg, errorText);
        }
      }
    } while ((retVal != 0) && (retries-- > 0));
    ReleaseMutex(ghMutex);
  }
  if (logging) {
    outputWriteMsg(reg, data, length);
  }
  return retVal;
}

int VL6180_I2cRead(VL6180Dev_t dev, unsigned int reg, unsigned char *data, unsigned int length)
{
  unsigned int retries = 3;
  unsigned int retVal;
  DWORD dwWaitResult;
  char errorText[VL6180_MAX_STR_SIZE];

  dwWaitResult = WaitForSingleObject(ghMutex, INFINITE);
  if (dwWaitResult == WAIT_OBJECT_0) {
    do{
      retVal = SERIAL_COMMS_Read_UBOOT(dev->i2c_addr, 0, reg, data, length);
      if (retVal != VL6180X_STATUS_OK) {
        SERIAL_COMMS_Get_Error_Text(errorText);
        if (logging) {
          fprintf_s(log_file, "Read Reg %#06x Failed : %s\n", reg, errorText);
        }
      }
    } while ((retVal != 0) && (retries-- > 0));
    ReleaseMutex(ghMutex);
  }

  if (logging) {
    outputReadMsg(reg, data, length);
  }
  return retVal;
}

int VL6180_WrByte(VL6180Dev_t dev, uint16_t index, uint8_t data)
{
  return VL6180_I2cWrite(dev, index, &data, 1);
}

int VL6180_WrWord(VL6180Dev_t dev, uint16_t index, uint16_t dataWord)
{
  static const uint16_t cBitsPerByte = 8;
  static const int cDataSize = 2;
  unsigned int retVal = 0;

  _dataBytes[1] = (unsigned char) (dataWord & 0xff);
  _dataBytes[0] = (unsigned char) ((dataWord & (uint16_t) 0xff00) >> cBitsPerByte);

  retVal = VL6180_I2cWrite(dev, index, _dataBytes, cDataSize);

  return retVal;
}

int VL6180_WrDWord(VL6180Dev_t dev, uint16_t index, uint32_t dataWord)
{
  static const int cBitsPerByte = 8;
  static const int cDataSize = 4;
  unsigned int retVal = 0;

  _dataBytes[3] = (unsigned char) (dataWord & 0xff);
  _dataBytes[2] = (unsigned char) ((dataWord & 0xff00) >> cBitsPerByte);
  _dataBytes[1] = (unsigned char) ((dataWord & 0x00ff0000) >> cBitsPerByte * 2);
  _dataBytes[0] = (unsigned char) ((dataWord & 0xff000000) >> cBitsPerByte * 3);

  retVal = VL6180_I2cWrite(dev, index, _dataBytes, cDataSize);

  return retVal;
}

int VL6180_UpdateByte(VL6180Dev_t dev, uint16_t index, uint8_t AndData, uint8_t OrData)
{
  int status = 0;

  return status;
}

int VL6180_RdMulti(VL6180Dev_t dev, uint16_t index, uint8_t *data, int nData)
{
  return VL6180_I2cRead(dev, index, data, nData);
}

int VL6180_RdByte(VL6180Dev_t dev, uint16_t index, uint8_t *data)
{
  return VL6180_I2cRead(dev, index, data, 1);
}

int VL6180_RdWord(VL6180Dev_t dev, uint16_t index, uint16_t *data)
{
  static const int cBitsPerByte = 8;
  static const int cDataSize = 2;
  int retVal = VL6180_I2cRead(dev, index, _dataBytes, cDataSize);

  *data = (_dataBytes[0] << cBitsPerByte) | _dataBytes[1];

  return retVal;
}

int  VL6180_RdDWord(VL6180Dev_t dev, uint16_t index, uint32_t *data)
{
  static const int cBitsPerByte = 8;
  static const int cDataSize = 4;
  int retVal = VL6180_I2cRead(dev, index, _dataBytes, cDataSize);

  *data = (((uint32_t) _dataBytes[0] << cBitsPerByte * 3) |
           ((uint32_t) _dataBytes[1] << cBitsPerByte * 2) |
           ((uint32_t) _dataBytes[2] << cBitsPerByte) |
           ((uint32_t) _dataBytes[3]));

  return retVal;
}

void VL6180_PollDelay(VL6180Dev_t dev)
{
  const DWORD cTimeout_ms = 1;
  HANDLE hEvent = CreateEvent(0, TRUE, FALSE, 0);

  if (hEvent != NULL) {
    DWORD dwWait = WaitForSingleObject(hEvent, cTimeout_ms);
  }
}

double getTimeSecs()
{
  clock_t clockTicks = clock();

  return clockTicks / (double) CLOCKS_PER_SEC;
}

void outputReadMsg(unsigned int reg,
                   unsigned char *byteArray,
                   int length)
{
  char outStr[VL6180_MAX_STR_SIZE];

  array2HexCString(byteArray, length, outStr, VL6180_MAX_STR_SIZE);
  fprintf_s(log_file, "Read Reg %#06x %s\n", reg, outStr);
  fflush(log_file);
}

void outputWriteMsg(unsigned int reg,
                    unsigned char *byteArray,
                    int length)
{
  char outStr[VL6180_MAX_STR_SIZE];

  array2HexCString(byteArray, length, outStr, VL6180_MAX_STR_SIZE);
  fprintf_s(log_file, "Write Reg %#06x %s\n", reg, outStr);
  fflush(log_file);
}

void array2HexCString(unsigned char *byteArray,
                      int length,
                      char *str,
                      int strLenMax)
{
  const int cMaxStr = 10;
  char tmpStr[10];
  int i = 0;

  sprintf_s(str, strLenMax, "0x");
  for (i = 0; i < length; i++) {
    sprintf_s(tmpStr, cMaxStr, "%02x", byteArray[i]);
    strcat_s(str, strLenMax, tmpStr);
  }
}
