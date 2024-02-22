import paho.mqtt.client as mqtt #Importando a biblioteca para utilizar mqtt

client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2 ,"UmUsuarioDiferenteSempre") #Instancia do cliente MQTT
client.connect("test.mosquitto.org")  #Broker mqtt a ser utilizado
client.publish("senaiAula109", "ligar") #Publicando uma informação

