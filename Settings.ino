void getWiFiSSID() {
  int i = 0;
  String aux = " ";

  if ((byte)EEPROM.read(0) != 0xFF) {
    aux = "";
    for (i = 0; i <= 19; i++) {
      byte b = (byte)EEPROM.read(i);
      aux += (char)b;
      if (b == 0x00) break;
    }
    Serial.print("Interna SSID: ");
    Serial.println(aux);
  }
  aux.toCharArray(SSID, 20);
}

void getWiFiPassword() {
  int i = 0;
  String aux = " ";

  if ((byte)EEPROM.read(20) != 0xFF) {
    aux = "";
    for (i = 20; i <= 39; i++) {
      byte b = (byte)EEPROM.read(i);
      aux += (char)b;
      if (b == 0x00) break;
    }
    Serial.print("Interna PASS: ");
    Serial.println(aux);
  }
  aux.toCharArray(PASSWORD, 20);
}

void getBrokerURL() {
  int i = 0;
  String aux = " ";

  if ((byte)EEPROM.read(40) != 0xFF) {
    aux = "";
    for (i = 40; i <= 54; i++) {
      byte b = (byte)EEPROM.read(i);
      aux += (char)b;
      if (b == 0x00) break;
    }
    Serial.print("Interna Broker: ");
    Serial.println(aux);
  }
  aux.toCharArray(BROKER_MQTT, 15);
}

void getBrokerPort() {

}

void getMqttClientID() {

}

void getMqttClientPassword() {

}

void getMqttUserID() {

}

void getMqttTopic() {

}

void setDataE2PROM(char data[], int iniAddress, int endAddress) {
  int i;
  int ini;
  int dLength = strlen(data);
  //Serial.println(dLength);

  for (ini = iniAddress, i = 0; ini <= endAddress; ini++, i++) {
    if (i < dLength) EEPROM.write(ini, (byte)data[i]);
    else EEPROM.write(ini, 0xFF);
  }

  EEPROM.commit();
}
