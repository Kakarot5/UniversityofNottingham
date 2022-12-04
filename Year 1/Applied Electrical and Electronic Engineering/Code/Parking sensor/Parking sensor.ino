#include <NewPing.h>
 
#define TRIGGER_PIN  3
#define ECHO_PIN     2
#define MAX_DISTANCE 100
#define led          5
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
 
void setup() {
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
      delay (1);
      digitalWrite(led, LOW);
      delay (1);
    }

    Serial.print("Ping: ");
    Serial.print(sonar.ping_cm());
    Serial.println("cm");
    delay (1);

    digitalWrite(led, HIGH);
    delay((sonar.ping_cm()*5));
    delay (1);
    digitalWrite(led, LOW);
    delay((sonar.ping_cm()*5));
    delay (1);

    while (sonar.ping_cm() <= 10)
    {
      Serial.print("Ping: ");
      Serial.print(sonar.ping_cm());
      Serial.println("cm");
      delay (1);
      digitalWrite(led, HIGH);
      delay (1);
    }
  }
}
  /* while (sonar.ping_cm() > 40 && sonar.ping_cm() <= 50)
  {
    delay(50);
    Serial.print("Ping: ");
    Serial.print(sonar.ping_cm());
    Serial.println("cm");
    digitalWrite(5, HIGH);
    delay(700);
    digitalWrite(5, LOW);
    delay(700);
  }
  while (sonar.ping_cm() > 30 && sonar.ping_cm() <= 40)
  {
    delay(50);
    Serial.print("Ping: ");
    Serial.print(sonar.ping_cm());
    Serial.println("cm");    
    digitalWrite(5, HIGH);
    delay(350);
    digitalWrite(5, LOW);
    delay(350);
  }
  while (sonar.ping_cm() > 20 && sonar.ping_cm() <= 30 )
  {
    delay(50);
    Serial.print("Ping: ");
    Serial.print(sonar.ping_cm());
    Serial.println("cm");  
    digitalWrite(5, HIGH);
    delay(150);
    digitalWrite(5, LOW);
    delay(150);
  }
  while (sonar.ping_cm() > 10 && sonar.ping_cm() <= 20 )
  {
    delay(50);
    Serial.print("Ping: ");
    Serial.print(sonar.ping_cm());
    Serial.println("cm");
    digitalWrite(5, HIGH);
    delay(50);
    digitalWrite(5, LOW);
    delay(50);
  }
  while (sonar.ping_cm() >= 00 && sonar.ping_cm() <= 10 )
  {
    delay(50);
    Serial.print("Ping: ");
    Serial.print(sonar.ping_cm());
    Serial.println("cm");
    digitalWrite(5, HIGH);*/



