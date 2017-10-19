#include <Servo.h>

Servo servo; //Definition of an instance of servo
String var;

void setup() 
{
  Serial.begin(115200);
  delay(10);
  Serial.setTimeout(1000); //MAX TIMEOUT

  servo.attach(D1);
  servo.write(0);
  Serial.print("Program began\n");
}

void loop() 
{
  Serial.print("\nWaiting for command:\n");
  do
  {
    var=Serial.readStringUntil('\r');
  }while(var.length()==0);
  
  Serial.print("Received command from serial port: ");
  Serial.print(var);
  Serial.print("\n\n");
  servo.write(var.toInt()%181);
  Serial.print("Servo moved to ");
  Serial.print(var.toInt()%181);
  Serial.print(" deg\n\n");

}
