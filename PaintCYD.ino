#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

#define XPT2046_IRQ 36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);
TFT_eSPI tft = TFT_eSPI();

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define BOXSIZE 40
#define PENRADIUS 3

int oldcolor, currentcolor;

void setup() {
  Serial.begin(115200);
  delay(1000);

  touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  touchscreen.begin(touchscreenSPI);
  touchscreen.setRotation(1);

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  tft.fillRect(0, 0, BOXSIZE, BOXSIZE, TFT_RED);
  tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, TFT_YELLOW);
  tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, TFT_GREEN);
  tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, TFT_CYAN);
  tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, TFT_BLUE);
  tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, TFT_MAGENTA);

  tft.drawRect(0, 0, BOXSIZE, BOXSIZE, TFT_WHITE);
  currentcolor = TFT_RED;
}

void loop() {
  if (!touchscreen.tirqTouched() || !touchscreen.touched()) return;

  TS_Point p = touchscreen.getPoint();

  int x = map(p.x, 200, 3700, 0, SCREEN_WIDTH);
  int y = map(p.y, 240, 3800, 0, SCREEN_HEIGHT);

  if (y < BOXSIZE) {
    oldcolor = currentcolor;

    if (x < BOXSIZE) {
      currentcolor = TFT_RED;
      tft.drawRect(0, 0, BOXSIZE, BOXSIZE, TFT_WHITE);
    } else if (x < BOXSIZE * 2) {
      currentcolor = TFT_YELLOW;
      tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, TFT_WHITE);
    } else if (x < BOXSIZE * 3) {
      currentcolor = TFT_GREEN;
      tft.drawRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, TFT_WHITE);
    } else if (x < BOXSIZE * 4) {
      currentcolor = TFT_CYAN;
      tft.drawRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, TFT_WHITE);
    } else if (x < BOXSIZE * 5) {
      currentcolor = TFT_BLUE;
      tft.drawRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, TFT_WHITE);
    } else if (x <= BOXSIZE * 6) {
      currentcolor = TFT_MAGENTA;
      tft.drawRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, TFT_WHITE);
    }

    if (oldcolor != currentcolor) {
      if (oldcolor == TFT_RED)
        tft.fillRect(0, 0, BOXSIZE, BOXSIZE, TFT_RED);
      if (oldcolor == TFT_YELLOW)
        tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, TFT_YELLOW);
      if (oldcolor == TFT_GREEN)
        tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, TFT_GREEN);
      if (oldcolor == TFT_CYAN)
        tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, TFT_CYAN);
      if (oldcolor == TFT_BLUE)
        tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, TFT_BLUE);
      if (oldcolor == TFT_MAGENTA)
        tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, TFT_MAGENTA);
    }
  }

  if ((y - PENRADIUS > BOXSIZE) && (y + PENRADIUS < tft.height())) {
    tft.fillCircle(x, y, PENRADIUS, currentcolor);
  }

  delay(10);
}
