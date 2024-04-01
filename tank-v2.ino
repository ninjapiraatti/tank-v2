#include <L298N.h>
#include <L298NX2.h>

#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_ST77xx.h>

#include "tank.h"


// Define TFT
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCK, TFT_RST);


void setup() 
{

	//data.angle = 0;
	//data.humidity = 0;
	//int wifiStatus = 2;
	Serial.begin(9600);
	//setup_tft(tft);
	//tft.fillScreen(ST7735_BLACK);
	//tft.setCursor(0, 0);
	//tft.setTextColor(ST7735_WHITE);
	//tft.println("Henlo. Booting up:");
	//tft.setCursor(0, 10);
	//tft.print("WiFi:");
	setup_engines();
	//tft.setCursor(0, 30);
	delay(200);
	//tft.fillScreen(ST7735_BLACK);  // Fill screen with black
	//pinMode(LED_BUILTIN, OUTPUT);
}

void loop() 
{
	/*
	tft.setCursor(0, 0);
	tft.setTextColor(0x07F9);
	tft.println("MQTT Gadget 0.1"); 
	tft.setCursor(0, 20);
	tft.print("Servo angle:");
	tft.fillRect(90, 20, 100, 10, 0x0000);
	tft.setCursor(90, 20);
	tft.print(data.angle);
	*/

	//tft.setCursor(0, 30);
	//tft.print("Humidity:");
	//tft.fillRect(90, 30, 100, 10, 0x0000);
	//tft.setCursor(90, 30);
	//tft.print(data.humidity);
	//delay(1000);
	//rotate_stepper(800);
	//tft.fillScreen(ST7735_BLACK);  // Print a text or value
	//delay(1500);
	//Fturnservo(90);
	//tft.println("Turning servo now."); 
	//tft.println(getWifiQuality());  // Print a text or value
	goforward(1500);
	delay(2000); 
  gobackward(1500);
	delay(2000); 
  turnright(1500);
	delay(2000); 
  turnleft(1500);
	delay(2000); 
	//digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  //delay(500);                      // wait for a second
  //digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  //delay(500);  
}

void setup_tft(Adafruit_ST7735 tft) {
	tft.initR(INITR_BLACKTAB);  // Initialize a ST7735S chip, black tab
	tft.fillScreen(ST7735_BLACK);  // Fill screen with black
	tft.setTextWrap(false);
	tft.setRotation(1);
	tft.setCursor(0, 0);  // Set position (x,y)
	tft.setTextColor(ST7735_WHITE);  // Set color of text. First is the color of text and after is color of background
	tft.setTextSize(1);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
	tft.println("Hello");  // Print a text or value
	tft.setTextSize(0);  // Set text size. We are using custom font so you should always set text size as 0
	tft.setCursor(0, 50);  // Set position (x,y)
	tft.setTextColor(ST7735_RED);  // Set color of text. We are using custom font so there is no background color supported
	tft.println("World!");  // Print a text or value
	tft.setCursor(0, 70);
	tft.setTextColor(ST7735_GREEN);  // Set color of text. We are using custom font so there is no background color supported
	tft.println("If you can read this, tft works");  // Print a text or value
	delay(1000);
	tft.fillScreen(ST7735_BLACK); 
}

void showMessage(char *msg, int milliseconds, bool resetscreen) {
	if (resetscreen == true) {
		tft.fillScreen(ST7735_BLACK);
		tft.setCursor(0, 0);
	}
	tft.setTextColor(ST7735_WHITE);
	tft.print(msg);
	delay(milliseconds);
}

void setup_engines() {
	pinMode(PIN_IN1, OUTPUT);
	pinMode(PIN_IN2, OUTPUT);
	pinMode(PIN_IN3, OUTPUT);
	pinMode(PIN_IN4, OUTPUT);
	pinMode(PIN_ENA, OUTPUT);
	pinMode(PIN_ENB, OUTPUT);
}

void turnright(int time)
{
	analogWrite(PIN_ENB, MAX_THROTTLE);
	analogWrite(PIN_ENA, MAX_THROTTLE);
	digitalWrite(PIN_IN1, LOW);
	digitalWrite(PIN_IN2, LOW);
	digitalWrite(PIN_IN3, HIGH);
	digitalWrite(PIN_IN4, HIGH);
	delay(time);
	stopengines(0);
}

void turnleft(int time)
{
	analogWrite(PIN_ENB, MAX_THROTTLE);
	analogWrite(PIN_ENA, MAX_THROTTLE);
	digitalWrite(PIN_IN1, HIGH);
	digitalWrite(PIN_IN2, HIGH);
	digitalWrite(PIN_IN3, LOW);
	digitalWrite(PIN_IN4, LOW);
	delay(time);
	stopengines(0);
}

void goforward(int time)
{
	analogWrite(PIN_ENB, MAX_THROTTLE);
	analogWrite(PIN_ENA, MAX_THROTTLE);
	digitalWrite(PIN_IN1, LOW);
	digitalWrite(PIN_IN2, HIGH);
	digitalWrite(PIN_IN3, HIGH);
	digitalWrite(PIN_IN4, LOW);
	delay(time);
	stopengines(0);
}

void gobackward(int time)
{
	analogWrite(PIN_ENB, MAX_THROTTLE);
	analogWrite(PIN_ENA, MAX_THROTTLE);
	digitalWrite(PIN_IN1, HIGH);
	digitalWrite(PIN_IN2, LOW);
	digitalWrite(PIN_IN3, LOW);
	digitalWrite(PIN_IN4, HIGH);
	delay(time);
	stopengines(0);
}

void stopengines(int time)
{
	analogWrite(PIN_ENA, 0);
	analogWrite(PIN_ENB, 0);
	delay(time);
}