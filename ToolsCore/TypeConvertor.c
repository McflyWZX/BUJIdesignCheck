//=============================================================
// �ļ����ƣ�	algorithm.c
// ����������	�㷨(�����������͵�ת��)
// ά����¼��	2010-01-31	V1.0  by xgc
//              2010-04-03  V1.1  by xgc
//
//  �������ߣ�  ��㳬  xgc94418297.blog.163.com
//  ����˵����  �������������TX2440ϵ�п����壬ʹ�õ���2440����2��������
//              ѡ������չ���Ĵ��ڡ�
//              ��������ṩ�˲������ڵķ�����GPS���ݽ�����ʵ�ַ��������ο���
//              ����Ĺ����д������Լ����� 
//=============================================================

#include "TypeConvertor.h"
#include "string.h"

//====================================================================//
// �﷨��ʽ: static int32_t Str_To_Int(int32_t *buf)
// ʵ�ֹ��ܣ� ��һ���ַ���ת��������
// ��    �����ַ���
// �� �� ֵ��ת��������ֵ
//====================================================================//
int32_t Str_To_Int(int32_t *buf)
{
	int32_t rev = 0;
	int32_t dat;
	int32_t *str = buf;
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
// �﷨��ʽ: static int32_t Get_Int_Number(int32_t *s)
// ʵ�ֹ��ܣ��Ѹ����ַ�����һ������֮ǰ���ַ�ת��������
// ��    �����ַ���
// �� �� ֵ��ת��������ֵ
//====================================================================//
int32_t Get_Int_Number(int32_t *s)
{
	int32_t buf[10];
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
// �﷨��ʽ: static float Str_To_Float(int32_t *buf)
// ʵ�ֹ��ܣ� ��һ���ַ���ת���ɸ�����
// ��    �����ַ���
// �� �� ֵ��ת���󵥾���ֵ
//====================================================================//
float Str_To_Float(int32_t *buf)
{
	float rev = 0;
	float dat;
	int32_t integer = 1;
	int32_t *str = buf;
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
// �﷨��ʽ: static float Get_Float_Number(int32_t *s)
// ʵ�ֹ��ܣ� �Ѹ����ַ�����һ������֮ǰ���ַ�ת���ɵ�������
// ��    �����ַ���
// �� �� ֵ��ת���󵥾���ֵ
//====================================================================//
float Get_Float_Number(int32_t *s)
{
	int32_t buf[10];
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
// �﷨��ʽ: static double Str_To_Double(int32_t *buf)
// ʵ�ֹ��ܣ� ��һ���ַ���ת���ɸ�����
// ��    �����ַ���
// �� �� ֵ��ת����˫����ֵ
//====================================================================//
double Str_To_Double(int32_t *buf)
{
	double rev = 0;
	double dat;
	int32_t integer = 1;
	int32_t *str = buf;
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
// �﷨��ʽ: static double Get_Double_Number(int32_t *s)
// ʵ�ֹ��ܣ��Ѹ����ַ�����һ������֮ǰ���ַ�ת����˫������
// ��    �����ַ���
// �� �� ֵ��ת����˫����ֵ
//====================================================================//
double Get_Double_Number(int32_t *s)
{
	int32_t buf[10];
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
// �﷨��ʽ��static uchar GetComma(uchar num,int32_t *str)
// ʵ�ֹ��ܣ������ַ����и������ŵ�λ��
// ��    �������ҵĶ����ǵڼ����ĸ�������Ҫ���ҵ��ַ���
// �� �� ֵ��0
//====================================================================//
uint8_t GetComma(uint8_t num,int32_t *str)
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
//	�﷨��ʽ��	Int_To_Str(int32_t x,int32_t *Str)
//	ʵ�ֹ��ܣ�	ת������ֵΪ�ַ�����ʽ
//	������		x: ת��������
//				Str:ת������ַ���
//	����ֵ��	��
//====================================================================//
void Int_To_Str(int32_t x,int32_t *Str)
{
	int32_t t;
	int32_t *Ptr,Buf[5];
	int32_t i = 0;
	Ptr = Str;
	if(x < 10)		// ������С��10ʱ,ת��Ϊ"0x"�ĸ�ʽ
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
			Buf[i++] = t+0x30;	// ͨ�����������ת����ASCII����ʽ
		}
		i -- ;
		for(;i >= 0;i --) 		// ���õ����ַ�������
		{
			*(Ptr++) = Buf[i];
		}
	}
	*Ptr = '\0';
}
