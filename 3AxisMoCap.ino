#include <AccelStepper.h>

int tiltMotorSpeed = 0;
int panMotorSpeed = 0;
int slideMotorSpeed = 0;
int incomingByte=0;
char savepositions;
char go;

//variables to store saved position
long xstart=0;
long ystart=0;
long zstart=0;


AccelStepper stepper3(AccelStepper::DRIVER, 8,7);
AccelStepper stepper2(AccelStepper::DRIVER, 12,11);
AccelStepper stepper1(AccelStepper::DRIVER, 10, 9);

void setup()
{
  Serial.begin(9600);

  stepper1.setMaxSpeed(100000);
  stepper1.setSpeed(0);        
  stepper2.setMaxSpeed(100000);
  stepper2.setSpeed(0);   
  stepper3.setMaxSpeed(100000);
  stepper3.setSpeed(0);   
  

}

void loop()
{        
  stepper1.runSpeed();
  stepper2.runSpeed();
  stepper3.runSpeed();

/////////////////////////////////////////////////////////////////////////////////////
//recieve serial string

  while (Serial.available() > 5) {

    incomingByte = Serial.read();
    if (incomingByte=='#')  //Start of packet byte
    {
      tiltMotorSpeed=Serial.read(); //Pick up motor speeds 
      panMotorSpeed=Serial.read();
      slideMotorSpeed=Serial.read();
      savepositions=Serial.read();
      go=Serial.read();
      
/////////////////////////////////////////////////////////////////////////////////////
// if button on controller is pressed save current position
      if   (savepositions=='H'){
        saveposition (stepper1.currentPosition(),stepper2.currentPosition(),stepper3.currentPosition());
      }

/////////////////////////////////////////////////////////////////////////////////////
// if button on controller is pressed go to saved position
      if   (go=='H'){
        stepper1.moveTo(xstart);
        stepper2.moveTo(ystart);
        stepper3.moveTo(zstart);
      }


/////////////////////////////////////////////////////////////////////////////////////
//set speed for tilt motor
      if (tiltMotorSpeed>=128)
      {
        tiltMotorSpeed=tiltMotorSpeed-256;
      }

      if (abs(tiltMotorSpeed)<11){
        stepper1.setSpeed(0);
      }
      else
      {
        stepper1.setSpeed(tiltMotorSpeed*10);
      }

/////////////////////////////////////////////////////////////////////////////////////
//set speed for pan motor

      if (panMotorSpeed>=128)
      {
        panMotorSpeed=panMotorSpeed-256;
      }

      if (abs(panMotorSpeed)<11){
        stepper2.setSpeed(0);
      }
      else
      {
        stepper2.setSpeed(panMotorSpeed*10);
      }

/////////////////////////////////////////////////////////////////////////////////////
//Set speed for slide motor
      if (slideMotorSpeed>=128)
      {
        slideMotorSpeed=slideMotorSpeed-256;
      }

      if (abs(slideMotorSpeed)<11){
        stepper3.setSpeed(0);
      }
      else
      {
        stepper3.setSpeed(slideMotorSpeed*150);
      }
/////////////////////////////////////////////////////////////////////////////////////

    }
  }
}
//save current position
void saveposition (long x,long y,long z){
  xstart=x;
  ystart=y;
  zstart=z;
}
