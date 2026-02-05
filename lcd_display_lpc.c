#include<lpc214x.h>

#define RS (1<<4)
#define RW (1<<5)
#define EN (1<<6)
#define DATA (0XFF << 8)  // D0-D7 = P0.8-P0.15

void my_delay(unsigned int ms);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_init(void);
void lcd_string(char *str);

int main(){
	IODIR0 |= RS| RW |EN| DATA;
	lcd_init();
	lcd_cmd(0X80);
	lcd_string("Hello Arm!");
	lcd_cmd(0XC0);
	lcd_string("8-bit LCD Mode");
	while(1);
}

void lcd_init(void){
	my_delay(20);
	lcd_cmd(0X38);
	lcd_cmd(0X0C);
	lcd_cmd(0X06);
	lcd_cmd(0X01);
	my_delay(2);
}
void lcd_cmd(unsigned char cmd){
	IOCLR0 = RS | RW;
	IOCLR0 = DATA;
	IOSET0 = (cmd<<8);
	IOSET0 = EN;
	my_delay(1);
	IOCLR0=EN;
	my_delay(2);
}
void lcd_data(unsigned char data){
	IOSET0 = RS;
	IOCLR0 = RW;
	IOCLR0 = DATA;
	IOSET0 = (data <<8);
	IOSET0 = EN;
	my_delay(1);
	IOCLR0 = EN;
	my_delay(2);
}
void lcd_string(char *str){
	while(*str){
		lcd_data(*str++);
	}
}
void my_delay(unsigned int ms){
	unsigned int i,j;
	for(i =0;i<ms;i++)
	 for(j=0;j<2000;j++);
}
	
