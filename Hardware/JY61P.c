/*
 * JY61P.c
 *
 *  Created on: Feb 28, 2021
 *      Author: Abner
 */

#include <JY61P.h>

void initJY61P(I2C_HandleTypeDef *hi2c);
float readAngle(uint8_t axis);

I2C_HandleTypeDef *mHi2c;


Atti getAtti();

JY jy61p = {
  initJY61P,
  readAngle,
  getAtti,
  {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}
};

/**
  * @brief  初始JY61P.
  * @param  hi2c: I2C_HandleTypeDef结构体，表示JY61P使用的I2C端口
  * @retval None
  */
void initJY61P(I2C_HandleTypeDef *hi2c)
{
  mHi2c = hi2c;
}

/**
  * @brief  读取一个轴的角度值.
  * @param  axis: 表示希望读取的轴向，如：ROLL
  * @retval 角度值
  */
float readAngle(uint8_t axis)
{
  uint8_t data[2] = {0, 0};
  HAL_I2C_Mem_Read(mHi2c, JY_ADDR << 1, axis, 1, data, 2, 10000);
  return ((data[1] << 8) | data[0]) / 32768.0f * 180;
}

/**
  * @brief  获取当前姿态.
  * @retval 当前姿态结构体.
  */
Atti getAtti()
{
	jy61p.atti.pitch = jy61p.ReadAngle(PITCH);
	jy61p.atti.roll = jy61p.ReadAngle(ROLL);
  if(jy61p.atti.roll >= 180)
    jy61p.atti.roll -= 360;
  jy61p.atti.yaw = jy61p.ReadAngle(YAW);
  jy61p.atti.gx = jy61p.ReadAngle(GX);
  jy61p.atti.gy = jy61p.ReadAngle(GY);
  jy61p.atti.gz = jy61p.ReadAngle(GZ);
	return jy61p.atti;
}
