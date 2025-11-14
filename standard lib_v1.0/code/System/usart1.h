#ifndef __USART1_H
#define __USART1_H

#include "stm32f10x.h"                  // Device header
#include "gizwits_protocol.h"
#include "usart2.h"



extern uint8_t Usart1_RxPacket[6];				//定义接收数据包数组
extern uint8_t Usart1_RxFlag;

void USART1_Config(void);
uint8_t Usart1_GetRxFlag(void);










#endif

