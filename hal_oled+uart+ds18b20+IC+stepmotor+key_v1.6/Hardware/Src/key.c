
#include "key.h"
#include "gpio.h"
#include "oled.h"

uint8_t KeyNum;	
extern uint8_t currentpage;//设置初始界面为界面0，按下按键后进入界面1

uint8_t Key_GetNum(void)//获取按键值，可拓展，有多个按键时按键可增加。
{
	uint8_t KeyNum = 0;		//定义变量，默认键码值为0
	
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == 0)			//读PC13输入寄存器的状态，如果为0，则代表按键1按下
	{
		HAL_Delay(20);											//延时消抖
		while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == 0);	//等待按键松手
		HAL_Delay(20);											//延时消抖
		KeyNum = 1;												//置键码为1
	}
	
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 0)			//读PA4输入寄存器的状态，如果为0，则代表按键1按下
	{
		HAL_Delay(20);											//延时消抖
		while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 0);	//等待按键松手
		HAL_Delay(20);											//延时消抖
		KeyNum = 2;												//置键码为2
	}
	
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10) == 0)			//读PB10输入寄存器的状态，如果为0，则代表按键1按下
	{
		HAL_Delay(20);											//延时消抖
		while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10) == 0);	//等待按键松手
		HAL_Delay(20);											//延时消抖
		KeyNum = 3;												//置键码为3
	}
	
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) == 0)			//读PA12输入寄存器的状态，如果为0，则代表按键1按下
	{
		HAL_Delay(20);											//延时消抖
		while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) == 0);	//等待按键松手
		HAL_Delay(20);											//延时消抖
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
	}
