#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

#define TRIGGER_PIN A1
#define ECHO_PIN A0
#define MAX_DISTANCE 300
#define IR A5

// initial motors pin
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

int val;
int Speeed = 255;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Servo servo;

void setup() {
  Serial.begin(9600);  // Set the baud rate to your Bluetooth module.
  servo.attach(10);
  servo.write(90);
  pinMode(IR, INPUT);
}
void loop() {
  if (Serial.available() > 0) {
    val = Serial.read();

    Stop();  // initialize with motors stoped

    switch (val) {
      case 'F':
        forward();
        break;
      case 'B':
        back();
        break;
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
      case 'G':
        topleft();
        break;
      case 'I':
        topright();
        break;
      case 'H':
        bottomright();
        break;
      case 'J':
        bottomleft();
        break;
      case 'T':
        Stop();
        break;
    }
  }
}

void forward() {
  // checking obstacle ahead
  int distance = sonar.ping_cm();

  if (distance < 10) {
    Stop();
    val = 0;
  } else {
    motor1.setSpeed(Speeed);  // Define maximum velocity
    motor1.run(FORWARD);      // rotate the motor clockwise
    motor2.setSpeed(Speeed);  // Define maximum velocity
    motor2.run(FORWARD);      // rotate the motor clockwise
    motor3.setSpeed(Speeed);  // Define maximum velocity
    motor3.run(FORWARD);      // rotate the motor clockwise
    motor4.setSpeed(Speeed);  // Define maximum velocity
    motor4.run(FORWARD);      // rotate the motor clockwise
  }
}

void back() {
  int IR_Sensor = digitalRead(IR);
  if (IR_Sensor == 0) {
    Stop();
    val = 0;
  } else {
    motor1.setSpeed(Speeed);  // Define maximum velocity
    motor1.run(BACKWARD);     // rotate the motor anti-clockwise
    motor2.setSpeed(Speeed);  // Define maximum velocity
    motor2.run(BACKWARD);     // rotate the motor anti-clockwise
    motor3.setSpeed(Speeed);  // Define maximum velocity
    motor3.run(BACKWARD);     // rotate the motor anti-clockwise
    motor4.setSpeed(Speeed);  // Define maximum velocity
    motor4.run(BACKWARD);     // rotate the motor anti-clockwise
  }
}

void left() {
  servo.write(180);
  delay(100);
  int distance = sonar.ping_cm();
  servo.write(90);
  if (distance < 10) {
    Stop();
    val = 0;
  } else {
    motor1.setSpeed(Speeed);  // Define maximum velocity
    motor1.run(BACKWARD);     // rotate the motor anti-clockwise
    motor2.setSpeed(Speeed);  // Define maximum velocity
    motor2.run(BACKWARD);     // rotate the motor anti-clockwise
    motor3.setSpeed(Speeed);  // Define maximum velocity
    motor3.run(FORWARD);      // rotate the motor clockwise
    motor4.setSpeed(Speeed);  // Define maximum velocity
    motor4.run(FORWARD);      // rotate the motor clockwise
  }
}

void right() {
  servo.write(0);
  delay(100);
  int distance = sonar.ping_cm();
  servo.write(90);
  if (distance < 10) {
    Stop();
    val = 0;
  } else {
    motor1.setSpeed(Speeed);  // Define maximum velocity
    motor1.run(FORWARD);      // rotate the motor clockwise
    motor2.setSpeed(Speeed);  // Define maximum velocity
    motor2.run(FORWARD);      // rotate the motor clockwise
    motor3.setSpeed(Speeed);  // Define maximum velocity
    motor3.run(BACKWARD);     // rotate the motor anti-clockwise
    motor4.setSpeed(Speeed);  // Define maximum velocity
    motor4.run(BACKWARD);     // rotate the motor anti-clockwise
  }
}

void topleft() {
  servo.write(135);
  delay(100);
  int distance = sonar.ping_cm();
  servo.write(90);
  if (distance < 10) {
    Stop();
    val = 0;
  } else {
    motor1.setSpeed(Speeed);        // Define maximum velocity
    motor1.run(FORWARD);            // rotate the motor clockwise
    motor2.setSpeed(Speeed);        // Define maximum velocity
    motor2.run(FORWARD);            // rotate the motor clockwise
    motor3.setSpeed(Speeed / 3.1);  // Define maximum velocity
    motor3.run(FORWARD);            // rotate the motor clockwise
    motor4.setSpeed(Speeed / 3.1);  // Define maximum velocity
    motor4.run(FORWARD);            // rotate the motor clockwise
  }
}

void topright() {
  servo.write(45);
  delay(100);
  int distance = sonar.ping_cm();
  servo.write(90);
  if (distance < 10) {
    Stop();
    val = 0;
  } else {
    motor1.setSpeed(Speeed / 3.1);  // Define maximum velocity
    motor1.run(FORWARD);            // rotate the motor clockwise
    motor2.setSpeed(Speeed / 3.1);  // Define maximum velocity
    motor2.run(FORWARD);            // rotate the motor clockwise
    motor3.setSpeed(Speeed);        // Define maximum velocity
    motor3.run(FORWARD);            // rotate the motor clockwise
    motor4.setSpeed(Speeed);        // Define maximum velocity
    motor4.run(FORWARD);            // rotate the motor clockwise
  }
}

void bottomleft() {
  int IR_Sensor = digitalRead(IR);
  if (IR_Sensor == 0) {
    Stop();
    val = 0;
  } else {
    motor1.setSpeed(Speeed);        // Define maximum velocity
    motor1.run(BACKWARD);           // rotate the motor anti-clockwise
    motor2.setSpeed(Speeed);        // Define maximum velocity
    motor2.run(BACKWARD);           // rotate the motor anti-clockwise
    motor3.setSpeed(Speeed / 3.1);  // Define maximum velocity
    motor3.run(BACKWARD);           // rotate the motor anti-clockwise
    motor4.setSpeed(Speeed / 3.1);  // Define maximum velocity
    motor4.run(BACKWARD);           // rotate the motor anti-clockwise
  }
}

void bottomright() {
  int IR_Sensor = digitalRead(IR);
  if (IR_Sensor == 0) {
    Stop();
    val = 0;
  } else {
    motor1.setSpeed(Speeed / 3.1);  // Define maximum velocity
    motor1.run(BACKWARD);           // rotate the motor anti-clockwise
    motor2.setSpeed(Speeed / 3.1);  // Define maximum velocity
    motor2.run(BACKWARD);           // rotate the motor anti-clockwise
    motor3.setSpeed(Speeed);        // Define maximum velocity
    motor3.run(BACKWARD);           // rotate the motor anti-clockwise
    motor4.setSpeed(Speeed);        // Define maximum velocity
    motor4.run(BACKWARD);           // rotate the motor anti-clockwise
  }
}

void Stop() {
  motor1.setSpeed(0);   // Define minimum velocity
  motor1.run(RELEASE);  // stop the motor when release the button
  motor2.setSpeed(0);   // Define minimum velocity
  motor2.run(RELEASE);  // rotate the motor clockwise
  motor3.setSpeed(0);   // Define minimum velocity
  motor3.run(RELEASE);  // stop the motor when release the button
  motor4.setSpeed(0);   // Define minimum velocity
  motor4.run(RELEASE);  // stop the motor when release the button
}