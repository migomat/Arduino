#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/TomThumb.h>


#include <ESP8266WiFi.h>

#define MAX_SRV_CLIENTS 1
const char* ssid = "local";
const char* password = "hujowapogoda";

WiFiServer server(21);
WiFiClient serverClients[MAX_SRV_CLIENTS];

#define OLED_RESET LED_BUILTIN  //4
Adafruit_SSD1306 display(OLED_RESET);
#define NUMFLAKES 1
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 32
#define LOGO16_GLCD_WIDTH  128
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ // 'adamski_logo4', 128x32px
  // 'adamski_logo4', 128x32px
  0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xfe, 0x03, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xfc, 0x03, 0xff, 0xff, 0xe0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xf0, 0x21, 0xff, 0xff, 0xc1, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xe0, 0xf1, 0xc1, 0xff, 0x87, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xc1, 0xf0, 0x00, 0x3f, 0x0f, 0xe0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0x83, 0xf0, 0x00, 0x0f, 0x19, 0xe0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0x87, 0xf8, 0x00, 0x06, 0x11, 0xf0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0x0c, 0xf8, 0xff, 0x80, 0x30, 0xf1, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xfe, 0x18, 0x78, 0xff, 0xe0, 0x70, 0xf0, 0x0f, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xfe, 0x18, 0xf8, 0xff, 0xf0, 0x70, 0xf0, 0x8f, 0xf0, 0xff, 0xfe, 0x0f, 0xff, 0xff, 0xff,
  0xff, 0xfe, 0x38, 0xf8, 0xff, 0xf8, 0xf0, 0xf8, 0x87, 0xe0, 0x7f, 0xf8, 0x00, 0xff, 0xe7, 0xff,
  0xff, 0xfc, 0x38, 0xf8, 0xf1, 0xf8, 0x70, 0xf8, 0xc7, 0xe0, 0x7f, 0xf0, 0x00, 0xff, 0xc7, 0xff,
  0xff, 0xfc, 0x78, 0xf8, 0xf1, 0xfc, 0x79, 0xf8, 0xc3, 0xc0, 0x7f, 0xe0, 0x60, 0xff, 0xc7, 0xff,
  0xff, 0xfc, 0x78, 0xf8, 0xf1, 0xfc, 0x7f, 0xf8, 0xe0, 0x04, 0x7f, 0xe3, 0xf8, 0xe7, 0xff, 0xff,
  0xff, 0xf8, 0x79, 0xf8, 0xf1, 0xfc, 0x3f, 0xf8, 0xe0, 0x0c, 0x3f, 0xe3, 0xf8, 0x83, 0xff, 0xff,
  0xff, 0xf8, 0xff, 0xf8, 0xf1, 0xfc, 0x3f, 0xf8, 0xf8, 0x1c, 0x20, 0x23, 0xf8, 0x07, 0xbf, 0xff,
  0xff, 0xf8, 0xff, 0xf8, 0xf1, 0xfc, 0x3f, 0xf8, 0xfc, 0x7e, 0x20, 0x01, 0xf8, 0x0f, 0x1f, 0xff,
  0xff, 0xf0, 0xfb, 0xf8, 0xf1, 0xfc, 0x7f, 0xf8, 0x7f, 0xfe, 0x20, 0x30, 0xf8, 0x3e, 0x1f, 0xff,
  0xff, 0xf1, 0xf1, 0xf8, 0xe1, 0xfc, 0x7d, 0xf8, 0x7f, 0xfe, 0x1f, 0xf8, 0x70, 0x7e, 0x3f, 0xff,
  0xff, 0xf1, 0xf1, 0xf8, 0xe3, 0xf8, 0x78, 0xf8, 0x7f, 0xfe, 0x1f, 0xfc, 0x30, 0x7e, 0x3f, 0xff,
  0xff, 0xf1, 0xf1, 0xf8, 0xf3, 0xf0, 0xf8, 0xf8, 0x7f, 0xff, 0x1f, 0xfc, 0x30, 0x0e, 0x3f, 0xff,
  0xff, 0xf1, 0xf1, 0xf8, 0xff, 0xe1, 0xf8, 0xf8, 0x7f, 0xff, 0x1f, 0xfe, 0x00, 0x02, 0x1f, 0xff,
  0xff, 0xe1, 0xf1, 0xf0, 0xff, 0xc1, 0xf8, 0xf8, 0xf1, 0xff, 0x1f, 0xff, 0x00, 0x02, 0x1f, 0xff,
  0xff, 0xe3, 0xf1, 0xf0, 0xff, 0x03, 0xf0, 0xf8, 0xf1, 0xff, 0x0f, 0xff, 0x03, 0x87, 0xff, 0xff,
  0xff, 0xe3, 0xf1, 0xf1, 0xf8, 0x00, 0x00, 0xf0, 0xf0, 0xff, 0x0f, 0x00, 0x03, 0xff, 0xff, 0xff,
  0xff, 0xe3, 0xf1, 0xf1, 0x80, 0x00, 0x00, 0x01, 0xf0, 0xff, 0x0f, 0x00, 0x17, 0xff, 0xff, 0xff,
  0xff, 0xe3, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0xfe, 0x1f, 0x80, 0x7f, 0xff, 0xff, 0xff,
  0xff, 0xe0, 0x00, 0x00, 0x01, 0xff, 0xc0, 0x03, 0xf0, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xe0, 0x00, 0x00, 0x1f, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xe0, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif







