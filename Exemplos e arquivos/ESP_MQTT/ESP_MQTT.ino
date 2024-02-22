 // ---------------------- inclusão das bibliotecas -------------------
#include <WiFi.h>         // inclui a biblioteca do wifi no programa
#include <PubSubClient.h> //inclui a biblioteca do protocolo MQTT

//-----------------------Instânciando bibliotecas-----------------------
WiFiClient wifi_esp;         // Objeto Wifi
PubSubClient MQTT(wifi_esp); // Objeto MQTT 

const char* ssid = ""; //Login wifi
const char* password = ""; //Senha wifi

void mqtt_callback(char* topic, byte* payload, unsigned int length);

#define TOPICO_SUBSCRIBE "senaiAula109" //Tópico para se inscrever

void setup() {
  //Configurações iniciais
    delay(1000);
    Serial.begin(115200);
    Serial.println();
    Serial.print("Conectando-se a ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
    
    Serial.println("WiFi conectada.");
    Serial.println("Endereço de IP: ");
    Serial.println(WiFi.localIP());


    while (!MQTT.connected()) //enquanto estiver desconectado
  {
      MQTT.setServer("test.mosquitto.org", 1883); //tenta conectar ao broker através da porta informada
      MQTT.setCallback(mqtt_callback);            //atribui função de callback (função chamada quando qualquer informação de um dos tópicos subescritos chega)
      Serial.println("Aguarde ...");
      delay(2000); //espera 2 segundos

      if (MQTT.connect("MudarAquiParaQualquerUm") )//se conectou
          {
            Serial.println("Conectado ao broker com sucesso !!!");
            MQTT.subscribe(TOPICO_SUBSCRIBE);
            break;
        }
        else//senão conectou
        {
          Serial.println("Falha de conexao com o broker");
          Serial.println("Havera uma nova tentativa de conexao em 2 segundos");
          delay(2000);//espera 2 segundos
        }
    
  }

  MQTT.publish("senaiAula109", "Opa, sou o ESP e eu to vivo viu." ); #Publicando um alo  
}

void loop() {
  MQTT.loop();

}

void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{
    String msg;
 
    //obtem a string do payload recebido
    for(int i = 0; i < length; i++) 
    {
       char c = (char)payload[i];
       msg += c;
    }
    Serial.print("[MQTT] Mensagem recebida: ");
    Serial.println(msg); 
    if(msg == "ligar"){
      Serial.println("Ligando o led");    
    }
}
