/*
 * @Author: Mcfly
 * @Date: 2021-04-18 20:52:53
 * @LastEditTime: 2021-04-22 09:51:12
 * @LastEditors: Mcfly
 * @Description: 
 * @FilePath: \BUJIdesignCheck\Ctrl\CtrlCenter.c
 * 本人github:https://github.com/McflyWZX
 */
#include "CtrlCenter.h"

#define debugVOSCchannels 3
float debugVOSCDatas[debugVOSCchannels];
uint8_t skipTimes = 5, skipCount = 0;

void initCtrlCenter();

CtrlCent ctrlCent = {
    initCtrlCenter
    };

/**
  * @brief  初始化控制程序，启动定时器控制循环.
  * @retval None
  */
void initCtrlCenter()
{
  ctrler.throttleInit(0);
  //ctrler.throttleTest();
  //GPS_Init(&huart4, NULL);
  jy61p.init(&hi2c2);
  comm.init(&huart4);
  //testGPS = get_GPS_INFO();
  ctrler.Init(0.005f);
  ctrler.initParams(PARAM_ROLL, 1, 0, 0, 0);
  //ctrler.initParams(PARAM_PITCH, 17, 48.0, 55, 350); //20 2.5 80
  ctrler.initParams(PARAM_PITCH, 0, 0, 0, 0); //20 2.5 80
  ctrler.initParams(PARAM_YAW, 0, 0, 0, 0);
  initVOT(3, debugVOSCchannels); //axis_Pitch, axis_GyroPitch, thr1, thr2, thr3, thr4
  HAL_TIM_Base_Start_IT(&htim3);
}

const uint8_t loopPSK = 10;
uint8_t loopCount = 0;
Atti nowAtti, expectAtti;
//200Hz,5ms
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == htim3.Instance)
  {
	  nowAtti = jy61p.getAtti();
    expectAtti.roll = 0;
    expectAtti.pitch = 0;
    expectAtti.yaw = 0;
    ctrler.updateCtrlFrame(nowAtti, expectAtti, comm.getThrottlePercent());

    //Debug用
    if(skipCount++ >= skipTimes)
    {
      debugVOSCDatas[0] = nowAtti.pitch;
      debugVOSCDatas[1] = nowAtti.gy;
      debugVOSCDatas[2] = comm.getThrottlePercent();
      appendData(debugVOSCDatas);
      skipCount = 0;
    }

    //LOOP指示灯闪烁
    if(++loopCount >= loopPSK)
    {
      HAL_GPIO_TogglePin(LED_LOOP_GPIO_Port, LED_LOOP_Pin);
      loopCount = 0;
    }
  }
}

