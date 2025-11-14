#include "stm32f10x.h"                  // Device header
#include "water.h"



void WATER_Init(void)
{

		GPIO_InitTypeDef GPIO_InitStructure;
		
		RCC_APB2PeriphClockCmd (WATER_GPIO_CLK, ENABLE);	// 打开连接 传感器DO 的单片机引脚端口时钟
		GPIO_InitStructure.GPIO_Pin = WATER_GPIO_PIN;			// 配置连接 传感器DO 的单片机引脚模式
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			// 设置为上拉输入
		
		GPIO_Init(WATER_GPIO_PORT, &GPIO_InitStructure);				// 初始化 
	
}

uint16_t WATER_GetData(void)
{
	
	uint16_t WaterData;
	WaterData = GPIO_ReadInputDataBit(WATER_GPIO_PORT, WATER_GPIO_PIN);
	return WaterData;
}

