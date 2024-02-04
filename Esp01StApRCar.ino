#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "iqhtyar";
const char* password = "12345678";
const char* APssid = "iqhtyar2k";
const char* APpassword = "23456789";

// Pins for L298N motor driver
const int IN1 = 0;
const int IN2 = 2;
const int IN3 = 3;
const int IN4 = 1;

ESP8266WebServer server(80);

void handleRoot() {
  String html = "<html><head><title>ESP8266 RC Car</title></head><body>";
  html += "<h1>ESP8266 RC Car</h1>";
  html += "<form action=\"/forward\" method=\"POST\">";
  html += "<input type=\"submit\" value=\"Forward\">";
  html += "</form>";
  html += "<form action=\"/backward\" method=\"POST\">";
  html += "<input type=\"submit\" value=\"Backward\">";
  html += "</form>";
  html += "<form action=\"/left\" method=\"POST\">";
  html += "<input type=\"submit\" value=\"Left\">";
  html += "</form>";
  html += "<form action=\"/right\" method=\"POST\">";
  html += "<input type=\"submit\" value=\"Right\">";
   html += "</form>";
  html += "<form action=\"/netral\" method=\"POST\">";
  html += "<input type=\"submit\" value=\"Netral\">";  
  html += "</form>";
  html += "</body></html>";

  // Send the web page to the client
  server.send(200, "text/html", html);
}

void handleForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(10);
}

void handleBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(10);
}

void handleLeft() {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(10);
}

void handleRight() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(10);
}

void handleNetral() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  delay(10);
}

void setup() {
  Serial.begin(9600);
  delay(100);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
if (WiFi.status() == WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}
else {
    Serial.println("WiFi not connected");
    delay(100);
    WiFi.mode(WIFI_AP);
    WiFi.softAP(APssid, APpassword);
    IPAddress myIP = WiFi.softAPIP();
    delay(500);
    Serial.print("Access Point IP address: ");
    Serial.println(myIP);
}

  // Initialize the L298N motor driver
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Configure server routes
  server.on("/", handleRoot);
  server.on("/forward", handleForward);
  server.on("/backward", handleBackward);
  server.on("/left", handleLeft);
  server.on("/right", handleRight);
  server.on("/netral", handleNetral);

  server.begin();
}

void loop() {
  server.handleClient();                     
  delay(10);
}