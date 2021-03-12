#include "PID.h"

void initPID(float deltaT);
void initParams(uint8_t axis, float Kp, float Ki, float Kd, float LimitI);
void updateCtrlFrame(Atti nowAtti, Atti expectAtti);

PIDctrler ctrler = {
  0,
  {{0}, {0}, {0}},
  initPID,
  initParams,
  updateCtrlFrame
};

void throttleInit()
{
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);

	HAL_Delay(100);
	THROTTLE1(THROTTLE_MAX);
	THROTTLE2(THROTTLE_MAX);
	THROTTLE3(THROTTLE_MAX);
	THROTTLE4(THROTTLE_MAX);
	HAL_Delay(3000);
	THROTTLE1(THROTTLE_MIN);
	THROTTLE2(THROTTLE_MIN);
	THROTTLE3(THROTTLE_MIN);
	THROTTLE4(THROTTLE_MIN);
	HAL_Delay(2000);
}



void initPID(float deltaT)
{
  ctrler.deltaT = deltaT;
}

void initParams(uint8_t axis, float Kp, float Ki, float Kd, float LimitI)
{
  ctrler.params[axis].Kp = Kp;
  ctrler.params[axis].Ki = Ki;
  ctrler.params[axis].Kd = Kd;
  ctrler.params[axis].LimitI = LimitI;
  ctrler.params[axis].Integral = 0;
}

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
void updateCtrlFrame(Atti nowAtti, Atti expectAtti)
{
  float Out[3];
  float error[3] = {expectAtti.roll - nowAtti.roll, 
                    expectAtti.pitch - nowAtti.pitch, 
                    expectAtti.yaw - nowAtti.yaw};
  float gyro[3] = {nowAtti.gx, nowAtti.gy, nowAtti.gz}; //TODO: 顺序待测
  for (uint32_t i = 0; i < 3; i++)
  {
    ctrler.params[i].Integral += error[i] * ctrler.deltaT;
    Out[i] = ctrler.params[i].Kp * error[i] + ctrler.params[i].Ki * ctrler.params[i].Integral - ctrler.params[i].Kd * gyro[i];
  }
  THROTTLE1( - Out[PARAM_ROLL] + Out[PARAM_PITCH]);
  THROTTLE2( + Out[PARAM_ROLL] + Out[PARAM_PITCH]);
  THROTTLE3( + Out[PARAM_ROLL] - Out[PARAM_PITCH]);
  THROTTLE4( - Out[PARAM_ROLL] - Out[PARAM_PITCH]);
}

