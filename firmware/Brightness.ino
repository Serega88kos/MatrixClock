void BrightnessCheck() {  // функция освещенности
  static gh::Timer timer(o.brg * 1000);
  if (timer) {
    if (o.auto_bright) {  // если включена адаптивная яркость
      if (o.min_max) {
        new_bright = map(analogRead(BRI_PIN), 0, 1023, o.min_bright, o.max_bright);  // считать показания с фоторезистора, перевести диапазон
      } else {
        new_bright = map(analogRead(BRI_PIN), 0, 1023, o.max_bright, o.min_bright);  // считать показания с фоторезистора, перевести диапазон
      }
      //Serial.println((String)"Освещенность: " + new_bright);
      display->setBrightness8(new_bright);  // установить новую яркость
    } else {
      display->setBrightness8(o.min_bright);  // если автояркость выключена, то в расчете минимальная
    }
  }
}