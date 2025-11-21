#include "OLED.h"
#include "Ds18B20.h"
#include "IC.h"
#include "tim.h"

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

//	while(currentpage==1)
//	{
	OLED_ShowFloatNum(46,32,temperature/10,2,1,OLED_8X16);
	OLED_Update();
//	break;
//	}
}




void disujiance(void)//滴速检测
{
//	while(currentpage==1)//位于页面1时
//	{

//	OLED_ShowNum(46,16,HAL_TIM_ReadCounter(),5,OLED_8X16);	//显示计数器的值，用于测试，对项目无用	
	OLED_ShowNum(46,16,IC_GetFreq(),5,OLED_8X16);//显示滴速
	OLED_Update();
//	break;
//	}	
}



