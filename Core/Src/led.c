/*https://blog.csdn.net/qq_32650719/article/details/108843550*/

#include "led.h"
#include "main.h"

#define TM1640_SCK_HIGHT  	  HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET)
#define TM1640_SCK_LOW  	    HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET)
#define TM1640_DOUT_HIGHT		  HAL_GPIO_WritePin(DIN_GPIO_Port, DIN_Pin, GPIO_PIN_SET)
#define TM1640_DOUT_LOW     	HAL_GPIO_WritePin(DIN_GPIO_Port, DIN_Pin, GPIO_PIN_RESET)

extern TIM_HandleTypeDef htim1;
void delay_us(uint16_t us)
{
	uint16_t differ=0xffff-us-5; 

	
	HAL_TIM_Base_Start(&htim1);
	__HAL_TIM_SetCounter(&htim1,differ); 
	while(differ < 0xffff-5) 
	{ 
		differ = __HAL_TIM_GetCounter(&htim1); 
	} 
	HAL_TIM_Base_Stop(&htim1);
 
}
void delay_ms(uint16_t nms)
{
	HAL_Delay(nms);
// uint32_t temp;
// SysTick->LOAD = 9000*nms;
// SysTick->VAL=0X00;//?????
// SysTick->CTRL=0X01;//??,???????,???????
// do
// {
//  temp=SysTick->CTRL;//????????
// }while((temp&0x01)&&(!(temp&(1<<16))));//??????
//    SysTick->CTRL=0x00; //?????
//    SysTick->VAL =0X00; //?????
}


void TM1640_Start(void)
{
	TM1640_SCK_HIGHT;
  TM1640_DOUT_HIGHT;
	delay_us(10);
	TM1640_DOUT_LOW;
	delay_us(10);
	TM1640_SCK_LOW;
	delay_us(10);
}

void TM1640_Stop(void)
{
  TM1640_DOUT_LOW;
	TM1640_SCK_HIGHT;
	delay_us(10);
	TM1640_DOUT_HIGHT;
	delay_us(10);
}

void TM1640_Write_Byte(uint8_t date)
{
	uint8_t i;
	uint8_t Temp;
	Temp=date;
	TM1640_SCK_LOW;
  TM1640_DOUT_LOW;
	for(i=0;i<8;i++)
	{
		TM1640_SCK_LOW;
		delay_us(2);
		if(Temp&0x01)
		{	
			TM1640_DOUT_HIGHT;
			delay_us(10);
		}
		else
		{
			TM1640_DOUT_LOW;
			delay_us(10);
		}
		TM1640_SCK_HIGHT;
		delay_us(1);
		Temp = Temp >> 1;
	}
	TM1640_SCK_LOW;
  TM1640_DOUT_LOW;
}

void Write_Com(uint8_t date)
{
	TM1640_Start();
	TM1640_Write_Byte(date);
	TM1640_Stop();
}

void Write_DATA(unsigned char add,unsigned char DATA)
{
	Write_Com(0x44);
	TM1640_Start();
	TM1640_Write_Byte(0xc0|add);
	TM1640_Write_Byte(DATA);
	TM1640_Stop();
}

void cls_TM1640(void)//清屏函数
{
	unsigned char i;	
	Write_Com(0x40);//连续地址模式
	TM1640_Start();
	TM1640_Write_Byte(0xc0);
	for(i=0;i<16;i++)
		TM1640_Write_Byte(0x00);
	TM1640_Stop();
}

void init_TM1640(void)
{
	cls_TM1640();
	Write_Com(0x8F);//亮度
}

