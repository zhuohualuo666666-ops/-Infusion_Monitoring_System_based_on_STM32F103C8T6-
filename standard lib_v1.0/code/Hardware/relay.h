#ifndef __RELAY_H
#define	__RELAY_H


#include "stm32f10x.h"                  // Device header




#define	RELAY_CLK					RCC_APB2Periph_GPIOA

#define RELAY_GPIO_PIN 				GPIO_Pin_8

#define RELAY_GPIO_PROT 			GPIOA

#define RELAY_OFF		GPIO_SetBits(RELAY_GPIO_PROT,RELAY_GPIO_PIN)
#define RELAY_ON 	GPIO_ResetBits(RELAY_GPIO_PROT,RELAY_GPIO_PIN)




void RELAY_Init(void);


#endif



