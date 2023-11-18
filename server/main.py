from datetime import datetime
import paho.mqtt.client as mqtt

from server.database import database

# MQTT Broker Settings
broker_address = "localhost"  # You can use any MQTT broker of your choice
port = 1883
topic = "humidity"  # Change this to the topic you want to subscribe to

# Callback when the client connects to the broker
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    # Subscribe to the specified topic
    client.subscribe(topic)

# Callback when a message is received from the broker
def on_message(client, userdata, msg):
    humidity = msg.payload.decode()
    print(f"Received message on topic {msg.topic}: {humidity}")
    now = datetime.now()
    database.humiditydb.insert_one({'date': now, 'humidity': humidity})

# Create an MQTT client instance
client = mqtt.Client()

# Set the callback functions
client.on_connect = on_connect
client.on_message = on_message

# Connect to the broker
client.connect(broker_address, port, 60)

# Loop to maintain the connection and receive messages
client.loop_forever()
