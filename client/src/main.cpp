#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define YELLOW_LED_PIN 12
#define GREEN_LED_PIN 14
#define HUMIDITY_SENSOR_PIN 32

const char* ssid = "Vora";
const char* password = "tomate01";
const char* mqttServer = "192.168.1.46";
const int mqttPort = 1883;
const char* mqttUser = "sensor_user";
const char* mqttPassword = "sensor123";

char stringHumidity[4];

WiFiClient espClient;
PubSubClient mosquitto_client(espClient);

void callback(char* topic, byte* payload, unsigned int length);
void reconnect();
float getHumidity();
void blink();


void setup() {
	// WIFI CONNECTION
	pinMode(GREEN_LED_PIN, OUTPUT);
	pinMode(YELLOW_LED_PIN, OUTPUT);

	digitalWrite(GREEN_LED_PIN, LOW);
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED){
		digitalWrite(YELLOW_LED_PIN, HIGH);
		delay(500);
	}
	digitalWrite(YELLOW_LED_PIN, LOW);
	blink();

	// MQTT CONNECTION
	mosquitto_client.setServer(mqttServer, mqttPort);
	mosquitto_client.setCallback(callback);

	while (!mosquitto_client.connected()){
		Serial.println("Connecting to MQTT...");
		if (mosquitto_client.connect("ESP32Client",mqttUser,mqttPassword)){
			Serial.println("connected");
			mosquitto_client.subscribe("esp32");
			mosquitto_client.publish("debug", "esp32 conectado");
		}else{
			delay(1500);
		}
	}
	digitalWrite(GREEN_LED_PIN, HIGH);
}


void loop() {
	if (!mosquitto_client.connected()) {
		reconnect();
	}
	mosquitto_client.loop();
	sprintf(stringHumidity, "%f", getHumidity());
	mosquitto_client.publish("sensor/humidity", stringHumidity);
	delay(1000);
}




void reconnect() {
	digitalWrite(YELLOW_LED_PIN, HIGH);
	while (!mosquitto_client.connected()) {
		//Serial.print("Attempting MQTT connection...");
		if (mosquitto_client.connect("ESP32Client", mqttUser, mqttPassword)) {
			mosquitto_client.subscribe("esp32");
			mosquitto_client.publish("debug", "esp32 reconectado");
		} else {
			//Serial.print("failed");
			delay(1000);
		}
	}
	digitalWrite(YELLOW_LED_PIN, LOW);
}


float getHumidity(){
	float humidity = 0;

	humidity = map(analogRead(HUMIDITY_SENSOR_PIN), 0, 1023, 100, 0);

	return humidity;
}

void blink(){
	digitalWrite(GREEN_LED_PIN, HIGH);
	delay(400);
	digitalWrite(GREEN_LED_PIN, LOW);
	delay(400);
	digitalWrite(GREEN_LED_PIN, HIGH);
	delay(400);
	digitalWrite(GREEN_LED_PIN, LOW);
	delay(400);
	digitalWrite(GREEN_LED_PIN, HIGH);
	delay(400);
	digitalWrite(GREEN_LED_PIN, LOW);
	delay(400);
}

void callback(char* topic, byte* payload, unsigned int length){
	return;
}