//Автор ASM
//Обсуждение работы на форуме https://community.alexgyver.ru/threasensor/bolshie-chasy-64x32-esp32.6716/
//Поблагодарить за труд, можно на Яндекс 410014148046232
#include "Constants.h"
#define GH_NO_MQTT  // MQTT
#define GH_INCLUDE_PORTAL
#include <GyverHub.h>
GyverHub hub("MyDevices", "MatrixClock", "");
#include "Adafruit_GFX.h"
#include "ESP32-HUB75-MatrixPanel-I2S-DMA.h"  // https://github.com/mrfaptastic/ESP32-HUB75-MatrixPanel-DMA
MatrixPanel_I2S_DMA *display = nullptr;
// шрифты
#include "fonts/asm_19x11.h"
#include "fonts/asm_10x6.h"
#include "fonts/asm_6x5.h"

#include "GyverBME280.h"
GyverBME280 bmp;
#include "microDS18B20.h"
MicroDS18B20<0> sensor;

#include <WiFi.h>
#include "FS.h"
#include "LittleFS.h"

#include "GyverNTP.h"
GyverNTP ntp(c.gmt);

unsigned long timing;
float FtempH, FtempS, Fpres;
int tempH, tempS, pres, hum, new_time, old_time = -1;
uint16_t new_bright;
uint8_t tab = 0;

#include <FileData.h>
FileData _clock(&LittleFS, "/clock.dat", 'A', &c, sizeof(c));
FileData _other(&LittleFS, "/other.dat", 'A', &o, sizeof(o));
FileData _narod(&LittleFS, "/narod.dat", 'A', &m, sizeof(m));
FileData _color(&LittleFS, "/color.dat", 'A', &col, sizeof(col));

void setup() {
  Serial.begin(115200);
  LittleFS.begin();
  FDstat_t stat1 = _clock.read();
  FDstat_t stat2 = _other.read();
  FDstat_t stat3 = _narod.read();
  FDstat_t stat4 = _color.read();
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
  hub.onBuild(build);  // подключаем билдер
  hub.setVersion(VF);
  ReadSens();
}

void loop() {
  hub.tick();  // обязательно тикаем тут
  hub.sendUpdate("n1");
  hub.sendUpdate("new_bright");

  static gh::Timer timer1 (1000);
  if (timer1) BrightnessCheck();

  //wifi_.tick();
  _clock.tick();
  _other.tick();
  _narod.tick();
  _color.tick();
  ntp.tick();
  Clock();
  Dots();
  rezhim();

  if (m.nm_enable) {
    static gh::Timer timer2(m.nm_delay * 1000);
    if (timer2) Monitoring();
  }

  static gh::Timer timer3(60000);
  if (timer3) ReadSens();
}

static bool mods = true;
void rezhim() {
  static uint32_t t = millis();
  if ((millis() - t) < o.interval * 1000) return;  // смена каждые * секунд
  t = millis();
  
  if (mods) {
    display->fillRect(0, 0, 63, 11, col.black);
    TempStreet();
    Press();
    mods = !mods;
    return;
  } else {
    display->fillRect(0, 0, 63, 11, col.black);
    TempHome();
    if (o.sens_bme) Hum();
    mods = !mods;
    return;
  }
}
