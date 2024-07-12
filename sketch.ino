#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <dht.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH        128 // OLED display width, in pixels
#define SCREEN_HEIGHT        64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

dht DHT;

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  while (!mpu.begin()) {
    Serial.println("MPU6050 not connected!");
    delay(1000);
  }

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  oled.begin(128, 64, sizeof(tiny4koled_init_128x64br), tiny4koled_init_128x64br);
  oled.setFont(FONT6X8);
  oled.clear();
  oled.on();
}
void loop() {
    mpu.getAccelerometerSensor()->getEvent(&event);

    // Update temperature
    float temperature = getTemperature();

    // Set cursor
    oled.setCursor(57, 4);

    // Print to display
    oled.print(DHT.temperature, 1);
    oled.print("C  ");

    // Update humidity

    // Set cursor
    oled.setCursor(57, 5);

    // Print to display
    oled.print(DHT.humidity, 1);
    oled.print("%  ");
}