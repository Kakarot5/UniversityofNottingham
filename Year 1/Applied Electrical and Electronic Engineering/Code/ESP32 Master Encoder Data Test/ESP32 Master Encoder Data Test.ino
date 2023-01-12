#include <MPU6050_tockn.h>
#include <NewPing.h>
#include <Wire.h>
#include <math.h>

#define I2C_SLAVE_ADDR 0x04

#define TRIGGER_PIN  26
#define ECHO_PIN     34
#define MAX_DISTANCE 100

long encoder, distance, enc;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

MPU6050 mpu6050(Wire);

void setup()
{
  Serial.begin(9600);  
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}

void loop()
{
 // displayAngles();
  //readEncoderData();
 // displayDistance();
  distanceTravelled(readEncoderData());
  }

void sendMechanicalData(int leftMotor, int rightMotor, int steeringAngle)
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

long readEncoderData ()
{
  Wire.requestFrom(I2C_SLAVE_ADDR, 4);

  int16_t enc1_count;
  int16_t enc2_count;

  uint8_t enc1_count16_9 = Wire.read();   // receive bits 16 to 9 of y (one byte)
  uint8_t enc1_count8_1 = Wire.read();   // receive bits 8 to 1 of y (one byte)
  uint8_t enc2_count16_9 = Wire.read();   // receive bits 16 to 9 of z (one byte)
  uint8_t enc2_count8_1 = Wire.read();   // receive bits 8 to 1 of z (one byte)

  enc1_count = (enc1_count16_9 << 8) | enc1_count8_1; // combine the two bytes into a 16 bit number
  enc2_count = (enc2_count16_9 << 8) | enc2_count8_1;

  encoder = ((enc1_count + enc2_count) / 2);
  
  if (enc1_count != 1 && enc1_count != -1)
    {
      Serial.print("Encoder = ");Serial.println(encoder);
    }
  else;
  return (encoder);
}
long distanceTravelled (long encoder)
{

  long dist;
  dist = (0.78539816339 * encoder);
   Serial.println(dist);
}