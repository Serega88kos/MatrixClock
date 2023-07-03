//Автор ASM
//Обсуждение работы на форуме https://community.alexgyver.ru/threasensor/bolshie-chasy-64x32-esp32.6716/
//Поблагодарить за труд, можно на Яндекс 410014148046232

#define GH_NO_MQTT      // MQTT
#include <GyverHub.h>
GyverHub hub("MyDevices", "MatrixClock", "");

#include "Constants.h"
#define ssidAP  "Clock_ESP"
#define passAP  "adminadmin"          // не менее 8 символов
// настройка фоторезистора
#define BRI_PIN             33        // PIN фоторезистора
// настройка панели
#include "Adafruit_GFX.h"
#include "ESP32-HUB75-MatrixPanel-I2S-DMA.h"
#define PANEL_RES_X 64                // ширина панели
#define PANEL_RES_Y 32                // высота панели
#define PANEL_CHAIN 1                 // кол-во
MatrixPanel_I2S_DMA *display = nullptr;
// шрифты
//#include "fonts/asm_12x7b.h"
#include "fonts/asm_19x11.h"
#include "fonts/asm_10x6b.h"
#include "fonts/asm_6x5.h"

#include "GyverBME280.h"
GyverBME280 bmp;

#include "microDS18B20.h"
MicroDS18B20 <0> sensor;

#include <WiFi.h>
#include "FS.h"
#include "LittleFS.h"

#include "GyverNTP.h"
GyverNTP ntp(c.gmt);

unsigned long timing;
float FtempH, FtempS, Fpres;
int tempH, tempS, pres, hum;
int new_time;
int old_time = -1;
byte set_light, brightness;
int new_bright, new_bright_f;
unsigned long bright_timer, off_timer;
uint8_t tab = 0;

#include "EEManager.h"
EEManager mem1(w);
EEManager mem2(c);
EEManager mem3(o);
EEManager mem4(m);

GHcolor color_minus(0, 0, 255);
GHcolor color_press(255, 0, 255);
GHcolor color_clock(0, 255, 255);
GHcolor color_home(255, 255, 0);
GHcolor color_street(0, 191, 255);
GHcolor color_text(250, 240, 230);

// настройка цветов
uint16_t minus_col   = display->color565(color_minus.r, color_minus.g, color_minus.b);  // знак минус темп-ры
uint16_t press_col   = display->color565(color_press.r, color_press.g, color_press.b);  // давление
uint16_t clock_col  = display->color565(color_clock.r, color_clock.g, color_clock.b);   // часы
uint16_t black  = display->color565(0, 0, 0);                                           // черный цвет, ничего не горит
uint16_t home_col = display->color565(color_home.r, color_home.g, color_home.b);        // дом темп-ра
uint16_t street_col = display->color565(color_street.r, color_street.g, color_street.b);// уличная темп-ра
uint16_t text_col = display->color565(color_text.r, color_text.g, color_text.b);// текст

void setup() {
  Serial.begin(115200);
  EEPROM.begin(1000);
  mem1.begin(0, 'a');
  mem2.begin(mem1.nextAddr(), 'a');
  mem3.begin(mem2.nextAddr(), 'a');
  mem4.begin(mem3.nextAddr(), 'a');
  HUB75_I2S_CFG mxconfig(PANEL_RES_X, PANEL_RES_Y, PANEL_CHAIN);
  mxconfig.clkphase = false;
  mxconfig.driver = HUB75_I2S_CFG::FM6126A;
  display = new MatrixPanel_I2S_DMA(mxconfig);
  display->begin();
  display->setBrightness8(30);
  display->setTextWrap(false);
  display->fillScreen(0);
  bmp.begin();
  wifi_connected();
  hub.setVersion(VF);
}

void loop() {
  hub.tick();  // обязательно тикаем тут
  hub.sendUpdate("n1,new_bright");
  BrightnessCheck();
  mem1.tick(); mem2.tick(); mem3.tick(); mem4.tick();
  ntp.tick();
  Clock();
  Dots();
  rezhim();
  if (m.Monitoring) {
    if (millis() - timing > m.delay_narod * 1000) {
      timing = millis();
      NarodMonitoring();
    }
  }
}

uint8_t mods = 0;
void rezhim() {
  static uint32_t test = millis();
  if ((millis() - test) < 5000) { // для теста смена каждые 5 секунд
    switch (mods) {
      case 0:
        TempStreet(); Press();
        break;
      case 1:
        TempHome();
        if (o.sens_bme)Hum();
        break;
    }
  } else {
    test = millis();
    mods++;
    display->fillRect(0, 0, 63, 10, black); // очистка верхней части экрана, путем заливки черного цвета
    if (mods > 1) mods = 0;
  }
}
