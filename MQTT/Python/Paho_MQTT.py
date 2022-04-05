from paho.mqtt import client as mqtt_client
import time

broker = 'Servidor'
port = 1883
topic = "Led1"
client_id = 'IDname'
username = 'USER'
password = 'PASSWORD'


def connect_mqtt():
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)

    client = mqtt_client.Client(client_id)
    client.username_pw_set(username, password)
    client.on_connect = on_connect
    client.connect(broker, port)
    return client


def publish(client, paquete):
    time.sleep(1)
    client.publish(topic, paquete )
    time.sleep(1)


def run():
    client = connect_mqtt()
    while True:
        mensaje = str(input("Ingresa un mensaje: "))
        client.loop_start()
        publish(client, mensaje)



run()
