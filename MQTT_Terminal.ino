#include <EEPROM.h>
#include <ESP8266WiFi.h> // Importa a Biblioteca ESP8266WiFi
#include <PubSubClient.h> // Importa a Biblioteca PubSubClient
#include <ESP8266WebServer.h>
#include <SPI.h>
#include <bitBangedSPI.h>
#include <MAX7219_Dot_Matrix.h>

#define WIFI_SSID_LENGTH 20
#define WIFI_PASSWORD_LENGTH 20
#define BROKER_URL_LENGTH 15
#define MQTT_USERID_LENGTH 20
#define MQTT_PASSWORD_LENGTH 20
#define MQTT_USERNAME_LENGTH 20
#define MQTT_TOPIC_SUBCRIBE_LENGTH 50
#define MQTT_TOPIC_KEYWORD_LENGTH 20

// MQTT
char BROKER_MQTT[BROKER_URL_LENGTH] = ""; //URL do broker MQTT que se deseja utilizar
int BROKER_PORT = 1883; // Porta do Broker MQTT
char USER_MQTT_ID[MQTT_USERID_LENGTH] = "";
char MQTT_PASSWORD[MQTT_PASSWORD_LENGTH] = "";
char TOPICO_SUBSCRIBE[MQTT_TOPIC_SUBCRIBE_LENGTH] = "";   //tópico MQTT de envio de informações para Broker
char ID_MQTT[MQTT_USERNAME_LENGTH] = "";     //id mqtt (para identificação de sessão)
char keyTopic[MQTT_TOPIC_KEYWORD_LENGTH] = "";

// WIFI
char SSID[WIFI_SSID_LENGTH] = ""; // SSID / nome da rede WI-FI que deseja se conectar
char PASSWORD[WIFI_PASSWORD_LENGTH] = ""; // Senha da rede WI-FI que deseja se conectar

// Matrix
const byte chips = 4;
unsigned long lastMoved = 0;
unsigned long MOVE_INTERVAL = 50;  // mS
int  messageOffset;
char message [100] = "";
String key = "";

// Web
String htmlPage = "";

//Variáveis e objetos globais
ESP8266WebServer server(80);
WiFiClient espClient; // Cria o objeto espClient
PubSubClient MQTT(espClient); // Instancia o Cliente MQTT passando o objeto espClient
MAX7219_Dot_Matrix display(chips, 2);  // Chips / LOAD

//Prototypes
void getWiFiSSID();
void getWiFiPassword();
void getBrokerURL();
void getBrokerPort();
void getMqttClientID();
void getMqttClientPassword();
void getMqttUserName();
void getMqttTopic();
void getKeyTopic();
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
  EEPROM.begin(256);
  getWiFiSSID();
  getWiFiPassword();
  getBrokerURL();
  getBrokerPort();
  getMqttClientID();
  getMqttClientPassword();
  getMqttUserName();
  getMqttTopic();
  getKeyTopic();
  EEPROM.end();
  initWebServer();
  initWiFi();
}

//programa principal
void loop()
{
  if (SSID[0] != ' ' && PASSWORD[0] != ' ' && BROKER_MQTT[0] != ' ') {
    VerificaConexoesWiFIEMQTT();
    MQTT.loop();
  }
  webServerLoop();
  displayLoop();
}
