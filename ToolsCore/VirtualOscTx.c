/*
 * @Author: Mcfly
 * @Date: 2021-04-19 15:14:18
 * @LastEditTime: 2021-04-19 15:24:47
 * @LastEditors: Mcfly
 * @Description: 
 * @FilePath: \BUJIdesignCheck\ToolsCore\VirtualOscTx.c
 * ����github:https://github.com/McflyWZX
 */
#include "VirtualOscTx.h"
#include "usart.h"

#define virtualOscUartSend(DAT, LEN) HAL_UART_Transmit_IT(&huart4, DAT, LEN)
uint8_t* data = NULL;		//�����������
uint16_t partSize;	//һ�η��͵�������
uint8_t channels;		//��ͨ����
uint32_t totalLen8;
uint8_t stepLen8;
uint32_t index;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ʼ������ʾ��������,�ǵ���lsl�ļ����޸ĶѵĴ�С
//  @param      _partSize		ÿ�η��͵����ݳ���(ռ�ÿռ��СΪ(channels + 1) * partSize * 4���ֽڣ�
//								���ڴ������ʹ��ͣ��ʵ�����˲����Ա�֤���η������ݵ�������
//  @param      _channels       ʾ����ͨ��������Ҫ��ʾx��ADC�����ݣ��ò�����Ϊx��
//  @return     void
//  @Sample usage:               initVOT(100, 2);       // 2ͨ����һ�η���100������
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
	index = 0;
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �������ݵ������б��У������������ﵽ��partSize���Ϳ�ʼ����ʽ����
//  @param      rawDatas		��ADC�ж�ȡ����ԭʼ�������飨����Ĵ�СΪͨ������
//  @return     void
//  @Sample usage:               appendData(adc[2]);       // ׷�ӵ��ζ�ȡ������ͨ����adc����
//-------------------------------------------------------------------------------------------------------------------
void appendData(float* rawDatas)
{
	for(uint8_t i = 0, j = 0; j < channels; i += 4, j++)
	{
		*((float*)(data + index + i)) = rawDatas[j];
	}
	index += stepLen8;
	if(index >= totalLen8)
	{
		virtualOscUartSend(data, totalLen8);
		index = 0;
	}
}
