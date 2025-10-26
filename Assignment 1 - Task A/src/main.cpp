// Name : Aleeha Aiman
//Reg No: 23-NTU-CS-1243
//Class: Bs Cs 5th (A)
//Title : Use one button to cycle through LED modes (display the current state on the OLED): 
//1. Both OFF 
//2. Alternate blink 
//3. Both ON 
//4. PWM fade 
//Use the second button to reset to OFF.


#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define BTN_MODE   15
#define BTN_RESET  4
#define LED1       13
#define LED2       12
#define LED3       14
#define BUZZER     27

const int PWMChannel = 0;
const int PWMFrequency = 5000; //I have given a higher frequency for smooth 
                               //oberservation as it Turns ON/OFF 5000 times in 1 second
const int PWMResolution = 8;   //it means duty cycle can be set from 0-255 i.e 2^8, so at 100% brightness
                               //we need to set it to 255

int mode = 0;
unsigned long lastPress = 0;   //I used unsigned as time is always positive
int fadeValue = 0;
int fadeDir = 1; //it is basically fade direction (1 for increasing, -1 for decreasing)

unsigned long blinkTimer = 0; // Timer for blinking LEDs
bool blinkState = false;

void showMode(const char* msg) {  //Print our current mode on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 20);
  display.print("Mode: ");
  display.println(msg);
  display.display();
}

void setup() {
  pinMode(BTN_MODE, INPUT_PULLUP); 
  pinMode(BTN_RESET, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  showMode("OFF");

  ledcSetup(PWMChannel, PWMFrequency, PWMResolution);
  ledcAttachPin(LED3, PWMChannel); //i connected LED3 to PWM for FADE mode
}

void loop() {
  if (digitalRead(BTN_MODE) == LOW && millis() - lastPress > 300) { //used millis for debouncing
    lastPress = millis();
    mode = (mode + 1) % 4; //4 modes: 0,1,2,3
    switch (mode) {
      case 0: showMode("OFF"); break;
      case 1: showMode("ALTERNATE BLINK"); break;
      case 2: showMode("ALL ON"); break;
      case 3: showMode("FADE"); break;
    }
  }

  if (digitalRead(BTN_RESET) == LOW) {
    mode = 0;
    showMode("OFF");
  }

  switch (mode) {
    case 0:
      digitalWrite(LED1, LOW); //Turn OFF LEDs
      digitalWrite(LED2, LOW);
      ledcWrite(PWMChannel, 0);
      break;

    case 1:
      if (millis() - blinkTimer >= 300) { //After every 300 ms toggle the LEDs
        blinkTimer = millis();
        blinkState = !blinkState;
        digitalWrite(LED1, blinkState);
        digitalWrite(LED2, !blinkState);
      }
      break;

    case 2:
      digitalWrite(LED1, HIGH); //Turn ON LEDs
      digitalWrite(LED2, HIGH);
      ledcWrite(PWMChannel, 255); //Full brightness
      break;

    case 3:
      ledcWrite(PWMChannel, fadeValue); //Set brightness according to fadeValue
      fadeValue += fadeDir * 5; //Change fadeValue by 5 in each iteration
      if (fadeValue <= 0 || fadeValue >= 255) fadeDir = -fadeDir; //Reverse direction like when we 
      //will reach at zero brighteness reverse the direction to increase brightness 
      delay(20);
      break;
  }
}
