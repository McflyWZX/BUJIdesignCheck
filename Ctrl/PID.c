#include "PID.h"

PIDctrler ctrler = {
  0, 
  0, 
  0,
  {0},
  init
};

void init(float deltaT, uint32_t throttleMax, uint32_t throttleMin)
{
  ctrler.throttleMax = throttleMax;
  ctrler.throttleMin = throttleMin;
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

