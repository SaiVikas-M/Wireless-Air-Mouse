#include<Keyboard.h>
#include<Mouse.h>
#include<VirtualWire.h>
//int 1:
int k = 0;
int n=0;
char a, b,c;
void setup ()
{
//Serial.begin (9600); // Debugging only
vw_setup (4000); // Bits per sec
vw_rx_start (); // Start the receiver PLL running
Keyboard.begin();
Mouse.begin();
}
void loop ()
{
uint8_t buf [VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;
char data[VW_MAX_MESSAGE_LEN] = {'0'};
char X[VW_MAX_MESSAGE_LEN] = {'0'};
char Y[VW_MAX_MESSAGE_LEN]={'0'};

if (vw_get_message (buf, &buflen)) // Non-blocking
{
// Message with a good checksum received, dump it.
for(int i = 0; i < buflen; i++)
{
data[i] = (char)buf[i];
}
for(int j = 0; j < buflen; j++)
{
if(data[j] != 'H'){

X[j] = data[j];
}
else

break;
}
for (k=0;data[k] !='A';k++)
{
if (data[k]=='H')
{
for (n=k+1;data [n] !='A';n++)
{
Y[n-k-1]=data [n];
}
break;
}
}

for (int m = 0; m<buflen; m++)
{
if(data[m] == 'A')
{
a=data [m+1];

break;
}
}
int xAxis = 0;
xAxis =atoi (X) ;
int yAxis = 0;
yAxis =atoi (Y);

Serial.print (data);
Serial.print ("\t");
Serial.print (X);
Serial.print ("\t");
Serial.print (Y) ;

Serial.print ("\t");
Serial.print (xAxis);
Serial.print ("\t");
Serial.print (yAxis);
Serial.print ("\t");
Serial.println (a);

Mouse.move (xAxis, yAxis);
if(a!=c)
{
if(a=='r')
{
Mouse.click(MOUSE_RIGHT);
delay (200);
}
if(a=='s')
{
Mouse.click (MOUSE_LEFT);
delay (200);
}
if (a=='h')
{
Mouse.press (MOUSE_LEFT);
delay (200);
}
if (a=='i')
{
Keyboard.press (0xD8) ;
delay (200) ;
Keyboard.releaseAll ();
}
if(a=='t')
{
Keyboard.press (0xD7) ;
delay (200);
Keyboard.releaseAll ();
}
}
c=a;
}
}
