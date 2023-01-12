#include <NewPing.h>
 
#define TRIGGER_PIN  3
#define ECHO_PIN     2
#define MAX_DISTANCE 100
#define led          5
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
 
void setup() 
{
  Serial.begin(115200);
}
 
void loop() 
{
  pinMode(5, OUTPUT);
  int x = sonar.ping_cm();

  for (sonar.ping_cm() < 50; x = 10; x-- )
  {
    while (sonar.ping_cm() > 50)
    {
      Serial.print("Ping: ");
      Serial.print(sonar.ping_cm());
      Serial.println("cm");
      delay (10);
      digitalWrite(led, LOW);
      delay (10);
    }

    Serial.print("Ping: ");
    Serial.print(sonar.ping_cm());
    Serial.println("cm");
    delay (10);

    digitalWrite(led, HIGH);
    delay((sonar.ping_cm()*5));
    delay (10);
    digitalWrite(led, LOW);
    delay((sonar.ping_cm()*5));
    delay (10);

    while (sonar.ping_cm() <= 10)
    {
      Serial.print("Ping: ");
      Serial.print(sonar.ping_cm());
      Serial.println("cm");
      delay (10);
      digitalWrite(led, HIGH);
      delay (10);
    }
  }
}