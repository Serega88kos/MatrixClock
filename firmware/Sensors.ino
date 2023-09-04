void TempHome() {
  FtempH = (bmp.readTemperature()) + o.cor_tempH;
  tempH = FtempH;
  //Serial.print F("Дом: ");  Serial.println(FtempH);
  display->setFont(&asm_6x5);
  display->setTextColor(text_col);
  display->setCursor(28, 9);
  display->print("dom");
  display->setFont(&asm_10x6);
  display->setTextColor(home_col);
  display->setCursor(45, 9);
  display->print(tempH);
}

void TempStreet() {
  sensor.requestTemp();
  if (sensor.readTemp()) FtempS = sensor.getTemp() + o.cor_tempS;
  tempS = FtempS;
  //Serial.print F("Улица: "); Serial.println(FtempS);
  display->setFont(&asm_6x5);
  display->setTextColor(text_col);
  display->setCursor(1, 9);
  display->print("ul");
  display->setFont(&asm_10x6);
  display->setTextColor(street_col);
  display->setCursor(12, 9);
  display->print(tempS);
}

void Press() {
  Fpres = (pressureToMmHg(bmp.readPressure())) + o.cor_pres;
  //Serial.print F("Давление: ");  Serial.println(Fpres);
  pres = Fpres;
  display->setFont(&asm_6x5);
  display->setTextColor(text_col);
  display->setCursor(28, 9);
  display->print("dav");
  display->setFont(&asm_10x6);
  display->setTextColor(press_col);
  display->setCursor(43, 9);
  display->print(pres);
}

void Hum() {
  if (o.sens_bme) {
    hum = bmp.readHumidity();
    //Serial.print F("Влажность: "); Serial.println(hum);
    display->setFont(&asm_6x5);
    display->setTextColor(text_col);
    display->setCursor(1, 9);
    display->print("vl");
    display->setFont(&asm_10x6);
    display->setTextColor(hum_col);
    display->setCursor(12, 9);
    display->print(hum);
  }
}
