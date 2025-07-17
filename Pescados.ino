#include "DS3231.h"
#include "Wire.h"
#include "Servo.h"
#define OUT(pin)    pinMode(pin,OUTPUT)
#define IN(pin)     pinMode(pin,INPUT)
#define ON(pin)     digitalWrite(pin,HIGH)
#define OFF(pin)    digitalWrite(pin,LOW)
#define PWM         3

Servo myServo;
DS3231 myRTC;
char Q=0;
bool century=false;
bool h12;
bool hPM;

void setup() {
  INICIO();

}

void loop() {
  myServo.write(90);
  delay(1000);
  myServo.write(0);
  delay(1000);
  Serial.print("Año: 20");
  Serial.println(myRTC.getYear(), DEC);
  Serial.print("Mes: ");
  Serial.println(myRTC.getMonth(century), DEC);
  Serial.print("Día: ");
  Serial.println(myRTC.getDate(), DEC);
  Serial.print("Hora: ");
  Serial.println(myRTC.getHour(h12,hPM), DEC);
  Serial.print("Minuto: ");
  Serial.println(myRTC.getMinute(), DEC);
  Serial.println(" ");
  Serial.println(' ');

  if (myRTC.getHour(h12,hPM)==21 && myRTC.getMinute()==35 && Q==0)
  {
    myServo.write(45);
    ON(13);
    delay(200);
    myServo.write(0);
    Q=1;
    
  } else if (!myRTC.getMinute()==35) {
    delay(10);
    myServo.write(0);
    OFF(13);
    Q=0;
  }
  delay(1000);
}

void INICIO()
{
  pinMode(13,OUTPUT);
  pinMode(3,OUTPUT);
  Wire.begin();
  Serial.begin(9600);
  OUT(PWM);
  myRTC.setClockMode(false);
  myServo.attach(3);
}
