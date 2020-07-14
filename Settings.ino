void getWiFiSSID() {
  int i;
  int j;
  String merda= "";
  EEPROM.begin(512);
  if ((byte)EEPROM.read(0) != 0xFF) {
    for (i = 0, j = 0; j <= 19; i++, j++) {
      byte b = (byte)EEPROM.read(j);
      merda += (char)b;
      //if(b == 0x00) break;
      //Serial.print((byte)EEPROM.read(j));
      //SSID[i] = (char)EEPROM.read(j);
    }

    merda.toCharArray(SSID, 20);
  }
  EEPROM.end();
}

void getWiFiPassword() {
  int i;
  int j;
  EEPROM.begin(512);
  if ((byte)EEPROM.read(20) != 0xFF) {
    for (i = 0, j = 20; j <= 39; i++, j++) PASSWORD[i] = (char)EEPROM.read(j);
  }
  EEPROM.end();
  Serial.println(PASSWORD);
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
