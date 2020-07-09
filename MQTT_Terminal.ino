#include <ESP8266WiFi.h> // Importa a Biblioteca ESP8266WiFi
#include <PubSubClient.h> // Importa a Biblioteca PubSubClient
#include <ESP8266WebServer.h>
#include <SPI.h>
#include <bitBangedSPI.h>
#include <MAX7219_Dot_Matrix.h>
#include "credentials.h"

char* TOPICO_SUBSCRIBE = "eMille/v1/Bet/IoTTemperatura";   //tópico MQTT de envio de informações para Broker
char* ID_MQTT = "Snnifer";     //id mqtt (para identificação de sessão)

// Matrix
const byte chips = 4;
unsigned long lastMoved = 0;
unsigned long MOVE_INTERVAL = 50;  // mS
int  messageOffset;
char message [100] = "";
String key = "";
String tempKey = "";

// Web
String htmlPage = "";

//Variáveis e objetos globais
ESP8266WebServer server(80);
WiFiClient espClient; // Cria o objeto espClient
PubSubClient MQTT(espClient); // Instancia o Cliente MQTT passando o objeto espClient
MAX7219_Dot_Matrix display(chips, 2);  // Chips / LOAD

//Prototypes
void initWebServer();
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
  initWebServer();
  initWiFi();
  initMQTT();
}

//programa principal
void loop()
{
  VerificaConexoesWiFIEMQTT();
  MQTT.loop();
  webServerLoop();
  displayLoop();

  while (Serial.available()) {
    char c = Serial.read();

    if (c != 13) {
      tempKey += c;
    }
    else {
      key = "\"" + tempKey + "\"";
      tempKey = "";
    }
  }
}
