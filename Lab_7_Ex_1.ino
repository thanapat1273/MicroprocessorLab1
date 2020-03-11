#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire,OLED_RESET);
int button_1 = 9;
int button_2 = 10;
int but1 = 0;
int but2 = 0;
void setup() {
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
 display.begin(SSD1306_SWITCHCAPVCC, 0x3c); //initialize I2C addr 0x3c
 display.clearDisplay(); // clears the screen and buffer
 //display.drawPixel(127, 63, WHITE);
 //display.drawLine(0, 63, 127, 21, WHITE);
 //display.fillCircle(90, 30, 20, WHITE);
 //display.fillCircle(30, 30, 20, WHITE);
 //display.drawTriangle(70, 60, 90, 60, 80, 46, WHITE);
 //display.setTextSize(1);
 //display.setTextColor(WHITE);
 display.setCursor(0,0);
 //display.println("RIP");
 //display.setTextSize(2);
 //display.println("PRAYUT");
 //display.setTextColor(BLACK, WHITE);
 //display.setTextSize(1);
 //display.println("RAI FOR PM");
 //display.setTextColor(WHITE, BLACK);
 display.display();
}
void loop() {
  but1 = digitalRead(9);
  but2 = digitalRead(10);
  display.clearDisplay();
  
  if ((but1 == LOW) && (but2 == LOW))  {
    display.clearDisplay();
    display.drawCircle(30, 30, 20, WHITE);
    display.drawCircle(90, 30, 20, WHITE);
  }
  else if (but1 == LOW){
    display.drawCircle(90, 30, 20, WHITE);
    display.drawCircle(30, 30, 20, WHITE);
    display.fillCircle(30, 30, 20, WHITE);
    
  }
  else if (but2 == LOW) {
    display.drawCircle(30, 30, 20, WHITE);
    display.drawCircle(90, 30, 20, WHITE);
    display.fillCircle(90, 30, 20, WHITE);
  }
  
  else{
    display.fillCircle(30, 30, 20, WHITE);
    display.fillCircle(90, 30, 20, WHITE);
  }
  display.display();
  delay(100);
}
