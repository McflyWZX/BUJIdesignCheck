#ifndef __TESTUARTCOMM_H_
#define __TESTUARTCOMM_H_

#include "stm32h7xx_hal.h"
#include "usart.h"

typedef struct {
  void (*init)(UART_HandleTypeDef *DebugHuart);
  uint8_t (*getThrottlePercent)(void);
} UartComm;

extern UartComm comm;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif