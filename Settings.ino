void getWiFiSSID() {
  int i;
  for (i = 0; i < 20; i++)
  {
    char c = (char)EEPROM.read(i);
    SSID[i] = c;
    if(c == '\0') break;
  }
  Serial.print("Lido");
  Serial.println(SSID);
}

void getWiFiPassword() {

}

void getBrokerURL() {

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

void setDataE2PROM(char* data, int iniAddres) {
  int i = 0;
  int ini = 0;
  int dLength = sizeof(data);
  Serial.println(dLength);
  
  for (ini = iniAddres; i < dLength; ini++, i++) {
    EEPROM.write(ini, (byte)data[i]);
  }
  EEPROM.commit();
}
