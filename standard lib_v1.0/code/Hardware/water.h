#ifndef __WATER_H
#define	__WATER_H

#include "stm32f10x.h"




#define		WATER_GPIO_CLK								RCC_APB2Periph_GPIOB
#define 	WATER_GPIO_PORT								GPIOB
#define 	WATER_GPIO_PIN								GPIO_Pin_0	




void WATER_Init(void);
uint16_t WATER_GetData(void);

#endif 

