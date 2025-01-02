void Brightness() {  // функция освещенности
  static gh::Timer timer(o.brg * 1000);
  if (timer) {
    if (o.night_mode && ((o.start_night > o.stop_night && (hour >= o.start_night || hour < o.stop_night)) || (o.start_night < o.stop_night && hour >= o.start_night && hour >= o.start_night && hour < o.stop_night))) {
      display->setBrightness8(o.night_brg);
      flag_night = true;
    } else {
      flag_night = false;
      if (o.auto_bright) {                                                                                               // если включена адаптивная яркость
        if (o.min_max) new_bright = map(constrain(analogRead(BRI_PIN), 0, 1023), 0, 1023, o.min_bright, o.max_bright);   // считать показания с фоторезистора, перевести диапазон
        if (!o.min_max) new_bright = map(constrain(analogRead(BRI_PIN), 0, 1023), 0, 1023, o.max_bright, o.min_bright);  // считать показания с фоторезистора, перевести диапазон
        Serial.println((String) "Освещенность: " + new_bright);
        display->setBrightness8(new_bright);  // установить новую яркость
      }
      if (!o.auto_bright) display->setBrightness8(o.min_bright);  // если автояркость выключена, то в расчете минимальная
    }
  }
}