void setup() {
  Serial.begin(115200);
  //Seria.setDebugOutput(true);
  WiFi.begin(ssid, password);



  Serial.println(ssid);
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 20) delay(500);
  if (i == 21) {
    Serial.print("Could not connect to"); Serial.println(ssid);
    while (1) delay(500);
  }
  Serial.begin(115200);
  server.begin();
  server.setNoDelay(true);
  Serial.print("Ready! Use 'telnet ");
  Serial.print(WiFi.localIP());
  Serial.println(" 21' to connect");

  //----------LCD section
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  display.clearDisplay();
  display.drawBitmap(0, 0,  logo16_glcd_bmp, 128, 32, 1);
  display.display();
  delay(2000);
  display.clearDisplay();
  //display.setFont(&TomThumb);
  display.setTextColor(WHITE);
  display.setCursor(0, 5);
  display.println("Mietek");
  display.display();
  delay(1000);
  display.clearDisplay();

}

void loop() {

  uint8_t i;
  if (server.hasClient()) {
    for (i = 0; i < MAX_SRV_CLIENTS; i++) {
      if (!serverClients[i] || !serverClients[i].connected()) {
        if (serverClients[i]) serverClients[i].stop();
        serverClients[i] = server.available();
        continue;
      }
    }
    //no free spot
    WiFiClient serverClient = server.available();
    serverClient.stop();
  }
  for (i = 0; i < MAX_SRV_CLIENTS; i++) {
    if (serverClients[i] && serverClients[i].connected()) {
      if (serverClients[i].available()) {
        while (serverClients[i].available()) displayPrint(char(serverClients[i].read()));
        //while (serverClients[i].available()) Serial.write(serverClients[i].read());
        //displayPrint(serverClients[i].read());
      }
    }
  }
  if (Serial.available()) {
    size_t len = Serial.available();
    uint8_t sbuf[len];
    Serial.readBytes(sbuf, len);
    //bello is a broadcast to all clients
    for (i = 0; i < MAX_SRV_CLIENTS; i++) {
      if (serverClients[i] && serverClients[i].connected()) {
        serverClients[i].write(sbuf, len);
        delay(1);
      }
    }
  }


}
void displayPrint(String text) {
  display.clearDisplay();
  //ckdisplay.setFont(&TomThumb);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(text);
  display.display();
  delay(1000);
}

void displayPrint(int text) {
  display.clearDisplay();
  //ckdisplay.setFont(&TomThumb);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(text);
  display.display();
  delay(1000);
}