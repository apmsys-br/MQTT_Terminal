void initMQTT()
{
  if (SSID != "" && PASSWORD != "" && BROKER_MQTT != "") {
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);   //informa qual broker e porta deve ser conectado
    MQTT.setCallback(mqtt_callback);            //atribui função de callback (função chamada quando qualquer informação de um dos tópicos subescritos chega)
  }
  else if (BROKER_MQTT == "") {
    String temp = "Broker not configured...";
    temp.toCharArray(message, 100);
  }
}

/*
  Function: callback function this function is called every time,
  information from one of the subscribed topics arrives)
  Parameters: None
  Return: none

  Função: função de callback esta função é chamada toda vez,
  que uma informação de um dos tópicos subescritos chega)
  Parâmetros: nenhum
  Retorno: nenhum
*/

void mqtt_callback(char* topic, byte* payload, unsigned int length)
{
  String msg;


  //obtem a string do payload recebido
  for (int i = 0; i < length; i++)
  {
    char c = (char)payload[i];
    msg += c;
  }
  Serial.println(msg);
  String temp = "";

  if (key != "") {
    int ini = msg.indexOf(key);
    int end = msg.indexOf(',', ini);
    if (end == -1) end = msg.indexOf('}', ini);



    if (ini != -1 && end != -1) {
      temp = msg.substring(ini, end);
    }
    else temp = "Message not found: " + key;
  }
  else temp = "Key not configured";

  temp.toCharArray(message, 100);

  // ===============================================================================   COMANDOS ==================================================================


}
// ============================================================================================================================================================
/*
  Function: reconnects to MQTT broker (if not already connected or if connection is dropped)
  On successful connection or reconnection, the subscribe of the threads is redone.
  Parameters: None
  Return: none

  Função: reconecta-se ao broker MQTT (caso ainda não esteja conectado ou em caso de a conexão cair)
  em caso de sucesso na conexão ou reconexão, o subscribe dos tópicos é refeito.
  Parâmetros: nenhum
  Retorno: nenhum
*/

void reconnectMQTT()
{
  if (ID_MQTT != "" && USER_MQTT_ID != "" && MQTT_PASSWORD != "") {
    while (!MQTT.connected())
    {
      String temp = "Wait connection...";
      temp.toCharArray(message, 100);

      Serial.print("* Tentando se conectar ao Broker MQTT: ");
      Serial.println(BROKER_MQTT);
      if (MQTT.connect(ID_MQTT, USER_MQTT_ID, MQTT_PASSWORD))
      {
        if (TOPICO_SUBSCRIBE == "") {
          temp = "Topic not configured";
          temp.toCharArray(message, 100);
        }
        Serial.println("Conectado com sucesso ao broker MQTT!");
        MQTT.subscribe(TOPICO_SUBSCRIBE);
      }
      else
      {
        Serial.println("Falha ao reconectar no broker.");
        Serial.println("Havera nova tentatica de conexao em 2s");
        delay(1000);
      }
    }
  }
  else {
    String temp = "Client MQTT not configured...";
    temp.toCharArray(message, 100);
  }
}
