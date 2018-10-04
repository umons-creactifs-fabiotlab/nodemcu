#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Servo.h>

WiFiUDP udp;
Servo servo; //Definition of an instance of servo
String var;

unsigned int localUdpPort = 4210;
char RX_BUF[255];
const char* ssid = *;
const char* password = *;
const char* ahostname = *;

IPAddress staticIP(*); //format *,*,*,*
IPAddress gateway(*);
IPAddress subnet(*);

int len;

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.config(staticIP,gateway,subnet,gateway);
  WiFi.hostname(ahostname);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());

  udp.begin(localUdpPort);
  servo.attach(D1);
  servo.write(0);
}

void loop()
{
  Serial.print("\nWaiting for command:\n");
  do
  {
    while(udp.parsePacket()<=0);
    len=0;
    len=udp.read(RX_BUF, 255);
    if (len > 0)
    {
      RX_BUF[len] = 0;
      Serial.print("Received command from UDP: ");
      Serial.print(RX_BUF);
      Serial.print("\n\n");
      servo.write(atoi(RX_BUF)%181);
      Serial.print("Servo moved to ");
      Serial.print(atoi(RX_BUF)%181);
      Serial.print(" deg\n\n");
    }
  }while(len<=0);
}
