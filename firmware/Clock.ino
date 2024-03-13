void Clock() {
  if (ntp.minute() != old_time) {
    int h = ntp.hour();
    int h1 = h / 10;
    int h2 = h % 10;
    int m = ntp.minute();
    int m1 = m / 10;
    int m2 = m % 10;
    display->fillRect(0, 12, 63, 31, col.black);
    display->setFont(&asm_19x11);
    display->setTextColor(col.clock);
    display->setCursor(6, 12);
    display->print(h1);  //первый символ часы
    display->setCursor(19, 12);
    display->print(h2);  //второй символ часы
    display->setCursor(34, 12);
    display->print(m1);  //первый символ минуты
    display->setCursor(47, 12);
    display->print(m2);  //второй символ минуты
    Serial.println(ntp.timeString());
    old_time = m;
  }
}

bool dot = true;
void Dots() {
  static uint32_t t = millis();
  if (millis() - t < 500) return;
  t = millis();
  display->setFont(&asm_19x11);
  display->setCursor(31, 12);
  if (dot) {
    display->setTextColor(col.clock);
    display->print(":");
    dot = !dot;
    return;
  } else {
    display->setTextColor(col.black);
    display->print(":");
    dot = !dot;
    return;
  }
}