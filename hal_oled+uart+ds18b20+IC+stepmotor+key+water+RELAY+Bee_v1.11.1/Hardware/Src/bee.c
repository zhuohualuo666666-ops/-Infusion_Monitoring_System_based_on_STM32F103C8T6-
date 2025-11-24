#include "bee.h"
#include "gpio.h"

void BEE_ON(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_RESET);
}



void BEE_OFF(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_SET);
}


