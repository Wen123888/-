#include <REGX51.H>
#include <INTRINS.H>

#define LED P0	//�궨��P0I/O��ΪLED
#define LED_Select P2	//�궨��P2I/O��ΪLED_Select P2	

sbit Key=P1^7;//����P1^7I/O��ΪKey

unsigned int i=0,j=0;

unsigned char Sign=0;	//�����־λ���жϰ����Ƿ���

unsigned char Position[] = {	//λѡ�ź�����
	0x01,	//	1��0000 0001
	0x02,	//	2��0000 0010
	0x04,	//	3��0000 0100
	0x08,	//	4��0000 1000
	0x10,	//	5��0001 0000
	0x20	//	6��0010 0000
};
unsigned char LED_Num[] = {	//�����ѡ�ź�0~9�����ֵ�����
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

unsigned char LED_Let[] = {	//�����ѡ�ź�H~O����ĸ������
	0x76,	// H��0111 0110
	0x79,	// E��0111 1001
	0x38,	// L��0011 1000
	0x38,	// L��0011 1000
	0x3f	// O��0011 1111
};
void Delay(unsigned int ms)//@12MHZ ������ʱ����
{
    unsigned int i, j;
    for (i = 0; i < ms; i++) 
	{
        for (j = 0; j < 120; j++);
	}
}

void LED_Number()	//�������ʾ���ֺ���
{
	for(i=0;i<6;i++)//ѭ��ɨ��λѡ����
	{
		//LED=0xff;	//��Ӱ
		LED_Select=~Position[i];	//��λѡ���Ž�����λ
		LED=LED_Num[i+1];	//��ֵ��ѡ�����źţ�ʹ�����������
		Delay(10);	//��ʱ10ms������LED������ʱ��ռ�ȣ���������
	}
}

void LED_Letter()	//�������ʾ��ĸ����
{
	for(j=0;j<5;j++)	//ѭ��ɨ��λѡ����
	{
		//LED=0xff;	//��Ӱ
		LED_Select=~Position[j];	//��λѡ���Ž�����λ
		LED=LED_Let[j];	//��ֵ��ѡ�����źţ�ʹ���������ĸ
		Delay(10);	//��ʱ10ms������LED������ʱ��ռ�ȣ���������
	}
}

void main()	//������
{
		LED_Number();	//ʹ������ϵ缴��ʾ����
		while(1)	//����ѭ��
		{
				if(!Key)	//�����ⰴ���Ƿ���
				{
					Delay(20);	//��ʱ20ms���������ȶ�����
					Sign=!Sign;	//��ÿ�ΰ��������º󣬽���־λȡ��
					while(!Key)//�жϰ����Ƿ�̧��
					{
						switch(Sign)//ʹ������ڰ���ʼ�մ��ڱ����µ�״̬��Ȼ������ʾ���ֻ���ĸ	
						{
							case 0:LED_Number();break;	
							case 1:LED_Letter();break;	
						}
					}
				}
				switch(Sign)	//ѡ������ͨ����־λ�ж������Ӧ����ʾ���ֻ���ĸ
					{
						case 0:LED_Number();break;	//����־λΪ���ֵ�������ٴ�ȡ��ֵ���������ʾ����
						case 1:LED_Letter();break;	//����־λΪȡ��ֵ���������ʾ��ĸ
					}
		}
}
