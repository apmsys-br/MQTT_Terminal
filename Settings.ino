void getWiFiSSID() {
  int i = 0;
  String aux = " ";

  if ((byte)EEPROM.read(0) != 0xFF) {
    aux = "";
    for (i = 0; i < WIFI_SSID_LENGTH; i++) {
      byte b = (byte)EEPROM.read(i);
      aux += (char)b;
      if (b == 0x00) break;
    }
  }
  aux.toCharArray(SSID, WIFI_SSID_LENGTH);
}

void getWiFiPassword() {
  int i = 0;
  int offset = WIFI_SSID_LENGTH;
  String aux = " ";

  if ((byte)EEPROM.read(offset) != 0xFF) {
    aux = "";
    for (i = offset; i < offset + WIFI_PASSWORD_LENGTH; i++) {
      byte b = (byte)EEPROM.read(i);
      aux += (char)b;
      if (b == 0x00) break;
    }
  }
  aux.toCharArray(PASSWORD, WIFI_PASSWORD_LENGTH);
}

void getBrokerURL() {
  int i = 0;
  int offset = WIFI_SSID_LENGTH + WIFI_PASSWORD_LENGTH;
  String aux = " ";

  if ((byte)EEPROM.read(offset) != 0xFF) {
    aux = "";
    for (i = offset; i < offset + BROKER_URL_LENGTH; i++) {
      byte b = (byte)EEPROM.read(i);
      aux += (char)b;
      if (b == 0x00) break;
    }
  }
  aux.toCharArray(BROKER_MQTT, BROKER_URL_LENGTH);
}

void getBrokerPort() {
  int i = 0;
  int j = 0;
  int offset = WIFI_SSID_LENGTH + WIFI_PASSWORD_LENGTH + BROKER_URL_LENGTH;
  char aux[5] = "";

  if ((byte)EEPROM.read(offset) != 0xFF) {
    for (i = offset, j = 0; i < offset + 5; i++, j++) {
      byte b = (byte)EEPROM.read(i);
      aux[j] += (char)b;
      if (b == 0x00) break;
    }
  }

  int k;
  bool eNum = true;
  for (k = 0; k < 5; k++) {
    if (aux[k] < 48 && aux[k] > 56) {
      eNum = false;
      break;
    }
  }

  if (eNum) BROKER_PORT = atoi(aux);
}

void getMqttClientID() {
  int i = 0;
  int offset = WIFI_SSID_LENGTH + WIFI_PASSWORD_LENGTH + BROKER_URL_LENGTH + 5;
  String aux = " ";

  if ((byte)EEPROM.read(offset) != 0xFF) {
    aux = "";
    for (i = offset; i < offset + MQTT_USERID_LENGTH; i++) {
      byte b = (byte)EEPROM.read(i);
      aux += (char)b;
      if (b == 0x00) break;
    }
  }
  aux.toCharArray(USER_MQTT_ID, MQTT_USERID_LENGTH);
}

void getMqttClientPassword() {
  int i = 0;
  int offset = WIFI_SSID_LENGTH + WIFI_PASSWORD_LENGTH + BROKER_URL_LENGTH + 5 + MQTT_USERID_LENGTH;
  String aux = " ";

  if ((byte)EEPROM.read(offset) != 0xFF) {
    aux = "";
    for (i = offset; i < offset + MQTT_PASSWORD_LENGTH; i++) {
      byte b = (byte)EEPROM.read(i);
      aux += (char)b;
      if (b == 0x00) break;
    }
  }
  aux.toCharArray(MQTT_PASSWORD, MQTT_PASSWORD_LENGTH);
}

void getMqttUserName() {
  int i = 0;
  int offset = WIFI_SSID_LENGTH + WIFI_PASSWORD_LENGTH + BROKER_URL_LENGTH + 5 + MQTT_USERID_LENGTH + MQTT_PASSWORD_LENGTH;
  String aux = " ";

  if ((byte)EEPROM.read(offset) != 0xFF) {
    aux = "";
    for (i = offset; i < offset + MQTT_USERNAME_LENGTH; i++) {
      byte b = (byte)EEPROM.read(i);
      aux += (char)b;
      if (b == 0x00) break;
    }
  }
  aux.toCharArray(ID_MQTT, MQTT_USERNAME_LENGTH);
}

void getMqttTopic() {
  int i = 0;
  int offset = WIFI_SSID_LENGTH + WIFI_PASSWORD_LENGTH + BROKER_URL_LENGTH + 5 + MQTT_USERID_LENGTH + MQTT_PASSWORD_LENGTH + MQTT_USERNAME_LENGTH;
  String aux = " ";

  if ((byte)EEPROM.read(offset) != 0xFF) {
    aux = "";
    for (i = offset; i < offset + MQTT_TOPIC_SUBCRIBE_LENGTH; i++) {
      byte b = (byte)EEPROM.read(i);
      aux += (char)b;
      if (b == 0x00) break;
    }
  }
  aux.toCharArray(TOPICO_SUBSCRIBE, MQTT_TOPIC_SUBCRIBE_LENGTH);
}

void getKeyTopic() {
  int i = 0;
  int offset = WIFI_SSID_LENGTH + WIFI_PASSWORD_LENGTH + BROKER_URL_LENGTH + 5 + MQTT_USERID_LENGTH + MQTT_PASSWORD_LENGTH + MQTT_USERNAME_LENGTH + MQTT_TOPIC_SUBCRIBE_LENGTH;
  String aux = " ";

  if ((byte)EEPROM.read(offset) != 0xFF) {
    aux = "";
    for (i = offset; i < offset + MQTT_TOPIC_KEYWORD_LENGTH; i++) {
      byte b = (byte)EEPROM.read(i);
      aux += (char)b;
      if (b == 0x00) break;
    }
  }
  aux.toCharArray(keyTopic, MQTT_TOPIC_KEYWORD_LENGTH);

  int j;
  key = "\"";;
  for (j = 0; j < i; j++) key += keyTopic[j];
  key += "\"";
}
