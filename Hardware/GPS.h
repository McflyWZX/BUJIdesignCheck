#ifndef __GPS_H
#define __GPS_H

#include "stm32h7xx_hal.h"
#include "TypeConvertor.h"

typedef struct{
	int32_t year;  
	int32_t month; 
	int32_t  day;
	int32_t hour;
	int32_t minute;
	int32_t second;
}DATE_TIME;

typedef struct{
	double    latitude;  //经度
	double    longitude; //纬度
	float 		height_sea;
	float 		speed;
	float 		direction;
	float 		height_ground;
	int32_t   latitude_Degree;	//度
	int32_t		latitude_Cent;		//分
  int32_t   latitude_Second;    //秒
	int32_t   longitude_Degree;	//度
	int32_t		longitude_Cent;		//分
	int32_t   longitude_Second;   //秒
	int32_t   satellite;
	uint8_t 	NS;
	uint8_t 	EW;
	DATE_TIME D;
}GPS_INFO;

#endif