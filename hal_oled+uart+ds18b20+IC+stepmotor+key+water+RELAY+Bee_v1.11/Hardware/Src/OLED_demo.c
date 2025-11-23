#include "OLED.h"
#include "Ds18B20.h"
#include "IC.h"
#include "tim.h"
#include "water.h"
#include "bee.h"
#include "relay.h"
#include "stepmotor.h"
float temperature; 
uint8_t currentpage=0;//设置初始界面为界面0，按下按键后进入界面1

float goaltem=25.0;
uint32_t goaldisu=40;
uint8_t zhuangtai=0;


void chushijiemian(void)//OLED初始界面
{
	OLED_ShowChinese(16,24,"输液监控系统");

	OLED_Update();

}

void jiemian1(void)//检测界面布局
{	
	OLED_Clear();

	OLED_ShowChinese(0,0,"工作状态：");
	OLED_ShowChinese(0,16,"滴速：");
	OLED_ShowChinese(90,16,"滴");
	OLED_ShowChar(106,16,'/',OLED_8X16);
	OLED_ShowChinese(112,16,"分");
	OLED_Printf(46,16,OLED_8X16,"%04d",0000);
	OLED_ShowChinese(0,32,"温度：");
	OLED_ShowChinese(90,32,"℃");
	OLED_Printf(46,32,OLED_8X16,"%04.1f",00.0);
	OLED_ShowChinese(0,48,"药液：");
	OLED_Update();
	currentpage=1;
}

void jiemian2(void)//滴速设置界面布局
{
	OLED_Clear();
	
	OLED_ShowChinese(16,16,"目标滴速设置");
	OLED_ShowChinese(64,32,"滴");
	OLED_ShowChar(80,32,'/',OLED_8X16);
	OLED_ShowChinese(96,32,"分");

	OLED_Update();
	currentpage=2;
}



void jiemian3(void)//温度设置界面布局
{
	OLED_Clear();
	

	OLED_ShowChinese(16,16,"目标温度设置");
	OLED_ShowChinese(64,32,"℃");

	OLED_Update();	
	currentpage=3;
	
}


void wendujiance(void)//温度检测
{	
					//温度值
	temperature=DS18B20_Get_Temp();	//读取温度

	while(currentpage==1)
	{
	OLED_ShowFloatNum(46,32,temperature/10,2,1,OLED_8X16);
	OLED_Update();
	break;
	}
}




void disujiance(void)//滴速检测
{
	while(currentpage==1)//位于页面1时
	{

//	OLED_ShowNum(46,16,HAL_TIM_ReadCounter(),5,OLED_8X16);	//显示计数器的值，用于测试，对项目无用	
	OLED_ShowNum(46,16,IC_GetFreq(),5,OLED_8X16);//显示滴速
	OLED_Update();
	break;
	}	
}

void yaoyejiance(void)//液位检测，液位传感器有液位输出低电平，无液位输出高电平
{
	while(currentpage==1)//位于页面1时
	{
	if(WATER_GetData()==0)
	{
	OLED_ClearArea(80,48,16,16);
	OLED_ShowChinese(80,48,"有");
	OLED_Update();
	}
	if(WATER_GetData()==1)
	{
	OLED_ClearArea(80,48,16,16);
	OLED_ShowChinese(80,48,"无");
	OLED_Update();
	BEE_ON();
	}
	break;
	}
}

void disushezhi(void)//目标滴速设置
{
	while(currentpage==2)
	{
	OLED_ShowNum(16,32,goaldisu,5,OLED_8X16);
	OLED_Update();
	break;
	}

}

void temset(void)//目标温度设置
{
	while(currentpage==3)
	{
	OLED_ShowFloatNum(16,32,goaltem,2,1,OLED_8X16);
	OLED_Update();
	break;

	}

}



void Relay_Control(void)//继电器控制
{
	float wendu=temperature/10;
	while((goaltem-wendu)>2)
	{
		RELAY_ON();
//		Delay_ms(1000);
		break;
	}
	while((wendu-goaltem)>2)
	{
		RELAY_OFF();
//		Delay_ms(1000);
		break;
	}
	
}


void Motor_Control(void)//电机控制
{
/*	while(IC_GetFreq()<goaldisu)
	{
		MOTOR_Direction_Angle(0,0,45,1);
		break;
	}
	while(IC_GetFreq()>goaldisu)
	{
		MOTOR_Direction_Angle(1,0,45,1);
		break;
	}
	while(IC_GetFreq()==goaldisu)
	{
		MOTOR_STOP();
		break;
	}
*/
	int16_t diff=IC_GetFreq()-goaldisu;
//	if(TIM_GetFlagStatus(TIM3, TIM_FLAG_Update) == SET)
//	{
		while(diff>20 && diff<=60)  //三档
		{
		MOTOR_Direction_Angle(1,0,5.625,2);
		break;
		}
	
		while(diff<-20 && diff>=-60)//三档
		{
		MOTOR_Direction_Angle(0,0,5.625,2);
		break;
		}
	
	
		while(diff>5 && diff<=20)//二档
		{
		MOTOR_Direction_Angle(1,0,2.8125,2);
		break;
		}
	
		while(diff<-5 && diff>=-20)//二档
		{
		MOTOR_Direction_Angle(0,0,2.8125,2);
		break;
		}
	
		while(diff>2 && diff<=5)//一档
		{
		MOTOR_Direction_Angle(1,0,1.40625,2);
		break;
		}
	
		while(diff<-2 && diff>=-5)//一档
		{
		MOTOR_Direction_Angle(0,0,1.40625,2);
		break;
		}
	
		while(-2 <= diff && diff <= 2)//停止
		{
		MOTOR_STOP();
		break;
		}
		
/*		while(60 <diff && diff < -60)//报警(未完成)
		{
		BEE_ON();
		break;
		}
*/	
//		TIM_ClearFlag(TIM3, TIM_FLAG_Update);

//	}
}

