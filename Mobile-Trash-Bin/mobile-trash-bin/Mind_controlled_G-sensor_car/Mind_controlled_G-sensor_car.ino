//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL_RX 2
#define REMOTEXY_SERIAL_TX 3
#define REMOTEXY_SERIAL_SPEED 9600


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 59 bytes
  { 255,3,0,0,0,52,0,16,31,1,5,32,11,51,41,41,4,26,31,2,
  0,21,27,22,11,4,26,31,31,76,70,0,66,84,0,129,0,3,8,57,
  6,12,77,79,66,73,76,69,32,84,82,65,83,72,32,66,73,78,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  int8_t joystick_1_x; // from -100 to 100  
  int8_t joystick_1_y; // from -100 to 100  
  uint8_t switch_1; // =1 if switch ON and =0 if OFF 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define IN1 9 

#define IN2 8 

#define ENA 11


//defining the pins for second motor

#define IN3 5

#define IN4 4

#define ENB 10


//defining the LED pin  
#define SENSOR_PIN_RIGHT A0
#define SENSOR_PIN_LEFT A1

#define ledpin 13 

const int sensorPinRight = A0;
const int sensorPinLeft = A1;
const int threshold = 300;

void setup() 

{ 

  //defining the motor pins as the output pins
  
  RemoteXY_Init ();
  

  pinMode (IN1, OUTPUT); 

  pinMode (IN2, OUTPUT); 

  pinMode (IN3, OUTPUT); 

  pinMode (IN4, OUTPUT); 

}

unsigned char first_motor[3] =  

  {IN1, IN2, ENA}; 

unsigned char second_motor[3] =  

  {IN3, IN4, ENB}; 


void Speed (unsigned char * pointer, int motor_speed) 

{ 

  if (motor_speed>100) motor_speed=100; 

  if (motor_speed<-100) motor_speed=-100; 

  if (motor_speed>0) { 

    digitalWrite(pointer[0], HIGH); 

    digitalWrite(pointer[1], LOW); 

    analogWrite(pointer[2], motor_speed*2.00); 

  } 

  else if (motor_speed<0) { 

    digitalWrite(pointer[0], LOW); 

    digitalWrite(pointer[1], HIGH); 

    analogWrite(pointer[2], (-motor_speed)*2.00); 

  } 

  else { 

    digitalWrite(pointer[0], LOW); 

    digitalWrite(pointer[1], LOW); 

    analogWrite(pointer[2], 0); 

  } 


} 





void loop() 

{ 

  RemoteXY_Handler (); 
   if (RemoteXY.switch_1 == 1)
  {
    int sensorValueLeft = analogRead(sensorPinLeft);
    int sensorValueRight = analogRead(sensorPinRight);

    // Check if both sensors detect the line
    if (sensorValueLeft < threshold && sensorValueRight < threshold)
    {
            Speed(first_motor, -35);
      Speed(second_motor, 35);
      // Line detected, move forward

    }
        else if (sensorValueLeft < threshold)
    {
      // Only right sensor detects the line, turn right
      Speed(first_motor, 80);
      Speed(second_motor, 80);
    }
    else if (sensorValueRight < threshold)
    {
      // Only left sensor detects the line, turn left
      Speed(first_motor, -80);
      Speed(second_motor, -80);
    }

    else
    {
      Speed(first_motor, 0);
      Speed(second_motor, 0);
      // Line not detected, stop motors

 
    }
  }
    else
  {
    int motor_speed1 = RemoteXY.joystick_1_x - RemoteXY.joystick_1_y;
    int motor_speed2 = RemoteXY.joystick_1_x + RemoteXY.joystick_1_y;
    

  Speed (first_motor, RemoteXY.joystick_1_x- RemoteXY.joystick_1_y); 

  Speed (second_motor, RemoteXY.joystick_1_y + RemoteXY.joystick_1_x); 

  }
  }