/* Import pitch library for Take me on song */

/* Code for the A-Ha song was originaly found here (https://create.arduino.cc/projecthub/GeneralSpud/passive-buzzer-song-take-on-me-by-a-ha-0f04a8) and then sliced up and adapted it to my needs. 
 *  Ive taken everything out of the original code and sliced it into my rave loop with an incremented control variable to replace "i". 
 *  this way i can trick my arduino into running what I originally had as two seperate functions; "play song" and "dance", asyncronously. 
 */

#include "pitches.h"


#include <avr/wdt.h>      //Import Watchdog woof woof

/*
 * 
 *    STATE REFERANCE 
 *    
 *     RAVE = 0
 *     DRIVE = 1 
 *     REPOSITION = 2
 *     PARK = 3
 * 
 */

/*********************    INSTANTIATE VARIABLES AND ASSOCIATED PINS      **********************************************/

int photoresistor = 0;              //this variable will hold a value based on the brightness of the ambient light
int threshold = 300;                //if the photoresistor reading is below this value the the light will turn on

//the right motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 13;           //control pin 1 on the motor driver for the right motor
const int AIN2 = 12;            //control pin 2 on the motor driver for the right motor
const int PWMA = 11;            //speed control pin on the motor driver for the right motor

//the left motor will be controlled by the motor B pins on the motor driver
const int PWMB = 10;           //speed control pin on the motor driver for the left motor
const int BIN2 = 9;           //control pin 2 on the motor driver for the left motor
const int BIN1 = 8;           //control pin 1 on the motor driver for the left motor


//distance variables
const int trigPin = 6;
const int echoPin = 5;

int switchPin = 7;             //switch to turn the robot on and off

float distance = 0;            //variable to store the distance measured by the distance sensor

//robot behaviour variables
int backupTime = 300;           //amount of time that the robot will back up when it senses an object
int turnTime = 200;             //amount that the robot will turn once it has backed up
int state = 3;
bool blink = true;
int noteCount = 0;

// The melody array 
int melody[] = {
  NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, NOTE_B4, NOTE_E5, 
  NOTE_E5, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5, 
  NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, NOTE_D5, NOTE_FS5, 
  NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5
};

// The note duration, 8 = 8th note, 4 = quarter note, etc.
int durations[] = {
8, 8, 8, 4, 4, 4,
4, 8, 8, 8, 8, 8,
8, 8, 8, 4, 4, 4,
4, 8, 8, 8, 8, 8
};

// determine the length of the arrays to use in the loop iteration
int songLength = sizeof(melody)/sizeof(melody[0]);

int duration = 0;
int pause = 0;




/**************************          RUN PROGRAM CONSTRUCTOR           ****************************************/


void setup()
{
  Serial.begin(9600);               //start a serial connection with the computer
  pinMode(trigPin, OUTPUT);       //this pin will send ultrasonic pulses out from the distance sensor
  pinMode(echoPin, INPUT);        //this pin will sense when the pulses reflect back to the distance sensor

  pinMode(switchPin, INPUT_PULLUP);   //set this as a pullup to sense whether the switch is flipped


  //set the motor control pins as outputs
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  
  pinMode(4, OUTPUT);              //set pin 4 as an output for the party LED

  wdt_enable(WDTO_4S);            //Enable watchdog 
}

/****************************      MAIN METHOD / PRORAM LOOP       *********************************************/

void loop()
{ 
  if(digitalRead(switchPin) == LOW){  //if the on switch is flipped
    distance = getDistance();
    Serial.print(distance);
    setState(distance);
    
  } else{                         //if the switch is off then set state to Being parked
    state = 3;
  }
  executeState();
  wdt_reset();                    // reset watchdog
}

/***********************************************************************************************************************************/

void checkForRave()
{
  photoresistor = analogRead(A0);   //set photoresistor to a number between 0 and 1023 based on how bright the ambient light is

  //if the photoresistor value is below the threshold turn the light on, otherwise turn it off
  if (photoresistor < threshold){
    state = 0;
  } else{
    digitalWrite(4, LOW);          // Turn off the LED
  }
}

/****************************************************************************************************************************/

void setState(float distance){
  if(distance < 10){                //if an object is detected
        state = 2;
      }else{                         //if no obstacle is detected drive forward
        state = 1;
  
  }
  checkForRave();                 //run check to see if the lights have dropped below photoresistor threshold
}

/****************************************************************************************************************************/

void executeState(){
  switch (state) {
    case 0:
      if (blink == true){
        digitalWrite(4, HIGH);          
      }else{
        digitalWrite(4, LOW);
      }
      
      //Dance in a circle
      rightMotor(255);
      leftMotor(-255);

      duration = 1000/ durations[noteCount];
      tone(3, melody[noteCount], duration);
      // pause between notes
      pause = duration * 1.3;
      delay(pause);
      // stop the tone
      noTone(3);

      noteCount ++;
      if (noteCount > songLength){
        noteCount = 0;
      }
      blink = !blink;
      break;
      
    case 1:
      rightMotor(255);
      leftMotor(255);
      break;
      
    case 2:
    
      //stop for a moment
      rightMotor(0);
      leftMotor(0);
      delay(200);

      //back up
      rightMotor(-255);
      leftMotor(-255);
      delay(backupTime);

      //turn away from obstacle 
      rightMotor(255);
      leftMotor(-255);    
      delay(turnTime);
      break;
      
    case 3:
      rightMotor(0);
      leftMotor(0);
      break;
    default:
      state = 3;
    break;
  } 
}


/**********************************************************************************************************************************/

void rightMotor(int motorSpeed)                       //function for driving the right motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(AIN1, HIGH);                         //set pin 1 to high
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMA, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}

/*******************************************************************************************************************************/

void leftMotor(int motorSpeed)                        //function for driving the left motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(BIN1, HIGH);                         //set pin 1 to high
    digitalWrite(BIN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(BIN1, LOW);                          //set pin 1 to low
    digitalWrite(BIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(BIN1, LOW);                          //set pin 1 to low
    digitalWrite(BIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMB, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}

/****************************************************************************************************************************/

//RETURNS THE DISTANCE MEASURED BY THE HC-SR04 DISTANCE SENSOR
float getDistance()
{
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;         //variable to store the distance calculated from the echo time

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);      //use the pulsein command to see how long it takes for the
                                          //pulse to bounce back to the sensor

  calculatedDistance = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  return calculatedDistance;              //send back the distance that was calculated
}
