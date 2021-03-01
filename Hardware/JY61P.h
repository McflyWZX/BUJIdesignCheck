/*
 * JY61P.h
 *
 *  Created on: Feb 28, 2021
 *      Author: Abner
 */

#ifndef JY61P_H_
#define JY61P_H_

#include "stm32h7xx_hal.h"

#define 	JY_ADDR		0x50
#define		ROLL		0x3d
#define		PITCH		0x3e
#define		YAW			0x3f

typedef struct{
  void (*Init)(I2C_HandleTypeDef *hi2c);
  float (*ReadAngle)(uint8_t axis);
} JY;

extern JY jy61p;

#endif /* JY61P_H_ */
