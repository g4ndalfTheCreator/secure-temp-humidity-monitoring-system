# python 3.11

import time
from paho.mqtt import client as mqtt_client

def publish(client: mqtt_client, topic: str):
    msg_count = 1
    while True:
        time.sleep(1)
        msg = f"messages: {msg_count}"
        result = client.publish(topic, msg)
        # result: [0, 1]
        status = result[0]
        if status == 0:
            print(f"Send `{msg}` to topic `{topic}`")
        else:
            print(f"Failed to send message to topic {topic}")
        msg_count += 1
        if msg_count > 5:
            break


def run(client: mqtt_client, topic: str):
    client.loop_start()
    publish(client, topic)
    client.loop_stop()
