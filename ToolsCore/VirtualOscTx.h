/*
 * @Author: Mcfly
 * @Date: 2021-04-19 15:14:18
 * @LastEditTime: 2021-04-19 15:29:55
 * @LastEditors: Mcfly
 * @Description: 和Vofa配合使用的串口虚拟示波器发送端
 * @FilePath: \BUJIdesignCheck\ToolsCore\VirtualOscTx.h
 * 本人github:https://github.com/McflyWZX
 */

#ifndef _VirtualOscTx_h
#define _VirtualOscTx_h
#include "stdlib.h"
#include "stm32h7xx_hal.h"

void initVOT(uint16_t _partSize, uint8_t _channels);
void appendData(float* rawDatas);

#endif
