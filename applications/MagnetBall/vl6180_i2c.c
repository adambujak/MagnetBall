#include "i2c.h"
#include "vl6180_i2c.h"

static i2c_t i2c_instance;

#define SLAVE_ADDR    0x52

static void hw_init(void)
{
  IMU_I2C_CLK_EN();
  IMU_I2C_GPIO_CLK_EN();

  LL_GPIO_InitTypeDef gpio_config = { 0 };

  gpio_config.Pin = IMU_I2C_SCL_PIN | IMU_I2C_SDA_PIN;
  gpio_config.Mode = LL_GPIO_MODE_ALTERNATE;
  gpio_config.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_config.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  gpio_config.Pull = LL_GPIO_PULL_NO;
  gpio_config.Alternate = IMU_I2C_GPIO_AF;
  LL_GPIO_Init(IMU_I2C_GPIO_PORT, &gpio_config);

  LL_I2C_InitTypeDef i2c_config = { 0 };

  i2c_config.PeripheralMode = LL_I2C_MODE_I2C;
  i2c_config.Timing = 0x00300F38;
  i2c_config.AnalogFilter = LL_I2C_ANALOGFILTER_ENABLE;
  i2c_config.DigitalFilter = 0;
  i2c_config.OwnAddress1 = 0;
  i2c_config.TypeAcknowledge = LL_I2C_ACK;
  i2c_config.OwnAddrSize = LL_I2C_OWNADDRESS1_7BIT;

  i2c_init(&i2c_instance, IMU_I2C, &i2c_config);
}

static int VL6180_I2CWrite(uint16_t index, uint8_t *data, uint8_t length)
{
  return i2c_write(&i2c_instance, SLAVE_ADDR, index, data, (uint16_t) length);
}

static int VL6180_I2CRead(uint16_t index, uint8_t *data, uint8_t length)
{
  return i2c_read(&i2c_instance, SLAVE_ADDR, index, data, (uint16_t) length);
}

int vl6180_i2c_init(void)
{
  hw_init();
  return 0;
}

int VL6180_WrByte(VL6180Dev_t dev, uint16_t index, uint8_t data)
{
  return VL6180_I2CWrite(index, &data, 1);
}

int VL6180_WrWord(VL6180Dev_t dev, uint16_t index, uint16_t data)
{
  uint8_t buffer[2];

  buffer[0] = data >> 8;
  buffer[1] = data & 0xFF;

  return VL6180_I2CWrite(index, buffer, 2);
}

int VL6180_WrDWord(VL6180Dev_t dev, uint16_t index, uint32_t data)
{
  uint8_t buffer[4];

  buffer[0] = data >> 24;
  buffer[1] = (data >> 16) & 0xFF;
  buffer[2] = (data >> 8) & 0xFF;;
  buffer[3] = data & 0xFF;

  return VL6180_I2CWrite(index, buffer, 4);
}

int VL6180_UpdateByte(VL6180Dev_t dev, uint16_t index, uint8_t AndData, uint8_t OrData)
{
  int status = 0;
  uint8_t buffer;

  status = VL6180_I2CRead(index, &buffer, 1);

  if (!status) {
    buffer = (buffer & AndData) | OrData;

    status = VL6180_I2CWrite(index, &buffer, 1);
  }

  return status;
}

int VL6180_RdByte(VL6180Dev_t dev, uint16_t index, uint8_t *data)
{
  int status;
  uint8_t buffer;

  status = VL6180_I2CRead(index, &buffer, 1);

  if (!status) {
    *data = buffer;
  }

  return status;
}

int VL6180_RdWord(VL6180Dev_t dev, uint16_t index, uint16_t *data)
{
  int status;
  uint8_t buffer[2];

  status = VL6180_I2CRead(index, buffer, 2);

  if (!status) {
    *data = ((uint16_t) buffer[0] << 8) | (uint16_t) buffer[1];
  }

  return status;
}

int  VL6180_RdDWord(VL6180Dev_t dev, uint16_t index, uint32_t *data)
{
  int status;
  uint8_t buffer[4];

  status = VL6180_I2CRead(index, buffer, 4);

  if (!status) {
    *data =
      ((uint32_t) buffer[0] <<
        24) | ((uint32_t) buffer[1] << 16) | ((uint32_t) buffer[2] << 8) | ((uint32_t) buffer[3]);
  }

  return status;
}

int  VL6180_RdMulti(VL6180Dev_t dev, uint16_t index, uint8_t *data, int nData)
{
  int status;

  status = VL6180_I2CRead(index, data, nData);
  return status;
}
