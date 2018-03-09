#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "local";
const char* password = "hujowapogoda";

WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
char  replyPacket[] = "Hi there! Got the message :-)";  // a reply string to send back

IPAddress ip(192, 168, 1, 8);
unsigned int serverPort = 4210;


void setup()
{
  Serial.begin(115200);
  Serial.println();

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
  pinMode(14, INPUT_PULLUP);
  
}


void loop()
{
  
    // receive incoming UDP packets
    //Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    //int len = Udp.read(incomingPacket, 255);
    //if (len > 0)
    //{
    //  incomingPacket[len] = 0;
    //}
    //Serial.printf("UDP packet contents: %s\n", incomingPacket);

    // send back a reply, to the IP address and port we got the packet from
    if(digitalRead(14)==0)
    {
    Udp.beginPacket(ip, serverPort);
    Udp.write("Lubie Placki");
    Udp.endPacket();
    delay(500);
    }

}