#include <EEPROM.h>
#include <ESP8266WiFi.h> // Importa a Biblioteca ESP8266WiFi
#include <PubSubClient.h> // Importa a Biblioteca PubSubClient
#include <ESP8266WebServer.h>
#include <SPI.h>
#include <bitBangedSPI.h>
#include <MAX7219_Dot_Matrix.h>

// MQTT
char* BROKER_MQTT = ""; //URL do broker MQTT que se deseja utilizar
int BROKER_PORT = 1883; // Porta do Broker MQTT
char* USER_MQTT_ID = "";
char* MQTT_PASSWORD = "";
char* TOPICO_SUBSCRIBE = "";   //tópico MQTT de envio de informações para Broker
char* ID_MQTT = "";     //id mqtt (para identificação de sessão)

// WIFI
char* SSID = ""; // SSID / nome da rede WI-FI que deseja se conectar
char* PASSWORD = ""; // Senha da rede WI-FI que deseja se conectar

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

char tempData[512] = ""

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
void getMqttUserID();
void getMqttTopic();
void setDataE2PROM(char* data, int iniAddres, int endAddress);
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
  getWiFiSSID();
  Serial.println(SSID);
  //getWiFiPassword();
  initWebServer();
  initWiFi();
}

//programa principal
void loop()
{
  if (SSID != "" && PASSWORD != "" && BROKER_MQTT != "") {
    VerificaConexoesWiFIEMQTT();
    MQTT.loop();
  }
  webServerLoop();
  displayLoop();
}
