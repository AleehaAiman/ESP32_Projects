// Title : Task B — Coding: Use a single button with press-type detection (display the event on the
// OLED):
// • Short press → toggle LED
// • Long press (> 1.5 s) → play a buzzer

// Aleeha Aiman
// Regno: 23-NTU-CS-1243
// BsCs5th A

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BTN1 15 // i have connected yellow button to pin 15
#define LED1 13
#define LED2 12
#define LED3 14
#define BUZZ 27

Adafruit_SSD1306 oled(128, 64, &Wire, -1);

unsigned long pressStart = 0; // it is for storing time in milis also i used unsigned as time will be positive always
bool isPressed = false;
bool ledsOn = false;

void setup()
{
  pinMode(BTN1, INPUT_PULLUP); // pin15 ie button 1 gets the input
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(BUZZ, OUTPUT);

  digitalWrite(LED1, LOW); // initially all led's and buzzer is low
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(BUZZ, LOW);

  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 0);
  oled.println("Ready...");
  oled.display(); // just when then the code executes OLED displays "ready"
}

void loop()
{
  int buttonState = digitalRead(BTN1);

  if (buttonState == LOW && !isPressed)
  {
    isPressed = true;
    pressStart = millis(); // when the button is pressed, this variables starts stroing time in milis
  }

  if (buttonState == HIGH && isPressed)
  {
    unsigned long duration = millis() - pressStart; // it records the total time when button is in pressed state
    isPressed = false;
    oled.clearDisplay();

    if (duration < 1500)
    {
      ledsOn = !ledsOn; // if button was ON for 1.5 sec then LEDs are turned ON
      digitalWrite(LED1, ledsOn);
      digitalWrite(LED2, ledsOn);
      digitalWrite(LED3, ledsOn);

      oled.setCursor(0, 0);
      oled.println("Short Press Detected");
      oled.setCursor(0, 16);
      oled.println(ledsOn ? "LEDs: ON" : "LEDs: OFF");
      oled.display();
    }
    else
    {
      oled.setCursor(0, 0); // if we held it for more than 1.5 sec, buzzer plays the sound
      oled.println("Long Press Detected");
      oled.setCursor(0, 16);
      oled.println("Playing buzzer...");
      oled.display();

      tone(BUZZ, 1000, 500); // sound is of 1000 Hz and it plays for half a sec
      delay(500);
      noTone(BUZZ); // Buzzer stops producing sound
    }
  }
}
