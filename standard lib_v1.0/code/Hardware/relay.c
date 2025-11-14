#include "stm32f10x.h"                  // Device header

#include "relay.h"





void RELAY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RELAY_CLK, ENABLE ); //≈‰÷√ ±÷”
	
	GPIO_InitStructure.GPIO_Pin = RELAY_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(RELAY_GPIO_PROT,&GPIO_InitStructure);

	RELAY_OFF;
}




