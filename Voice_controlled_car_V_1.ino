

/*
 -----------------------------------------
  Mert Arduino Tutorial and Projects
  Subscribe for more videos and projects
  Thanks all subscribers ;)
 ----------------------------------------
*/

#include <AFMotor.h> //Adafruit Motor Shield Library. First you must download and install AFMotor library
#include <Servo.h>   //Servo library. This is standard library. (Sketch -> Include Library -> Servo)
//#include <Keypad.h>

String voice;
int i,lockflag,lp;

//char* password ="123"; //create a password
int pozisyon = 0; //keypad position

const byte rows = 4; //number of the keypad's rows and columns
const byte cols = 4;

char keyMap [rows] [cols] = { //define the cymbols on the buttons of the keypad

  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

//byte rowPins [rows] = {6, 7, 8, 9}; //pins of the keypad
//byte colPins [cols] = {5, 11, 12, 13};

//Keypad myKeypad = Keypad( makeKeymap(keyMap), rowPins, colPins, rows, cols);



AF_DCMotor motor1 (1, MOTOR12_1KHZ); //create motor #1 using M1 output on Motor Drive Shield, set to 1kHz PWM frequency
AF_DCMotor motor2 (2, MOTOR12_1KHZ); //create motor #2 using M2 output on Motor Drive Shield, set to 1kHz PWM frequency
AF_DCMotor motor3 (3, MOTOR34_1KHZ);
Servo servo; //define servo name
Servo servo1;
int LED1 = A0; //define LED 1 pin
int LED2 = 2; //define LED 2 pin
//int LED3 = A2;
int buzzerPin = A3; //define buzzer pin
const int trigPin = A2;
const int echoPin = A1;
float tempC;
float tempF;
int tempPin = 6;

long duration;
int distance;
int safetyDistance;
int angle;

void setup()
{
  
  Serial.begin(9600); //start serial communication
  servo.attach(10);
  servo.write(90);

  servo1.attach(9);
  servo1.write(angle);
  
//  myServo.attach(10); //define our servo pin (the motor shield servo1 input = digital pin 10)
//  myServo.write(90);  //servo position is 90 degrees
  pinMode(LED1, OUTPUT); //A0 is output pin
  pinMode(LED2, OUTPUT); //A1 is output pin
  pinMode(buzzerPin, OUTPUT); //A2 is output pin
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  setLocked (true);
}

void loop() 
{
  
 forward_car();
//  if(lockflag==0){
//  char whichKey = myKeypad.getKey();
//
//  if(whichKey == '*' || whichKey == '#' || whichKey == 'A' ||       //define invalid keys
//  whichKey == 'B' || whichKey == 'C' || whichKey == 'D'){
//        pozisyon=0;
//        setLocked (true);
//        //digitalWrite(LED2, LOW);
//        lockflag==0;
//        delay(500);
//  }
//  else if(whichKey == '1' || whichKey == '2' || whichKey == '3' ||       //define invalid keys
//  whichKey == '4' || whichKey == '5' || whichKey == '6')
//  {
//    Serial.println("Kisu chapse");
//  }
//  if(whichKey == password [pozisyon]){
//
//    pozisyon ++;
//  }
//  if(pozisyon == 3){
//    //digitalWrite(LED2, HIGH);
//    setLocked (false);
//    lockflag=1;
//    
//  }
//  delay(100);
//  
//
//  }
//  else{

//    delay(2000);
//    digitalWrite(LED2, LOW);
//    for(lp=0;lp<4;lp++)
//    {
//      digitalWrite(rowPins[lp],LOW);
//      digitalWrite(colPins[lp],LOW);
//    }
 
 
// back_car();
 if(i==0){
    digitalWrite (buzzerPin, LOW);
 }
  while (Serial.available()){ //Check if there is an available byte to read
     delay(10); //Delay added to make thing stable 
    char c = Serial.read(); //Conduct a serial read
    Serial.println("ABC");
    if (c == '#') {break;} //Exit the loop when the # is detected after the word
    voice += c; //Shorthand for voice = voice + c
  }
  if (voice.length() > 0){
    if(voice.equals("*go ahead")){
      digitalWrite (buzzerPin, LOW);
      forward_car();
      }
    else if(voice.equals("*go back")){
      digitalWrite (buzzerPin, LOW);
      back_car();
      }
    else if(voice.equals("*turn right")) {
      digitalWrite (buzzerPin, LOW);
      right_car();
      voice="*go ahead";
      
    }
    else if(voice.equals("*turn left")) {
      digitalWrite (buzzerPin, LOW);
      left_car();
      voice="*go ahead";
    }
    else if(voice.equals("*turn on light")) {
      digitalWrite (buzzerPin, LOW);
      LED_on();
    }
    else if(voice.equals("*turn off light")) {
      digitalWrite (buzzerPin, LOW);
      LED_off();
    }
    else if(voice.equals("*alarm on")) {
      buzzer_on();
      i=1;
    }
    else if(voice.equals("*alarm off"))
    {
      buzzer_off();
      i=0;
    }
    else if(voice.equals("*stop")) {
      stop_car();
    }
    else if(voice.equals("*open"))
    {
      servo1.write(90);
    }
    else if(voice.equals("*close"))
    {
      servo1.write(0);
    }
    else if(voice.equals("*light"))
    {
      digitalWrite(LED2, HIGH);
    }
    else if(voice.equals("*no"))
    {
      digitalWrite(LED2, LOW);
    }
    else if(voice.equals("*open door")) {
      servo.write(0);
    }
    else if(voice.equals("*close door")){
      servo.write(90);
    }
    else if(voice.equals("*call"))
    {
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      
      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      
      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration = pulseIn(echoPin, HIGH);
      
      // Calculating the distance
      distance= duration*0.034/2;
      
      safetyDistance = distance;
      if (safetyDistance <= 5){
        buzzer_on();
        i=1;
        //digitalWrite(ledPin, HIGH);
      }
      else{
        buzzer_off();
        i=0;
        //digitalWrite(ledPin, LOW);
      }
      delay(300);
    }
    else if(voice.equals("*temperature"))
    {
      
      tempC = analogRead(tempPin);           //read the value from the sensor
      tempC = ((5.0 * tempC * 100.0)/1024.0)/7;  //convert the analog data to temperature
      tempF = ((tempC*9)/5) + 32;            //convert celcius to farenheit

      if(tempC>=0 && tempC<=50)
      {
        motor3.run(FORWARD);
        motor3.setSpeed(70);
      }
      else
      {
        motor3.run(RELEASE);
      }
    }
    
  //voice=""; //Reset the variable after initiating
  }
  //}
}
void call()
{
  digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      
      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      
      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration = pulseIn(echoPin, HIGH);
      
      // Calculating the distance
      distance= duration*0.034/2;
      
      safetyDistance = distance;
      delay(100);
      if (safetyDistance <= 15){
        right_car(); 
      }
}
void forward_car()
{
  motor1.run(FORWARD);
  motor1.setSpeed(30);
  motor2.run(FORWARD);
  motor2.setSpeed(30);
  delay(2000);
   motor1.run(RELEASE);
  motor2.run(RELEASE);
}
  
void back_car()
{
  motor1.run(BACKWARD);
  motor1.setSpeed(70);
  motor2.run(BACKWARD);
  motor2.setSpeed(70);
  delay(2000);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}
  
void right_car()
{
//  myServo.write(0);
//  delay(1000);
//  myServo.write(90);
//  delay(1000);
  motor1.run(FORWARD);
  motor1.setSpeed(70);
  motor2.run(BACKWARD);
  motor2.setSpeed(70);
  delay(1000);

  motor1.run(RELEASE);
  motor2.run(RELEASE);
}
  
void left_car()
{
//  myServo.write(180);
//  delay(1000);
//  myServo.write(90);
//  delay(1000);
  motor1.run(BACKWARD);
  motor1.setSpeed(70);
  motor2.run(FORWARD);
  motor2.setSpeed(70);
  delay(1000);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void LED_on ()
{
  digitalWrite(LED1, HIGH);
//  digitalWrite(LED2, HIGH);
}

void LED_off ()
{
  digitalWrite(LED1, LOW);
//  digitalWrite(LED2, LOW);
}

void buzzer_on ()
{
  digitalWrite (buzzerPin, HIGH);
  delay(1000);
}

void buzzer_off ()
{
  digitalWrite (buzzerPin, LOW);
  delay(1000);
}

void stop_car ()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}


void setLocked(int locked){
  if(locked){
    //digitalWrite(redLED, HIGH);
  //  digitalWrite(LED2, LOW);
    }
    else{
     // digitalWrite(redLED, LOW);
//      digitalWrite(LED2, HIGH);
    }
  }

