#include <LiquidCrystal.h>                  //the liquid crystal library contains commands for printing to the display
#include <arduinoFFT.h>                     //Import Library for reading the audio input as Hertz (This was found online as part of me trying to solve the problem of audio noise) 
 
#define SAMPLES 128                         //SAMPLES-pt FFT. Must be a base 2 number. Max 128 for Arduino Uno.
#define SAMPLING_FREQUENCY 2048              //Ts = Based on Nyquist, must be 2 times the highest expected frequency.
 

 
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);      
arduinoFFT FFT = arduinoFFT();
int sensorPin = A0;
boolean val =0;
double audioInput;
String note;
int ledNum=0;

unsigned int samplingPeriod;
unsigned long microSeconds;
double vReal[SAMPLES];                    //create vector of size SAMPLES to hold real values
double vImag[SAMPLES];                    //create vector of size SAMPLES to hold imaginary values

void setup() {                     

  lcd.begin(16, 2);                                            //tell the lcd library that we are using a display that is 16 characters wide and 2 characters high
  lcd.clear();                                                  //clear the display
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(115200);                                     //Baud rate for the Serial Monitor
  samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY)); //Period in microseconds 
 // testComponents();                                       //Uncomment to test your components are working
}

void loop() {

   audioInput = findPeak();
   findNote(audioInput);
   lightLED(ledNum);
   writeToScreen(audioInput);
   
    while (1); //do one time
}  

/* Methods are to check if my outputs are working as expected. */
   
void checkLeds(){
  
  digitalWrite(3, HIGH);   // Turn on the LED
  delay(1000);             // Wait for two seconds
  digitalWrite(3, LOW);    // Turn off the LED
  delay(1000);             // Wait for two seconds

  digitalWrite(4, HIGH);   // Turn on the LED
  delay(1000);             // Wait for two seconds
  digitalWrite(4, LOW);    // Turn off the LED
  delay(1000);             // Wait for two seconds

  digitalWrite(5, HIGH);   // Turn on the LED
  delay(1000);             // Wait for two seconds
  digitalWrite(5, LOW);    // Turn off the LED
  delay(1000);             // Wait for two seconds
}


void checkLCD(){
  
  lcd.setCursor(0,0);       //set the cursor to the 0,0 position (top left corner)
  lcd.print("Test");       //print hello, world! starting at that position

  lcd.setCursor(0,1);       //move the cursor to the first space of the bottom row
  lcd.print("Successful");         //print the number of seconds that have passed since the last reset
  
}

void checkMic(){
  val =analogRead(sensorPin);
  Serial.println (val); // when the sensor detects a signal above the threshold value, LED flashes
  if (val==HIGH) {
    digitalWrite(5, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(3, HIGH);
  }
  else {
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
  }
  delay(3000);
}

void testComponents(){
  checkLCD();     // Write to Screen
  checkLeds();    // Blink each light once 
  checkMic();     // If there is Audio input Turn all lights on
  reset();
}

void reset(){
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    lcd.clear();  
}


/* Methods for the rest of the project, code to find avg frequency was chop-shopped from https://create.arduino.cc/projecthub/calettso/audio-frequency-detector-617856 */ 

double findPeak(){
     for(int i=0; i<SAMPLES; i++)
    {
        microSeconds = micros();    //Returns the number of microseconds since the Arduino board began running the current script. 
     
        vReal[i] = analogRead(sensorPin); //Reads the value from analog pin 0 (A0), quantize it and save it as a real term.
        vImag[i] = 0; //Makes imaginary term 0 always

        /*remaining wait time between samples if necessary*/
        while(micros() < (microSeconds + samplingPeriod))
        {
          //do nothing
        }
    }

        /*Perform FFT on samples*/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

    /*Find peak frequency and print peak*/
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);

    return peak;
}

/* Series of if statements to determine which sting you are on and if the note is too high or too low. */

void findNote(double htz){
  //LOW E
  
  if (htz >154 && htz < 174){
    note = "Low E";
    if(htz < 163 ){
      ledNum = 1;
    }else if(htz >165){
      ledNum = 3;
    }else{
      ledNum = 2; 
    }
  }

    if (htz >70 && htz < 90){
    note = "Low E";
    if(htz < 79 ){
      ledNum = 1;
    }else if(htz >81){
      ledNum = 3;
    }else{
      ledNum = 2; 
    }
  }

  //A
  
  if (htz >112 && htz < 122){
    note = "A";
    if(htz < 111 ){
      ledNum = 1;
    }else if(htz >113){
      ledNum = 3;
    }else{
      ledNum = 2; 
    }
  }

    if (htz >212 && htz < 232){
    note = "A";
    if(htz < 221 ){
      ledNum = 1;
    }else if(htz >223){
      ledNum = 3;
    }else{
      ledNum = 2; 
    }
  }

    //D
  
  if (htz >137 && htz < 157){
    note = "D";
    if(htz < 146 ){
      ledNum = 1;
    }else if(htz >148){
      ledNum = 3;
    }else{
      ledNum = 2; 
    }
  }

    //G
  
  if (htz >390 && htz < 410){
    note = "G";
    if(htz < 399 ){
      ledNum = 1;
    }else if(htz > 401){
      ledNum = 3;
    }else{
      ledNum = 2; 
    }
  }

    //B
  
  if (htz >490 && htz < 510){
    note = "B";
    if(htz < 499 ){
      ledNum = 1;
    }else if(htz >502){
      ledNum = 3;
    }else{
      ledNum = 2; 
    }
  }

    //HIGH E
  
  if (htz >325 && htz < 345 ){
    note = "HIGH E";
    if(htz < 334 ){
      ledNum = 1;
    }else if(htz >336){
      ledNum = 3;
    }else{
      ledNum = 2; 
    }
  }
  
}

/* Switch statement to see which led to light up */
void lightLED(int number){
  
  switch (number){ 
    case 1:
    digitalWrite(5, HIGH);
    break;
  
    case 2:
    digitalWrite(4, HIGH);
    break;
  
    case 3:
    digitalWrite(3, HIGH);
    break;

    default:
    break;
  }
}   

/* Write the note (String thats being played) and the frequency to the screen. */

void writeToScreen(double htz){
  
  lcd.setCursor(0,0);       
  lcd.print(note);       

  lcd.setCursor(0,1);       
  lcd.print(htz);
  
}
