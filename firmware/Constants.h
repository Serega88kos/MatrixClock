#include <Arduino.h>
#define VF "Serega88kos/MatrixClock@1.2"  // версия прошивки

struct Wifi {
  char ssid[32] = "";
  char pass[32] = "";
};
Wifi w;

struct Clock {
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
  bool Monitoring = false;  // включаем мониторинг, иначе false
  int delay_narod = 300;    // как часто отправлять значения датчиков на мониторинг, минимум 5 минут, значение в секундах, плюс запас в 5 сек, на всякий случай, получается минимум 305
  bool nm_tempH = false;    // включить отправку показаний комнатной температуры
  bool nm_tempS = false;    // включить отправку показаний уличной температуры
  bool nm_pres = false;     // включить отправку показаний давления
  bool nm_hum = false;      // включить отправку показаний влажности
};
Monitoring m;

struct Color {
  GHcolor color_minus{ 0, 255, 255 };
  GHcolor color_clock{ 0, 255, 255 };
  GHcolor color_home{ 255, 211, 0 };
  GHcolor color_street{ 99, 99, 209 };
  GHcolor color_press{ 252, 150, 7 };
  GHcolor color_hum{ 189, 53, 211 };
  GHcolor color_text{ 197, 187, 187 };
};
Color col;
