#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Delay.h"
#include "IC.h"
#include "DS18B20.h"
#include "relay.h"
#include "stepmotor.h"
#include "bee.h"
#include "jiaohu.h"
#include "intertim.h"
#include "water.h"




uint8_t KeyNum;		//定义用于接收按键键码的变量
uint8_t currentpage=0;//设置初始界面为界面0，按下按键后进入界面1
float goaltem=25.0;
uint32_t goaldisu=40;
uint8_t zhuangtai=0;

float temperature ; 				//温度值

uint16_t Timer2_GetCounter(void)//测试用
{
	return TIM_GetCounter(TIM2);	//返回定时器TIM2的CNT
}


uint16_t Timer3_GetCounter(void)//测试用
{
	return TIM_GetCounter(TIM3);	//返回定时器TIM2的CNT
}


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

void Key_Init(void) //按键初始化
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitTypeDef GPIOC_InitStructure;					//定义结构体变量
	
	GPIOC_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//GPIO模式，赋值为推挽输出模式
	GPIOC_InitStructure.GPIO_Pin = GPIO_Pin_13 ;			//GPIO引脚，赋值为第PC13号引脚
	GPIOC_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//GPIO速度，赋值为50MHz
	
	GPIO_Init(GPIOC, &GPIOC_InitStructure);	
	
	
	GPIO_InitTypeDef GPIOB_InitStructure;					//定义结构体变量
	
	GPIOB_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//GPIO模式，赋值为推挽输出模式
	GPIOB_InitStructure.GPIO_Pin = GPIO_Pin_10 ;			//GPIO引脚，赋值为第PB10号引脚
	GPIOB_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//GPIO速度，赋值为50MHz
	
	GPIO_Init(GPIOB, &GPIOB_InitStructure);	
	
	
	GPIO_InitTypeDef GPIOA_InitStructure;					//定义结构体变量
	
	GPIOA_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//GPIO模式，赋值为推挽输出模式
	GPIOA_InitStructure.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_12;			//GPIO引脚，赋值为第PA4号引脚
	GPIOA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//GPIO速度，赋值为50MHz
	
	GPIO_Init(GPIOA, &GPIOA_InitStructure);	

}


uint8_t Key_GetNum(void)//获取按键值，可拓展，有多个按键时按键可增加。
{
	uint8_t KeyNum = 0;		//定义变量，默认键码值为0
	
	if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == 0)			//读PC13输入寄存器的状态，如果为0，则代表按键1按下
	{
		Delay_ms(20);											//延时消抖
		while (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == 0);	//等待按键松手
		Delay_ms(20);											//延时消抖
		KeyNum = 1;												//置键码为1
	}
	
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == 0)			//读PA4输入寄存器的状态，如果为0，则代表按键1按下
	{
		Delay_ms(20);											//延时消抖
		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == 0);	//等待按键松手
		Delay_ms(20);											//延时消抖
		KeyNum = 2;												//置键码为2
	}
	
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10) == 0)			//读PB10输入寄存器的状态，如果为0，则代表按键1按下
	{
		Delay_ms(20);											//延时消抖
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10) == 0);	//等待按键松手
		Delay_ms(20);											//延时消抖
		KeyNum = 3;												//置键码为3
	}
	
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == 0)			//读PA12输入寄存器的状态，如果为0，则代表按键1按下
	{
		Delay_ms(20);											//延时消抖
		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == 0);	//等待按键松手
		Delay_ms(20);											//延时消抖
		KeyNum = 4;												//置键码为4
	}
	
	return KeyNum;			//返回键码值，如果没有按键按下，所有if都不成立，则键码为默认值0

}



	
void anjianjiance(void)//检测当前按键按下情况
{
	KeyNum = Key_GetNum();		//获取按键键码
		
		if (KeyNum == 1)			//按键1按下且系统处于关闭状态
		{
		switch (currentpage)
		{
			case 0:jiemian1();break;
			case 1:jiemian2();break;
			case 2:jiemian3();break;
			case 3:jiemian1();break;
			
		}
		}
		

		if (KeyNum == 2)			//按键2按下
		{
			if(currentpage==3 && goaltem<=34.5)
			{
			goaltem +=0.5;
			}
			if(currentpage==2 && goaldisu<=59)
			{
			goaldisu +=1;
			}
			if(currentpage==1 && zhuangtai==0)
			{
			MOTOR_Direction_Angle(1,1,90,4);

			}
			
		}
		
		if (KeyNum == 3)			//按键3按下
		{
			if(currentpage==3 && goaltem>=20.5)
			{
			goaltem -=0.5;
			}
			if(currentpage==2 && goaldisu>=21)
			{
			goaldisu -=1;
			}
			if(currentpage==1 && zhuangtai==0)
			{
			MOTOR_Direction_Angle(0,1,90,4);
			}
		}
		
		if (KeyNum == 4)			//按键4按下
		{
			if(currentpage==1)
			{
			switch (zhuangtai)
			{
				case 0:zhuangtai=1;break;
				case 1:zhuangtai=0;break;
			}
			}
		}

}


void disujiance(void)//滴速检测
{
	while(currentpage==1)//位于页面1时
	{

//	OLED_ShowNum(46,16,Timer3_GetCounter(),5,OLED_8X16);	//显示计数器的值，用于测试，对项目无用	
	OLED_ShowNum(46,16,IC_GetFreq(),5,OLED_8X16);//显示滴速
	OLED_Update();
	break;
	}	
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
		RELAY_ON;
//		Delay_ms(1000);
		break;
	}
	while((wendu-goaltem)>2)
	{
		RELAY_OFF;
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
	if(TIM_GetFlagStatus(TIM3, TIM_FLAG_Update) == SET)
	{
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

	}
}

void kaiguan_control(void)
{
	if(currentpage==1)
	{
	if(zhuangtai==0)
	{
	OLED_ClearArea(80,0,16,16);
	OLED_ShowChinese(80,0,"关");
	OLED_Update();
	}
	if(zhuangtai==1)
	{
	OLED_ClearArea(80,0,16,16);
	OLED_ShowChinese(80,0,"开");
	OLED_Update();
	}
	}
}


void tim_alarm(void)
{
	if (TIM_GetFlagStatus(TIM2, TIM_FLAG_Update) == SET) 
	{
		BEE_ON();
		TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	}
	else
	{
		BEE_OFF();
	}

}
