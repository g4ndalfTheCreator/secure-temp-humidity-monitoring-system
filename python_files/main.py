# Main file of python handler

import mqtt_utils.connect_mqtt as connect_mqtt
import mqtt_utils.mqtt_pub as pub
import mqtt_utils.mqtt_sub as sub

import os

import postgreSQL_utils.postgres as pg

broker = '192.168.0.112'
port = 1883
topics = ["temperature", "humidity"]
# Generate a Client ID with the subscribe prefix.
client_id = 'server-sub-1'
username = 'test_user'
password = 'pw'


psql_host = 'postgres'
psql_port = '5432'

# MQTT configuration
# broker = os.environ['MQTT_BROKER']
# port = int(os.environ['MQTT_PORT'])
# topics = os.environ['MQTT_TOPICS'].split(',')
# sensors = os.environ['MQTT_SENSORS'].split(',')
# client_id = os.environ['MQTT_CLIENT_ID']
# username = os.environ['MQTT_USERNAME']
# password = os.environ['MQTT_PASSWORD']

# # PostgreSQL configuration
# psql_host = os.environ['POSTGRES_HOST']
# psql_port = os.environ['POSTGRES_PORT']
# dbname = os.environ['POSTGRES_DB']
# user = os.environ['POSTGRES_USER']
# password = os.environ['POSTGRES_PASSWORD']


# # postgreSQL connection details
# DatabaseLogger = pg.DatabaseLogger(dbname='temp-hum-db', user='usr', password='pw', host=psql_host, port=psql_port, device_name='demo_device')
# DatabaseLogger.connect_to_db()
# DatabaseLogger.initialize_db()

# # Variables to store latest temperature and humidity values
# latest_temperature = None
# latest_humidity = None

# def handle_callback(topic, payload):
#     global latest_temperature, latest_humidity

#     #print(f"Received topic: {topic}, payload: {payload}")

#     if topic == "temperature":
#         latest_temperature = payload
#     elif topic == "humidity":
#         latest_humidity = payload

#     if latest_temperature is not None and latest_humidity is not None:
#         print(f"Received temperature: {latest_temperature}, humidity: {latest_humidity}")
#         DatabaseLogger.log_data_to_db(temperature=latest_temperature, humidity=latest_humidity)
#         latest_temperature = None
#         latest_humidity = None


# def main():

#     client = connect_mqtt.connector(broker=broker, port=port, 
#                          client_id=client_id, 
#                          username=username, password=password)

#     #pub.run()
#     sub.run(client=client, topics=topics, callback=handle_callback)
#     sub.run()

# if __name__ == '__main__':
#     main()

import time

while(1):
    time.sleep(100)
    print("Hello World")