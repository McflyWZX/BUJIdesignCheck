//=============================================================
// 文件名称：	algorithm.c
// 功能描述：	算法(各种数据类型的转换)
// 维护记录：	2010-01-31	V1.0  by xgc
//              2010-04-03  V1.1  by xgc
//
//  代码作者：  相广超  xgc94418297.blog.163.com
//  程序说明：  本程序仅试用于TX2440系列开发板，使用的是2440串口2经过数据
//              选择器扩展出的串口。
//              本程序仅提供了操作串口的方法和GPS数据解析的实现方法，供参考。
//              更多的功能有待读者自己开发 
//=============================================================

#include "TypeConvertor.h"

//====================================================================//
// 语法格式: static int Str_To_Int(char *buf)
// 实现功能： 把一个字符串转化成整数
// 参    数：字符串
// 返 回 值：转化后整数值
//====================================================================//
int32_t Str_To_Int(uint8_t *buf)
{
	int32_t rev = 0;
	int32_t dat;
	uint8_t *str = buf;
	while(*str != '\0')
	{
		switch(*str)
		{
			case '0':
				dat = 0;
				break;
			case '1':
				dat = 1;
				break;
			case '2':
				dat = 2;
				break;		
			case '3':
				dat = 3;
				break;
			case '4':
				dat = 4;
				break;
			case '5':
				dat = 5;
				break;
			case '6':
				dat = 6;
				break;
			case '7':
				dat = 7;
				break;
			case '8':
				dat = 8;
				break;
			case '9':
				dat = 9;
				break;
		}

		rev = rev * 10 + dat;
		str ++;
	}

	return rev;
}

//====================================================================//
// 语法格式: static int Get_Int_Number(char *s)
// 实现功能：把给定字符串第一个逗号之前的字符转化成整型
// 参    数：字符串
// 返 回 值：转化后整数值
//====================================================================//
int32_t Get_Int_Number(uint8_t *s)
{
	uint8_t buf[10];
	uint8_t i;
	int32_t rev;
	i=GetComma(1, s);
	i = i - 1;
	strncpy(buf, s, i);
	buf[i] = 0;
	rev=Str_To_Int(buf);
	return rev;	
}

//====================================================================//
// 语法格式: static float Str_To_Float(char *buf)
// 实现功能： 把一个字符串转化成浮点数
// 参    数：字符串
// 返 回 值：转化后单精度值
//====================================================================//
float Str_To_Float(uint8_t *buf)
{
	float rev = 0;
	float dat;
	int32_t integer = 1;
	uint8_t *str = buf;
	int32_t i;
	while(*str != '\0')
	{
		switch(*str)
		{
			case '0':
				dat = 0;
				break;
			case '1':
				dat = 1;
				break;
			case '2':
				dat = 2;
				break;		
			case '3':
				dat = 3;
				break;
			case '4':
				dat = 4;
				break;
			case '5':
				dat = 5;
				break;
			case '6':
				dat = 6;
				break;
			case '7':
				dat = 7;
				break;
			case '8':
				dat = 8;
				break;
			case '9':
				dat = 9;
				break;
			case '.':
				dat = '.';
				break;
		}
		if(dat == '.')
		{
			integer = 0;
			i = 1;
			str ++;
			continue;
		}
		if( integer == 1 )
		{
			rev = rev * 10 + dat;
		}
		else
		{
			rev = rev + dat / (10 * i);
			i = i * 10 ;
		}
		str ++;
	}
	return rev;

}
												
//====================================================================//
// 语法格式: static float Get_Float_Number(char *s)
// 实现功能： 把给定字符串第一个逗号之前的字符转化成单精度型
// 参    数：字符串
// 返 回 值：转化后单精度值
//====================================================================//
float Get_Float_Number(uint8_t *s)
{
	uint8_t buf[10];
	uint8_t i;
	float rev;
	i=GetComma(1, s);
	i = i - 1;
	strncpy(buf, s, i);
	buf[i] = 0;
	rev=Str_To_Float(buf);
	return rev;	
}

//====================================================================//
// 语法格式: static double Str_To_Double(char *buf)
// 实现功能： 把一个字符串转化成浮点数
// 参    数：字符串
// 返 回 值：转化后双精度值
//====================================================================//
double Str_To_Double(uint8_t *buf)
{
	double rev = 0;
	double dat;
	int32_t integer = 1;
	uint8_t *str = buf;
	int32_t i;
	while(*str != '\0')
	{
		switch(*str)
		{
			case '0':
				dat = 0;
				break;
			case '1':
				dat = 1;
				break;
			case '2':
				dat = 2;
				break;		
			case '3':
				dat = 3;
				break;
			case '4':
				dat = 4;
				break;
			case '5':
				dat = 5;
				break;
			case '6':
				dat = 6;
				break;
			case '7':
				dat = 7;
				break;
			case '8':
				dat = 8;
				break;
			case '9':
				dat = 9;
				break;
			case '.':
				dat = '.';
				break;
		}
		if(dat == '.')
		{
			integer = 0;
			i = 1;
			str ++;
			continue;
		}
		if( integer == 1 )
		{
			rev = rev * 10 + dat;
		}
		else
		{
			rev = rev + dat / (10 * i);
			i = i * 10 ;
		}
		str ++;
	}
	return rev;
}
												
//====================================================================//
// 语法格式: static double Get_Double_Number(char *s)
// 实现功能：把给定字符串第一个逗号之前的字符转化成双精度型
// 参    数：字符串
// 返 回 值：转化后双精度值
//====================================================================//
double Get_Double_Number(uint8_t *s)
{
	uint8_t buf[10];
	uint8_t i;
	double rev;
	i=GetComma(1, s);
	i = i - 1;
	strncpy(buf, s, i);
	buf[i] = 0;
	rev=Str_To_Double(buf);
	return rev;	
}

//====================================================================//
// 语法格式：static uchar GetComma(uchar num,char *str)
// 实现功能：计算字符串中各个逗号的位置
// 参    数：查找的逗号是第几个的个数，需要查找的字符串
// 返 回 值：0
//====================================================================//
uint8_t GetComma(uint8_t num,uint8_t *str)
{
	uint8_t i,j = 0;
	int32_t len=strlen(str);

	for(i = 0;i < len;i ++)
	{
		if(str[i] == ',')
			j++;
		if(j == num)
			return i + 1;	
	}

	return 0;	
}

//====================================================================//
//	语法格式：	Int_To_Str(int x,char *Str)
//	实现功能：	转化整型值为字符串形式
//	参数：		x: 转化的整数
//				Str:转化后的字符串
//	返回值：	无
//====================================================================//
void Int_To_Str(int32_t x,uint8_t *Str)
{
	int32_t t;
	uint8_t *Ptr,Buf[5];
	int32_t i = 0;
	Ptr = Str;
	if(x < 10)		// 锟斤拷锟斤拷锟斤拷小锟斤拷10时,转锟斤拷为"0x"锟侥革拷式
	{
		*Ptr ++ = '0';
		*Ptr ++ = x+0x30;
	}
	else
	{
		while(x > 0)
		{
			t = x % 10;
			x = x / 10;
			Buf[i++] = t+0x30;	// 通锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟阶�锟斤拷锟斤拷ASCII锟斤拷锟斤拷式
		}
		i -- ;
		for(;i >= 0;i --) 		// 锟斤拷锟矫碉拷锟斤拷锟街凤拷锟斤拷锟斤拷锟斤拷
		{
			*(Ptr++) = Buf[i];
		}
	}
	*Ptr = '\0';
}
