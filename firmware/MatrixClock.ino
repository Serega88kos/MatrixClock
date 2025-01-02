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
#include "Color.h"
// шрифты
#include "fonts/asm_19x11.h"
#include "fonts/asm_10x6.h"
#include "fonts/asm_6x5.h"

#include "GyverBME280.h"
GyverBME280 bmp;
#include <GyverDS18.h>
GyverDS18Single ds(0);

#include <WiFi.h>
#include <WiFiUdp.h>
WiFiUDP udp;
#include "FS.h"
#include "LittleFS.h"

#include "GyverNTP.h"
GyverNTP ntp(c.gmt);

int hour;
unsigned long timing;
float FtempH, FtempS, Fpres;
int tempH, tempS, pres, hum, new_time, old_time = -1;
uint16_t new_bright;
uint8_t tab = 0;
bool flag_night;
unsigned int localPort = 8888;

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
  ReadSens();
  wifi_connected();
  hub.onBuild(build);  // подключаем билдер
  hub.setVersion(VF);
}

void loop() {
  hub.tick();  // обязательно тикаем тут
  _clock.tick();
  _other.tick();
  _narod.tick();
  _color.tick();

  Dots();
  rezhim();
  ReadSens();
  Brightness();
  if (ntp.tick()) {  // новая секунда
    hub.sendUpdate("time");
    hub.update("new_bright").value(new_bright);
    hub.update("FtempH").value(FtempH);
    hub.update("FtempS").value(FtempS);
    hub.update("pres").value(pres);
    hub.update("hum").value(hum);
    if (!o.new_god) Clock();
    if (o.new_god) ClockNG();
  }
  if (flag_night) display->setTextColor(ColorTableNight[o.night_color]);

  if (m.nm_enable) {
    static gh::Timer narMon(m.nm_delay * 1000);
    if (narMon) Monitoring();
  }
}
