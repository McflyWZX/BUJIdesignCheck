#include "TestUartComm.h"

void init(UART_HandleTypeDef *DebugHuart);
uint8_t getThrottlePercent();

UartComm comm = {
  init,
  getThrottlePercent
};

UART_HandleTypeDef *debugHuart;
uint8_t recvChr;
uint8_t throttlePercent = 0;
void init(UART_HandleTypeDef *DebugHuart)
{
  debugHuart = DebugHuart;
  HAL_UART_Receive_DMA(debugHuart, &throttlePercent, 1);
}

uint8_t getThrottlePercent()
{
  return throttlePercent;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	UNUSED(huart);
  //throttlePercent = recvChr;
  HAL_UART_Receive_DMA(debugHuart, &throttlePercent, 1);
}
