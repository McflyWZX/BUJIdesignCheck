/*
 * JY61P.c
 *
 *  Created on: Feb 28, 2021
 *      Author: Abner
 */

#include <JY61P.h>

I2C_HandleTypeDef *mHi2c;

void Init(I2C_HandleTypeDef *hi2c);
float ReadAngle(uint8_t axis);

JY jy61p = {
  Init,
  ReadAngle
};

void Init(I2C_HandleTypeDef *hi2c)
{
  mHi2c = hi2c;
}

float ReadAngle(uint8_t axis)
{
  uint8_t data[2] = {0, 0};
  HAL_I2C_Mem_Read(mHi2c, JY_ADDR << 1, axis, 1, data, 2, 10000);
  return ((data[1] << 8) | data[0]) / 32768 * 180;
}
