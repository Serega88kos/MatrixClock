void TempHome() {
  FtempH = (bmp.readTemperature()) + o.cor_tempH;
  tempH = FtempH;
  //Serial.print F("Дом: ");  Serial.println(FtempH);

  display->setFont(&asm_6x5);
  display->setTextColor(text_col);
  display->setCursor(28, 7);
  display->print ("dom");

  display->setFont(&asm_10x6b);
  display->setTextColor(home_col);
  display->setCursor(45, 9);
  display->print (tempH);
}

void TempStreet() {
  sensor.requestTemp();
  if (sensor.readTemp()) FtempS = sensor.getTemp() + o.cor_tempS;
  tempS = FtempS;
  Serial.print F("Улица: ");  Serial.println(FtempS);

  display->setFont(&asm_6x5);
  display->setTextColor(text_col);
  display->setCursor(1, 7);
  display->print ("ul");

  display->setFont(&asm_10x6b);
  display->setTextColor(home_col);
  display->setCursor(12, 9);
  display->print (tempS);
}

void Hum() {
  //hum = bmp.readHumidity();
  hum = 47;
  //Serial.print F("Влажность: ");  Serial.println(hum);

  display->setFont(&asm_6x5);
  display->setTextColor(text_col);
  display->setCursor(1, 7);
  display->print ("vl");

  display->setFont(&asm_10x6b);
  display->setTextColor(home_col);
  display->setCursor(12, 9);
  display->print (hum);
}

void Press() {
  Fpres = (pressureToMmHg(bmp.readPressure())) + o.cor_pres;
  //Serial.print F("Давление: ");  Serial.println(Fpres);
  pres = Fpres;

  display->setFont(&asm_6x5);
  display->setTextColor(text_col);
  display->setCursor(28, 7);
  display->print ("dav");

  display->setFont(&asm_10x6b);
  display->setTextColor(home_col);
  display->setCursor(43, 9);
  display->print (pres);
}
