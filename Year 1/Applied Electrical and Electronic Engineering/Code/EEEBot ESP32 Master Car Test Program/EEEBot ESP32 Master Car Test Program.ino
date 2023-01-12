#include <MPU6050_tockn.h>
#include <NewPing.h>
#include <Wire.h>
#define I2C_SLAVE_ADDR 0x04

#define TRIGGER_PIN  19
#define ECHO_PIN     18
#define MAX_DISTANCE 100

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

MPU6050 mpu6050(Wire);

long timer = 0;

void setup()
{
  Serial.begin(115200);  
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets();
}

void loop()
{
  sendData(255, 255, 0);
  delay(500);
  displayAngles();
  displayDistance();

  sendData(0, 0, 90);
  delay (500);
  displayAngles();
  displayDistance();

  sendData(-255, -255, 180);
  delay(500);
  displayAngles();
  displayDistance();

  sendData(0, 0, 90);
  delay (500); 
  displayAngles();
  displayDistance();   
}

void sendData(int leftMotor, int rightMotor, int steeringAngle)
{
  Wire.beginTransmission(I2C_SLAVE_ADDR);
  Wire.write((byte)((leftMotor & 0x0000FF00) >> 8));
  Wire.write((byte)(leftMotor & 0x000000FF));
  Wire.write((byte)((rightMotor & 0x0000FF00) >> 8));
  Wire.write((byte)(rightMotor & 0x000000FF));
  Wire.write((byte)((steeringAngle & 0x0000FF00) >> 8));
  Wire.write((byte)(steeringAngle & 0x000000FF));
  Wire.endTransmission();
}

void displayAngles ()
{
  mpu6050.update();
  Serial.print("Angle X = ");Serial.print(mpu6050.getAngleX());
  Serial.print("\t\tAngle Y = ");Serial.print(mpu6050.getAngleY());
  Serial.print("\t\tAngle Z = ");Serial.println(mpu6050.getAngleZ());
}
void displayDistance ()
{
  Serial.print("Ping = ");
  Serial.print(sonar.ping_cm());
  Serial.println("cm");
}