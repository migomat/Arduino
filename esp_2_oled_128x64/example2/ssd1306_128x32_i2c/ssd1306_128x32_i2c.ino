#include <Adafruit_SSD1306.h>

/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x32 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/TomThumb.h>

#define OLED_RESET LED_BUILTIN  //4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 1
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 32 
#define LOGO16_GLCD_WIDTH  128 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{   // 'adamski_logo4', 128x32px
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
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,};

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {                
  Serial.begin(9600);
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);;  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
 // delay(2000);

  // Clear the buffer.
  display.clearDisplay();

 /*// draw a single pixel
  display.drawPixel(10, 10, WHITE);
  // Show the display buffer on the hardware.
  // NOTE: You _must_ call display after making any drawing commands
  // to make them visible on the display hardware!
  display.display();
  delay(2000);
  display.clearDisplay();

  // draw many lines
  testdrawline();
  display.display();
  delay(2000);
  display.clearDisplay();

  // draw rectangles
  testdrawrect();
  display.display();
  delay(2000);
  display.clearDisplay();

  // draw multiple rectangles
  testfillrect();
  display.display();
  delay(2000);
  display.clearDisplay();

  // draw mulitple circles
  testdrawcircle();
  display.display();
  delay(2000);
  display.clearDisplay();

  // draw a white circle, 10 pixel radius
  display.fillCircle(display.width()/2, display.height()/2, 10, WHITE);
  display.display();
  delay(2000);
  display.clearDisplay();

  testdrawroundrect();
  delay(2000);
  display.clearDisplay();

  testfillroundrect();
  delay(2000);
  display.clearDisplay();

  testdrawtriangle();
  delay(2000);
  display.clearDisplay();
   
  testfilltriangle();
  delay(2000);
  display.clearDisplay();

  // draw the first ~12 characters in the font
  testdrawchar();
  display.display();
  delay(2000);
  display.clearDisplay();
*/
 /* // draw scrolling text
  testscrolltext();
  delay(2000);
  display.clearDisplay();
*/

  // text display tests
  display.setFont(&TomThumb);
  //display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,5);
  display.println("Hello, world! sdasd asdasdasdasdsadasda d asd asd as a a a da a da da da");
  //display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.println(3.141592);
  //display.setTextSize(2);
 // display.setTextColor(WHITE);
  //display.print("0x"); display.println(0xDEADBEEF, HEX);
  display.display();
  delay(2000);
  display.clearDisplay();

  // miniature bitmap display
  display.drawBitmap(0, 0,  logo16_glcd_bmp, 128, 32, 1);
  display.display();
  delay(5000);

  // invert the display
  display.invertDisplay(true);
  delay(2000); 
  display.invertDisplay(false);
  delay(2000); 
 display.invertDisplay(true);
 // display.clearDisplay();

  // draw a bitmap icon and 'animate' movement
  //testdrawbitmap(logo16_glcd_bmp, LOGO16_GLCD_HEIGHT, LOGO16_GLCD_WIDTH);
}


void loop() {
 // testscrolltext();
 // delay(2000);
 // display.clearDisplay();

 display.invertDisplay(true);
  delay(2000); 
  display.invertDisplay(false);
  delay(2000); 
}


void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icons[NUMFLAKES][1];
 
  // initialize
  for (uint8_t f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS] = random(display.width());
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random(5) + 1;
    
    Serial.print("x: ");
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(" y: ");
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(" dy: ");
    Serial.println(icons[f][DELTAY], DEC);
  }

  while (1) {
    // draw each icon
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, WHITE);
    }
    display.display();
    delay(200);
    
    // then erase it + move it
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, BLACK);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > display.height()) {
        icons[f][XPOS] = random(display.width());
        icons[f][YPOS] = 0;
        icons[f][DELTAY] = random(5) + 1;
      }
    }
   }
}


void testdrawchar(void) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  for (uint8_t i=0; i < 168; i++) {
    if (i == '\n') continue;
    display.write(i);
    if ((i > 0) && (i % 21 == 0))
      display.println();
  }    
  display.display();
  delay(1);
}

void testdrawcircle(void) {
  for (int16_t i=0; i<display.height(); i+=2) {
    display.drawCircle(display.width()/2, display.height()/2, i, WHITE);
    display.display();
    delay(1);
  }
}

void testfillrect(void) {
  uint8_t color = 1;
  for (int16_t i=0; i<display.height()/2; i+=3) {
    // alternate colors
    display.fillRect(i, i, display.width()-i*2, display.height()-i*2, color%2);
    display.display();
    delay(1);
    color++;
  }
}

void testdrawtriangle(void) {
  for (int16_t i=0; i<min(display.width(),display.height())/2; i+=5) {
    display.drawTriangle(display.width()/2, display.height()/2-i,
                     display.width()/2-i, display.height()/2+i,
                     display.width()/2+i, display.height()/2+i, WHITE);
    display.display();
    delay(1);
  }
}

void testfilltriangle(void) {
  uint8_t color = WHITE;
  for (int16_t i=min(display.width(),display.height())/2; i>0; i-=5) {
    display.fillTriangle(display.width()/2, display.height()/2-i,
                     display.width()/2-i, display.height()/2+i,
                     display.width()/2+i, display.height()/2+i, WHITE);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    display.display();
    delay(1);
  }
}

void testdrawroundrect(void) {
  for (int16_t i=0; i<display.height()/2-2; i+=2) {
    display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i, display.height()/4, WHITE);
    display.display();
    delay(1);
  }
}

void testfillroundrect(void) {
  uint8_t color = WHITE;
  for (int16_t i=0; i<display.height()/2-2; i+=2) {
    display.fillRoundRect(i, i, display.width()-2*i, display.height()-2*i, display.height()/4, color);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    display.display();
    delay(1);
  }
}
   
void testdrawrect(void) {
  for (int16_t i=0; i<display.height()/2; i+=2) {
    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, WHITE);
    display.display();
    delay(1);
  }
}

void testdrawline() {  
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, 0, i, display.height()-1, WHITE);
    display.display();
    delay(1);
  }
  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(0, 0, display.width()-1, i, WHITE);
    display.display();
    delay(1);
  }
  delay(250);
  
  display.clearDisplay();
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, display.height()-1, i, 0, WHITE);
    display.display();
    delay(1);
  }
  for (int16_t i=display.height()-1; i>=0; i-=4) {
    display.drawLine(0, display.height()-1, display.width()-1, i, WHITE);
    display.display();
    delay(1);
  }
  delay(250);
  
  display.clearDisplay();
  for (int16_t i=display.width()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, i, 0, WHITE);
    display.display();
    delay(1);
  }
  for (int16_t i=display.height()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, 0, i, WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();
  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(display.width()-1, 0, 0, i, WHITE);
    display.display();
    delay(1);
  }
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(display.width()-1, 0, i, display.height()-1, WHITE); 
    display.display();
    delay(1);
  }
  delay(250);
}

void testscrolltext(void) {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.clearDisplay();
  display.println("Passat");
  display.setTextColor(BLACK,WHITE);
  display.println("turbo");
  display.display();
  delay(1);
 
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);    
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
}
