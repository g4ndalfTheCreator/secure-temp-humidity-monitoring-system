from paho.mqtt import client as mqtt_client


def subscribe(client: mqtt_client, topic: str, callback):
    def on_message(client, userdata, msg):
        callback(msg.topic, msg.payload.decode())

    client.subscribe(topic)
    client.on_message = on_message


def run(client: mqtt_client, topics: dict, callback):

    for topic in topics:
        subscribe(client=client, topic=topic, callback=callback)

    client.loop_forever()
