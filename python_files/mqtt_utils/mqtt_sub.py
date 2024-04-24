from paho.mqtt import client as mqtt_client

def subscribe(client: mqtt_client, topic: str, callback):
    def on_message(client, userdata, msg):
        callback(msg.topic, msg.payload.decode())

    client.subscribe(topic)
    client.on_message = on_message


def run(client: mqtt_client, topics: dict, callback):
    subscribe(client=client, topic=topics[0], callback=callback) # temperature
    subscribe(client=client, topic=topics[1], callback=callback) # humidity
    client.loop_forever()
