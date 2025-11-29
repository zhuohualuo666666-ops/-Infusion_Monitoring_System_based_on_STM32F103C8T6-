#ifndef __DS18B20_H
#define __DS18B20_H 
  
#include <stdint.h>

					

#define DS18B20_GPIO_PORT		GPIOA
#define DS18B20_GPIO_PIN		GPIO_PIN_6
//#define DS18B20_GPIO_CLK   	RCC_APB2Periph_GPIOA


//输出状态定义
#define OUT 1
#define IN  0

//控制DS18B20引脚输出高低电平
#define DS18B20_Low  HAL_GPIO_WritePin(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN,GPIO_PIN_RESET)
#define DS18B20_High HAL_GPIO_WritePin(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN,GPIO_PIN_SET)	
		
uint8_t DS18B20_Init(void);//初始化DS18B20
//short DS18B20_Get_Temp(void);//获取温度

int16_t DS18B20_Get_Temp(void);
void DS18B20_Print_Temp(void);

void DS18B20_Start(void);//开始温度转换
void DS18B20_Write_Byte(uint8_t dat);//写入一个字节
uint8_t DS18B20_Read_Byte(void);//读出一个字节
uint8_t DS18B20_Read_Bit(void);//读出一个位
void DS18B20_Mode(uint8_t mode);//DS18B20引脚输出模式控制
uint8_t DS18B20_Check(void);//检测是否存在DS18B20
void DS18B20_Rst(void);//复位DS18B20   

#endif





