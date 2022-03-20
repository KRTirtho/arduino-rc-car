#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>
#define TRIGGER_PIN A1
#define ECHO_PIN A0
#define MAX_DISTANCE 300
#define IR A5

// initial motors pin
AF_DCMotor frontRightMotor(1, MOTOR12_1KHZ);
AF_DCMotor frontLeftMotor(2, MOTOR12_1KHZ);
AF_DCMotor backLeftMotor(3, MOTOR34_1KHZ);
AF_DCMotor backRightMotor(4, MOTOR34_1KHZ);

char val;
int Speeed = 255;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Servo servo;

void setup() {
  Serial.begin(9600);  // Set the baud rate to your Bluetooth module.
  // servo.attach(10);
  // servo.write(90);
  // pinMode(IR, INPUT);
}
void loop() {
  if (Serial.available() > 0) {
    val = static_cast<char>(Serial.read());

    // R -> Forward  L -> back  F -> Right  B -> Left

    Serial.print("Received Data:");
    Serial.println(val);

    Stop();  // initialize with motors stoped
    switch (val) {
      case 'R':
        forward();
        break;
      case 'L':
        back();
        break;
      case 'B':
        left();
        break;
      case 'F':
        right();
        break;
      case 'G':
        bottomright();
        break;
      case 'I':
        bottomleft();
        break;
      case 'H':
        topleft();
        break;
      case 'J':
        topright();
        break;
      case 'T':
        Stop();
        break;
    }
  }
}

void forward() {
  // checking obstacle ahead
  // int distance = sonar.ping_cm();

  // if (distance < 10) {
  //   Stop();
  //   val = 0;
  // } else {
  frontRightMotor.setSpeed(Speeed);  // Define maximum velocity
  frontLeftMotor.setSpeed(Speeed);   // Define maximum velocity
  backLeftMotor.setSpeed(Speeed);    // Define maximum velocity
  backRightMotor.setSpeed(Speeed);   // Define maximum velocity

  frontRightMotor.run(FORWARD);  // rotate the motor clockwise
  frontLeftMotor.run(FORWARD);   // rotate the motor clockwise
  backLeftMotor.run(FORWARD);    // rotate the motor clockwise
  backRightMotor.run(FORWARD);   // rotate the motor clockwise
  // }
}

void back() {
  // int IR_Sensor = digitalRead(IR);
  // if (IR_Sensor == 0) {
  //   Stop();
  //   val = 0;
  // } else {
  frontRightMotor.setSpeed(Speeed);  // Define maximum velocity
  frontLeftMotor.setSpeed(Speeed);   // Define maximum velocity
  backLeftMotor.setSpeed(Speeed);    // Define maximum velocity
  backRightMotor.setSpeed(Speeed);   // Define maximum velocity

  frontRightMotor.run(BACKWARD);  // rotate the motor anti-clockwise
  frontLeftMotor.run(BACKWARD);   // rotate the motor anti-clockwise
  backLeftMotor.run(BACKWARD);    // rotate the motor anti-clockwise
  backRightMotor.run(BACKWARD);   // rotate the motor anti-clockwise
  // }
}

void left() {
  // servo.write(180);
  // delay(100);
  // int distance = sonar.ping_cm();
  // servo.write(90);
  // if (distance < 10) {
  //   Stop();
  //   val = 0;
  // } else {
  frontRightMotor.setSpeed(Speeed);  // Define maximum velocity
  frontLeftMotor.setSpeed(Speeed);   // Define maximum velocity
  backLeftMotor.setSpeed(Speeed);    // Define maximum velocity
  backRightMotor.setSpeed(Speeed);   // Define maximum velocity

  frontRightMotor.run(BACKWARD);  // rotate the motor anti-clockwise
  frontLeftMotor.run(BACKWARD);   // rotate the motor anti-clockwise
  backLeftMotor.run(FORWARD);     // rotate the motor clockwise
  backRightMotor.run(FORWARD);    // rotate the motor clockwise
  // }
}

void right() {
  // servo.write(0);
  // delay(100);
  // int distance = sonar.ping_cm();
  // servo.write(90);
  // if (distance < 10) {
  //   Stop();
  //   val = 0;
  // } else {
  frontRightMotor.setSpeed(Speeed);  // Define maximum velocity
  frontLeftMotor.setSpeed(Speeed);   // Define maximum velocity
  backLeftMotor.setSpeed(Speeed);    // Define maximum velocity
  backRightMotor.setSpeed(Speeed);   // Define maximum velocity

  frontRightMotor.run(FORWARD);  // rotate the motor clockwise
  frontLeftMotor.run(FORWARD);   // rotate the motor clockwise
  backLeftMotor.run(BACKWARD);   // rotate the motor anti-clockwise
  backRightMotor.run(BACKWARD);  // rotate the motor anti-clockwise
  // }
}

