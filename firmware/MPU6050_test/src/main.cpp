#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200); // Start communication highway to PC
  
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

  // Print Gyroscope data (Detects Speed of Rotation/Twisting)
  // Serial.print("Gyro X: "); Serial.print(g.gyro.x);

  delay(200); // Pause briefly so the monitor screen doesn't flood
}