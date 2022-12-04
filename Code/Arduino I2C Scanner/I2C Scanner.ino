#include <Wire.h>
#define I2C_SLAVE_ADDR 0x04

void setup() 
{
  Serial.begin(115200);
  Wire.begin();
}

int leftMotor = 255;
int rightMotor = 255;
int steeringAngle = 90;

void loop() {
  Wire.beginTransmission(I2C_SLAVE_ADDR);

  Wire.write((byte)((leftMotor & 0x0000FF00) >> 8));
  Wire.write((byte)(leftMotor & 0x000000FF));
  Wire.write((byte)((rightMotor & 0x0000FF00) >> 8));
  Wire.write((byte)(rightMotor & 0x000000FF));
  Wire.write((byte)((steeringAngle & 0x0000FF00) >> 8));
  Wire.write((byte)(steeringAngle & 0x000000FF));  

  Wire.endTransmission();
  delay(100);
}

void receiveEvent(int howMany)
{
  if(howMany != 4)  // for 3 16-bit numbers, the data will be 6 bytes long - anything else is an error
  {
    emptyBuffer();
    return;
  }
  int16_t enc1_count = 0;
  int16_t enc2_count = 0;

  uint8_t enc1_count = Wire.read();

  uint8_t enc2_count16_9 = Wire.read();
  uint8_t enc2_count8_1 = Wire.read();

  enc1_count = (enc1_count16_9 << 8) | enc1_count8_1;
  enc2_count = (enc2_count16_9 << 8) | enc2_count8_1;

  Serial.print("Encoder 1 - ");
  Serial.print(enc1_count);
  Serial.print("     Encoder 2 - ");
  Serial.println(enc2_count);
}

void emptyBuffer(void)
{
  Serial.println("Error: I2C Byte Size Mismatch"); // i.e. an incorrect number of bytes has been received
  while(Wire.available())
  {
    Wire.read();
  }
}