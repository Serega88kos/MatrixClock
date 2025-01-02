static gh::Timer sens(30000);
void ReadSens() {
  if (sens) {
    FtempH = bmp.readTemperature() + m.cor_tempH;
    if (o.mode_udp == 0) {
      ds.requestTemp();
      if (ds.readTemp()) FtempS = ds.getTemp() + m.cor_tempS;
    }
    Fpres = pressureToMmHg(bmp.readPressure()) + m.cor_pres;
    if (o.sens_bme) hum = bmp.readHumidity() + m.cor_hum;
    if (o.mode_udp == 1) readUDP();
    if (o.mode_udp == 2) sendUDP();
  }
}

void TempHome() {
  tempH = FtempH;
  //Serial.println((String) "Дом: " + FtempH);
  display->setFont(&asm_6x5);
  if (!flag_night) display->setTextColor(ColorTable[col.text]);
  display->setCursor(28, 9);
  display->print("dom");
  display->setFont(&asm_10x6);
  if (!flag_night) display->setTextColor(ColorTable[col.home]);
  display->setCursor(45, 9);
  display->print(tempH);
}

void TempStreet() {
  tempS = FtempS;
  //Serial.print F("Улица: "); Serial.println(FtempS);
  display->setFont(&asm_6x5);
  if (!flag_night) display->setTextColor(ColorTable[col.text]);
  display->setCursor(1, 9);
  display->print("ul");
  display->setFont(&asm_10x6);
  if (!flag_night) display->setTextColor(ColorTable[col.street]);
  display->setCursor(12, 9);
  display->print(tempS);
}

void Press() {
  //Serial.println((String) "Давление: " + Fpres);
  pres = Fpres;
  display->setFont(&asm_6x5);
  if (!flag_night) display->setTextColor(ColorTable[col.text]);
  display->setCursor(28, 9);
  display->print("dav");
  display->setFont(&asm_10x6);
  if (!flag_night) display->setTextColor(ColorTable[col.press]);
  display->setCursor(43, 9);
  display->print(pres);
}

void Hum() {
  if (o.sens_bme) {
    //Serial.print F("Влажность: "); Serial.println(hum);
    display->setFont(&asm_6x5);
    if (!flag_night) display->setTextColor(ColorTable[col.text]);
    display->setCursor(1, 9);
    display->print("vl");
    display->setFont(&asm_10x6);
    if (!flag_night) display->setTextColor(ColorTable[col.hum]);
    display->setCursor(12, 9);
    display->print(hum);
  }
}
