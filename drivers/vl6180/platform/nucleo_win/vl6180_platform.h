/*******************************************************************************
 * Copyright © 2014, STMicroelectronics International N.V.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * Neither the name of STMicroelectronics nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND
 * NON-INFRINGEMENT OF INTELLECTUAL PROPERTY RIGHTS ARE DISCLAIMED.
 * IN NO EVENT SHALL STMICROELECTRONICS INTERNATIONAL N.V. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ********************************************************************************/


#ifndef VL6180_PLATFORM_H
#define VL6180_PLATFORM_H

#ifdef _MSC_VER
#   ifdef VL6180_API_EXPORTS
#       define VL6180_API    __declspec(dllexport)
#   else
#       define VL6180_API
#   endif
#else
#   define VL6180_API
#endif

/**
 * pebble Linux platform
 *
 * Pebble is a arm (cortex R4) based CortexR4 uclinux system
 * It can access up to 4 accessible vl6180 in multiple i2c bus
 * device i2c  is going true the cci-to i2c layer and /dev/i2cx bus ( may required root privilege)
 * device gpio are mape to linux gpio (sys/class/gpio/--- may require special or root privilege)
 *
 * refer to src/VL6180_PebbleLinux.c for more details
 */
#include "vl6180_def.h"
#include <stdlib.h>

/**
 * @def VL6180_RANGE_STATUS_ERRSTRING
 * @brief when define include range status Error string and related
 *
 * The string table lookup require some space in read only area
 * @ingroup Configuration
 */
#define VL6180_RANGE_STATUS_ERRSTRING    1

/**
 * @def VL6180_SAFE_POLLING_ENTER
 *
 * @brief Ensure safe polling method when set
 *
 * Polling for a condition can be hazardous and result in infinite looping if any previous interrupt status
 * condition is not cleared. \n
 * Setting these flags enforce error clearing on start of polling method to avoid it.
 * the drawback are : \n
 * @li extra use-less i2c bus usage and traffic
 * @li potentially slower measure rate.
 * If application ensure interrupt get clear on mode or interrupt configuration change
 * then keep option disabled. \n
 * To be safe set these option to 1
 * @ingroup Configuration
 */
#define VL6180_SAFE_POLLING_ENTER        0


/**
 * @brief Enable function start/end logging
 *
 * requires porting  @a #LOG_FUNCTION_START @a #LOG_FUNCTION_END @a #LOG_FUNCTION_END_FMT
 * @ingroup Configuration
 */
#define VL6180_LOG_ENABLE    0


#define VL6180_DEV_DATA_ATTR
#define ROMABLE_DATA

#define VL6180_SINGLE_DEVICE_DRIVER    0

#if VL6180_SINGLE_DEVICE_DRIVER
#error "Not suported set redef VL6180_SINGLE_DEVICE_DRIVER 0"
#endif

#define VL6180_RANGE_STATUS_ERRSTRING    1
#define VL6180X_SAFE_POLLING_ENTER       0

#define DEFAULT_RANGE_MAX_LOOP           200
#define DEFAULT_ALS_MAX_LOOP             1000

/**
 * @brief  multiple VL6180 Linux Device structure
 * @ingroup porting_multi
 */
struct MyVL6180Dev_t {
  struct VL6180DevData_t Data;         /*!< embed ST VL6180 Dev  data as "Data"*/
/* #error ADD HERE any extra device data         */
//pthread_mutex_t i2c_lock;

  int                    power_en_gpio; /*!< power enable gpio pin */
  int                    intr_gpio;     /*!< interrupt 1  gpio pin */
  int                    chip_en_gpio;  /*!< chip enable gpio pin  */
  int                    i2c_addr;      /*!< device i2c address on bus */

  int                    i2c_fd;        /*!< file descriptor  for device at current i2cbus @addr  */
  int                    i2c_bus;       /*!< device i2c bus number */

