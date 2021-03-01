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
Atti getAtti();

JY jy61p = {
  Init,
  ReadAngle,
  getAtti,
  {0.0f, 0.0f, 0.0f}
};

void Init(I2C_HandleTypeDef *hi2c)
{
  mHi2c = hi2c;
}

float ReadAngle(uint8_t axis)
{
  uint8_t data[2] = {0, 0};
  HAL_I2C_Mem_Read(mHi2c, JY_ADDR << 1, axis, 1, data, 2, 10000);
  return ((data[1] << 8) | data[0]) / 32768.0f * 180;
}

Atti getAtti()
{
	jy61p.atti.pitch = jy61p.ReadAngle(PITCH);
	jy61p.atti.roll = jy61p.ReadAngle(ROLL);
	jy61p.atti.yaw = jy61p.ReadAngle(YAW);
	return jy61p.atti;
}
