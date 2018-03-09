/*CLIENT
Geekstips.com
IoT project - Communication between two ESP8266 - Talk with Each Other
ESP8266 Arduino code example
*/
//#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
//#define DHTPIN 2

// AP Wi-Fi credentials
const char* ssid = "ESP";
const char* password = "hujowapogoda";

// Local ESP web-server address
String serverHost = "http://192.168.4.1/feed";
String data;
// DEEP_SLEEP Timeout interval
//int sleepInterval = 5;
// DEEP_SLEEP Timeout interval when connecting to AP fails
//int failConnectRetryInterval = 2;
int counter = 0;

float h;
float t;
// Static network configuration
IPAddress ip(192, 168, 4, 4);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

//DHT dht(DHTPIN, DHT22);
WiFiClient client;

void setup() {
  ESP.eraseConfig();
  WiFi.persistent(false);
  Serial.begin(115200);
  Serial.println();
 // Serial.println("**************************");
 // Serial.println("**************************");
  Serial.println("******** BEGIN ***********");
  //Serial.println("- start DHT sensor");
//  dht.begin();
  delay(500);
  Serial.println("- set ESP STA mode");
  WiFi.mode(WIFI_STA);
  Serial.println("- connecting to wifi");
  WiFi.config(ip, gateway, subnet); 
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    if(counter > 20){
       Serial.println("- can't connect, going to sleep");    
      // hibernate(failConnectRetryInterval);
    }
    delay(500);
    Serial.print(".");
    counter++;
  }
  
  Serial.println("- wifi connected");
  Serial.println("- read DHT sensor");
  readDHTSensor();
  Serial.println("- build DATA stream string");
  buildDataStream();
  Serial.println("- send GET request");
  sendHttpRequest();
 // Serial.println();
 // Serial.println("- got back to sleep");
//  Serial.println("**************************");
 // Serial.println("**************************");
  //hibernate(sleepInterval);
   Serial.println("setup done");
}

void sendHttpRequest() {
Serial.println("weszlo do funckji"); 
  HTTPClient http;
  Serial.println("nadano klienta"); 
  http.begin(serverHost);
  Serial.println("weszlo na strone"); 
  //http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  http.addHeader("Content-Type", "text/plain");
  Serial.println("dodano naglowek"); 
  http.POST("1");
  //http.POST("data");
  Serial.print("wyslano: ");
  Serial.println(data);
  http.writeToStream(&Serial);
  http.end();
}

void readDHTSensor() {
  delay(200);
  h = 9;
  t = 21;
  if (isnan(h) || isnan(t)) {
    t = 1.00;
    h = 1.00;
  }
  Serial.println("- temperature read : "+String(t));
  Serial.println("- humidity read : "+String(h));
}

void buildDataStream() {
  data = "temp=";
  data += String(t);
  data += "&hum=";
  data += String(h);
  Serial.println("- data stream: "+data);
}


void hibernate(int pInterval) {
  WiFi.disconnect();
  ESP.deepSleep(1000 * pInterval, WAKE_RFCAL);
  delay(100);
}

void loop() {}
