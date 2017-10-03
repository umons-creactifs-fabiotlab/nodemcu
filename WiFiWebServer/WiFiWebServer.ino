#include <ESP8266WiFi.h>
#include <Servo.h>

const char* ssid = "froland-xps15-l";
const char* password = "Bv3IwsJi";

Servo myservo;
int pos;

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  // prepare servo
  myservo.attach(D1);
  myservo.write(0);
  pos = 0;
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request
  int val;
  if (req.indexOf("GET") != -1) {
    client.flush();
  
    // Prepare the response
    String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html><p>Servo position is now: " + String(pos) + "°</p>";
    s += "<form method=\"POST\" action=\"/\">";
    s += "<p><input type=\"text\" name=\"pos\"> <input type=\"submit\"></p>";
    s += "</form>";
    s += "</html>\n";
  
    // Send the response to the client
    client.print(s);
  } else {
    if (req.indexOf("POST") != -1) {
      String formData;
      int retry = 0;
      do {
        req = client.readStringUntil('\r');
        client.readStringUntil('\n');
        if (req.indexOf("pos=") != -1) {
          int index = req.indexOf("pos=") + 4;
          pos = req.substring(index).toInt();
          myservo.write(pos);
        }
        if (req == "") break;
        retry++;
      } while(req.length() == 0 && retry < 3);
    }
    client.flush();

    String s = "HTTP/1.1 303 See Other\r\n";
    s +="Location: /\r\n";

    client.print(s);
  }

  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}

