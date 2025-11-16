

//#include "gpio.h"
#include "Ds18B20.h"
#include "dwt_delay.h"	

//OUT为1，IN为0

void DS18B20_Rst(void)	   
{                 
	DS18B20_Mode(OUT); 	//设置为推挽输出模式
    DS18B20_Low; 				//拉低DQ电平
    Delay_us(750);    	//拉低750us（大于480us）
    DS18B20_High; 			//拉高DQ电平
	Delay_us(15);     	//等待应答15US（范围15-60us）
}
//等待DS18B20的回应
//返回1:未检测到DS18B20的存在
//返回0:存在
uint8_t DS18B20_Check(void) 	   
{   
	uint8_t retry=0;
	DS18B20_Mode(IN);	//设置为浮空输入模式，主机检测设备存在与否
 
	while (HAL_GPIO_ReadPin(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN)&&retry<200)//等待应答的过程中电平为高，延时增加，检测到电平被拉低后或延时超过200退出
	{
		retry++;
		Delay_us(1);
	};	 
	if(retry>=200)return 1;//延时大于等于200，电平没有被再次拉低，无应答脉冲，代表未检测到
	else retry=0; //延时再200us以内，电平再次被拉低，代表检测到应答脉冲，设备存在
    while (!HAL_GPIO_ReadPin(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN)&&retry<240)//拉低DQ为低电平，应答脉冲发出后，应该变回高电平，如果240us后没有拉高，代表应答脉冲不完整，仍然返回1，表示未检测到DS18B20存在
	{
		retry++;
		Delay_us(1);
	};
	if(retry>=240)return 1;	    
	return 0;
}
//从DS18B20读取一个位
//返回值：1/0
uint8_t DS18B20_Read_Bit(void) 	 //拉低至少1us最多15us释放总线，采集总线状态
{
    uint8_t data;
	DS18B20_Mode(OUT);	//设置PA6为推挽输出模式，SET OUTPUT
    DS18B20_Low;        //拉低PA6电平
	Delay_us(2);        //延时2us
    DS18B20_High;       //拉高PA6电平，释放总线
	DS18B20_Mode(IN);	//设置PA6为浮空输入模式
	Delay_us(12);       //延时12us
	if(HAL_GPIO_ReadPin(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN))data=1;//读取DS18B20发给单片机的信号是高电平还是低电平
    else data=0;	    
    Delay_us(50);       //延时50us    
    return data;
}
//从DS18B20读取一个字节
//返回值：读到的数据
uint8_t DS18B20_Read_Byte(void)     
{        
    uint8_t i,j,dat;
    dat=0;
	for (i=1;i<=8;i++)   //循环八次，阅读8bit
	{
        j=DS18B20_Read_Bit();  //从传感器读取一个电平，并存入j
        dat=(j<<7)|(dat>>1);   //j左移七位至最高位，dat右移1位丢弃最低位，|表示一个条件满足结果为真，
    }						    
    return dat;
}
//写一个字节到DS18B20
//dat：要写入的字节
void DS18B20_Write_Byte(uint8_t dat)    //写时序第一步要拉低电平，写1：在拉低后15us内选择释放总线，通过上拉电阻拉高，并在15us-60us之间保持高电平；写0：拉低后保持60us；两个写时序之间要有至少1us恢复时间 
 {             
    uint8_t j;
    uint8_t testb;
	DS18B20_Mode(OUT);	//设置PA6为推挽输出模式
    for (j=1;j<=8;j++) 
	{
        testb=dat&0x01;//判断变量dat的最低位是0还是1，&为按位与，0x01转为二进制00000001，其他位都为0，只有最低位为1，dat最低位的值与testb值相同
        dat=dat>>1;//变量dat右移一位
        if (testb) //testb值为1
        {
            DS18B20_Low;	// 写1，拉低后2us拉高，并保持60us
            Delay_us(2);                            
            DS18B20_High;
            Delay_us(60);             
        }
        else 
        {
            DS18B20_Low;	// 写0，拉低后保持60us，拉高后保持2us，为两个写时序之间的恢复时间
            Delay_us(60);             
            DS18B20_High;
            Delay_us(2);                          
        }
    }
}
//开始温度转换
void DS18B20_Start(void) 
{   						               
	DS18B20_Rst();			//发送复位脉冲
		DS18B20_Check();	 //检测应答脉冲
    DS18B20_Write_Byte(0xcc);	// skip rom
    DS18B20_Write_Byte(0x44);	// convert
	    Delay_us(100);             	

} 

//初始化DS18B20的IO口 DQ 同时检测DS的存在
//返回1:不存在
//返回0:存在    	 
uint8_t DS18B20_Init(void)
{
// 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
// 	RCC_APB2PeriphClockCmd(DS18B20_GPIO_CLK, ENABLE);	 //使能PORTA口时钟 
//	
// 	GPIO_InitStructure.GPIO_Pin = DS18B20_GPIO_PIN;				//PORTA.6 推挽输出
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(DS18B20_GPIO_PORT, &GPIO_InitStructure);

// 	GPIO_SetBits(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN);    //输出1
	DS18B20_High;
	DS18B20_Rst();

	return DS18B20_Check();
}  
//从ds18b20得到温度值
//精度：0.1C
//返回值：温度值 （-550~1250） 
short DS18B20_Get_Temp(void)
{
    uint8_t temp;
    uint8_t TL,TH;
	short tem;
    DS18B20_Start ();  			// ds1820 start convert
    DS18B20_Rst();              //复位脉冲发送
    DS18B20_Check();	        //应答脉冲发送
    DS18B20_Write_Byte(0xcc);	// skip rom
    DS18B20_Write_Byte(0xbe);	// read scratchpad指令，主机读取暂存器内容    
    TL=DS18B20_Read_Byte(); 	// LSB，读取存入低八位   
    TH=DS18B20_Read_Byte(); 	// MSB，读取存入高八位
	    	  
    if(TH>7)
    {
        TH=~TH;
        TL=~TL; 
        temp=0;					//温度为负  
    }else temp=1;				//温度为正	  	  
    tem=TH; 					//获得高八位
    tem<<=8;    
    tem+=TL;					//获得底八位
    tem=(float)tem*0.625;		//转换     
	if(temp)return tem; 		//返回温度值
	else return -tem;    
}

void DS18B20_Mode(uint8_t mode)
{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	RCC_APB2PeriphClockCmd(DS18B20_GPIO_CLK, ENABLE);	 //使能PORTA口时钟
	
	if(mode)
	{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DS18B20_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	}
	else
	{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DS18B20_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(DS18B20_GPIO_PORT, &GPIO_InitStruct);
	}
//	GPIO_Init(DS18B20_GPIO_PORT, &GPIO_InitStructure);
}


 
