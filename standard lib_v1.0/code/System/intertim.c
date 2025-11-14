#include "stm32f10x.h"                  // Device header



void Timer3_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);			//开启TIM3的时钟
	TIM_InternalClockConfig(TIM3);
	
	
	TIM_TimeBaseInitTypeDef TIM3_TimeBaseInitStructure;				//定义结构体变量
	TIM3_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元功能
	TIM3_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //计数器模式，选择向上计数
	TIM3_TimeBaseInitStructure.TIM_Period = 65536 - 1;               //计数周期，即ARR的值，计数最大间隔为6.5536/30s
	TIM3_TimeBaseInitStructure.TIM_Prescaler = 240 - 1;               //预分频器，即PSC的值
	TIM3_TimeBaseInitStructure.TIM_RepetitionCounter = 0;            //重复计数器，高级定时器才会用到
	TIM_TimeBaseInit(TIM3, &TIM3_TimeBaseInitStructure);             //将结构体变量交给TIM_TimeBaseInit，配置TIM3的时基单元
	
	
//	TIM_Cmd(TIM3, ENABLE);
	
}


void TIM3_START(void)
{
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);  
	TIM_Cmd(TIM3, ENABLE);
}

void TIM3_STOP(void)
{
	TIM_Cmd(TIM3, DISABLE);
	TIM_SetCounter(TIM3,0);
}







