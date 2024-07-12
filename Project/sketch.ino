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
Servo servo;  // create servo object to control a servo

const unsigned long interval = 40;
unsigned long previousMillis;
const int rgbPins[] = { 27, 26, 22};

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  servo.attach(14);  // attaches the servo on pin 9 to the servo object

  for( int i=0; i<3; i++) {
    pinMode( rgbPins[i], OUTPUT);
  }

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
  }

  display.clearDisplay();
  display.setTextSize(1);             
  display.setTextColor(WHITE);        
  display.setCursor(0,10);             
  display.println("Hello, world!");
  display.display();
  delay(2000); 
}


void loop() {
    servo.write(0);
    tone(21, 250, 1000);
    analogWrite( rgbPins[0], 1);
    analogWrite( rgbPins[1], 1);
    analogWrite( rgbPins[2], 1);
}