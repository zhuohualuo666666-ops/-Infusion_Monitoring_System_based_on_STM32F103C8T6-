#include "OLED.h"
#include "Ds18B20.h"



float temperature; 


void jiemian2(void)//滴速设置界面布局
{
	OLED_Clear();
	
	OLED_ShowChinese(16,16,"目标滴速设置");
	OLED_ShowChinese(64,32,"滴");
	OLED_ShowChar(80,32,'/',OLED_8X16);
	OLED_ShowChinese(96,32,"分");

	OLED_Update();
//	currentpage=2;
	

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
//	currentpage=1;
	
	

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
