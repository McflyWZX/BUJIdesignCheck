#include "GPS.h"

#define NUMPARSERS 3
#define GPSBUAD 38400

uint8_t GPS_RMC_Parse(GPS_INFO *GPS, uint8_t *line);
uint8_t GPS_GGA_Parse(GPS_INFO *GPS, uint8_t *line);
uint8_t GPS_GSV_Parse(GPS_INFO *GPS, uint8_t *line);
void UTC2BTC(DATE_TIME *date_time);
UART_HandleTypeDef *mGPSuart, *DebugHuart;
uint8_t isDebug = 0, recvChr, recvBuf[200], recvCount = 0, gpsFlag = 0, recvFlag = 0, LEDflag = 0;
uint8_t (*GPS_Parsers[])(GPS_INFO*, uint8_t*) = {GPS_RMC_Parse, GPS_GGA_Parse, GPS_GSV_Parse};
GPS_INFO mGPS;

void GPS_Init(UART_HandleTypeDef *GPShuart, UART_HandleTypeDef *DebugHuart)
{
  if(DebugHuart != NULL)
  {
    isDebug = 1;
  }
  mGPSuart = GPShuart;
  DebugHuart = DebugHuart;
  HAL_UART_Receive_IT(mGPSuart, &recvChr, 1);
}

const GPS_INFO * get_GPS_INFO()
{
	return (const GPS_INFO *)(&mGPS);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	UNUSED(huart);
	if(recvChr == '$')  //如果收到字符'$'，便开始接收
	{
		recvFlag = 1;
		recvBuf[0] = '$';
    	recvCount = 1;
  } else if(recvFlag == 1)  //标志位为1，开始接收
	{
		recvBuf[recvCount++] = recvChr;  //字符存到数组中
		if(recvChr == '\n')     //如果接收到换行
		{
			recvBuf[recvCount] = '\0';
		  recvFlag = 0;
			  gpsFlag = 1;
			recvCount = 1;
		}
	}
  if(gpsFlag == 1)
  {
		for (uint32_t i = 0; i < NUMPARSERS; i++)
		{
			if(GPS_Parsers[i](&mGPS, recvBuf))
			{
				HAL_GPIO_WritePin(LED_GPS_GPIO_Port, LED_GPS_Pin, LEDflag);
				LEDflag = !LEDflag;
				break;
			}
		}
		gpsFlag = 0;
	}
	HAL_UART_Receive_IT(mGPSuart, &recvChr, 1);
}

//====================================================================//
// 语法格式：int GPS_RMC_Parse(int8_t *line, GPS_INFO *GPS)  
// 实现功能：把gps模块的GPRMC信息解析为可识别的数据
// 参    数：存放原始信息字符数组、存储可识别数据的结构体
// 返 回 值：
//			 1: 解析GPRMC完毕
//           0: 没有进行解析，或数据无效
//====================================================================//
uint8_t GPS_RMC_Parse(GPS_INFO *GPS, uint8_t *line)
{
	uint8_t ch, status, tmp;
	float lati_cent_tmp, lati_second_tmp;
	float long_cent_tmp, long_second_tmp;
	float speed_tmp;
	uint8_t *buf = line;
	ch = buf[5];
	status = buf[GetComma(2, buf)];

	if (ch == 'C')  //如果第五个字符是C，($GPRMC)
	{
		if (status == 'A')  //如果数据有效，则分析
		{
			GPS -> NS       = buf[GetComma(4, buf)];
			GPS -> EW       = buf[GetComma(6, buf)];

			GPS->latitude   = Get_Double_Number(&buf[GetComma(3, buf)]);
			GPS->longitude  = Get_Double_Number(&buf[GetComma( 5, buf)]);

      GPS->latitude_Degree  = (int32_t)GPS->latitude / 100;       //分离纬度
			lati_cent_tmp         = (GPS->latitude - GPS->latitude_Degree * 100);
			GPS->latitude_Cent    = (int32_t)lati_cent_tmp;
			lati_second_tmp       = (lati_cent_tmp - GPS->latitude_Cent) * 60;
			GPS->latitude_Second  = (int32_t)lati_second_tmp;

			GPS->longitude_Degree = (int32_t)GPS->longitude / 100;	//分离经度
			long_cent_tmp         = (GPS->longitude - GPS->longitude_Degree * 100);
			GPS->longitude_Cent   = (int32_t)long_cent_tmp;    
			long_second_tmp       = (long_cent_tmp - GPS->longitude_Cent) * 60;
			GPS->longitude_Second = (int32_t)long_second_tmp;

			speed_tmp      = Get_Float_Number(&buf[GetComma(7, buf)]);    //速度(单位：海里/时)
			GPS->speed     = speed_tmp * 1.85;                           //1海里=1.85公里
			GPS->direction = Get_Float_Number(&buf[GetComma(8, buf)]); //角度			

			GPS->D.hour    = (buf[7] - '0') * 10 + (buf[8] - '0');		//时间
			GPS->D.minute  = (buf[9] - '0') * 10 + (buf[10] - '0');
			GPS->D.second  = (buf[11] - '0') * 10 + (buf[12] - '0');
			tmp = GetComma(9, buf);
			GPS->D.day     = (buf[tmp + 0] - '0') * 10 + (buf[tmp + 1] - '0'); //日期
			GPS->D.month   = (buf[tmp + 2] - '0') * 10 + (buf[tmp + 3] - '0');
			GPS->D.year    = (buf[tmp + 4] - '0') * 10 + (buf[tmp + 5] - '0')+2000;

			UTC2BTC(&GPS->D);
			
			return 1;
		}		
	}
	
	return 0;
}

