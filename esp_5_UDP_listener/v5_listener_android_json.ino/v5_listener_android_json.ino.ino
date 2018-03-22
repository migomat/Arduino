#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

//static const uint8_t D0   = 16;
//static const uint8_t D1   = 5;
//static const uint8_t D3   = 0;
//static const uint8_t D4   = 2;
//static const uint8_t D5   = 14;
//static const uint8_t D6   = 12;
//static const uint8_t D7   = 13;
//static const uint8_t D8   = 15;
//static const uint8_t D9   = 3;
//static const uint8_t D10  = 1;

static const uint8_t pFwd = D6;
static const uint8_t pRwd = D5;
static const uint8_t pRh  = D7;
static const uint8_t pLh  = D8;
#define b_crossByteNr 3
#define b_squareByteNr 2
//#define b_triangleByteNr 
//#define b_circleByteNr 
#define b_dpadLeftByteNr 5
#define b_dpadRightByteNr 4
#define b_dpadUpByteNr 7
#define b_dpadDownByteNr 6

const char* ssid = "local";
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

  pinMode(pFwd, OUTPUT);//fwd
  pinMode(pRwd, OUTPUT);//rwd
  pinMode(pRh, OUTPUT);//rh
  pinMode(pLh, OUTPUT);//lh

  
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
    //moventCalc(root["m"].as<char*>());
    moventCalcAndr(root["ac"].as<char*>());
    
    //JSON enda=
  }

}


void moventCalcAndr(String text){
  //bit positions number counted from [0] left=5, right=4, up=7, dPadDown=6, cross=3, square=2, circle=1, triangle=0

  if (text=="l1")
    {
      directions[0]=1;
      }
  if (text=="l0")
    {
      directions[0]=0;
      }
  if (text=="r1")
    {
      directions[1]=1;
      }
  if (text=="r0")
    {
      directions[1]=0;
      }
  if (text=="f1")
    {
      directions[2]=1;
      }
  if (text=="f0")
    {
      directions[2]=0;
      }

     if (text=="b1")
    {
      directions[3]=1;
      }
  if (text=="b0")
    {
      directions[3]=0;
      }     
  bool b_cross = directions[2];
  Serial.print("cross");
  Serial.println(directions[2]);
 // bool b_triangle = charToBool(text[0]);
  //Serial.print("triangle");
  //Serial.println(b_triangle);
 // bool b_circle = charToBool(text[b_circleByteNr]);
  //Serial.print("circle");
  //Serial.println(b_circle);
  bool b_square = directions[3];
  Serial.print("square");
  Serial.println(directions[3]);
  //bool b_r1 = charToBool(text[8]);
  //bool b_r2 = charToBool(text[9]);
  //bool b_rThumb = charToBool(text[10]);
 // bool b_l1 = charToBool(text[11]);
  //bool b_l2 = charToBool(text[12]);
 // bool b_lThumb = charToBool(text[13]);
  //bool b_start = charToBool(text[14]);
  //bool b_select = charToBool(text[15]);
  //bool b_dPadUp = charToBool(text[7]);
  //bool b_dPadDown = charToBool(text[6]);
  bool b_dPadLeft = directions[0];
  Serial.print("left ");
  Serial.println(b_dPadLeft);
  bool b_dPadRight = directions[1];
    Serial.print("right ");
  Serial.println(b_dPadRight);
  //car motors protection 
  if(b_dPadLeft == 1)
  {
    b_dPadRight=0;
    }
    if(b_dPadRight == 1)
  {
    b_dPadLeft=0;
    }

   if(b_cross == 1)
  {
    b_square=0;
    }
   if(b_square == 1)
  {
    b_cross=0;
    } 

  //end car motors protection
  
  digitalWrite(pLh, b_dPadLeft);
  digitalWrite(pRh, b_dPadRight);
  digitalWrite(pFwd, b_cross);
  digitalWrite(pRwd, b_square);

 // analogWrite(pin,0);
  }


void moventCalc(String text){
  //bit positions number counted from [0] left=5, right=4, up=7, dPadDown=6, cross=3, square=2, circle=1, triangle=0
  Serial.print("move: ");
  Serial.println(text);
  bool b_cross = charToBool(text[b_crossByteNr]);
  Serial.print("cross");
  Serial.println(b_cross);
 // bool b_triangle = charToBool(text[0]);
  //Serial.print("triangle");
  //Serial.println(b_triangle);
 // bool b_circle = charToBool(text[b_circleByteNr]);
  //Serial.print("circle");
  //Serial.println(b_circle);
  bool b_square = charToBool(text[b_squareByteNr]);
  Serial.print("square");
  Serial.println(b_square);
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
  bool b_dPadLeft = charToBool(text[b_dpadLeftByteNr]);
  Serial.print("left ");
  Serial.println(b_dPadLeft);
  bool b_dPadRight = charToBool(text[b_dpadRightByteNr]);
    Serial.print("right ");
  Serial.println(b_dPadRight);
  //car motors protection 
  if(b_dPadLeft == 1)
  {
    b_dPadRight=0;
    }
    if(b_dPadRight == 1)
  {
    b_dPadLeft=0;
    }

   if(b_cross == 1)
  {
    b_square=0;
    }
   if(b_square == 1)
  {
    b_cross=0;
    } 

  //end car motors protection
  
  digitalWrite(pLh, b_dPadLeft);
  digitalWrite(pRh, b_dPadRight);
  digitalWrite(pFwd, b_cross);
  digitalWrite(pRwd, b_square);

 // analogWrite(pin,0);
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



