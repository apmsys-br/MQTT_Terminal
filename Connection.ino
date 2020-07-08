/*
Function: Checks the state of WiFI and MQTT broker connections.
In case of disconnection (either), the connection is redone.
Parameters: None
Return: none

Função: verifica o estado das conexões WiFI e ao broker MQTT. 
Em caso de desconexão (qualquer uma das duas), a conexão é refeita.
Parâmetros: nenhum
Retorno: nenhum
*/

void VerificaConexoesWiFIEMQTT(void)
{

    if (!MQTT.connected()) 
        reconnectMQTT(); //se não há conexão com o Broker, a conexão é refeita     
        reconectWiFi(); //se não há conexão com o WiFI, a conexão é refeita
        //Timer_milles();
}
