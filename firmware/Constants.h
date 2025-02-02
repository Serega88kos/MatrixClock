#include <Arduino.h>
#define VF "Serega88kos/MatrixClock@1.5"  // версия прошивки
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
  bool auto_bright;      // автоматическая подстройка яркости от уровня внешнего освещения (1 - включить, 0 - выключить)
  int min_bright = 10;   // минимальная яркость (0 - 255)
  int max_bright = 200;  // максимальная яркость (0 - 255)
  int brg = 10;          // как часто проверять изменение по датчику освещенности в сек
  bool min_max = false;
  bool sens_bme = false;  // если модуль bme, то true, иначе false
  int interval = 5;
  uint8_t mode_udp = 0;     // режим работы локального UDP для отправки показаний DS18B20
  bool night_mode = 0;      // ночной режим
  uint8_t start_night = 0;  // начало ночного режима в часах
  uint8_t stop_night = 0;   // окончание ночного режима в часах
  int night_brg = 10;       // яркость ночного режима
  uint8_t night_color = 0;  // цвет ночного режима
  bool new_god = 0;
};
Other o;

struct Monitoring {
  bool nm_enable = false;  // включаем мониторинг, иначе false
  int nm_delay = 300;      // как часто отправлять значения датчиков на мониторинг, минимум 5 минут, значение в секундах, плюс запас в 5 сек, на всякий случай, получается минимум 305
  bool nm_tempH = false;   // включить отправку показаний комнатной температуры
  bool nm_tempS = false;   // включить отправку показаний уличной температуры
  bool nm_pres = false;    // включить отправку показаний давления
  bool nm_hum = false;     // включить отправку показаний влажности
  float cor_tempH = 0;     // корректировка показаний датчика комнатной температуры
  float cor_tempS = 0;     // корректировка показаний датчика уличной температуры
  int cor_pres = 0;        // корректировка показаний датчика давления
  int cor_hum = 0;         // корректировка показаний датчика влажности
};
Monitoring m;

struct Color {
  uint8_t clock = 3;
  uint8_t home = 5;
  uint8_t street = 0;
  uint8_t press = 4;
  uint8_t hum = 4;
  uint8_t text = 2;
};
Color col;
