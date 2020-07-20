
void handleRoot() {
  htmlPage = "<html>";
  htmlPage += "<head>";
  htmlPage += "<title>Setting</title>";
  htmlPage += "<style>";
  htmlPage += "html, body {height: 100%;}";
  htmlPage += "body, input, select {padding: 0;margin: 0;outline: none;font-family: Roboto, Arial, sans-serif;font-size: 16px;color: #fff;}";
  htmlPage += "h1 {font-weight: 400;font-size: 32px;}";
  htmlPage += ".main-block, .info {display: flex;flex-direction: column;}";
  htmlPage += ".main-block {justify-content: center;align-items: center;width: 100%;min-height: 100%;background-size: cover;}";
  htmlPage += "form {width: 80%;padding: 25px;margin-bottom: 20px;background: rgba(0, 0, 0, 0.9);}";
  htmlPage += "input {padding: 5px;margin-bottom: 20px;background: transparent;border: none;border-bottom: 1px solid #eee;}";
  htmlPage += "input::placeholder {color: #eee;}";
  htmlPage += "button {display: block;width: 200px;padding: 10px;margin: 20px auto 0;border: none;border-radius: 5px;background: #1c87c9;font-size: 14px;font-weight: 600;color: #fff;}";
  htmlPage += "button:hover {background: #095484;}";
  htmlPage += "@media (min-width: 568px) {";
  htmlPage += ".info {flex-flow: row wrap;justify-content: space-between;}";
  htmlPage += "h1 {font-weight: 400;font-size: 60px;color: rgb(9, 114, 211);}";
  htmlPage += "input {width: 80%;}}";
  htmlPage += "</style>";
  htmlPage += "</head>";
  htmlPage += "<body>";
  htmlPage += "<div class=\"main-block\">";
  htmlPage += "<h1>MQTT Terminal Settings</h1>";
  htmlPage += "<form action=\"/info\" method=\"POST\">";
  htmlPage += "<div class=\"info\">";
  htmlPage += "<input type=\"text\" name=\"wssid\" placeholder=\"WiFi SSID\" value=\"" + String(SSID) + "\">WiFi SSID</input>";
  htmlPage += "<input type=\"text\" name=\"wpass\" placeholder=\"WiFi password\" value=\"" + String(PASSWORD) + "\">WiFi password</input>";
  htmlPage += "<input type=\"text\" name=\"burl\" placeholder=\"Broker url\" value=\"" + String(BROKER_MQTT) + "\">Broker url</input>";
  htmlPage += "<input type=\"text\" name=\"bport\" placeholder=\"Broker port\" value=\"" + String(BROKER_PORT) + "\">Broker port</input>";
  htmlPage += "<input type=\"text\" name=\"usrid\" placeholder=\"MQTT UserID\" value=\"" + String(USER_MQTT_ID) + "\">MQTT UserID</input>";
  htmlPage += "<input type=\"text\" name=\"mpass\" placeholder=\"MQTT password\" value=\"" + String(MQTT_PASSWORD) + "\">MQTT password</input>";
  htmlPage += "<input type=\"text\" name=\"devtar\" placeholder=\"MQTT Device target\" value=\"" + String(deviceTarget) + "\">MQTT Device target</input>";
  htmlPage += "<input type=\"text\" name=\"topic\" placeholder=\"Topic subscribe\" value=\"" + String(TOPICO_SUBSCRIBE) + "\">Topic subscribe</input>";;
  htmlPage += "<input type=\"text\" name=\"key\" placeholder=\"Key target\" value=\"" + String(keyTopic) + "\">Key target</input>";
  htmlPage += "</div>";
  htmlPage += "<button href=\"/info\" class=\"button\">Submit</button>";
  htmlPage += "</form>";
  htmlPage += "</div>";
  htmlPage += "</body>";
  htmlPage += "</html>";

  server.send(200, "text/html", htmlPage);
}

void handleInfo() {
  char ssid[WIFI_SSID_LENGTH] = "";
  char pass[WIFI_PASSWORD_LENGTH] = "";
  char broker[BROKER_URL_LENGTH] = "";
  char port[5] = "";
  char mqttID[MQTT_USERID_LENGTH] = "";
  char mqttPass[MQTT_PASSWORD_LENGTH] = "";
  char topicSub[MQTT_TOPIC_SUBCRIBE_LENGTH] = "";
  char targetDev[MQTT_DEVTARGET_LENGTH] = "";
  char topicKey[MQTT_TOPIC_KEYWORD_LENGTH] = "";

  server.arg("wssid").toCharArray(ssid, WIFI_SSID_LENGTH);
  server.arg("wpass").toCharArray(pass, WIFI_PASSWORD_LENGTH);
  server.arg("burl").toCharArray(broker, BROKER_URL_LENGTH);
  server.arg("bport").toCharArray(port, 5);
  server.arg("usrid").toCharArray(mqttID, MQTT_USERID_LENGTH);
  server.arg("mpass").toCharArray(mqttPass, MQTT_PASSWORD_LENGTH);
  server.arg("devtar").toCharArray(targetDev, MQTT_DEVTARGET_LENGTH);
  server.arg("topic").toCharArray(topicSub, MQTT_TOPIC_SUBCRIBE_LENGTH);
  server.arg("key").toCharArray(topicKey, MQTT_TOPIC_KEYWORD_LENGTH);

  Serial.println(ssid);
  Serial.println(pass);
  Serial.println(broker);
  Serial.println(port);
  Serial.println(mqttID);
  Serial.println(mqttPass);
  Serial.println(topicSub);
  Serial.println(targetDev);
  Serial.println(topicKey);

  htmlPage = "<html>";
  htmlPage += "<head>";
  htmlPage += "<title>Settings</title>";
  htmlPage += "</head>";
  htmlPage += "<body>";
  htmlPage += "<form action=\"/\">";
  htmlPage += "<div><h1>Sucess. Please reset this device and press Back button!</h1></div>";
  htmlPage += "<div><button href=\"/\">Back</button></div>";
  htmlPage += "</form>";
  htmlPage += "</body>";
  htmlPage += "</html>";

  server.send(200, "text/html", htmlPage);

  int offset = 0;

  EEPROM.begin(256);
  EEPROM.put(offset, ssid);
  offset += WIFI_SSID_LENGTH;
  EEPROM.put(offset, pass);
  offset += WIFI_PASSWORD_LENGTH;
  EEPROM.put(offset, broker);
  offset += BROKER_URL_LENGTH;
  EEPROM.put(offset, port);
  offset += 5;
  EEPROM.put(offset, mqttID);
  offset += MQTT_USERID_LENGTH;
  EEPROM.put(offset, mqttPass);
  offset += MQTT_PASSWORD_LENGTH;
  EEPROM.put(offset, targetDev);
  offset += MQTT_DEVTARGET_LENGTH;
  EEPROM.put(offset, topicSub);
  offset += MQTT_TOPIC_SUBCRIBE_LENGTH;
  EEPROM.put(offset, topicKey);
  EEPROM.commit();
  delay(1000);

  int w;
  for (w = 0; w < 256; w++) Serial.print((char)EEPROM.read(w));

  String temp = "Reset device!";
  temp.toCharArray(message, 100);
}

void initWebServer() {
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", HTTP_GET, handleRoot);
  server.on("/info", HTTP_POST, handleInfo);
  server.begin();
  Serial.println("HTTP server started");
}

void webServerLoop() {
  server.handleClient();
}
