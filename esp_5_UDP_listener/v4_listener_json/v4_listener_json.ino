#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "mietek";
const char* password = "hujowapogoda";

bool directions[32];


WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
char  replyPacket[] = "Hi there! Got the message :-)";  // a reply string to send back


void setup()
{
  Serial.begin(115200);
  Serial.println();


  //JSON begin configure 
  StaticJsonBuffer<200> jsonBuffer; //setup JSON buffer size http://arduinojson.org/assistant
  JsonObject& root = jsonBuffer.createObject();
  root["m"] = "00000000000000000000000000000000"; //move command 16 bits for 16 buttons + 16 bits for 4x256 axis values, psx style gamepad, 32bits for whole communication
  root["t"] = "Lets begin"; //text command 
  root.printTo(Serial);
  Serial.println();
  root.prettyPrintTo(Serial);
  //JSON end

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
}


void loop()
{
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    Serial.printf("UDP packet contents: %s\n", incomingPacket);

    // send back a reply, to the IP address and port we got the packet from
    //Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    //Udp.write(replyPacket);
    //Udp.endPacket();

    //JSON begin
    DynamicJsonBuffer jsonBuffer(200);
    JsonObject& root = jsonBuffer.parseObject(incomingPacket); 
    root.prettyPrintTo(Serial);

    Serial.println();
    Serial.print("teraz wartosc: ");
    Serial.println(root["m"].as<char*>());
    Serial.println("pojedyncze pozycje z tablicy:");
    Serial.println(root["m"].as<char*>()[1]);
    Serial.println();
    
    //JSON enda=
  }

}

void moventCalc(String text){
  bool b_cross = text[0]
  bool b_triangle = text[1]
  bool b_circle = 
  bool b_square
  bool b_r1
  bool b_r2
  bool b_rThumb
  bool b_l1
  bool b_l2
  bool b_lThumb
  bool b_start
  bool b_select
  bool b_dPadUp
  bool b_dPadDown
  bool b_dPadLeft
  bool b_dPadRight
  
  
  }
