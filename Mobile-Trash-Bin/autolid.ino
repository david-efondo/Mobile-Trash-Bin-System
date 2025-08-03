#include <Servo.h>
#define trigPin 9
#define echoPin 8
Servo servo1;
long distance = 0;
long duration = 0;
int angle = 0;
 
void setup() 
{
  Serial.begin(9600);
  servo1.attach(7); 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
  
if (distance <= 30)
  {
    servo1.write(100);
    delay(5000);
  }
  else 
  {
      servo1.write(0);
  }
  delay(2000);
}