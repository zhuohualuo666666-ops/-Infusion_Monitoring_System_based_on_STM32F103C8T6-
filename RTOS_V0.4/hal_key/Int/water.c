#include "water.h"
#include "gpio.h"




uint16_t WATER_GetData(void)
{
	uint16_t WaterData=1;
	
 
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)==GPIO_PIN_RESET) {WaterData=0;}
	else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)==GPIO_PIN_SET){WaterData=1;}
	return WaterData;
}


void water_printf(void)
{
	if(WATER_GetData()==0)
	{
		printf("ÓÐÒ©Òº\r\n");
	}
	else if(WATER_GetData()==1)
	{
		printf("ÎÞÒ©Òº\r\n");
	}
}

