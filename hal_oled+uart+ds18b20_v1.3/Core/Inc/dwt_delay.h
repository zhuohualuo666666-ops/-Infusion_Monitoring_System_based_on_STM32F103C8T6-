// dwt_delay.h
#ifndef __DWT_DELAY_H
#define __DWT_DELAY_H

#include "stm32f1xx_hal.h"  // CubeMX 自动生成

void DWT_Init(void);
void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);  // 顺便送你毫秒延时（比 HAL_Delay 更快）

#endif
