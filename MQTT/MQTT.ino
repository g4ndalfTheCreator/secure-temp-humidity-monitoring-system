#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define seconds() (millis()/1000)

// Set up temp sensors
#define DHT_PIN 4 // D1
//#define DHT_PIN 13 // D1 mini

// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

DHT_Unified dht(DHT_PIN, DHTTYPE);

// Define wifi connection
const char *ssid = "*";
const char *password = "*"; 

// Define mqtt connection
const char *mqtt_broker = "***.***.***.***"; 
const char *user = "test_user";
const char *pw = "pw";

static const char* cert_sha1 PROGMEM = "D3:9C:27:19:F9:56:91:BA:1A:C3:74:83:E0:FE:42:B6:D5:68:DB:2E";

// Define topics
String client_id = "demo_sensor_1_";
const char *temp_topic = "demo_sensor_1_temperature";
const char *hum_topic = "demo_sensor_1_humidity";

// Define times
unsigned long prev_seconds = 0; 
const unsigned refresh_rate = 30; // sec
unsigned sec_counter = 0; // under refresh rate

// define hum/temp
float temperatures[refresh_rate];
float humidities[refresh_rate];

// Define mqtt connection 
const int mqtt_port = 8883;
WiFiClientSecure measurementClient;
PubSubClient client(measurementClient);

// Adds values into arraylogs
void update_values(unsigned sec_counter){

  // Read temperature and humidity
  sensors_event_t event;
  
  dht.temperature().getEvent(&event);

  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature! No changed value kept old val"));
  }
  else {
    temperatures[sec_counter] = event.temperature;
  }

  dht.humidity().getEvent(&event);

  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity! No changed value kept old val"));
  }
  else {
    humidities[sec_counter] = event.relative_humidity;
  }

}

// Calculate average of values (used for temperature and humidity)
float calculate_average(float values[]){
  float sum = 0;
  for(int i = 0; i < refresh_rate; i++){
    sum += values[i];
  }
  return sum/refresh_rate;
}

void setup_connections(){
    // connecting to a WiFi network
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi network: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.print("\nConnected with ip: ");
    Serial.println(WiFi.localIP());

    //connecting to a mqtt broker
    measurementClient.setFingerprint(cert_sha1);
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
    
    client_id += String(WiFi.macAddress());

    while (!client.connected()) {
    
        Serial.printf("The client %s connects to mosquitto mqtt broker\n", client_id.c_str());
 
        if (client.connect(client_id.c_str(), user, pw)) {
            Serial.println("The mqtt broker connected");
        } 
        else {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }
}

void reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT re-connection... ");
        if (client.connect(client_id.c_str(), user, pw)) {
            Serial.println("re-connected successfully to the mqtt broker");
        } 
        else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void setup() {
    Serial.begin(9600);
    dht.begin();
    
    setup_connections();
    // publish and subscribe
    //client.subscribe(temp_topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    
    for (int i = 0; i < length; i++) {
    Serial.print((char) payload[i]);
    }
    
    Serial.println();
    Serial.println(" - - - - - - - - - - - -");
}

void loop() {

    unsigned long seconds = seconds();

    if(sec_counter >= refresh_rate){
        const float avg_temp = calculate_average(temperatures);
        const float avg_hum = calculate_average(humidities);

        client.publish(temp_topic, String(avg_temp).c_str());
        client.publish(hum_topic, String(avg_hum).c_str());
        sec_counter = 0;
    }

    // Update values every one second
    if(seconds - prev_seconds >= 1){
        update_values(sec_counter);

        prev_seconds = seconds();
        sec_counter += 1;
    }

    if (!client.connected()) {
        reconnect();
    }

    client.loop();

    
}
