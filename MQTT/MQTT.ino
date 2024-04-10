#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DFRobot_DHT11.h>

#define seconds() (millis()/1000)

// Set up temp sensors DHT11
DFRobot_DHT11 DHT;
#define DHT11_PIN D3

// Define wifi connection
const char *ssid = "x";
const char *password = "x"; 

// Define mqtt connection
const char *mqtt_broker = "192.168.0.112"; 
const char *user = "test"; // not real username
const char *pw = "pw"; // not real password

// Define topics
const char *temp_topic = "temperature";
const char *hum_topic = "humidity";

// define hum/temp
float temperature;
float humidity;

// Define times
unsigned long prev_seconds = 0; 
unsigned refresh_rate = 10; // sec

const int mqtt_port = 1883;
WiFiClient espClient;
PubSubClient client(espClient);

// Adds values into arraylogs
void update_values(){
  
  // Read temperature and humidity
  DHT.read(DHT11_PIN);
  temperature = DHT.temperature;
  humidity = DHT.humidity;

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
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
    
    while (!client.connected()) {
        String client_id = "esp8266-client-";
        client_id += String(WiFi.macAddress());
    
        Serial.printf("The client %s connects to mosquitto mqtt broker\n", client_id.c_str());
 
        if (client.connect(client_id.c_str(), user, pw)) {
            Serial.println("Public emqx mqtt broker connected");
        } 
        else {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }
}

void setup() {
    Serial.begin(9600);
    
    setup_connections();
    // publish and subscribe
    client.publish(temp_topic, "Hello From ESP8266!");
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

    if(seconds - prev_seconds >= refresh_rate){
        update_values();
        client.publish(temp_topic, String(temperature).c_str());
        client.publish(hum_topic, String(humidity).c_str());
        prev_seconds = seconds();
    }

    client.loop();

    
}
