#ifndef __PID_H_
#define __PID_H_

#include "stm32h7xx_hal.h"
#include "JY61P.h"

/************************
 *      ^ Roll   /^\FRONT
 *      |         |
 *   2    1
 *    \  /
 *     \/    -->Pitch
 *     /\
 *    /  \
 *   3    4
 *  右手螺旋
 * **********************/
//TODO: 确认以下语句
#define THROTTLE1(X) TIM3->CCR3 = (X)
#define THROTTLE2(X) TIM3->CCR3 = (X)
#define THROTTLE3(X) TIM3->CCR3 = (X)
#define THROTTLE4(X) TIM3->CCR3 = (X)

#define PARAM_ROLL    0
#define PARAM_PITCH   1
#define PARAM_YAW     2

typedef struct {
  float Kp;
  float Ki;
  float Kd;
  float LimitI;
  float Integral;
} PIDparams;

typedef struct {
  uint32_t throttleMax;
  uint32_t throttleMin;
  float deltaT;
  PIDparams params[3];
  void (*Init)(float Kp, float Ki, float Kd, float LimitI, float deltaT, uint32_t throttleMax, uint32_t throttleMin);
  void (*initParams)(uint8_t axis, float Kp, float Ki, float Kd, float LimitI);
  void (*updateCtrlFrame)(Atti nowAtti, Atti expectAtti);
} PIDctrler;

extern PIDctrler ctrler;

#endif