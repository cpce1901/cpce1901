#include <ESP8266WiFi.h>
#include <PubSubClient.h>


//************************Datos de Wifi***********************//
const char* ssid = "xxxxxxx";
const char* password = "xxxxxxxxx";

//************************Datos de Brocker***********************//

const char* mqtt_server = "xxxxxxxxx"; 
const char* Id = "xxxxxxxx";
const char* User = "xxxxxxxx";
const char* CodePass = "xxxxxxxx";

WiFiClient espClient;
PubSubClient client(espClient);
String _topic;
String _payload;

//************************ Conexion Wifi ***********************//

void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("OK");
}

//************************ Reconect ***********************//

void reconnect() {
  while (!client.connected()) {
    Serial.println("Intentando concetar con servidor MQTT...");
    if (client.connect(Id, User, CodePass)) {
      Serial.println("connectado");
      client.subscribe("Led1");
      client.subscribe("Led2");

    } else {
      Serial.print("Falla, Estado: ");
      Serial.print(client.state());
      Serial.println("Intentando en 5 segundos..");
      delay(5000);
    }
  }
}

//************************ Callback ***********************//

void callback (char* topic, byte* payload, unsigned int length) {
  String conc_payload_;
  for (int i = 0; i < length; i++) {
    conc_payload_ += (char)payload[i];
  }
  _topic = topic;
  _payload = conc_payload_;

}


void setup() {
  
  Serial.begin(115200);
  Serial.println("iniciando");
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  Serial.println(_topic);
  Serial.println(_payload);
  delay(1000);

}
