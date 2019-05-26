

/*
 -----------------------------------------
  Mert Arduino Tutorial and Projects
  Subscribe for more videos and projects
  Thanks all subscribers ;)
 ----------------------------------------
*/

#include <AFMotor.h> //Adafruit Motor Shield Library. First you must download and install AFMotor library
#include <Servo.h>   //Servo library. This is standard library. (Sketch -> Include Library -> Servo)


String voice;
String code="123";
int i;
int lockflag;
int lp;
int fanflag;
void call();
void forward_car();
void right_car();
void back_car();
void rights_car();
void left_car();
void LED_on();
void LED_off();
void buzzer_on();
void buzzer_off();
void stop_car();
int flag;
int k;
int cnt;
int lock=1;
AF_DCMotor motor1 (3, MOTOR34_1KHZ); //create motor #1 using M1 output on Motor Drive Shield, set to 1kHz PWM frequency
AF_DCMotor motor2 (1, MOTOR12_1KHZ); //create motor #2 using M2 output on Motor Drive Shield, set to 1kHz PWM frequency
AF_DCMotor motor3 (4, MOTOR34_1KHZ);
Servo servo; //define servo name
Servo servo1;
int LED1 = A0; //define LED 1 pin
int LED2 = 2; //define LED 2 pin
int LED3 = A8;
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

int prev1;
int prev2;


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
  //setLocked (true);
}

