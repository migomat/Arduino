#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET LED_BUILTIN  //4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("0.4bar");
  //display.println("http://arduino-er.blogspot.com/");
  display.display();

 delay(2000);
 display.clearDisplay();
 display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("0.4bar");
  //display.println("http://arduino-er.blogspot.com/");
  display.display();

  delay(2000);
  display.clearDisplay();
 display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("0.4bar");
  //display.println("http://arduino-er.blogspot.com/");
  display.display();
    delay(2000);
    display.clearDisplay();
 display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("0.4");
display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(75,10);
  display.println("bar");
  
  //display.println("http://arduino-er.blogspot.com/");
  display.display();

}

void loop() {
  // put your main code here, to run repeatedly:

}
