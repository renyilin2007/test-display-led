#include "bsp_display_led.h"
#include "main.h"

/* 								  '0'		'1'		'2'		'3'		'4'		'5'		'6'		'7'		'8'		'9' */
uint8_t num_up[] = {0x00, 0x30, 0x6d, 0x79, 0x33, 0x5b, 0x5f, 0x70, 0x7f, 0x7b};
uint8_t num_dw[] = {0x00, 0x06, 0x6d, 0x4f, 0x17, 0x5b, 0x7b, 0x0e, 0x7f, 0x5f};

static void delay_xms(u32 x)
{
	u32 i,j;
	
	for(i=0;i<x;i++)
	
	for(j=0;j<112;j++);
}

static void write_max7219_byte(u8 DATA)         
{
	u8 i;    

	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
	for(i=8;i>=1;i--)
	{		  
		HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DIN_GPIO_Port, DIN_Pin, (GPIO_PinState)(DATA&0x80));
		DATA=DATA<<1;
		HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET);
	}                                 
}

static void write_max7219(u8 address,u8 dat)
{ 
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
	write_max7219_byte(address);           //д���ַ��������ܱ��
	write_max7219_byte(dat);               //д�����ݣ����������ʾ����
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
}

static void init_max7219(void)
{
	write_max7219(0x09, 0x00);  //���뷽ʽ��BCD��     
	write_max7219(0x0a, 0x03);  //����     
	write_max7219(0x0b, 0x07);  //ɨ����ޣ�4���������ʾ    
	write_max7219(0x0c, 0x01);  //����ģʽ��0����ͨģʽ��1
	write_max7219(0x0f, 0x01);  //��ʾ���ԣ�1�����Խ�����������ʾ��0  
}

void bsp_display_led_init(void)
{
	HAL_Delay(500);//delay
	delay_xms(50);
	init_max7219();
	delay_xms(2000);
	write_max7219(0x0f, 0x00);  //��ʾ���ԣ�1�����Խ�����������ʾ��0
	bsp_set_display_led_alloff(1);
}

void bsp_display_led_deinit(void)
{
    bsp_set_display_led_alloff(1);
}

//index:����ܵ�λ��1~8��Ӧ1~8�����λ val:��ֵ
int bsp_set_display_led_val(uint8_t index, uint8_t val)
{
	if(index < 1 || index > 8 || val > 9)
		return -1;
		
	write_max7219(index, num_up[val]);
	
	return 0;
}

int bsp_set_display_led_val_down(uint8_t index, uint8_t val)
{
	if(index < 1 || index > 8 || val > 9)
		return -1;
		
	write_max7219(8 - (index - 1), num_dw[val]);
	
	return 0;
}

int bsp_set_display_led_allon(void)
{
	//write_max7219(0x0f, 0x01);  //��ʾ���ԣ�1�����Խ�����������ʾ��0  
    for(int i = 1; i <= 8; i++)
        bsp_set_display_led_val(i, 0x00);
        
	return 0;
}

//opt 0:����ԭ��(Ŀǰģʽ�л����õ���ģʽ�л���Ҫ����ȫΪ0) 1:���еƹر�
int bsp_set_display_led_alloff(int opt)
{
	write_max7219(0x0f, 0x00);  //��ʾ���ԣ�1�����Խ�����������ʾ��0  

	if(opt)
	{
    	for(int i = 1; i <= 8; i++)
    		bsp_set_display_led_val(i, 0x00);
	}
	
	return 0;
}

int bsp_set_display_led_off(uint8_t index)
{
	bsp_set_display_led_val(index, 0x0f);
	
	return 0;
}

//������������� ���ṩ�������û�ʹ�ã�ֻ��bsp_set_displays_led_levelʹ��
int _bsp_set_displays_led_level(int level)
{
	switch(level)
	{
		case 1:
			write_max7219(0x0a, 0);
			break;
		case 2:
			write_max7219(0x0a, 1);
			break;
		case 3:
			write_max7219(0x0a, 2);
			break;
		case 4:
			write_max7219(0x0a, 3);
			break;
		case 5:
			write_max7219(0x0a, 4);
			break;
		case 6:
			write_max7219(0x0a, 6);
			break;
		case 7:
			write_max7219(0x0a, 8);
			break;
		case 8:
			write_max7219(0x0a, 10);
			break;
		case 9:
			write_max7219(0x0a, 13);
			break;
		case 10:
			write_max7219(0x0a, 15);
			break;
	}

	return 0;
}

