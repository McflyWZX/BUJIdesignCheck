#ifndef __PID_H_
#define __PID_H_

#include "stm32h7xx_hal.h"
#include "JY61P.h"
#include "tim.h"

/************************
 *      ^ Roll   /^\FRONT
 *      |         |
 *   2    1
 *    \  /
 *     \/    <--Pitch
 *     /\
 *    /  \
 *   3    4
 *  右手螺旋
 * **********************/
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define LIMIT(X,Y,Z)  MIN(MAX(X,Z),Y)  //X->最小值，Y->最大值

#define THROTTLE_MAX 	4000
#define THROTTLE_MIN	2000

//TODO: 确认以下语句
#define THROTTLE1(X) TIM5->CCR4 = (LIMIT(THROTTLE_MIN,THROTTLE_MAX,X))
#define THROTTLE2(X) TIM4->CCR2 = (LIMIT(THROTTLE_MIN,THROTTLE_MAX,X))
#define THROTTLE3(X) TIM4->CCR3 = (LIMIT(THROTTLE_MIN,THROTTLE_MAX,X))
#define THROTTLE4(X) TIM16->CCR1 = (LIMIT(THROTTLE_MIN,THROTTLE_MAX,X))

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
  float deltaT;
  PIDparams params[3];
  void (*Init)(float deltaT);
  void (*initParams)(uint8_t axis, float Kp, float Ki, float Kd, float LimitI);
  void (*updateCtrlFrame)(Atti nowAtti, Atti expectAtti, uint32_t throttle);
  void (*throttleInit)(uint8_t withCalibration);
  void (*throttleTest)(void);
} PIDctrler;

extern PIDctrler ctrler;

#endif
