# Main file of python handler

import mqtt_utils.connect_mqtt as connect_mqtt
import mqtt_utils.mqtt_pub as pub
import mqtt_utils.mqtt_sub as sub

broker = '192.168.0.112'
port = 1883
topic = "temperature"
# Generate a Client ID with the subscribe prefix.
client_id = 'server-sub'
username = 'test_user'
password = 'pw'

# InfluxDB connection details
# tbd

def handle_callback(payload):
    print(f"Received `{payload}` from topic `{topic}`")


def main():

    temperature_payload = 0

    client = connect_mqtt.connector(broker=broker, port=port, 
                         client_id=client_id, 
                         username=username, password=password)

    #pub.run()
    sub.run(client=client, topic=topic, callback=handle_callback)
    print(temperature_payload)

if __name__ == '__main__':
    main()
