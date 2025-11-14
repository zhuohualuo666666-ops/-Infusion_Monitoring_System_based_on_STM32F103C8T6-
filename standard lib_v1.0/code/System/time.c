#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "time.h"
#include "string.h"
#include "gizwits_product.h"	


void TIM4_Int_Init(u16 arr,u16 psc)
{
	
	NVIC_InitTypeDef NVIC_InitStructure; 
    // 设置中断组为2
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		
		// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn ;	
		// 设置抢占优先级为 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // 设置响应优先级为3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;		
		// 开启定时器时钟,即内部时钟CK_INT=72M
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	
		// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
    TIM_TimeBaseStructure.TIM_Period=arr;
	  // 时钟预分频数
    TIM_TimeBaseStructure.TIM_Prescaler= psc;	
		// 时钟分频因子 ，没用到不用管
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
		// 计数器计数模式，设置为向上计数
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 		
		// 重复计数器的值，没用到不用管
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	  // 初始化定时器
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
		// 清除计数器中断标志位
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);
	  
		// 开启计数器中断
    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
		
		// 使能计数器
    TIM_Cmd(TIM4, ENABLE);
}

//定时器4中断服务程序
void TIM4_IRQHandler(void)   //TIM4中断		
{
		if ( TIM_GetITStatus( TIM4, TIM_IT_Update) != RESET ) 
		{	
				TIM_ClearITPendingBit(TIM4, TIM_FLAG_Update);  	
				gizTimerMs();
		}		 	
}
