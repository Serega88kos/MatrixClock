void BrightnessCheck() {  // функция освещенности
  static uint32_t last_br = millis();
  static uint32_t bright_timer = millis();
  if ((millis() - last_br) < o.brg * 1000) return;
  last_br = millis();
  if (o.auto_bright) {                    // если включена адаптивная яркость
    if (millis() - bright_timer > 100) {  // каждые 100 мс
      bright_timer = millis();            // сбросить таймер
      if (o.min_max) {
        new_bright = map(analogRead(BRI_PIN), 0, 1023, o.min_bright, o.max_bright);  // считать показания с фоторезистора, перевести диапазон
      } else {
        new_bright = map(analogRead(BRI_PIN), 0, 1023, o.max_bright, o.min_bright);  // считать показания с фоторезистора, перевести диапазон
      }
      //Serial.println((String)"Освещенность: " + new_bright);
      display->setBrightness8(new_bright);  // установить новую яркость
    }
  } else display->setBrightness8(o.min_bright);  // если автояркость выключена, то в расчете минимальная
}
