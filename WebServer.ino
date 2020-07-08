
void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1><input></input>");
}

void initWebServer() {
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void webServerLoop() {
  server.handleClient();
}

