#include "PID.h"

void initPID(float deltaT);
void initParams(uint8_t axis, float Kp, float Ki, float Kd, float LimitI);
void updateCtrlFrame(Atti nowAtti, Atti expectAtti);
void throttleInit();
void throttleTest();

PIDctrler ctrler = {
  0,
  {{0}, {0}, {0}},
  initPID,
  initParams,
  updateCtrlFrame,
  throttleInit,
  throttleTest
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

void throttleTest()
{
  uint32_t throttle = THROTTLE_MIN;
  int8_t dir = +1;
  while(1)
  {
    HAL_Delay(100);
    throttle += (THROTTLE_MAX - THROTTLE_MIN) / 100 * dir;
    THROTTLE1(throttle);
	  THROTTLE2(throttle);
	  THROTTLE3(throttle);
	  THROTTLE4(throttle);
    if(throttle <= THROTTLE_MIN || throttle >= (THROTTLE_MAX * 3 / 4))dir = -dir;
  }
}

void initPID(float deltaT)
{
  ctrler.deltaT = deltaT;
}

/**
  * @brief  初始化一个轴向的控制器参数.
  * @param  axis: 轴向，例如:PARAM_ROLL
  * @param  Kp: 比例控制器的K.
  * @param  Ki: 积分控制器的K.
  * @param  Kd: 微分控制器的K.
  * @param  LimitI: 积分限幅，正数.
  * @retval None
  */
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
/**
  * @brief  控制量更新一次.
  * @param  nowAtti: 当前姿态.
  * @param  expectAtti: 期望姿态.
  * @retval None
  */
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
    //积分限幅
    ctrler.params[i].Integral = LIMIT(-ctrler.params[i].LimitI, ctrler.params[i].LimitI, ctrler.params[i].Integral);
    //输出计算
    Out[i] = ctrler.params[i].Kp * error[i] + ctrler.params[i].Ki * ctrler.params[i].Integral - ctrler.params[i].Kd * gyro[i];
  }
  THROTTLE1( - Out[PARAM_ROLL] + Out[PARAM_PITCH]);
  THROTTLE2( + Out[PARAM_ROLL] + Out[PARAM_PITCH]);
  THROTTLE3( + Out[PARAM_ROLL] - Out[PARAM_PITCH]);
  THROTTLE4( - Out[PARAM_ROLL] - Out[PARAM_PITCH]);
}