  char                  *name;          /*!< humane readable device "name"  ie "bayer ch 1" */

#if I2C_BUFFER_CONFIG == 2
  uint8_t                i2c_buffer[VL6180_MAX_I2C_XFER_SIZE]; /*!< Example per device i2c buffer declaration and it's accessing macro  */
    #define VL6180_GetI2cBuffer(dev, n)    ((dev)->i2c_buffer)
#endif

  /**
   * @def VL6180DevDataGet
   * @brief Get ST private structure @a VL6180DevData_t data access
   *
   * maybe used and as real data "ref" not just as "get" for sub-structure item
   * like VL6180DevDataGet(FilterData.field)[i] or VL6180DevDataGet(FilterData.MeasurementIndex)++
   * @ingroup porting_multi
   */
    #define VL6180DevDataGet(dev, field)          (dev->Data.field)

  /**
   * @def VL6180DevDataSet(dev, field, data)
   * @brief  Set ST private structure @a VL6180DevData_t data field
   * @param dev    The device
   * @param field  St structure field name
   * @param data   Data to set
   * @ingroup porting_multi
   */
    #define VL6180DevDataSet(dev, field, data)    (dev->Data.field) = (data)
};

typedef struct MyVL6180Dev_t *VL6180Dev_t;



/* is implemanted a a real fucntion */
void VL6180_PollDelay(VL6180Dev_t dev);

double getTimeSecs();


/**
 * I2C to CCI
 */
VL6180_API int VL6180_I2CWrite(VL6180Dev_t dev, uint8_t *buff, uint8_t len);
VL6180_API int VL6180_I2CRead(VL6180Dev_t dev, uint8_t *buff, uint8_t len);

VL6180_API int VL6180_i2c_init(VL6180Dev_t dev, char *comPortStr, unsigned int baudRate);
VL6180_API int VL6180_i2c_fini(VL6180Dev_t dev);
VL6180_API int VL6180_i2c_startLogging(VL6180Dev_t dev, char *);
VL6180_API int VL6180_i2c_stopLogging(VL6180Dev_t dev);

VL6180_API int VL6180_I2cRead(VL6180Dev_t dev, unsigned int reg, unsigned char *data, unsigned int length);
VL6180_API int VL6180_I2cWrite(VL6180Dev_t dev, unsigned int reg, unsigned char *data, unsigned int length);

VL6180_API int VL6180_GetErrorText(char *errorText);

#define VL6180_I2C_USER_VAR

void VL6180_GetI2CAccess(VL6180Dev_t dev);
void VL6180_DoneI2CAccess(VL6180Dev_t dev);



#if VL6180X_LOG_ENABLE
#include <sys/time.h>
#include <stdio.h>
extern FILE *log_file;

#define trace_printf      fprinf
#define LOG_GET_TIME()    clock()

#define LOG_FUNCTION_START(fmt, ...) \
  fprintf(log_file, "VL61080 beg %s start @%d\t" fmt "\n", __FUNCTION__, LOG_GET_TIME(), ## __VA_ARGS__)

#define LOG_FUNCTION_END(status) \
  fprintf(log_file, "VL61080  end %s @%d %d\n", __FUNCTION__, LOG_GET_TIME(), (int) status)

#define LOG_FUNCTION_END_FMT(status, fmt, ...) \
  fprintf(log_file, "End %s @%d %d\t"fmt "\n", __FUNCTION__, LOG_GET_TIME(), (int) status, ## __VA_ARGS__)

#define VL6180_ErrLog(fmt, ...)          fprintf(stderr, "VL6180_ErrLog %s" fmt "\n", __func__, ## __VA_ARGS__)

#else /* VL6180X_LOG_ENABLE no logging */
    #define LOG_FUNCTION_START(...)      (void) 0
    #define LOG_FUNCTION_END(...)        (void) 0
    #define LOG_FUNCTION_END_FMT(...)    (void) 0
    #define VL6180_ErrLog(...)           (void) 0
#endif /* else */

#endif  /* VL6180_PLATFORM_H */
