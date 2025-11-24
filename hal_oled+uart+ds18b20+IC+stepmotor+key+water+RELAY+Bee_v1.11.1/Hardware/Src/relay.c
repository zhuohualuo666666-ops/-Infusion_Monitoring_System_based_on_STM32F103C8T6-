#include "relay.h"

#include "gpio.h"



void RELAY_OFF(void)
{
	HAL_GPIO_WritePin(RELAY_GPIO_PROT,RELAY_GPIO_PIN,GPIO_PIN_SET);
}

void RELAY_ON(void)
{
	HAL_GPIO_WritePin(RELAY_GPIO_PROT,RELAY_GPIO_PIN,GPIO_PIN_RESET);
}

