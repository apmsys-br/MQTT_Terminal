//#include <ESP8266WiFi.h> // Importa a Biblioteca ESP8266WiFi
//#include <PubSubClient.h> // Importa a Biblioteca PubSubClient
#include <SPI.h>
#include "libs/bitBangedSPI-master/bitBangedSPI.h"
#include "libs/MAX7219_Dot_Matrix-master/src/MAX7219_Dot_Matrix.h"

/*
#define TOPICO_SUBSCRIBE   "eMille/v1/Bet/IoTTemperatura"   //tópico MQTT de envio de informações para Broker
#define ID_MQTT  "Snnifer"     //id mqtt (para identificação de sessão)

// MQTT
const char* BROKER_MQTT = "172.20.207.248"; //URL do broker MQTT que se deseja utilizar
int BROKER_PORT = 1883; // Porta do Broker MQTT
const char* USER_MQTT_ID = "emille";
const char* MQTT_PASSWORD = "XksbMVFR3WnEexmd";
*/

// Matrix
const byte chips = 4;
unsigned long lastMoved = 0;
unsigned long MOVE_INTERVAL = 20;  // mS
int  messageOffset;
const char message [] = "Testing 1234567890";

//Variáveis e objetos globais
//WiFiClient espClient; // Cria o objeto espClient
//PubSubClient MQTT(espClient); // Instancia o Cliente MQTT passando o objeto espClient
MAX7219_Dot_Matrix display(chips, 2);  // Chips / LOAD

//Prototypes
//void initWiFi();
//void initMQTT();
//void reconectWiFi();
//void updateDisplay();
//void mqtt_callback(char* topic, byte* payload, unsigned int length);
//void VerificaConexoesWiFIEMQTT(void);

void setup()
{
  Serial.begin(9600);
  //display.begin();
  //initWiFi();
  //initMQTT();
}

//programa principal
void loop()
{
  //VerificaConexoesWiFIEMQTT();
  //MQTT.loop();
  //displayLoop();
}
