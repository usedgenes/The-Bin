#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define SCREEN_WIDTH        128 // OLED display width, in pixels
#define SCREEN_HEIGHT        64 // OLED display height, in pixels

Adafruit_MPU6050 mpu;
sensors_event_t event;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Servo servo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
  }

  while (!mpu.begin()) {
    Serial.println("MPU6050 not connected!");
    delay(1000);
  }

  display.clearDisplay();
  display.setTextSize(1);             
  display.setTextColor(WHITE);        
  display.setCursor(0,10);             
  display.println("Starting");
  display.display();
  
  pinMode(7, INPUT);

  servo.attach(14);
}


void loop() {
  int pinValue = digitalRead(7);
  if(pinValue != LOW) {
    if(pinValue == HIGH) {
      mpu.getAccelerometerSensor()->getEvent(&event);
      display.clearDisplay();

      display.setCursor(0,0);
      display.print("X: ");
      display.print(event.acceleration.x);
      display.println(" m/s^2");
      display.print("Y: ");
      display.print(event.acceleration.y);
      display.println(" m/s^2");
      display.print("Z: ");
      display.print(event.acceleration.z);
      display.println(" m/s^2");
      display.display();
      
      if(event.acceleration.x == 0 && event.acceleration.y == 0 && event.acceleration.z == 0) {
        tone(21, 440, 1000);
      }
      else {
        if(event.acceleration.x > 0) {
          servo.write(0);
        }
        if(event.acceleration.x < 0) {
          servo.write(180);
        }
      }
    }
  }

  delay(100);
}