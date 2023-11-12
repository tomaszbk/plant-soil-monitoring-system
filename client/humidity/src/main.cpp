#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define GREEN_LED_PIN 5
#define YELLOW_LED_PIN 6
#define HUMIDITY_SENSOR_PIN 34

const char* ssid = "Vora 2.4G";
const char* password = "tomate0001";
const char* mqttServer = "192.168.0.18";
const int mqttPort = 1883;
const char* mqttUser = "tomas";
const char* mqttPassword = "escape";

char stringHumidity[4];

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length);
void reconnect();
float getHumidity();


void setup() {
	// WIFI CONNECTION
	pinMode(GREEN_LED_PIN, OUTPUT);
	digitalWrite(GREEN_LED_PIN, LOW);
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED){
		digitalWrite(YELLOW_LED_PIN, HIGH);
		delay(500);
	}
	digitalWrite(YELLOW_LED_PIN, LOW);
	digitalWrite(GREEN_LED_PIN, HIGH);

	// MQTT CONNECTION
	client.setServer(mqttServer, mqttPort);
	client.setCallback(callback);

	while (!client.connected()){
		Serial.println("Connecting to MQTT...");
		if (client.connect("ESP32Client",mqttUser,mqttPassword)){
			Serial.println("connected");
			client.subscribe("esp32");
			client.publish("debug", "esp32 conectado");
		}else{
			delay(1500);
		}
	}
}


void loop() {
	if (!client.connected()) {
		reconnect();
	}
	client.loop();
	//get humidity
	sprintf(stringHumidity, "%f", getHumidity());
	client.publish("humidity", stringHumidity);
}


void reconnect() {
	while (!client.connected()) {
		//Serial.print("Attempting MQTT connection...");
		if (client.connect("ESP32Client", mqttUser, mqttPassword)) {
			client.subscribe("esp32");
			client.publish("debug", "esp32 reconectado");
		} else {
			//Serial.print("failed");
			delay(1000);
		}
	}
}


float getHumidity(){
	float humidity = 0;
	for (int i = 0; i < 10; i++){
		humidity += analogRead(HUMIDITY_SENSOR_PIN);
		delay(100);
	}
	humidity = humidity/10;
	return humidity;
}