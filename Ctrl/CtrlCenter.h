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

typedef struct {
  void (*init)();
} CtrlCent;

extern CtrlCent ctrlCent;

#endif
