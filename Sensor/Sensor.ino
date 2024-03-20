#include <ESP8266WiFi.h>
#include <DFRobot_DHT11.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>
#include <NTPClient.h>


// Set up temp sensort DHT11
DFRobot_DHT11 DHT;
#define DHT11_PIN D4
#define DHT11_PIN2 D3

// Define wifi connection
#define WIFI_SSID "tonttumetsa"
#define WIFI_PASSWORD "Taigametsa30"

// Define real time
const long utcOffsetInSeconds = 3600;
WiFiUDP ntpUDP;
//NTPClient timeClient(ntpUDP, "fi.pool.ntp.org", utcOffsetInSeconds);

// Define server
//WiFiServer server(80);

float temperature;
float humidity;
float temperature2;
float humidity2;
//unsigned long time;

// Adds values into arraylogs
void update_values(){

  // Read temperature and humidity
  DHT.read(DHT11_PIN);
  temperature = DHT.temperature + 2;
  humidity = DHT.humidity;
  
  // Read temperature and humidity
  DHT.read(DHT11_PIN2);
  temperature2 = DHT.temperature;
  humidity2 = DHT.humidity;

  // Get the current time
  // timeClient.update();
  // time = timeClient.getEpochTime() - 3600;
}


void setup() {
  Serial.begin(115200);

  delay(500);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to " + (String)WIFI_SSID);
  }
  Serial.print("Device connected with ip: ");
  Serial.println(WiFi.localIP());
}

void loop() {
    delay(2000);
    update_values();
    Serial.println(); 
    Serial.println("Sensor 1 Temp: " + (String)temperature + "C Hum: " + (String)humidity + "'%'");
    Serial.println("Sensor 2 Temp: " + (String)temperature2 + "C Hum: " + (String)humidity2 + "'%'");
}