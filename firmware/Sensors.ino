void ReadSens() {
  FtempH = (bmp.readTemperature()) + o.cor_tempH;
  sensor.requestTemp();
  if (sensor.readTemp()) {
    FtempS = sensor.getTemp() + o.cor_tempS;
    Fpres = (pressureToMmHg(bmp.readPressure())) + o.cor_pres;
    if (o.sens_bme) hum = bmp.readHumidity();
  }
}

void TempHome() {
  tempH = FtempH;
  //Serial.print F("Дом: ");  Serial.println(FtempH);
  display->setFont(&asm_6x5);
  display->setTextColor(col.text);
  display->setCursor(28, 9);
  display->print("dom");
  display->setFont(&asm_10x6);
  display->setTextColor(col.home);
  display->setCursor(45, 9);
  display->print(tempH);
}

void TempStreet() {
  tempS = FtempS;
  //Serial.print F("Улица: "); Serial.println(FtempS);
  display->setFont(&asm_6x5);
  display->setTextColor(col.text);
  display->setCursor(1, 9);
  display->print("ul");
  display->setFont(&asm_10x6);
  display->setTextColor(col.street);
  display->setCursor(12, 9);
  display->print(tempS);
}

void Press() {
  //Serial.print F("Давление: ");  Serial.println(Fpres);
  pres = Fpres;
  display->setFont(&asm_6x5);
  display->setTextColor(col.text);
  display->setCursor(28, 9);
  display->print("dav");
  display->setFont(&asm_10x6);
  display->setTextColor(col.press);
  display->setCursor(43, 9);
  display->print(pres);
}

void Hum() {
  if (o.sens_bme) {
    //Serial.print F("Влажность: "); Serial.println(hum);
    display->setFont(&asm_6x5);
    display->setTextColor(col.text);
    display->setCursor(1, 9);
    display->print("vl");
    display->setFont(&asm_10x6);
    display->setTextColor(col.hum);
    display->setCursor(12, 9);
    display->print(hum);
  }
}
