#include <ESP8266WiFi.h>

const char* ssid = "*";
const char* password = "*";
const char* ahostname = "*";

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
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
  Serial.print("\n");
  delay(10000);
}
