#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

bool automatic=0;

void setup() {
 
  Serial.begin(115200);//Serial connection
  WiFi.mode(WIFI_STA); //very important without it it's not working
  WiFi.begin("ESP", "hujowapogoda");   //WiFi connection
  Serial.setTimeout(100); // how long it need to wait for complete sentence
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
    delay(500);
    Serial.println("Waiting for connection");
    if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
       Serial.println("connected...");
    }
    else{
      Serial.println("Error in WiFi connection"); 
    }
 
  }


  
  
}
void loop() {
 
   if (automatic==0)
   {
   if (Serial.available()>0)
   {
   String readDATA=Serial.readString();
   sendMSG(readDATA);
    }
   }
   else
   {
    signalSTRprint();
    delay(2000);
    }
 
 }
 


void sendMSG(String text){
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
    Serial.println("connected...");
    HTTPClient http;    //Declare object of class HTTPClient
    http.begin("http://192.168.4.1/body");      //Specify request destination
    Serial.println("bd dodawal naglowek");
    http.addHeader("Content-Type", "text/plain");  //Specify content-type header
    int httpCode = http.POST(text);   //Send the request
    String payload = http.getString();                  //Get the response payload
    Serial.print("Code: ");
    Serial.println(httpCode);   //Print HTTP return code
    Serial.print("payload: ");
    Serial.println(payload);    //Print request response payload
    http.end();  //Close connection
  }
  else{
    Serial.println("Error in WiFi connection");   
  }
}

void signalSTRprint(){
  int32_t i_signalSTR = WiFi.RSSI();
String signalSTR = String(i_signalSTR);
signalSTR += " dbi"; 
sendMSG(signalSTR);
}

void jsoninit()// functions necessary to start work with json
{
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

}



