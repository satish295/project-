#include<reg51.h>
sbit RS=P1^4;
sbit EN=P1^5;
sbit in0=P1^0;
sbit in1=P1^1;
sbit in2=P1^2;
sbit in3=P1^3;
sbit LED=P3^0;
void delay();
void lcdcmd(unsigned char);
void lcddat(unsigned char);
void delayled();
void delay()
{
int i;
for(i=0;i<=1275;i++);
}
void delayled()
{
int i,j;
for(i=0;i<=1275;i++)
for(j=0;j<=10;j++);
}
void lcdcmd(unsigned char val)
{
P2=val;
RS=0;
EN=1;
delay();
EN=0;
}
void lcddat(unsigned char val)
{
P2=val;
RS=1;
EN=1;
delay();
EN=0;
}
void main()
{
char i;
char a[]={"WATER INDICATOR "};
char b[]={"TANK : EMPTY "};
char c[]={"TANK : 25% "}; 
char d[]={"TANK : 50% "}; 
char e[]={"TANK : 75% "}; 
char f[]={"TANK : 100% "}; 
P2=0x00; 
lcdcmd(0x38); 
lcdcmd(0x10); 
lcdcmd(0x0c); 
lcdcmd(0x80); 
LED=1; 
in0=0; 
in1=0; 
in2=0; 
in3=0;
while(1) 
{ 
if(in0!=1 && in1!=1 && in2!=1 && in3!=1) 
{ 
for(i=0;a[i]!=0;i++) 
{ 
lcddat(a[i]); 
} 
lcdcmd(0xc0); 
for(i=0;b[i]!=0;i++) 
{ 
lcddat(b[i]); 
}
}
else if(in3==1) 
{ 
for(i=0;a[i]!=0;i++) 
{ 
lcddat(a[i]); 
} 
lcdcmd(0xc0); 
for(i=0;f[i]!=0;i++) 
{ 
lcddat(f[i]); 
} 
while(in3==1) 
{ 
LED=0; 
delayled(); 
LED=1; 
delayled(); 
} 
} 
else if(in2==1) 
{ 
for(i=0;a[i]!=0;i++) 
{ 
lcddat(a[i]); 
} 
lcdcmd(0xc0); 
for(i=0;e[i]!=0;i++) 
{ 
lcddat(e[i]); 
} 
} 
else if(in1==1) 
{
for(i=0;a[i]!=0;i++) 
{ 
lcddat(a[i]); 
} 
lcdcmd(0xc0); 
for(i=0;d[i]!=0;i++) 
{ 
lcddat(d[i]); 
} 
} 
else if(in0==1) 
{ 
for(i=0;a[i]!=0;i++) 
{ 
lcddat(a[i]); 
} 
lcdcmd(0xc0); 
for(i=0;c[i]!=0;i++) 
{ 
lcddat(c[i]);
}
}
}
}