#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The parameter -1 means the display doesn't have a shared reset pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

  // Initialize with the I2C address 0x3C (common for 0.96" OLEDs)
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  Serial.println("Display initialized");
  
  delay(2000);
  display.clearDisplay();

  // Set text size, color, and cursor position
  display.setTextSize(1);             
  display.setTextColor(SSD1306_WHITE);  
  display.setTextWrap(false);         
  display.setCursor(0,20);             
  display.println(F("Armani"));
  
  // Push the buffer to the actual hardware display
  display.display();
}

void loop() {
  // Scroll the text across the screen
  display.startscrollleft(0x00, 0x0F);
  
}