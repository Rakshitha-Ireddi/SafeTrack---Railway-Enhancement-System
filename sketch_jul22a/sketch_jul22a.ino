#include <TinyGPS.h>
TinyGPS gps;
float flat=0, flon=0;
const int pingPin = A0; // Trigger Pin of Ultrasonic Sensor
const int echoPin = A1; // Echo Pin of Ultrasonic Sensor`
long duration;
int distance;
int buz=13;
int lm1=2;
int lm2=3;
int rm1=4;
int rm2=5;
int ls=8;
int Rs=9;
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
pinMode(ls,INPUT);
pinMode(Rs,INPUT);
pinMode(lm1,OUTPUT);
pinMode(lm2,OUTPUT);
pinMode(rm1,OUTPUT);
pinMode(rm2,OUTPUT);
pinMode(buz,OUTPUT);
Serial.begin(9600); // Starting Serial Terminal
pinMode(pingPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(buz,OUTPUT);
digitalWrite(lm1,0);
digitalWrite(lm2,0);
digitalWrite(rm1,0);
digitalWrite(rm2,0);
}

void loop() {
  //read_gps();
 digitalWrite(pingPin, LOW);
delayMicroseconds(2);
digitalWrite(pingPin, HIGH);
delayMicroseconds(10);
digitalWrite(pingPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance=duration*0.034/2;
 if((digitalRead(ls)==0) && (digitalRead(Rs)==0))
  {
   digitalWrite(lm1,1);
   digitalWrite(lm2,0);
   digitalWrite(rm1,1);
   digitalWrite(rm2,0); 
  }
 if((digitalRead(ls)==1) && (digitalRead(Rs)==0))
  { 
    delay(1000);
   digitalWrite(lm1,0);
   digitalWrite(lm2,0);
   digitalWrite(rm1,0);
   digitalWrite(rm2,0);
   digitalWrite(buz,1); 
   read_gps();
   Serial.println("https://www.google.com/maps/search/?api=1&query=" + String(flat,6)+ "," + String(flon,6) +"^0");
     delay(2000);
   digitalWrite(buz,0);
   digitalWrite(lm1,1);
   digitalWrite(lm2,0);
   digitalWrite(rm1,1);
   digitalWrite(rm2,0); 
  
  }
  if((digitalRead(ls)==0) && (digitalRead(Rs)==1))
  {
     delay(1000);
   digitalWrite(lm1,0);
   digitalWrite(lm2,0);
   digitalWrite(rm1,0);
   digitalWrite(rm2,0);
   digitalWrite(buz,1);
    read_gps();
    Serial.println("https://www.google.com/maps/search/?api=1&query=" + String(flat,6)+ "," + String(flon,6) +"^0");
     delay(2000);
    digitalWrite(buz,0);
   digitalWrite(lm1,1);
   digitalWrite(lm2,0);
   digitalWrite(rm1,1);
   digitalWrite(rm2,0); 

  }

 if((digitalRead(ls)==1) && (digitalRead(Rs)==1))
  {
      delay(1000);
   digitalWrite(lm1,0);
   digitalWrite(lm2,0);
   digitalWrite(rm1,0);
   digitalWrite(rm2,0);
   digitalWrite(buz,1);
    read_gps();
     Serial.println("https://www.google.com/maps/search/?api=1&query=" + String(flat,6)+ "," + String(flon,6) +"^0");
     delay(2000);
    digitalWrite(buz,0);
   digitalWrite(lm1,1);
   digitalWrite(lm2,0);
   digitalWrite(rm1,1);
   digitalWrite(rm2,0); 
  } 
 if(distance<20)
{
   digitalWrite(lm1,0);
   digitalWrite(lm2,0);
   digitalWrite(rm1,0);
   digitalWrite(rm2,0);
}
}
