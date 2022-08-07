#ifndef __TM1640_H
#define __TM1640_H
#include "stdint.h"
void TM1640_Init(void);
void TM1640_Start(void);
void TM1640_Stop(void);
void TM1640_Write_Byte(uint8_t date);
void Write_Com(uint8_t date);//发送命令字
void Write_DATA(unsigned char add,unsigned char DATA);		//指定地址写入数据
void cls_TM1640(void);
void init_TM1640(void);
#endif
