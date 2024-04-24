import paho.mqtt.client as mqtt

# Define callback function for when a message is received
def on_message(client, userdata, message):
    print("Received message on topic: " + message.topic)
    print("Message payload: " + str(message.payload))

client_id = 'test'
# Create MQTT client instance
client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION1, client_id)

# Set callback function
client.on_message = on_message

broker = '192.168.0.112'
port = 1883

# Connect to MQTT broker
client.connect(broker, 1883)

# Subscribe to multiple topics
topics = [(client_id, "temperature"), (client_id, "humidity")]  # List of tuples (topic, qos)
for topic in topics:
    client.subscribe(topic[0], qos=topic[1])

# Start the loop to process MQTT messages
client.loop_forever()
