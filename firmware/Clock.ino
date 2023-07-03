void Clock() {
  int h = ntp.hour();
  int h1 = h / 10;
  int h2 = h % 10;
  int m = ntp.minute();
  int m1 = m / 10;
  int m2 = m % 10;

  display->setFont(&asm_19x11);
  display->setTextColor(clock_col);
  display->setCursor(1, 13);
  display->print (h1);           //первый символ часы
  display->setCursor(14, 13);
  display->print (h2);           //второй символ часы
  display->setCursor(29, 13);
  display->print (m1);           //первый символ минуты
  display->setCursor(42, 13);
  display->print (m2);           //второй символ минуты

  new_time = m2;
  if (new_time != old_time) {
    display->fillRect(0, 13, 54, 31, black);
    Serial.println(ntp.timeString());
    sensor.requestTemp();
    if (sensor.readTemp()) FtempS = sensor.getTemp() + o.cor_tempS;
    old_time = new_time;
  }
}

bool dot = true;
void Dots() {
  static uint32_t t = millis();
  if (millis() - t < 500) return;
  t = millis();
  display->setFont(&asm_19x11);
  display->setCursor(26, 13);
  if (dot) {
    display->setTextColor(clock_col);
    display->print(":");
    dot = false;
    return;
  } else {
    display->setTextColor(black);
    display->print(":");
    dot = true;
    return;
  }
}
