#include <ESP8266WiFi.h> // Importa a Biblioteca ESP8266WiFi
#include <PubSubClient.h> // Importa a Biblioteca PubSubClient
#include <SPI.h>
#include <bitBangedSPI.h>
#include <MAX7219_Dot_Matrix.h>
#include "credentials.h"

#define TOPICO_SUBSCRIBE   "eMille/v1/Bet/IoTTemperatura"   //tópico MQTT de envio de informações para Broker
#define ID_MQTT  "Snnifer"     //id mqtt (para identificação de sessão)

// Matrix
const byte chips = 4;
unsigned long lastMoved = 0;
unsigned long MOVE_INTERVAL = 20;  // mS
int  messageOffset;
char message [400] = "";

//Variáveis e objetos globais
WiFiClient espClient; // Cria o objeto espClient
PubSubClient MQTT(espClient); // Instancia o Cliente MQTT passando o objeto espClient
MAX7219_Dot_Matrix display(chips, 2);  // Chips / LOAD

//Prototypes
void initWiFi();
void initMQTT();
void reconectWiFi();
void updateDisplay();
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void VerificaConexoesWiFIEMQTT(void);

void setup()
{
  Serial.begin(9600);
  display.begin();
  initWiFi();
  initMQTT();
}

//programa principal
void loop()
{
  VerificaConexoesWiFIEMQTT();
  MQTT.loop();
  displayLoop();
}
