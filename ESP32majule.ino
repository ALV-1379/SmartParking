#include <WiFi.h>

const int trigPin = 4; 
const int echoPin = 5; 
const int led1 = 22; 
const int led2 = 23; 

const char *ssid = "ESP32_Ultrasonic"; 
const char *password = "12345678";    

WiFiServer server(80); 

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  Serial.begin(115200);

  WiFi.softAP(ssid, password);
  Serial.println("Access Point started.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  server.begin(); 
}

void loop() {
  long duration;
  float distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034) / 2; 

  if (distance < 10) {
    digitalWrite(led1, LOW);  
    digitalWrite(led2, HIGH); 
  } else {
    digitalWrite(led1, HIGH); 
    digitalWrite(led2, LOW); 
  }


//res to the clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client.");
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    client.print("<h1>Distance: ");
    client.print(distance);
    client.print(" cm</h1>");
 
    client.stop();
    Serial.println("Client Disconnected.");
  }

  delay(100);
}
