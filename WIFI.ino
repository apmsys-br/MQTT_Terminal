//Função: inicializa e conecta-se na rede WI-FI desejada
//Parâmetros: nenhum
//Retorno: nenhum

void initWiFi()
{
  if (SSID != "" && PASSWORD != "") {
    delay(10);
    Serial.println("------Conexao WI-FI------");
    Serial.print("Conectando-se na rede: ");
    Serial.println(SSID);
    Serial.println("Aguarde");


    if (WiFi.status() == WL_CONNECTED)
      return;
    WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI

    while (WiFi.status() != WL_CONNECTED)
    {
      delay(100);
      Serial.print(".");
    }

    reconectWiFi();
  }
  else {
    String temp = "Wifi not configured...";
    temp.toCharArray(message, 100);
  }
}

/*
  Function: reconnects to WiFi
  Parameters: None
  Return: none

  Função: reconecta-se ao WiFi
  Parâmetros: nenhum
  Retorno: nenhum
*/

void reconectWiFi()
{
  /*
    if you are already connected to WIFI, nothing is done.
        Otherwise, connection attempts are made
    se já está conectado a rede WI-FI, nada é feito.
    Caso contrário, são efetuadas tentativas de conexão
  */
  if (WiFi.status() == WL_CONNECTED)
    return;
  WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    //Serial.print(".");
  }

  Serial.println();
  Serial.print("Conectado com sucesso na rede ");
  Serial.print(SSID);
  Serial.println("IP obtido: ");
  Serial.println(WiFi.localIP());
}
