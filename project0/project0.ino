#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
#define NUMFLAKES     10

#define XPOS   0
#define YPOS   1
#define DELTAY 2

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int Red = 9;
const int Green = 10;
const int Blue = 11;

static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };

void setup() {
  Serial.begin(9600);
  
  pinMode(Red, OUTPUT);
  pinMode(Green, OUTPUT);
  pinMode(Blue, OUTPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000); // Pause for 2 seconds

  visualEffect(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT);
}

void loop() {
  
}

void visualEffect(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  int8_t f, icons[NUMFLAKES][3];
  int randomX = 10;
  int randomY = 10;

  // Initialize snowflake positions
  for(f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
    icons[f][YPOS]   = -LOGO_HEIGHT;
    icons[f][DELTAY] = random(randomX, randomY);
  }

  for(;;) { // Loop forever...
    int sensorValue = analogRead(A0);
    Serial.println(sensorValue);
    
    if(sensorValue > 540){   //當音量超過一定數值
      analogWrite(Red,200);
      analogWrite(Green,0);
      analogWrite(Blue,50);
      randomX = 51;
      randomY = 56;
    }
    else if(sensorValue > 500 && sensorValue < 540){
      analogWrite(Red,100);
      analogWrite(Green,0);
      analogWrite(Blue,100);
      randomX = 21;
      randomY = 26;
    }
    else {
      analogWrite(Red,0);
      analogWrite(Green,0);
      analogWrite(Blue,0);
      randomX = 11;
      randomY = 16;
    }
    
    display.clearDisplay(); // Clear the display buffer

    // Draw each snowflake:
    for(f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SSD1306_WHITE);
    }

    display.display(); // Show the display buffer on the screen
    delay(200);        // Pause for 1/10 second

    // Then update coordinates of each flake...
    for(f=0; f< NUMFLAKES; f++) {
      icons[f][YPOS] += icons[f][DELTAY];
      // If snowflake is off the bottom of the screen...
      if (icons[f][YPOS] >= display.height()) {
        // Reinitialize to a random position, just off the top
        icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
        icons[f][YPOS]   = -LOGO_HEIGHT;
        icons[f][DELTAY] = random(randomX, randomY);
      }
    }
  }
}






















//void OLEDScrollingText() {
//    display.clearDisplay();
//    display.setTextSize(3);
//    display.setTextColor(WHITE);
//    display.setCursor(0, 0);
//    // Display static text
//    display.println("WSS"); //Write custom text here
//    display.display(); 
//    delay(100);
//    // Scroll in various directions, pausing in-between:
//    display.startscrollright(0x00, 0x0F);
//    delay(5000);
//    display.stopscroll();
//    delay(1000);
//    display.startscrollleft(0x00, 0x0F);
//    delay(5000);
//    display.stopscroll();
//    delay(1000);
//    display.startscrolldiagright(0x00, 0x07);
//    delay(2000);
//    display.startscrolldiagleft(0x00, 0x07);
//    delay(2000);
//    display.stopscroll();
//    delay(1000);
//}

void OLEDnoise() {
//  display.clearDisplay();
//  display.drawBitmap(0, 0, gImage0, 128, 48, 1);
//  display.display();
//  display.clearDisplay();
//  display.drawBitmap(0, 0, gImage1, 128, 48, 1);
//  display.display();
//  display.clearDisplay();
//  display.drawBitmap(0, 0, gImage2, 128, 48, 1);
//  display.display();
//  display.clearDisplay();
//  display.drawBitmap(0, 0, gImage3, 128, 48, 1);
//  display.display();
//  display.clearDisplay();
//  display.drawBitmap(0, 0, gImage4, 128, 48, 1);
//  display.display();
//  display.clearDisplay();
//  display.drawBitmap(0, 0, gImage5, 128, 48, 1);
//  display.display();
//  display.clearDisplay();
//  display.drawBitmap(0, 0, gImage6, 128, 48, 1);
//  display.display();
//  display.clearDisplay();
//  display.drawBitmap(0, 0, gImage7, 128, 48, 1);
//  display.display();
}
