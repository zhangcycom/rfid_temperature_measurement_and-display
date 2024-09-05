 /**************************************************************************
* �� �� ���� main.c
* ʹ��оƬ�� STM32F103C8T6
* Ӳ�����ӣ� ��
* �������ܣ� ����MLX90614�ɼ��¶ȣ�OLED��ʾ
* �޸ļ�¼�� ��
**************************************************************************/

#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"	 
#include "mlx90614.h" 
#include "oled.h"


//�¶ȵĵ�λ ��
unsigned char TempCompany[][16]=
{
	0x06,0x09,0x09,0xE6,0xF8,0x0C,0x04,0x02,0x02,0x02,0x02,0x02,0x04,0x1E,0x00,0x00,
	0x00,0x00,0x00,0x07,0x1F,0x30,0x20,0x40,0x40,0x40,0x40,0x40,0x20,0x10,0x00,0x00,/*"��",0*/	
};

int main(void)
{	
//	uint8_t i,j;	
	float Temperature = 0;    //�¶����ݱ����������ͣ�
	char TempValue[80] = {0}; //�¶�ֵ���ַ�����
	int k=20;
	delay_init();	  //��ʱ������ʼ��	  
	uart_init(115200);//���ڳ�ʼ��Ϊ115200
	OLED_Init();
	OLED_Clear();
 	LED_Init();		//LED�˿ڳ�ʼ��
  SMBus_Init();
    display();//��ʾ�����ַ�
	
	//ִ��while
	while(1)
	{		
		Temperature = SMBus_ReadTemp();
		printf("Temperature = %f\r\n",Temperature);	//�ڴ��ڵ��������ϴ�ӡ���
		delay_ms(100);//������ʱ�ڴ����Ͽ���������
		sprintf(TempValue,"%.1f", Temperature); //������ת�����ַ���		

		OLED_ShowString(40,0,(uint8_t *)TempValue,16);//��OLED����ʾʵʱ�������¶�
    
		//�����¶���ֵ������37.3��Ϊ�쳣
		if(Temperature>37.3)
		{
			while(k--)//��˸2s
			{
				PCout(13)=!PCout(13);
			  delay_ms(100);				
			}
			k=20;
		}
	}
}


