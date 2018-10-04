#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

const char* ssid = "xxx";
const char* password = "xxx";

Servo myservo;
int pos;

ESP8266WebServer server(80);

/* Handle the GET / request. */
void handleStatus() {
  // Prepare the response
  String s = "<!DOCTYPE HTML>\r\n<html><p>Servo position is now: " + String(pos) + "°</p>";
  s += "<form method=\"POST\" action=\"/\">";
  s += "<p><input type=\"radio\" name=\"pos\" value=\"0\"";
  if (pos == 0) s += " checked";
  s += "> 0°</p>";
  s += "<p><input type=\"radio\" name=\"pos\" value=\"90\"";
  if (pos == 90) s += " checked";
  s += "> 90°</p>";
  s += "<p><input type=\"radio\" name=\"pos\" value=\"180\"";
  if (pos == 180) s += " checked";
  s += "> 180°</p>";
  s += "<p><input type=\"submit\"></p>";
  s += "</form>";
  s += "</html>\n";
  server.send(200, "text/html", s);
}

/* Handle requests to change position. */
void handleChangePosition() {
  pos = server.arg("pos").toInt();
  int realPos = map(pos, 0, 180, 0, 160); /* our servo doesn't accept more than 160 */
  myservo.attach(D1);
  myservo.write(realPos);
  handleNotFound();
  delay(1000);
  myservo.detach();
}

/* Handle all the other requests. */
void handleNotFound() {
  server.sendHeader("Location", "/", true);
  server.send(303, "text/plain", "");
}

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  // prepare servo
  myservo.attach(D1);
  pos = 0;
  myservo.write(0);
  delay(1000);
  myservo.detach();
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.on("/", HTTP_GET, handleStatus);
  server.on("/", HTTP_POST, handleChangePosition);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  server.handleClient();
}

