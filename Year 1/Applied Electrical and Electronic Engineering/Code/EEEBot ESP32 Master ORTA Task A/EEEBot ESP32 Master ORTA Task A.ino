#include <MPU6050_tockn.h>
#include <NewPing.h>
#include <Wire.h>

#define I2C_SLAVE_ADDR 0x04
#define TRIGGER_PIN  19
#define ECHO_PIN     33
#define MAX_DISTANCE 100

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

MPU6050 mpu6050(Wire);

void setup()
{
  Serial.begin(115200);  
  Wire.begin();
  mpu6050.begin();
  delay(500);
  mpu6050.calcGyroOffsets(true);
  delay(500);
}

void loop()
{ 
  displayAngles();
  displaySonarDistance();
  sendMechanicalData(160, 160, 87);
  delay(1000);

  long hundredEightyDegrees = mpu6050.getAngleZ() + 180;

  do
  {
    sendMechanicalData(160, 160, 40);
    displayAngles();
    displaySonarDistance();
  }
  while (mpu6050.getAngleZ() < hundredEightyDegrees);

  while (sonar.ping_cm() > 10 || sonar.ping_cm() == 0)
  {
    sendMechanicalData(-160, -160, 90);
    displayAngles();
    displaySonarDistance();
  }

    sendMechanicalData(0, 0, 90);
    long ninetyDegrees = mpu6050.getAngleZ() - 90;
    displayAngles();
    displaySonarDistance();

    do
    {
      sendMechanicalData(160, 160, 140);
      displayAngles();
      displaySonarDistance();
      Serial.print(ninetyDegrees);
    }
    while (mpu6050.getAngleZ() > ninetyDegrees);

  while (sonar.ping_cm() > 10 || sonar.ping_cm() == 0)
  {
    sendMechanicalData(-160, -160, 90);
    displayAngles();
    displaySonarDistance();
  }
 
  while (1)
  {
    sendMechanicalData(0, 0, 90);
    displayAngles();
    displaySonarDistance();    
  }
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
  delay(100);
  Serial.print("Angle X = ");Serial.print(mpu6050.getAngleX());
  Serial.print("\t\tAngle Y = ");Serial.print(mpu6050.getAngleY());
  Serial.print("\t\tAngle Z = ");Serial.println(mpu6050.getAngleZ());
}
void displaySonarDistance ()
{
  Serial.print("Ping = ");
  Serial.print(sonar.ping_cm());
  Serial.println("cm");
}