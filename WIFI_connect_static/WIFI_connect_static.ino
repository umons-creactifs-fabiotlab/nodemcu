#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
WiFiUDP udp;

const char* ssid = "*";
const char* password = "*";
const char* ahostname = "*";

IPAddress staticIP(*); //format *,*,*,*
IPAddress dest(*);
IPAddress gateway(*);
IPAddress subnet(*);

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
}

void loop() {
  WiFi.printDiag(Serial);
  Serial.print("MAC Address: ");
  Serial.print(WiFi.macAddress());
  udp.beginPacket(dest, 6000);
  udp.endPacket(); 
  Serial.print("\n");
  delay(10000);
}
