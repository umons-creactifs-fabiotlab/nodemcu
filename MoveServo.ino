#include <Servo.h>

Servo myservo;

void setup() {
  Serial.begin(115200);
  delay(10);

  myservo.attach(D1);
  myservo.write(0);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Setup");
}

void loop() {
  for (int i = 0; i < 17; i++) {
    Serial.println();
    Serial.print("Move to ");
    Serial.print(String(i * 10));
    myservo.write(i * 10);
    delay(2000);
  }
}

