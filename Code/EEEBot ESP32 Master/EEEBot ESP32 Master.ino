#include <MPU6050_tockn.h>
#include <Wire.h>
#define I2C_SLAVE_ADDR 0x04

MPU6050 mpu6050(Wire);

long timer = 0;

void setup()
{
  Serial.begin(9600);  
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true, 0, 500);
}

int leftMotor = 255;
int rightMotor = 255;
int steeringAngle = 90;

void loop()
{
  Wire.beginTransmission(I2C_SLAVE_ADDR);
  Wire.write((byte)((leftMotor & 0x0000FF00) >> 8));
  Wire.write((byte)(leftMotor & 0x000000FF));
  Wire.write((byte)((rightMotor & 0x0000FF00) >> 8));
  Wire.write((byte)(rightMotor & 0x000000FF));
  Wire.write((byte)((steeringAngle & 0x0000FF00) >> 8));
  Wire.write((byte)(steeringAngle & 0x000000FF));
  Wire.endTransmission();
  delay(100);

  mpu6050.update();

  if(millis() - timer > 1000)
  {
    Serial.println();    
    Serial.print("angleX : ");Serial.print(mpu6050.getAngleX());
    Serial.print("\tangleY : ");Serial.print(mpu6050.getAngleY());
    Serial.print("\tangleZ : ");Serial.println(mpu6050.getAngleZ()); 
    timer = millis();
  }
}

void receiveEvent(int howMany)
{
  if(howMany != 4) 
  {
    emptyBuffer();
    return;
  }
  
  int enc1_count = Wire.read();
  int enc2_count = Wire.read();

  Serial.print("Encoder 1 - ");
  Serial.print(enc1_count);
  Serial.print("     Encoder 2 - ");
  Serial.print(enc2_count);
}


// function to clear the I2C buffer
void emptyBuffer(void)
{
  Serial.println("Error: I2C Byte Size Mismatch"); // i.e. an incorrect number of bytes has been received
  while(Wire.available())
  {
    Wire.read();
  }
}
