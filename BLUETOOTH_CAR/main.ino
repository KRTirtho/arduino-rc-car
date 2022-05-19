/*obstacle avoiding,bluetooth control,voice control robot car.
   https://srituhobby.com
*/
// v1 Motor Shield Lib
#include <AFMotor.h>
#include <Servo.h>
#include <arduino-timer.h>

#define Echo A0
#define Trig A1
#define motor 10
#define Speed 170
#define spoint 103
#define IR_PIN A4

#define FRONT_LED_PIN A2
#define BACK_LED_PIN A3
#define HORNY_PIN A5

char value;
int distance;
int Left;
int Right;
int Forward;
int Backward;

int L = 0;
int R = 0;
int F = 0;
int B = 0;

int L1 = 0;
int R1 = 0;

Servo servo;
AF_DCMotor M1(1);
AF_DCMotor M2(2);
AF_DCMotor M3(3);
AF_DCMotor M4(4);

auto fTimer = timer_create_default();
auto bTimer = timer_create_default();

void setup() {
  Serial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(IR_PIN, INPUT);
  pinMode(FRONT_LED_PIN, OUTPUT);
  pinMode(BACK_LED_PIN, OUTPUT);
  pinMode(HORNY_PIN, OUTPUT);
  servo.attach(motor);
  M1.setSpeed(Speed);
  M2.setSpeed(Speed);
  M3.setSpeed(Speed);
  M4.setSpeed(Speed);
  fTimer.every(200, stopforward);
  bTimer.every(200, stopbackward);
}
void loop() {
  fTimer.tick();
  bTimer.tick();
  // Obstacle();
  // Bluetoothcontrol();
  voicecontrol();
}

bool stopforward(void *) {
  int VF = ultrasonic();
  if (VF < 10) {
    Stop();
  }
  return true;
}

bool stopbackward(void *) {
  int VB = digitalRead(IR_PIN);
  if (VB == LOW) {
    Stop();
  }
}

void Bluetoothcontrol() {
  if (Serial.available() > 0) {
    value = Serial.read();
    Serial.println(value);
  }
  if (value == 'F') {
    forward();
  } else if (value == 'B') {
    backward();
  } else if (value == 'L') {
    left();
  } else if (value == 'R') {
    right();
  } else if (value == 'S') {
    Stop();
  }
}

void Obstacle() {
  distance = ultrasonic();
  if (distance <= 12) {
    Stop();
    backward();
    delay(100);
    Stop();
    L = leftsee();
    servo.write(spoint);
    delay(800);
    R = rightsee();
    servo.write(spoint);
    if (L < R) {
      right();
      delay(500);
      Stop();
      delay(200);
    } else if (L > R) {
      left();
      delay(500);
      Stop();
      delay(200);
    }
  } else {
    forward();
  }
}

void voicecontrol() {
  if (Serial.available() > 0) {
    value = Serial.read();
    Serial.println(value);
    if (value == 'F') {
      F = forwardsee();
      servo.write(spoint);
      if (F >= 10) {
        forward();
        delay(15);
      } else if (F < 10) {
        Stop();
      }
    } else if (value == 'B') {
      B = backwardsee();
      if (B == LOW) {
        Stop();
      } else {
        backward();
        delay(150);
      }
    } else if (value == '<') {
      L = leftsee();
      servo.write(spoint);
      if (L >= 10) {
        left();
        delay(500);
        Stop();
      } else if (L < 10) {
        Stop();
      }
    } else if (value == '>') {
      R = rightsee();
      servo.write(spoint);
      if (R >= 10) {
        right();
        delay(500);
        Stop();
      } else if (R < 10) {
        Stop();
      }
    } else if (value == 'L') {
      left();
    } else if (value == 'R') {
      right();
    } else if (value == 'T') {
      Stop();
    } else if(value == 'X'){
      digitalToggle(FRONT_LED_PIN);
    } else if(value == 'C'){
      digitalToggle(BACK_LED_PIN);
    } else if(value == 'H'){
      digitalToggle(HORNY_PIN);
    }
  }
}

int ultrasonic() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(4);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  long t = pulseIn(Echo, HIGH);
  long cm = t / 29 / 2;  // time convert distance
  return cm;
}

void digitalToggle(uint8_t pin){
  digitalWrite(pin, !analogRead(pin));
  delay(500);
}

void forward() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}

void backward() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}
void left() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}
void right() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}
void Stop() {
  digitalWrite(BACK_LED_PIN, HIGH);
  M1.run(RELEASE);
  M2.run(RELEASE);
  M3.run(RELEASE);
  M4.run(RELEASE);
}
int leftsee() {
  servo.write(20);
  delay(800);
  Left = ultrasonic();
  return Left;
}

int rightsee() {
  servo.write(180);
  delay(800);
  Right = ultrasonic();
  return Right;
}

int forwardsee() {
  servo.write(90);
  delay(800);
  Forward = ultrasonic();
  return Forward;
}

int backwardsee() {
  Backward = digitalRead(IR_PIN);
  return Backward;
}