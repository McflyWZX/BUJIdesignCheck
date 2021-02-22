#ifndef __TYPECONVERTOR_H_
#define __TYPECONVERTOR_H_

#include "stm32h7xx_hal.h"

uint8_t GetComma(uint8_t num,int32_t* str);
int32_t Get_Int_Number(int32_t *s);
double Get_Double_Number(int32_t *s);
float Get_Float_Number(int32_t *s);

int32_t Str_To_Int(int32_t *buf);
float Str_To_Float(int32_t *buf);
double Str_To_Double(int32_t *buf);
void Int_To_Str(int32_t x,int32_t *Str);

#endif __TYPECONVERTOR_H_