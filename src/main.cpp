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

int right_sensor;
float sensor_difference;
int left_velocity;
int right_velocity;

float base_speed = 0.2;
float scale_factor = 0.1;

void loop() {

  left_sensor = analogRead(2);
  center_sensor = analogRead(1);
  right_sensor = analogRead(0);


  // Serial.println("\n\nSensor values:");
  // Serial.print(left_sensor);
  // Serial.print(" | ");
  // Serial.print(center_sensor);
  // Serial.print(" | ");
  // Serial.print(right_sensor);


  
  // Let's implement the simple bang bang controller to start
  // We will implement it in the skeleton of a proportional controller
  sensor_difference =  2.0 * (left_sensor - center_sensor)/315.0;

  // left_velocity =  map(base_speed - (sensor_difference * scale_factor), 0.0, 1.0, 0.0, 255.0 );
  // right_velocity =  map(base_speed + (sensor_difference * scale_factor), 0.0, 1.0, 0.0, 255.0 );
  left_velocity =  255.0*(base_speed - (sensor_difference * scale_factor));
  right_velocity = 255.0*(base_speed + (sensor_difference * scale_factor));

  leftMotor->run(FORWARD);
  rightMotor->run(BACKWARD);

  leftMotor->setSpeed(left_velocity);
  rightMotor->setSpeed(right_velocity);
  
  delay(16);
}