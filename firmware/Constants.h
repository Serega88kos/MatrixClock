#include <Arduino.h>
#define VF "Serega88kos/MatrixClock@1.3"  // версия прошивки
//Настройки точки доступа, IP 192.168.4.1
#define ssidAP "MatrixClock"
#define passAP "administrator"  // не менее 8 символов
// настройка фоторезистора
#define BRI_PIN 33  // PIN фоторезистора
// настройка панели
#define PANEL_RES_X 64  // ширина панели
#define PANEL_RES_Y 32  // высота панели
#define PANEL_CHAIN 1   // кол-во

struct Clock {
  char ssid[32] = "";
  char pass[32] = "";
  int gmt = 3;                     // часовой пояс, 3 для МСК
  char host[32] = "pool.ntp.org";  // NTP сервер
};
Clock c;

struct Other {
  float cor_tempH = 0;   // корректировка показаний датчика комнатной температуры
  float cor_tempS = 0;   // корректировка показаний датчика уличной температуры
  int cor_pres = 0;      // корректировка показаний датчика давления
  int cor_hum = 0;       // корректировка показаний датчика влажности
  bool auto_bright;      // автоматическая подстройка яркости от уровня внешнего освещения (1 - включить, 0 - выключить)
  int min_bright = 10;   // минимальная яркость (0 - 255)
  int max_bright = 200;  // максимальная яркость (0 - 255)
  int brg = 10;          // как часто проверять изменение по датчику освещенности в сек
  bool min_max = false;
  bool sens_bme = false;  // если модуль bme, то true, иначе false
  int interval = 5;
};
Other o;

struct Monitoring {
  bool nm_enable = false;  // включаем мониторинг, иначе false
  int nm_delay = 300;      // как часто отправлять значения датчиков на мониторинг, минимум 5 минут, значение в секундах, плюс запас в 5 сек, на всякий случай, получается минимум 305
  bool nm_tempH = false;   // включить отправку показаний комнатной температуры
  bool nm_tempS = false;   // включить отправку показаний уличной температуры
  bool nm_pres = false;    // включить отправку показаний давления
  bool nm_hum = false;     // включить отправку показаний влажности
};
Monitoring m;

struct Color {
  uint32_t minus = 0x00FFFF;
  uint32_t clock = 0x00FFFF;
  uint32_t home = 0xFFD300;
  uint32_t street = 0x6363D1;
  uint32_t press = 0xFC9607;
  uint32_t hum = 0xBD35D3;
  uint32_t text = 0xC5BBBB;
  uint16_t black = 0x000000;
};
Color col;
