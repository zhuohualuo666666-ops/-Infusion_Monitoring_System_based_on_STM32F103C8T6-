#include "water.h"
#include "gpio.h"




uint16_t WATER_GetData(void)
{
	
	uint16_t WaterData;
	WaterData = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);
	return WaterData;
}
