#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Delay.h"
#include "DS18B20.h"
#include "jiaohu.h"
#include "IC.h"
#include "stepmotor.h"
#include "relay.h"
#include "bee.h"
#include "intertim.h"
#include "usart1.h"
#include "usart2.h"
#include "time.h"
#include "gizwits_protocol.h"
#include "gizwits_product.h"	
#include "water.h"


extern uint8_t zhuangtai;
	

//编码格式：GB2312

int main(void)
{
	

	MOTOR_Init();         //电机控制引脚初始化
	OLED_Init();		  //OLED初始化
	IC_Init();           //输入捕获模式初始化
	Key_Init();          //按键引脚初始化
	chushijiemian();    //输液系统启动初始界面
	RELAY_Init();       //继电器初始化
	Bee_Init();         //蜂鸣器初始化
	Timer3_Init();     //定时器初始化
	
	USART1_Config();
	USART2_Config();
	TIM4_Int_Init(1000-1,72-1);
	
	
	userInit();
	gizwitsInit();
	gizwitsSetMode(WIFI_SOFTAP_MODE);
	
	while (1)
	{
	
	anjianjiance();     //循环检测按键是否被按下
	disushezhi();       //OLED屏幕上显示设置的滴速
	temset();           //OLED屏幕上显示设置的温度
	kaiguan_control();  //检测系统运行状态


	if(zhuangtai==1)  //单独一个按键控制系统运行状态
	{
	TIM2_START();     //启动定时器2
	TIM3_START();     //启动定时器3
	disujiance();     //不断检测滴速
	wendujiance();    //不断检测温度
	yaoyejiance();    //不断检测药液有无
	Relay_Control();  //调用继电器控制函数，根据设定的阈值控制加热片
	Motor_Control();  //调用电机控制函数，根据设定的算法控制电机
	tim_alarm();          //蜂鸣器报警
	
	userHandle();
        
	gizwitsHandle((dataPoint_t *)&currentDataPoint);
	}
	else
	{
	RELAY_OFF;//关闭继电器
	MOTOR_STOP();//电机停止
	TIM2_STOP();//关闭定时器2，并将计数器清0
	TIM3_STOP();//关闭定时器3，并将计数器清0
	}
	}
		
}

