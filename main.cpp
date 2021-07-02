#include <VirtualWire.h>
#include<Wire.h>

int buttonstate=0;

int Right = 11;
int Left = 10;
int left_arrow = 8;
int right_arrow = 7;
int IR=4;
long int i = 0;
char a,b;

const int MPU_addr=0x68;// 12C address of th
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

void setup()
{
// Initialize the I0 and ISR

pinMode (Right, INPUT);
pinMode (Left, INPUT);
pinMode (left_arrow,INPUT);
pinMode (right_arrow, INPUT);

vw_set_tx_pin(2);

Wire.begin();
Wire.beginTransmission (MPU_addr);
Wire.write (0x6B); // PWR_MGMT_1 register
Wire.write(0); // set to zero (wakes up the MPU-6050)
Wire.endTransmission (true);
vw_setup (4000); // Bits per sec
Serial.begin (9600);
}
void loop()
{
i=0;
Wire.beginTransmission (MPU_addr);
Wire.write (0x3B); // starting with register Ox3B (ACCEL_XOUT_H)
Wire.endTransmission (false);
Wire.requestFrom (MPU_addr, 14, true); // request a total of 14 registers
AcX=Wire.read()<<8|Wire.read(); // Ox 3B (ACCEL_XOUT_H) : Ox3C (ACCEL_XOUT_L)
AcY=Wire.read()<<8|Wire.read(); // Ox3D (ACCEL_YOUT_H) s OX3E (ACCEL_YOUT_L)
AcZ=Wire.read()<<8|Wire.read(); // 0x3F (RCCEL_ZOUT_M) 0x40 (ACCEL_ZOUT_I)
Tmp=Wire.read()<<8|Wire.read();// 0x41 (TEMP OUT) 50x42 (TEMP_OUT_L!
GyX=Wire.read()<<8|Wire.read(); //0x43 (GYRO XOUT # $ 0x44 (GYRO XOUT L)
GyY=Wire.read()<<8|Wire.read(); // 0x45 (GYRO YOUTH) 50x46 (GYRO YOUT L)
GyZ=Wire.read()<<8|Wire.read(); // Ox 47 GYRO_20UT_$) 50x45 (GYRO_20UI_L)

GyZ = -GyZ/300;
GyX = GyX/280;
if(GyX ==-1)
  GyX =0;

char cGyZ[4];
  itoa(GyZ,cGyZ,10);

char cGyX[4];
  itoa(GyX,cGyX,10);




char dest[6];
strcpy (dest, cGyZ);
strcat (dest, "H");
strcat (dest, cGyX);
strcat (dest, "A");


if(digitalRead (Right)==HIGH)
  {
    strcat (dest, "r");
   
  }
if(digitalRead (Left)==HIGH)
 {
  strcat (dest, "s");
 
 }
if(digitalRead(right_arrow) == HIGH)
  {
    strcat (dest, "t");
   
  }
if(digitalRead(left_arrow) == HIGH)
  {
    strcat(dest, "i");
   
  }



Serial.print (GyZ);
Serial.print (" ");
Serial.print (GyX);
Serial.print ("\t");
Serial.println(dest);
vw_send( (uint8_t *) dest, strlen (dest));
vw_wait_tx ();



}