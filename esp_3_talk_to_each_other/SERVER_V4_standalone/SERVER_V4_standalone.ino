#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

// Internet router credentials
const char* ssid = "ESP";
const char* password = "hujowapogoda";

void setup() {
 
    Serial.begin(115200);
    WiFi.mode(WIFI_AP_STA);
    setupAccessPoint();
    server.on("/body", handleBody); //Associate the handler function to the path
    server.begin(); //Start the server
    Serial.println("Server listening"); 
    }


void loop() {
 
    server.handleClient(); //Handling of incoming requests
 
}


void setupAccessPoint(){
  Serial.println("** SETUP ACCESS POINT **");
  Serial.println("- disconnect from any other modes");
  WiFi.disconnect();
  Serial.println("- start ap with SID: "+ String(ssid));
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("- AP IP address is :");
  Serial.print(myIP);
}

void handleBody() { //Handler for the body path
 
      if (server.hasArg("plain")== false){ //Check if body received
 
            server.send(200, "text/plain", "Body not received");
            return;
 
      }
 
      String message = "Body received:\n";
             message += server.arg("plain");
             message += "\n";
 
      server.send(200, "text/plain", message);
      Serial.println(message);
}
