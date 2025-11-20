#ifndef __STEPMOTOR_H
#define	__STEPMOTOR_H
#include "stm32f1xx_hal.h"  // CubeMX 自动生成
#include <stdint.h>





#define u8 uint8_t


#define MOTOR_A 				GPIO_PIN_12
#define MOTOR_B 				GPIO_PIN_13
#define MOTOR_C 				GPIO_PIN_14
#define MOTOR_D 				GPIO_PIN_15
#define MOTOR_PROT 			GPIOB

#define MOTOR_A_HIGH HAL_GPIO_WritePin(MOTOR_PROT,MOTOR_A,GPIO_PIN_SET)
#define MOTOR_A_LOW HAL_GPIO_WritePin(MOTOR_PROT,MOTOR_A,GPIO_PIN_RESET)

#define MOTOR_B_HIGH HAL_GPIO_WritePin(MOTOR_PROT,MOTOR_B,GPIO_PIN_SET)
#define MOTOR_B_LOW HAL_GPIO_WritePin(MOTOR_PROT,MOTOR_B,GPIO_PIN_RESET)

#define MOTOR_C_HIGH HAL_GPIO_WritePin(MOTOR_PROT,MOTOR_C,GPIO_PIN_SET)
#define MOTOR_C_LOW HAL_GPIO_WritePin(MOTOR_PROT,MOTOR_C,GPIO_PIN_RESET)

#define MOTOR_D_HIGH HAL_GPIO_WritePin(MOTOR_PROT,MOTOR_D,GPIO_PIN_SET)
#define MOTOR_D_LOW HAL_GPIO_WritePin(MOTOR_PROT,MOTOR_D,GPIO_PIN_RESET)



void MOTOR_Init(void);
void MOTOR_Rhythm_4_1_4(u8 step,u8 dly);
void MOTOR_Direction(u8 dir,u8 num,u8 dly);
void MOTOR_Direction_Angle(u8 dir,u8 num,float angle,u8 dly);
void MOTOR_STOP(void);
#endif