void topleft() {
  // servo.write(135);
  // delay(100);
  // int distance = sonar.ping_cm();
  // servo.write(90);
  // if (distance < 10) {
  //   Stop();
  //   val = 0;
  // } else {
  frontRightMotor.setSpeed(Speeed);       // Define maximum velocity
  frontRightMotor.run(FORWARD);           // rotate the motor clockwise
  frontLeftMotor.setSpeed(Speeed / 3.1);  // Define maximum velocity
  frontLeftMotor.run(FORWARD);            // rotate the motor clockwise
  backLeftMotor.setSpeed(Speeed);         // Define maximum velocity
  backLeftMotor.run(FORWARD);             // rotate the motor clockwise
  backRightMotor.setSpeed(Speeed);        // Define maximum velocity
  backRightMotor.run(FORWARD);            // rotate the motor clockwise
  // }
}

void topright() {
  // servo.write(45);
  // delay(100);
  // int distance = sonar.ping_cm();
  // servo.write(90);
  // if (distance < 10) {
  //   Stop();
  //   val = 0;
  // } else {
  frontRightMotor.setSpeed(Speeed / 3.1);  // Define maximum velocity
  frontRightMotor.run(FORWARD);            // rotate the motor clockwise
  frontLeftMotor.setSpeed(Speeed);         // Define maximum velocity
  frontLeftMotor.run(FORWARD);             // rotate the motor clockwise
  backLeftMotor.setSpeed(Speeed);          // Define maximum velocity
  backLeftMotor.run(FORWARD);              // rotate the motor clockwise
  backRightMotor.setSpeed(Speeed);         // Define maximum velocity
  backRightMotor.run(FORWARD);             // rotate the motor clockwise
  // }
}

void bottomleft() {
  // int IR_Sensor = digitalRead(IR);
  // if (IR_Sensor == 0) {
  //   Stop();
  //   val = 0;
  // } else {
  frontRightMotor.setSpeed(Speeed);      // Define maximum velocity
  frontRightMotor.run(BACKWARD);         // rotate the motor anti-clockwise
  frontLeftMotor.setSpeed(Speeed);       // Define maximum velocity
  frontLeftMotor.run(BACKWARD);          // rotate the motor anti-clockwise
  backLeftMotor.setSpeed(Speeed / 3.1);  // Define maximum velocity
  backLeftMotor.run(BACKWARD);           // rotate the motor anti-clockwise
  backRightMotor.setSpeed(Speeed);       // Define maximum velocity
  backRightMotor.run(BACKWARD);          // rotate the motor anti-clockwise
  // }
}

void bottomright() {
  // int IR_Sensor = digitalRead(IR);
  // if (IR_Sensor == 0) {
  //   Stop();
  //   val = 0;
  // } else {
  frontRightMotor.setSpeed(Speeed);       // Define maximum velocity
  frontRightMotor.run(BACKWARD);          // rotate the motor anti-clockwise
  frontLeftMotor.setSpeed(Speeed);        // Define maximum velocity
  frontLeftMotor.run(BACKWARD);           // rotate the motor anti-clockwise
  backLeftMotor.setSpeed(Speeed);         // Define maximum velocity
  backLeftMotor.run(BACKWARD);            // rotate the motor anti-clockwise
  backRightMotor.setSpeed(Speeed / 3.1);  // Define maximum velocity
  backRightMotor.run(BACKWARD);           // rotate the motor anti-clockwise
  // }
}

void Stop() {
  frontRightMotor.setSpeed(0);   // Define minimum velocity
  frontRightMotor.run(RELEASE);  // stop the motor when release the button
  frontLeftMotor.setSpeed(0);    // Define minimum velocity
  frontLeftMotor.run(RELEASE);   // rotate the motor clockwise
  backLeftMotor.setSpeed(0);     // Define minimum velocity
  backLeftMotor.run(RELEASE);    // stop the motor when release the button
  backRightMotor.setSpeed(0);    // Define minimum velocity
  backRightMotor.run(RELEASE);   // stop the motor when release the button
}