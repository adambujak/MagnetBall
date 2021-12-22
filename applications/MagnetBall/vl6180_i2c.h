#ifndef VL6180_I2C_H_
#define VL6180_I2C_H_

#include "vl6180_platform.h"

int vl6180_i2c_init(void);

int VL6180_WrByte(VL6180Dev_t dev, uint16_t index, uint8_t data);

int VL6180_WrWord(VL6180Dev_t dev, uint16_t index, uint16_t data);

int VL6180_WrDWord(VL6180Dev_t dev, uint16_t index, uint32_t data);

int VL6180_UpdateByte(VL6180Dev_t dev, uint16_t index, uint8_t AndData, uint8_t OrData);

int VL6180_RdByte(VL6180Dev_t dev, uint16_t index, uint8_t *data);

int VL6180_RdWord(VL6180Dev_t dev, uint16_t index, uint16_t *data);

int  VL6180_RdDWord(VL6180Dev_t dev, uint16_t index, uint32_t *data);

int  VL6180_RdMulti(VL6180Dev_t dev, uint16_t index, uint8_t *data, int nData);

#endif /* VL6180_I2C_H_ */
