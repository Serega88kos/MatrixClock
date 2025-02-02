void Clock() {
  hour = ntp.hour();
  int h1 = hour / 10;
  int h2 = hour % 10;
  int m = ntp.minute();
  int m1 = m / 10;
  int m2 = m % 10;
  if (ntp.minute() != old_time) {
    display->fillRect(0, 12, 30, 31, BLACK);
    display->fillRect(34, 12, 63, 31, BLACK);
    old_time = m;
  }
  display->setFont(&asm_19x11);
  if (!flag_night) display->setTextColor(ColorTable[col.clock]);
  display->setCursor(6, 12);
  display->print(h1);  //первый символ часы
  display->setCursor(19, 12);
  display->print(h2);  //второй символ часы
  display->setCursor(34, 12);
  display->print(m1);  //первый символ минуты
  display->setCursor(47, 12);
  display->print(m2);  //второй символ минуты
  //Serial.println(ntp.toString());
  old_time = m;
}

void ClockNG() {
  for (int i = 0; i < 64; i++) {
    if (!flag_night) display->drawPixel(i, 0, display->color444(random(0, 255), random(0, 255), random(0, 255)));
    if (!flag_night) display->drawPixel(i, 31, display->color444(random(0, 255), random(0, 255), random(0, 255)));
  }
  for (int j = 0; j < 32; j++) {
    if (!flag_night) display->drawPixel(0, j, display->color444(random(0, 255), random(0, 255), random(0, 255)));
    if (!flag_night) display->drawPixel(63, j, display->color444(random(0, 255), random(0, 255), random(0, 255)));
  }
  if (flag_night) display->drawRect(0, 0, 64, 32, BLACK);
  hour = ntp.hour();
  int h1 = hour / 10;
  int h2 = hour % 10;
  int m = ntp.minute();
  int m1 = m / 10;
  int m2 = m % 10;
  if (ntp.minute() != old_time) {
    display->fillRect(0, 12, 30, 31, BLACK);
    display->fillRect(34, 12, 63, 31, BLACK);
    old_time = m;
  }
  display->setFont(&asm_19x11);
  display->setCursor(6, 12);
  if (!flag_night) display->setTextColor(display->color444(random(0, 255), random(0, 255), random(0, 255)));
  display->print(h1);  //первый символ часы
  display->setCursor(19, 12);
  if (!flag_night) display->setTextColor(display->color444(random(0, 255), random(0, 255), random(0, 255)));
  display->print(h2);  //второй символ часы
  display->setCursor(34, 12);
  if (!flag_night) display->setTextColor(display->color444(random(0, 255), random(0, 255), random(0, 255)));
  display->print(m1);  //первый символ минуты
  display->setCursor(47, 12);
  if (!flag_night) display->setTextColor(display->color444(random(0, 255), random(0, 255), random(0, 255)));
  display->print(m2);  //второй символ минуты
  //Serial.println(ntp.toString());
  old_time = m;
}

bool dot = true;
static gh::Timer dots(500);
void Dots() {
  if (dots) {
    dot = !dot;
    display->setFont(&asm_19x11);
    display->setCursor(31, 12);
    if (dot) {
      if (o.new_god) {
        if (!flag_night) display->setTextColor(display->color444(random(0, 255), random(0, 255), random(0, 255)));
      }
      if (!o.new_god) {
        if (!flag_night) display->setTextColor(ColorTable[col.clock]);
      }
      display->print(":");
    }
    if (!dot) {
      display->setTextColor(BLACK);
      display->print(":");
    }
  }
}

bool mods = true;
void rezhim() {
  static gh::Timer Ttime(o.interval * 1000);
  if (Ttime) {
    mods = !mods;
    display->fillRect(1, 1, 63, 11, BLACK);
    if (mods) {
      TempStreet();
      Press();
    }
    if (!mods) {
      TempHome();
      if (o.sens_bme) Hum();
    }
  }
}