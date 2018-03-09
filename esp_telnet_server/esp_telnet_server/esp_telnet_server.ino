#include <ESP8266WiFi.h>

#define MAX_SRV_CLIENTS 3
const char* ssid = "local";
const char* password = "hujowapogoda";

WiFiServer server(21);
WiFiClient serverClients[MAX_SRV_CLIENTS];

void setup() {
  Serial.begin(115200);
  //Seria.setDebugOutput(true);
  WiFi.begin(ssid, password);

  
  
  Serial.println(ssid);
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 20) delay(500);
  if(i == 21){
    Serial.print("Could not connect to"); Serial.println(ssid);
    while(1) delay(500);
  }
  Serial.begin(115200);
  server.begin();
  server.setNoDelay(true);
  Serial.print("Ready! Use 'telnet ");
  Serial.print(WiFi.localIP());
  Serial.println(" 21' to connect");
}

void loop() {
  
  uint8_t i;
  if (server.hasClient()){
    for(i = 0; i < MAX_SRV_CLIENTS; i++){
      if (!serverClients[i] || !serverClients[i].connected()){
        if(serverClients[i]) serverClients[i].stop();
        serverClients[i] = server.available();
        continue;
      }
    }
    //no free spot
    WiFiClient serverClient = server.available();
    serverClient.stop();
  }
  for(i = 0; i < MAX_SRV_CLIENTS; i++){
    if (serverClients[i] && serverClients[i].connected()){
      if(serverClients[i].available()){
        while(serverClients[i].available()) Serial.write(serverClients[i].read());
        //you can reply to the client here
      }
    }
  }
  if(Serial.available()){
    size_t len = Serial.available();
    uint8_t sbuf[len];
    Serial.readBytes(sbuf, len);
    //bello is a broadcast to all clients
    for(i = 0; i < MAX_SRV_CLIENTS; i++){
      if (serverClients[i] && serverClients[i].connected()){
        serverClients[i].write(sbuf, len);
        delay(1);
      }
    }
  }
}
