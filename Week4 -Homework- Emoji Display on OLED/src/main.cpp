#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#ifndef PI
#endif

void showSmiley();
void showCool();
void showHeart();
void showMoon();
void showStar();
void showCoffee();
void showMusic();
void drawArc(int16_t cx, int16_t cy, int16_t r, float startDeg, float endDeg, uint16_t color);

void setup() {
  Wire.begin(21, 22); // SDA, SCL for ESP32
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    for (;;);
  }
  display.clearDisplay();
  display.display();
}

void loop() {
  showSmiley(); delay(1500);
  showCool(); delay(1500);
  showHeart(); delay(1500);
  showMoon(); delay(1500);
  showStar(); delay(1500);
  showCoffee(); delay(1500);
  showMusic(); delay(1500);
}

void drawArc(int16_t cx, int16_t cy, int16_t r, float startDeg, float endDeg, uint16_t color) {
  float start = startDeg * PI / 180.0;
  float end = endDeg * PI / 180.0;
  float step = 0.05;
  for (float a = start; a <= end; a += step) {
    int16_t x = cx + (int16_t)(r * cos(a));
    int16_t y = cy + (int16_t)(r * sin(a));
    display.drawPixel(x, y, color);
  }
}

void showSmiley() {
  display.clearDisplay();
  display.drawCircle(64, 16, 10, SSD1306_WHITE);
  display.fillCircle(60, 13, 1, SSD1306_WHITE);
  display.fillCircle(68, 13, 1, SSD1306_WHITE);
  drawArc(64, 17, 6, 20, 160, SSD1306_WHITE);
  display.display();
}

void showCool() {
  display.clearDisplay();
  display.drawCircle(64, 48, 10, SSD1306_WHITE);
  display.fillRect(56, 45, 16, 3, SSD1306_WHITE);
  display.fillCircle(60, 46, 1, SSD1306_BLACK);
  display.fillCircle(68, 46, 1, SSD1306_BLACK);
  display.display();
}

void showHeart() {
  display.clearDisplay();
  display.fillCircle(60, 16, 5, SSD1306_WHITE);
  display.fillCircle(68, 16, 5, SSD1306_WHITE);
  display.fillTriangle(55, 18, 73, 18, 64, 32, SSD1306_WHITE);
  display.display();
}

void showMoon() {
  display.clearDisplay();
  display.fillCircle(64, 48, 10, SSD1306_WHITE);
  display.fillCircle(68, 48, 8, SSD1306_BLACK);
  display.display();
}

void showStar() {
  display.clearDisplay();
  display.fillTriangle(64, 10, 60, 20, 68, 20, SSD1306_WHITE);
  display.fillTriangle(64, 22, 60, 12, 68, 12, SSD1306_WHITE);
  display.display();
}

void showCoffee() {
  display.clearDisplay();
  display.drawRect(55, 40, 18, 12, SSD1306_WHITE);
  display.drawLine(73, 43, 76, 47, SSD1306_WHITE);
  display.drawLine(60, 36, 62, 40, SSD1306_WHITE);
  display.drawLine(64, 36, 66, 40, SSD1306_WHITE);
  display.display();
}

void showMusic() {
  display.clearDisplay();
  display.drawLine(60, 20, 60, 40, SSD1306_WHITE);
  display.drawLine(60, 20, 75, 25, SSD1306_WHITE);
  display.drawLine(75, 25, 75, 45, SSD1306_WHITE);
  display.fillCircle(60, 43, 3, SSD1306_WHITE);
  display.fillCircle(75, 48, 3, SSD1306_WHITE);
  display.display();
}
