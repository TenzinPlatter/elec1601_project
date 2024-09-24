#include <Servo.h>  // Include servo library


Servo servoLeft;   // Declare left servo
Servo servoRight;  // Declare right servo


const int sensorLeftPin = 10;  // Pin for the left photoresistor
const int sensorRightPin = 2;  // Pin for the right photoresistor


void setup() {
  pinMode(11, INPUT);
  pinMode(3, INPUT);
  pinMode(10, OUTPUT);
  pinMode(2, OUTPUT);
  Serial.begin(9600);     // Start the serial monitor at 9600 baud rate
  servoLeft.attach(13);   // Attach left servo to pin 13
  servoRight.attach(12);  // Attach right servo to pin 12


  // Start moving forward at medium speed
  while (true) {
    Serial.println("Hi");
    int d = irDistance(2, 3);
    Serial.println("Left distance: " + d);
    d = irDistance(10, 11);
    Serial.println("Right distance: " + d);
  }
}


void loop() {
  int leftSensorValue = irDetect(38000, 10, 11);  // Read left sensor
  int rightSensorValue = irDetect(38000, 2, 3);   // Read right sensor


  // Print sensor values to the Serial Monitor
  Serial.print("Left Sensor: ");
  Serial.print(leftSensorValue);
  Serial.print(" | Right Sensor: ");
  Serial.println(rightSensorValue);


  if (!rightSensorValue) {  // If right sensor detects an opening (2V or less)
    Serial.println("Opening detected on the right, turning right...");
    turnRight();
    moveForward(1500);            // Resume moving forward at medium speed
  } else if (!leftSensorValue) {  // If left sensor detects an opening (2V or less)
    Serial.println("Opening detected on the left, turning left...");
    turnLeft();
    moveForward(1500);  // Resume moving forward at medium speed
  } else {
    Serial.println("Moving forward...");
  }
  delay(500);  // Small delay for readability in the serial monitor
}


int irDetect(long frequency, int ledPin, int sensorPin) {
  tone(ledPin, frequency);          // Turn on the IR LED square wave
  delay(1);                         // Wait 1 ms
  noTone(ledPin);                   // Turn off the IR LED
  int ir = digitalRead(sensorPin);  // IR receiver -> ir variable
  delay(1);                         // Down time before recheck
  return ir;                        // Return 0 detect, 1 no detect
}

int irDistance(int ledPin, int receiverPin) {
  int distance = 0;
  for (long f = 38000; f <= 42000; f += 1000) {
    distance += irDetect(f, ledPin, receiverPin);
  }
  return distance;
}

void moveForward(int speed) {
  servoLeft.writeMicroseconds(1700);   // Left servo rotates counterclockwise (forward)
  servoRight.writeMicroseconds(1300);  // Right servo rotates clockwise (forward)
}


void turnRight() {
  servoLeft.writeMicroseconds(1300);   // Left servo rotates clockwise (right turn)
  servoRight.writeMicroseconds(1300);  // Right servo rotates clockwise (right turn)


  delay(670);  // Wait 3 seconds to complete the turn


  stopServos();  // Stop servos after turning
}


void turnLeft() {
  servoLeft.writeMicroseconds(1700);   // Left servo rotates counterclockwise (left turn)
  servoRight.writeMicroseconds(1700);  // Right servo rotates counterclockwise (left turn)


  delay(670);  // Wait 3 seconds to complete the turn


  stopServos();  // Stop servos after turning
}


void stopServos() {
  servoLeft.writeMicroseconds(1500);   // Stop left servo
  servoRight.writeMicroseconds(1500);  // Stop right servo
}
