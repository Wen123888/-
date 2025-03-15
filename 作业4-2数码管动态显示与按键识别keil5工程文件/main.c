#include <REGX51.H>
#include <INTRINS.H>

#define LED P0	//宏定义P0I/O口为LED
#define LED_Select P2	//宏定义P2I/O口为LED_Select P2	

sbit Key=P1^7;//定义P1^7I/O口为Key

unsigned int i=0,j=0;

unsigned char Sign=0;	//定义标志位，判断按键是否按下

unsigned char Position[] = {	//位选信号数组
	0x01,	//	1：0000 0001
	0x02,	//	2：0000 0010
	0x04,	//	3：0000 0100
	0x08,	//	4：0000 1000
	0x10,	//	5：0001 0000
	0x20	//	6：0010 0000
};
unsigned char LED_Num[] = {	//储存段选信号0~9的数字的数组
  0x3F, // 0: 0011 1111
  0x06, // 1: 0000 0110
  0x5B, // 2: 0101 1011
  0x4F, // 3: 0100 1111
  0x66, // 4: 0110 0110
  0x6D, // 5: 0110 1101
  0x7D, // 6: 0111 1101
  0x07, // 7: 0000 0111
  0x7F, // 8: 0111 1111
  0x6F  // 9: 0110 1111
};

unsigned char LED_Let[] = {	//储存段选信号H~O的字母的数组
	0x76,	// H：0111 0110
	0x79,	// E：0111 1001
	0x38,	// L：0011 1000
	0x38,	// L：0011 1000
	0x3f	// O：0011 1111
};
void Delay(unsigned int ms)//@12MHZ 带参延时函数
{
    unsigned int i, j;
    for (i = 0; i < ms; i++) 
	{
        for (j = 0; j < 120; j++);
	}
}

void LED_Number()	//数码管显示数字函数
{
	for(i=0;i<6;i++)//循环扫描位选引脚
	{
		//LED=0xff;	//消影
		LED_Select=~Position[i];	//将位选引脚进行移位
		LED=LED_Num[i+1];	//赋值段选引脚信号，使数码管显数字
		Delay(10);	//延时10ms，增加LED灯闪亮时间占比，增加亮度
	}
}

void LED_Letter()	//数码管显示字母函数
{
	for(j=0;j<5;j++)	//循环扫描位选引脚
	{
		//LED=0xff;	//消影
		LED_Select=~Position[j];	//将位选引脚进行移位
		LED=LED_Let[j];	//赋值段选引脚信号，使数码管显字母
		Delay(10);	//延时10ms，增加LED灯闪亮时间占比，增加亮度
	}
}

void main()	//主函数
{
		LED_Number();	//使数码管上电即显示数字
		while(1)	//无限循环
		{
				if(!Key)	//代码检测按键是否按下
				{
					Delay(20);	//延时20ms，消抖，稳定程序
					Sign=!Sign;	//当每次按键被按下后，将标志位取反
					while(!Key)//判断按键是否抬起
					{
						switch(Sign)//使数码管在按键始终处于被按下的状态仍然可以显示数字或字母	
						{
							case 0:LED_Number();break;	
							case 1:LED_Letter();break;	
						}
					}
				}
				switch(Sign)	//选择函数，通过标志位判断数码管应该显示数字或字母
					{
						case 0:LED_Number();break;	//当标志位为最初值或者是再次取反值，数码管显示数字
						case 1:LED_Letter();break;	//当标志位为取反值，数码管显示字母
					}
		}
}
