#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "mabzone.net";
const char* password = "Cisco@#0912";

const int ledPin = D1; // GPIO pin connected to the LED

WiFiServer server(80);

void setup() {
  pinMode(ledPin, OUTPUT);
  
  Serial.begin(115200);
  delay(10);

  // Connect to Wi-Fi
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
  Serial.println("WiFi connected.");

  // Start the server
  server.begin();
  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  Serial.println("New client");
  while (!client.available()) {
    delay(1);
  }

  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  if (request.indexOf("/on") != -1) {
    digitalWrite(ledPin, HIGH);
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<h1>LED is ON</h1>");
    client.println("</html>");
  } else if (request.indexOf("/off") != -1) {
    digitalWrite(ledPin, LOW);
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<h1>LED is OFF</h1>");
    client.println("</html>");
  }

  delay(1);
  Serial.println("Client disconnected");
}
