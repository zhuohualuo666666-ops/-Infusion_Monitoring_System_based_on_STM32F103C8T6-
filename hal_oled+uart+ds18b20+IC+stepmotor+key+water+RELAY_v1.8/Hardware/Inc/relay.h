#ifndef __RELAY_H
#define	__RELAY_H

#include "stm32f1xx_hal.h"  // CubeMX 自动生成
#include <stdint.h>




#define RELAY_GPIO_PIN 				GPIO_PIN_8

#define RELAY_GPIO_PROT 			GPIOA






void RELAY_OFF(void);
void RELAY_ON(void);

#endif



