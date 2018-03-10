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

  pinMode(
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
    //Serial.println(root["m"].as<char*>()[1]);
    Serial.println();
    moventCalc(root["m"].as<char*>());
    //JSON enda=
  }

}

void moventCalc(String text){
  //bit positions number counted from [0] left=5, right=4, up=7, dPadDown=6, cross=3, square=2, circle=1, triangle=0
  //Serial.println(text);
  bool b_cross = charToBool(text[3]);
  //Serial.print("cross");
  //Serial.println(b_cross);
  bool b_triangle = charToBool(text[0]);
  //Serial.print("triangle");
  //Serial.println(b_triangle);
  bool b_circle = charToBool(text[1]);
  //Serial.print("circle");
  //Serial.println(b_circle);
  bool b_square = charToBool(text[2]);
  //Serial.print("square");
  //Serial.println(b_square);
  bool b_r1 = charToBool(text[8]);
  bool b_r2 = charToBool(text[9]);
  bool b_rThumb = charToBool(text[10]);
  bool b_l1 = charToBool(text[11]);
  bool b_l2 = charToBool(text[12]);
  bool b_lThumb = charToBool(text[13]);
  bool b_start = charToBool(text[14]);
  bool b_select = charToBool(text[15]);
  bool b_dPadUp = charToBool(text[7]);
  bool b_dPadDown = charToBool(text[6]);
  bool b_dPadLeft = charToBool(text[5]);
  bool b_dPadRight = charToBool(text[4]);

  
  }

bool charToBool(char text){
  if(text=='0')
    {
      return 0;
    }
  else
    {
      return 1;  
    }
}


