// Arduino Obstacle Avoidance + Voice Control Robot
// Created by M Ideas
//You need to install the AFMotor and NewPing Libraries before uploading the sketch

#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>
#define TRIGGER_PIN A1
#define ECHO_PIN A0
#define MAX_DISTANCE 300
#define IR A5

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);



NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

Servo servo;

String voice;

void setup() {
Serial.begin(9600);
servo.attach(10);
servo.write(90);
pinMode(IR, INPUT);

}

void loop() {
  int distance = sonar.ping_cm();
  //int IR1 = digitalRead(IR);
  //Serial.println(IR1);
  
if(Serial.available()>0) {
  voice="";
  delay(2);
  voice = Serial.readString();
  delay(2);
  Serial.println(voice);

  

if (voice == "turn left") {
  left();
}else if (voice == "left") {
  left();
}else if(voice == "turn right") {
  right();
}else if(voice == "right") {
  right();
}
 
}
while(voice == "move forward") {
  forward();
}
while(voice == "move backward") {
  backward();
}
}



void forward() {
  int distance = sonar.ping_cm();
  
 if(distance < 10){
  Stop();
  voice="";
 }else {
  motor1.setSpeed(255); 
  motor1.run(FORWARD); 
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  motor3.setSpeed(255); 
  motor3.run(FORWARD); 
  motor4.setSpeed(255); 
  motor4.run(FORWARD); 
}
}
void backward() {
  int IR_Sensor = digitalRead(IR);
  if(IR_Sensor == 0) {
    Stop();
    voice="";
  }else {
  motor1.setSpeed(255); 
  motor1.run(BACKWARD); 
  motor2.setSpeed(255); 
  motor2.run(BACKWARD); 
  motor3.setSpeed(255); 
  motor3.run(BACKWARD);
  motor4.setSpeed(255); 
  motor4.run(BACKWARD); 
 
}
}
void left() {
  servo.write(180);
  delay(500);
  servo.write(90);
  delay(500);
  motor1.run(BACKWARD);
  motor1.setSpeed(255);
  motor2.run(BACKWARD);
  motor2.setSpeed(255);
  motor3.run(FORWARD);
  motor3.setSpeed(255);
  motor4.run(FORWARD);
  motor4.setSpeed(255);
  delay(700);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void right() {
  servo.write(0);
  delay(500);
  servo.write(90);
  delay(500);
  motor1.run(FORWARD);
  motor1.setSpeed(255);
  motor2.run(FORWARD);
  motor2.setSpeed(255);
  motor3.run(BACKWARD);
  motor3.setSpeed(255);
  motor4.run(BACKWARD);
  motor4.setSpeed(255);
  delay(700);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void Stop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
