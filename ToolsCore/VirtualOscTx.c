/*
 * @Author: Mcfly
 * @Date: 2021-04-19 15:14:18
 * @LastEditTime: 2021-04-19 15:31:04
 * @LastEditors: Mcfly
 * @Description: 
 * @FilePath: \BUJIdesignCheck\ToolsCore\VirtualOscTx.c
 * 本人github:https://github.com/McflyWZX
 */
#include "VirtualOscTx.h"
#include "usart.h"

#define virtualOscUartSend(DAT, LEN) HAL_UART_Transmit_IT(&huart4, DAT, LEN)
uint8_t* data = NULL;		//待传输的数据
uint16_t partSize;	//一次发送的数据量
uint8_t channels;		//总通道数
uint32_t totalLen8;
uint8_t stepLen8;
uint32_t dataAppendIndex;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      初始化虚拟示波器传送,记得在lsl文件中修改堆的大小
//  @param      _partSize		每次发送的数据长度(占用空间大小为(channels + 1) * partSize * 4个字节，
//								由于串口速率过低，适当调大此参数以保证单次发送数据的完整性
//  @param      _channels       示波器通道数（如要显示x组ADC的数据，该参数就为x）
//  @return     void
//  @Sample usage:               initVOT(100, 2);       // 2通道，一次发送100个数据
//-------------------------------------------------------------------------------------------------------------------
void initVOT(uint16_t _partSize, uint8_t _channels)
{
	partSize = _partSize;
	channels = _channels;
	totalLen8 = channels * partSize * 4 + partSize * 4;
	data = (uint8_t*)malloc(totalLen8);
	stepLen8 = (channels + 1) * 4;
	for(uint16_t i = channels * 4; i < totalLen8; i += stepLen8)
	{
		data[i + 0] = 0x00;
		data[i + 1] = 0x00;
		data[i + 2] = 0x80;
		data[i + 3] = 0x7f;
	}
	dataAppendIndex = 0;
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      加入数据到传送列表中，当数据数量达到了partSize，就开始阻塞式发送
//  @param      rawDatas		从ADC中读取出的原始数据数组（数组的大小为通道数）
//  @return     void
//  @Sample usage:               appendData(adc[2]);       // 追加单次读取的两个通道的adc数据
//-------------------------------------------------------------------------------------------------------------------
void appendData(float* rawDatas)
{
	for(uint8_t i = 0, j = 0; j < channels; i += 4, j++)
	{
		*((float*)(data + dataAppendIndex + i)) = rawDatas[j];
	}
	dataAppendIndex += stepLen8;
	if(dataAppendIndex >= totalLen8)
	{
		virtualOscUartSend(data, totalLen8);
		dataAppendIndex = 0;
	}
}
