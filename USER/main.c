 /**************************************************************************
* 文 件 名： main.c
* 使用芯片： STM32F103C8T6
* 硬件连接： 无
* 描述功能： 利用MLX90614采集温度，OLED显示
* 修改记录： 无
**************************************************************************/

#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"	 
#include "mlx90614.h" 
#include "oled.h"


//温度的单位 ℃
unsigned char TempCompany[][16]=
{
	0x06,0x09,0x09,0xE6,0xF8,0x0C,0x04,0x02,0x02,0x02,0x02,0x02,0x04,0x1E,0x00,0x00,
	0x00,0x00,0x00,0x07,0x1F,0x30,0x20,0x40,0x40,0x40,0x40,0x40,0x20,0x10,0x00,0x00,/*"℃",0*/	
};

int main(void)
{	
//	uint8_t i,j;	
	float Temperature = 0;    //温度数据变量（浮点型）
	char TempValue[80] = {0}; //温度值（字符串）
	int k=20;
	delay_init();	  //延时函数初始化	  
	uart_init(115200);//串口初始化为115200
	OLED_Init();
	OLED_Clear();
 	LED_Init();		//LED端口初始化
  SMBus_Init();
    display();//显示不变字符
	
	//执行while
	while(1)
	{		
		Temperature = SMBus_ReadTemp();
		printf("Temperature = %f\r\n",Temperature);	//在串口调试助手上打印结果
		delay_ms(100);//不加延时在串口上看不到数据
		sprintf(TempValue,"%.1f", Temperature); //浮点型转换成字符串		

		OLED_ShowString(40,0,(uint8_t *)TempValue,16);//在OLED上显示实时测量的温度
    
		//设置温度阈值，超过37.3℃为异常
		if(Temperature>37.3)
		{
			while(k--)//闪烁2s
			{
				PCout(13)=!PCout(13);
			  delay_ms(100);				
			}
			k=20;
		}
	}
}