//====================================================================//
// 语法格式：int GPS_GGA_Parse(int8_t *line, GPS_INFO *GPS)  
// 实现功能：把gps模块的GPGGA信息解析为可识别的数据
// 参    数：存放原始信息字符数组、存储可识别数据的结构体
// 返 回 值：
//			 1: 解析GPGGA完毕
//           0: 没有进行解析，或数据无效
//====================================================================//
uint8_t GPS_GGA_Parse(GPS_INFO *GPS, uint8_t *line)
{
	uint8_t ch, status;
	uint8_t *buf = line;
	ch = buf[4];
	status = buf[GetComma(2, buf)];

	if (ch == 'G')  //$GPGGA
	{
		if (status != ',')
		{
			GPS->height_sea = Get_Float_Number(&buf[GetComma(9, buf)]);
			GPS->height_ground = Get_Float_Number(&buf[GetComma(11, buf)]);

			return 1;
		}
	}
	
	return 0;
}

//====================================================================//
// 语法格式：int GPS_GSV_Parse(int8_t *line, GPS_INFO *GPS)  
// 实现功能：把gps模块的GPGSV信息解析为可识别的数据
// 参    数：存放原始信息字符数组、存储可识别数据的结构体
// 返 回 值：
//			 1: 解析GPGGA完毕
//           0: 没有进行解析，或数据无效
//====================================================================//
uint8_t GPS_GSV_Parse(GPS_INFO *GPS, uint8_t *line)
{
	uint8_t ch;
	uint8_t *buf = line;
	ch = buf[5];

	if (ch == 'V')  //$GPGSV
	{
		GPS->satellite = Get_Int_Number(&buf[GetComma(3, buf)]);
		return 1;
	}
	
	return 0;
}

//====================================================================//
// 语法格式：void UTC2BTC(DATE_TIME *GPS)
// 实现功能：转化时间为北京时区的时间
// 参    数：存放时间的结构体
// 返 回 值：无
//====================================================================//
void UTC2BTC(DATE_TIME *date_time)
{
	date_time->second ++;  
	if(date_time->second > 59)
	{
		date_time->second = 0;
		date_time->minute ++;
		if(date_time->minute > 59)
		{
			date_time->minute = 0;
			date_time->hour ++;
		}
	}	

    date_time->hour = date_time->hour + 8;
	if(date_time->hour > 23)
	{
		date_time->hour -= 24;
		date_time->day += 1;
		if(date_time->month == 2 ||
		   		date_time->month == 4 ||
		   		date_time->month == 6 ||
		   		date_time->month == 9 ||
		   		date_time->month == 11 )
		{
			if(date_time->day > 30)
			{
		   		date_time->day = 1;
				date_time->month++;
			}
		}
		else
		{
			if(date_time->day > 31)
			{	
		   		date_time->day = 1;
				date_time->month ++;
			}
		}
		if(date_time->year % 4 == 0 )
		{
	   		if(date_time->day > 29 && date_time->month == 2)
			{		
	   			date_time->day = 1;
				date_time->month ++;
			}
		}
		else
		{
	   		if(date_time->day > 28 &&date_time->month == 2)
			{
	   			date_time->day = 1;
				date_time->month ++;
			}
		}
		if(date_time->month > 12)
		{
			date_time->month -= 12;
			date_time->year ++;
		}		
	}
}