void loop() 
{
  int a=0;
 if(i==0){
    digitalWrite (buzzerPin, LOW);
 }
 if(lock==1)
 {
   while(1)
    {
      a++;
      while (Serial.available())
      { //Check if there is an available byte to read
      delay(10); //Delay added to make thing stable 
      char c = Serial.read(); //Conduct a serial read
      if (c == '#') {break;} //Exit the loop when the # is detected after the word
      voice += c; //Shorthand for voice = voice + c
      }
       Serial.println(voice);
      if(voice.equals("*123"))
      {
        lock=0;
         Serial.println("Ar");
         digitalWrite(LED2, HIGH);
         delay(1500);
         digitalWrite(LED2, LOW);
         voice="";
         break;
      }
      if(a==150)
      {
      voice="";
      a=0;
      }
    }
 }
  while (Serial.available()){ //Check if there is an available byte to read
    if(flag==1)
    {
      flag=0;
      k=1;
        motor1.run(RELEASE);
      motor2.run(RELEASE);
    }
     delay(10); //Delay added to make thing stable 
    char c = Serial.read(); //Conduct a serial read
    if (c == '#') {break;} //Exit the loop when the # is detected after the word
    voice += c; //Shorthand for voice = voice + c
  }
  if(fanflag==1){
    temp();
  }
  if (voice.length() > 0){
    if(voice.equals("*go ahead")){
      digitalWrite (buzzerPin, LOW);
      forward_car();
      }
    else if(voice.equals("*go back")){
      digitalWrite (buzzerPin, LOW);
      back_car();
      k=0;
      }
    else if(voice.equals("*turn right")) {
      digitalWrite (buzzerPin, LOW);
      rights_car();
      k=0;
    }
    else if(voice.equals("*turn left")) {
      digitalWrite (buzzerPin, LOW);
      left_car();
      k=0;
    }
    else if(voice.equals("*turn on light")) {
      digitalWrite (buzzerPin, LOW);
      LED_on();
      if(k==1)
      forward_car();
      k=0;
    }
    else if(voice.equals("*turn off light")) {
      digitalWrite (buzzerPin, LOW);
      LED_off();
      if(k==1)
      forward_car();
      k=0;
    }
    else if(voice.equals("*alarm on")) {
      buzzer_on();
      i=1;
      if(k==1)
      forward_car();
      k=0;
    }
    else if(voice.equals("*alarm off"))
    {
      buzzer_off();
      i=0;
      if(k==1)
      forward_car();
      k=0;
    }
    else if(voice.equals("*stop")) {
      stop_car();
      k=0;
    }
    else if(voice.equals("*open right door"))
    {
      servo1.write(90);
      if(k==1)
      forward_car();
      k=0;
    }
    else if(voice.equals("*close right door"))
    {
      servo1.write(0);
      if(k==1)
      forward_car();
      k=0;
    }
    else if(voice.equals("*radio on"))
    {
      digitalWrite(LED3, HIGH);
      if(k==1)
      forward_car();
      k=0;
      
    }
    else if(voice.equals("*radio off"))
    {
      digitalWrite(LED3, LOW);
      if(k==1)
      forward_car();
      k=0;
    }
    else if(voice.equals("*open left door")) {
      servo.write(0);
      if(k==1)
      forward_car();
      k=0;
    }
    else if(voice.equals("*close left door")){
      servo.write(90);
      if(k==1)
      forward_car();
      k=0;
    }
    else if(voice.equals("*AC off"))
    {
      motor3.run(RELEASE);
      fanflag=0;
      if(k==1)
      forward_car();
      k=0;
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
        if(k==1)
        forward_car();
        k=0;
      }
      else{
        buzzer_off();
        i=0;
        //digitalWrite(ledPin, LOW);
        if(k==1)
        forward_car();
        k=0;
      }
      delay(300);
    }
    else if(voice.equals("*fan on"))
    {
        fanflag=1;
    }
    
  voice=""; //Reset the variable after initiating
  }
  //}
}
void temp()
{
  tempC = analogRead(tempPin);           //read the value from the sensor
      tempC = ((5.0 * tempC * 100.0)/1024.0)/7;  //convert the analog data to temperature
      tempF = ((tempC*9)/5) + 32;            //convert celcius to farenheit

      if( tempC>=20 && tempC<30)
      {
        motor3.run(FORWARD);
        motor3.setSpeed(130);
      }
      else if ( tempC>=30 && tempC<40)
      {
        motor3.run(FORWARD);
        motor3.setSpeed(150);
      }
      else if(tempC>= 40)
      {
        motor3.run(FORWARD);
        motor3.setSpeed(170);
      }
      else
      {
        motor3.run(RELEASE);
      }
      Serial.println(k);
      if(k==1){
        forward_car();
        Serial.println("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
        

      }
      k=0;
      
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
      Serial.println(distance);
      
      safetyDistance = distance;
      delay(100);
      if (safetyDistance <= 40){
        cnt++;
        
        right_car(); 
      }
      else
      cnt=0;
}
void forward_car()
{
   motor1.run(FORWARD);
  motor1.setSpeed(70);
  motor2.run(FORWARD);
  motor2.setSpeed(70);
  k=1;
  int forwardMove=0;
  while(1)
  {
    forwardMove++;
    if(forwardMove==5){
       motor1.run(FORWARD);
        motor1.setSpeed(70);
        motor2.run(FORWARD);
        motor2.setSpeed(66);
        forwardMove=0;
    }
  if(cnt==3)
  {
    cnt=0;
    Serial.println("AR");
    back_car();
    delay(700);
    motor1.run(FORWARD);
    motor1.setSpeed(70);
    motor2.run(FORWARD);
    motor2.setSpeed(70);
    right_car();
    forwardMove=0;
  }
  call();
  //Serial.println(Serial.available());
  if(Serial.available())
  {
    flag=1;
    break;
  }
 }
}
  
void back_car()
{
  motor1.run(BACKWARD);
  motor1.setSpeed(100);
  motor2.run(BACKWARD);
  motor2.setSpeed(60);
 
  delay(1000);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  delay(100);
  

}
  
void right_car()
{
//  myServo.write(0);
//  delay(1000);
//  myServo.write(90);
//  delay(1000);
   motor1.run(RELEASE);
  motor2.run(RELEASE);
  delay(500);
  motor1.run(FORWARD);
  motor1.setSpeed(100);
  motor2.run(BACKWARD);
  motor2.setSpeed(80);
  delay(500);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  delay(50);
  motor1.run(FORWARD);
  motor1.setSpeed(60);
  motor2.run(FORWARD);
  motor2.setSpeed(60);
}
void rights_car()
{
//  myServo.write(0);
//  delay(1000);
//  myServo.write(90);
//  delay(1000);
  motor1.run(FORWARD);
  motor1.setSpeed(100);
  motor2.run(BACKWARD);
  motor2.setSpeed(80);
  delay(500);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  forward_car();
}  
void left_car()
{
//  myServo.write(180);
//  delay(1000);
//  myServo.write(90);
//  delay(1000);
  motor1.run(BACKWARD);
  motor1.setSpeed(80);
  motor2.run(FORWARD);
  motor2.setSpeed(100);
  delay(500);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  forward_car();
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



