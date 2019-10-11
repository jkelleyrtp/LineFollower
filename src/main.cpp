#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_MotorShield.h>


// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
// You can also make another motor on port M2
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  leftMotor->setSpeed(150);
  leftMotor->run(FORWARD);

  rightMotor->setSpeed(150);
  rightMotor->run(BACKWARD);
  // turn on motor
  leftMotor->run(RELEASE);
  rightMotor->run(RELEASE);

  Serial.println("Motors enabled - no i2c issues");

}


// These sensors measure the amount of light reflected, therefore a lower value means a darker reading
// Ideally, we keep the difference between the left sensor and the right sensor the same, but there might
// be some electrical discrepencies between the two, so we should have a built in error factor
//
// We will subtract the left sensor from the right sensor. -> difference = left_sensor - right_sensor
  // If the value is positive, then the right sensor is getting a darker reading than the left (the line is under it)
    // Therefore, we should turn left to correct
  // else, the right sensor is getting a brighter reading than the left (the line is under the left sensor)
    // Therefore we should turn right to correct


int left_sensor;
int center_sensor;
int right_sensor;
int sensor_difference;


int base_speed = 0.0 * 255;
float scale_factor = 0;

void loop() {

  left_sensor = analogRead(5);
  center_sensor = analogRead(4);
  right_sensor = analogRead(3);


  Serial.println("\n\nSensor values:");
  Serial.print(left_sensor);
  Serial.print(" | ");
  Serial.print(center_sensor);
  Serial.print(" | ");
  Serial.print(right_sensor);


  
  // Let's implement the simple bang bang controller to start
  // We will implement it in the skeleton of a proportional controller
  // sensor_difference = left_sensor - right_sensor;


  // leftMotor->run(FORWARD);
  // rightMotor->run(BACKWARD);

  // leftMotor->setSpeed(base_speed + sensor_difference * scale_factor);
  // rightMotor->setSpeed(base_speed - sensor_difference *scale_factor );
  delay(200);
}