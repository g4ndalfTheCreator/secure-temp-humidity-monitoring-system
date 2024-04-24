# Main file of python handler

import mqtt_utils.connect_mqtt as connect_mqtt
import mqtt_utils.mqtt_pub as pub
import mqtt_utils.mqtt_sub as sub

import os

import postgreSQL_utils.postgres as pg


# MQTT configuration
broker = os.environ['MQTT_BROKER']
port = int(os.environ['MQTT_PORT'])
topics = os.environ['MQTT_TOPICS'].split(',')
sensors = os.environ['MQTT_SENSORS'].split(',')
client_id = os.environ['MQTT_CLIENT_ID']
username = os.environ['MQTT_USERNAME']
password = os.environ['MQTT_PASSWORD']

# PostgreSQL configuration
psql_host = os.environ['POSTGRES_HOST']
psql_port = os.environ['POSTGRES_PORT']
dbname = os.environ['POSTGRES_DB']
psql_user = os.environ['POSTGRES_USER']
psql_password = os.environ['POSTGRES_PASSWORD']


# postgreSQL connection details
DatabaseLogger = pg.DatabaseLogger(dbname=dbname, user=psql_user, password=psql_password, host=psql_host, port=psql_port, sensors=sensors)
DatabaseLogger.connect_to_db()
DatabaseLogger.initialize_db()

# Variables to store latest temperature and humidity values
latest_temperature = None
latest_humidity = None

def handle_callback(topic, payload):
    global latest_temperature, latest_humidity

    #print(f"Received topic: {topic}, payload: {payload}")

    sensor = ""

    if "temperature" in topic:
        latest_temperature = payload
        sensor = topic.replace("temperature", "")

    elif "humidity" in topic:
        latest_humidity = payload
        sensor = topic.replace("humidity", "")

    if latest_temperature is not None and latest_humidity is not None:
        
        print(f"Received temperature: {latest_temperature}, humidity: {latest_humidity}")
        DatabaseLogger.log_data_to_db(temperature=latest_temperature, humidity=latest_humidity, sensor=sensor)
        latest_temperature = None
        latest_humidity = None


def main():

    client = connect_mqtt.connector(broker=broker, port=port, 
                         client_id=client_id, 
                         username=username, password=password)

    #pub.run()
    index = 0
    for topic in topics:
        # Temperature topic for One (1) sensor
        topics[index] = sensors[0] + topic
        index += 1

    sub.run(client=client, topics=topics, callback=handle_callback)
    sub.run()

if __name__ == '__main__':
    main()
