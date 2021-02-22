#ifndef __TYPECONVERTOR_H_
#define __TYPECONVERTOR_H_

#include "stm32h7xx_hal.h"

uint8_t GetComma(uint8_t num,uint8_t* str);
int32_t Get_Int_Number(uint8_t *s);
double Get_Double_Number(uint8_t *s);
float Get_Float_Number(uint8_t *s);

int32_t Str_To_Int(uint8_t *buf);
float Str_To_Float(uint8_t *buf);
double Str_To_Double(uint8_t *buf);
void Int_To_Str(int32_t x,uint8_t *Str);

#endif
