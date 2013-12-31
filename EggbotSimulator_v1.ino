#include <GSerialCommand.h>
#include <AccelStepper.h>
#include <Servo.h> 
 

AccelStepper motorA(4, 2, 4, 3, 5);
AccelStepper motorB(4, 8, 10, 9, 11);

Servo myservo;

long interval = 1000;  
GSerialCommand sCmd;     // The demo SerialCommand object
boolean turning = false;
long previousMillis = 0; 
int stepsPerRevolution = 2048;
int STEPSPERREVOLUTION = 3200;
double MAXSPEED = 400.0;
double MAXACCELERATION = 400.0;
float ratio;
void setup() {
  
   Serial.begin(9600);
   
   sCmd.addCommand("SM",     processCommand);  // Converts two arguments to integers and echos them back 
   sCmd.addCommand("SP", processCommand2);
   sCmd.addCommand("QB", returnposition);
   sCmd.addCommand("v", returnversion);
   sCmd.setDefaultHandler(unrecognized);      // Handler for command that isn't matched  (says "What?")
   
   myservo.attach(12);
   
    motorA.setMaxSpeed(MAXSPEED);
  motorA.setAcceleration(MAXACCELERATION);
  motorB.setMaxSpeed(MAXSPEED);
  motorB.setAcceleration(MAXACCELERATION);
  turning = false; 
  
}

void loop() {
    if(turning == false)
    {
      unsigned long currentMillis = millis();
      sCmd.readSerial();    
      if(currentMillis - previousMillis > interval) 
      {
        previousMillis = currentMillis;  
      }
    }
    while(turning == true)
    {
      
      motorA.run();
      motorB.run();
       if (motorA.distanceToGo() == 0 && motorB.distanceToGo() == 0 && turning == true)
       {
       
          Serial.println("OK\n\r");
          turning = false;
       }
    }
    
}

void unrecognized(const char *command) 
{
  Serial.println("OK\n\r");
}


void processCommand() {
  float x;
  float d; 
  char *arg;
  arg = sCmd.next();
  if (arg != NULL) 
  {
    d = atof(arg);    
  }
  
  arg = sCmd.next();
  if (arg != NULL) 
  {
    x = atof(arg);    
  }
  
  float y;
  arg = sCmd.next();
  if (arg != NULL) 
  {
    y = atof(arg);
    if( x == 0 && y == 0)
    {
      delay(d);
      Serial.println("OK\n\r");
    }
    else
    {
      ratio = x/y;
       
  
      if (ratio >=1 || y==0 && x>0)
      {
        //x>y
        motorA.setMaxSpeed(MAXSPEED);
        motorA.setAcceleration(MAXACCELERATION);
        motorB.setMaxSpeed(MAXSPEED/ratio);
        motorB.setAcceleration(MAXACCELERATION/ratio);
      }
      if (ratio <1 && ratio >0)
      {
        //y>x
        motorA.setMaxSpeed(MAXSPEED*ratio);
        motorA.setAcceleration(MAXACCELERATION*ratio);
        motorB.setMaxSpeed(MAXSPEED);
        motorB.setAcceleration(MAXACCELERATION);
      }
      if (ratio >=-1 && ratio <0)
      {
        //x>y
        motorA.setMaxSpeed(MAXSPEED*-ratio);
        motorA.setAcceleration(MAXACCELERATION*-ratio);
        motorB.setMaxSpeed(MAXSPEED);
        motorB.setAcceleration(MAXACCELERATION);
      }
      if (ratio< -1)
      {
        //y>x
        motorA.setMaxSpeed(MAXSPEED*-ratio);
        motorA.setAcceleration(MAXACCELERATION*-ratio);
        motorB.setMaxSpeed(MAXSPEED);
        motorB.setAcceleration(MAXACCELERATION);
      }
      if (y==0 && x<0)
      {
        
        motorA.setMaxSpeed(MAXSPEED);
        motorA.setAcceleration(MAXACCELERATION);
      }
      if(y != 0)
      {
        motorB.move(y*5.688*360/STEPSPERREVOLUTION);
      }
      if (x!= 0)
      {
        motorA.move(x*5.688*360/STEPSPERREVOLUTION);
  
      }
      turning = true;
    }
  }
}

 void returnposition()
 {
   Serial.println("0");
   Serial.println("OK\n\r");
 }
 
 void returnversion()
 {
   Serial.println("EBB Version 2.1-");
   Serial.println("OK\n\r");
 }


 void processCommand2() {
   char *arg;
   arg = sCmd.next();
   int iNumber = atoi(arg);
   
   if (arg != NULL) 
   {
     iNumber = atoi(arg); 
       if (iNumber == 1)
       {
         myservo.write(0);
       }
       else
       {
        myservo.write(180);
       }
   }
   Serial.println("OK\n\r");
}
 

