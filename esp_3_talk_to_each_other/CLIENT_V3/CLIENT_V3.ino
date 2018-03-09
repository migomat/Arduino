#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
 
void setup() {
 
  Serial.begin(115200);//Serial connection
  WiFi.mode(WIFI_STA); //very important without it it's not working
  WiFi.begin("ESP", "hujowapogoda");   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
    delay(500);
    Serial.println("Waiting for connection");
 
  }
 
}
 
void loop() {
 
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
 Serial.println("connected...");
   HTTPClient http;    //Declare object of class HTTPClient
 
   http.begin("http://192.168.4.1/body");      //Specify request destination
    Serial.println("bd dodawal naglowek");
   http.addHeader("Content-Type", "text/plain");  //Specify content-type header
 
   int httpCode = http.POST("Message from ESP8266");   //Send the request
   String payload = http.getString();                  //Get the response payload
   Serial.print("Code: ");
   Serial.println(httpCode);   //Print HTTP return code
   Serial.print("payload: ");
   Serial.println(payload);    //Print request response payload
 
   http.end();  //Close connection
 
 }else{
 
    Serial.println("Error in WiFi connection");   
 
 }
 
  delay(5000);  //Send a request every 30 seconds
 
}
