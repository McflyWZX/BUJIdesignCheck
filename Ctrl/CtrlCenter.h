/*
 * @Author: Mcfly
 * @Date: 2021-04-18 20:52:53
 * @LastEditTime: 2021-04-19 15:28:16
 * @LastEditors: Mcfly
 * @Description: 
 * @FilePath: \BUJIdesignCheck\Ctrl\CtrlCenter.h
 * 本人github:https://github.com/McflyWZX
 */
#ifndef __CTRLCENTER_H_
#define __CTRLCENTER_H_

#include "stm32h7xx_hal.h"
#include "tim.h"
#include "main.h"
#include "PID.h"
#include "i2c.h"
#include "OV2640.h"
#include "GPS.h"
#include "JY61P.h"
#include "TestUartComm.h"
#include "VirtualOscTx.h"

typedef struct {
  void (*init)();
} CtrlCent;

extern CtrlCent ctrlCent;

#endif
