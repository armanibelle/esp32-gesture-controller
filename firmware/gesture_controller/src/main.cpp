#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_MPU6050 mpu;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200); // Start communication highway to PC
  Serial.begin(115200);

  // Initialize with the I2C address 0x3C (common for 0.96" OLEDs)
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  Serial.println("Display initialized");
  
  delay(2000);            
  
  
  // Initialize the MPU6050 Sensor on default I2C pins (21 and 22)
  if (!mpu.begin()) {
    Serial.println("Failed to find GY-521/MPU6050 chip! Check wiring.");
    while (1) { delay(10); } // Stop program if sensor isn't found
  }
  Serial.println("GY-521 Sensor Ready!");

  // Set sensor settings for standard hand movements
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  delay(100);
}

void loop() {
  // Read raw tracking data from the sensor
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Print Acceleration data (Detects Hand Tilt & Jerks)
  Serial.print("Accel X: "); Serial.print(a.acceleration.x);
  Serial.print(" | Y: "); Serial.print(a.acceleration.y);
  Serial.print(" | Z: "); Serial.println(a.acceleration.z);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  display.setCursor(0,0);
  display.print("AX: ");
  display.println(a.acceleration.x);
  
  display.setCursor(0,15);
  display.print("AY: ");
  display.println(a.acceleration.y);

  display.setCursor(0,30);
  display.print("AZ: ");
  display.println(a.acceleration.z);
  
  display.display();

  // Print Gyroscope data (Detects Speed of Rotation/Twisting)
  // Serial.print("Gyro X: "); Serial.print(g.gyro.x);

  delay(200); // Pause briefly so the monitor screen doesn't flood
  
}