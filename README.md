# 🌱 Plant Soil Monitoring System

📌
The project consists of an ESP32 client connected to a soil moisture sensor which send the readings to a Mosquitto queue, and a python server which reads the queue and stores the data in a Mongo Database.

The readings are read from the database and visualized through in real time with grafana.

![Alt Text](/docs/system_diagram.png)

## 📝 Requirements
### Hardware
- ESP32
- Soil Moisture Sensor
- 9v Battery
### Software
- Python 3.10+
- Mosquitto
- MongoDB
- Grafana

## Client Setup
![Alt Text](/docs/humidity_sensor_setup.jpg)

## How it looks
### Sensor readings in the database:
![Alt Text](/docs/mongodb_database_documents.png)