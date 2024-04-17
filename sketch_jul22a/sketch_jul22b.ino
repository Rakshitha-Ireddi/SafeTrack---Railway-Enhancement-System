#include <TinyGPS.h>
TinyGPS gps;
float flat=0, flon=0;
int but1=2;
int but2=3;
int g1=5;
int g2=7;
int r1=4;
int r2=6;
int buz=13;
void read_gps()
{
    bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial.available())
    {
      char c = Serial.read();
      if (gps.encode(c)) 
        newData = true;
   
    }
  }

  if (newData)
  {
    
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    
  }
}
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(but1,INPUT_PULLUP);
pinMode(but2,INPUT_PULLUP);
pinMode(buz,OUTPUT);
pinMode(r1,OUTPUT);
pinMode(r2,OUTPUT);
pinMode(g1,OUTPUT);
pinMode(g2,OUTPUT);
digitalWrite(r1,0);
digitalWrite(r2,0);
digitalWrite(g1,0);
digitalWrite(g2,0);
digitalWrite(buz,0);
}
void loop() {
int b1val=digitalRead(but1);
int b2val=digitalRead(but2);
//Serial.println("B1:"+String(b1val));
//Serial.println("B2:"+String(b2val));
delay(1000);
if(b1val==0)
{
  digitalWrite(r1,1);
  digitalWrite(r2,1);
   digitalWrite(g1,0);
  digitalWrite(g2,0);
 
}
else
{
  digitalWrite(g1,1);
  digitalWrite(g2,1);
  digitalWrite(r1,0);
  digitalWrite(r2,0);
}
if((b2val==0)&&(b1val==0))
{
  digitalWrite(buz,1);
  digitalWrite(g1,1);
  digitalWrite(r2,1);
  digitalWrite(g2,0);
  digitalWrite(r1,0);
  read_gps();

 Serial.println("https://www.google.com/maps/search/?api=1&query=" + String(flat,6)+ "," + String(flon,6) +"^0");
 Serial.println("ABNORMAL SIGNAL CONDITION^0");
}
else
{
  delay(10);
}
}
