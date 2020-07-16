
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
  htmlPage += "<input type=\"text\" name=\"burl\" placeholder=\"Broker url\">";
  htmlPage += "<input type=\"text\" name=\"bport\" placeholder=\"Broker port\">";
  htmlPage += "<input type=\"text\" name=\"usrid\" placeholder=\"MQTT UserID\">";
  htmlPage += "<input type=\"text\" name=\"mpass\" placeholder=\"MQTT password\">";
  htmlPage += "<input type=\"text\" name=\"topic\" placeholder=\"Topic subscribe\" value=\"eMille/v1/Bet/IoTTemperatura\">";
  htmlPage += "<input type=\"text\" name=\"key\" placeholder=\"Key target\">";
  htmlPage += "</div>";
  htmlPage += "<button href=\"/info\" class=\"button\">Submit</button>";
  htmlPage += "</form>";
  htmlPage += "</div>";
  htmlPage += "</body>";
  htmlPage += "</html>";

  server.send(200, "text/html", htmlPage);
}

void handleInfo() {
  char ssid[20] = "";
  char pass[20] = "";
  char broker[15] = "";
  char port[4] = "";
  server.arg("wssid").toCharArray(ssid, 20);
  server.arg("wpass").toCharArray(pass, 20);
  server.arg("burl").toCharArray(broker, 15);
  server.arg("bport").toCharArray(port, 4);
  server.arg("usrid").toCharArray(USER_MQTT_ID, 50);
  server.arg("mpass").toCharArray(MQTT_PASSWORD, 20);
  server.arg("topic").toCharArray(TOPICO_SUBSCRIBE, 100);
  key = "\"" + server.arg("key") + "\"";

  Serial.println(ssid);
  Serial.println(pass);
  Serial.println(broker);
  Serial.println(port);
  //Serial.println(USER_MQTT_ID);
  //println(MQTT_PASSWORD);
  //Serial.println(TOPICO_SUBSCRIBE);
  //Serial.println(key);

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

  EEPROM.begin(512);
  EEPROM.put(0, ssid);
  EEPROM.put(20, pass);
  EEPROM.put(40, broker);
  EEPROM.put(55, port);
  EEPROM.commit();
  delay(1000);

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

