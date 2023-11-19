from datetime import datetime
import paho.mqtt.client as mqtt
from loguru import logger
from server.database import cursor, connection

# MQTT Broker Settings
broker_address = "humidity_sensor-mosquitto-1"  # You can use any MQTT broker of your choice
port = 1883
topic = "sensor/humidity"
username = "sensor_user"
password = "sensor123"

# Callback when the client connects to the broker
def on_connect(client, userdata, flags, rc):
    print(f"Connected with result code {str(rc)}")
    # Subscribe to the specified topic
    client.subscribe(topic)

# Callback when a message is received from the broker
def on_message(client, userdata, msg):
    logger.info("Message received...")
    humidity = msg.payload.decode()
    print(f"Received message on topic {msg.topic}: {humidity}")
    now = datetime.now()
    cursor.execute('insert into sensor.humidity (value, timestamp) values (%s, %s)', (humidity, now))
    connection.commit()

# Create an MQTT client instance
client = mqtt.Client()

# Set the callback functions
client.on_connect = on_connect
client.on_message = on_message

# Set MQTT username and password
client.username_pw_set(username, password)

# Connect to the broker
client.connect(broker_address, port, 60)

# Loop to maintain the connection and receive messages
client.loop_forever()
