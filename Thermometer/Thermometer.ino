#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <SPI.h>
#include <Wire.h>


#define OLED_RESET 4 // not used 
Adafruit_SSD1306 display(OLED_RESET);

void setup()   {                

	// initialize with the I2C addr 0x3C 
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  pinMode(13, OUTPUT);

  Serial.begin(9600);
}

#define DRAW_DELAY 118
#define D_NUM 47

float voltageSum = 0.0;
int voltageCount = 0;
int currentTemp = 33;
const int temperaturePin = 0;

void loop() {
  
	setText((int)getTemp());
	delay(1000);
}

float getTemp() {
  float degreesC, degreesF;
  voltageSum = 0.0;
  voltageCount = 0;
  
  for (int i=0; i<100; i++) {
    voltageSum += getVoltage(temperaturePin);
    voltageCount++;
    delay(10);
  }
  
  degreesC = (voltageSum/voltageCount - 0.5) * 100.0;
  degreesF = degreesC * (9.0/5.0) + 32.0;

  return degreesF;
}

void setText(int tempToDisplay) {
  display.clearDisplay();
  
  display.setTextColor(WHITE);
  display.setTextSize(1);
  // set text cursor position 
  display.setCursor(1,0);
  display.println("www.StephanKoch.me");
  display.setTextSize(3);
  display.setCursor(30,8);
  display.print(String(tempToDisplay));
  display.drawCircle(69,11,3,WHITE);
  display.setCursor(77,8);
  display.print("F");
  display.display();

  if (tempToDisplay != currentTemp) {
    currentTemp = tempToDisplay;
    blinkLED();
  }
}

void blinkLED() {
  for (int i=0;i<3;i++) {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
  }
}

float getVoltage(int pin)
{
  float readValue = analogRead(pin);
  Serial.println(String(readValue));
  return (readValue * 0.004882814);
}

