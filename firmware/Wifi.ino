void wifi_connected() {
  WiFi.mode(WIFI_STA);
  byte tries = 30;
  WiFi.begin(c.ssid, c.pass);
  while (--tries && WiFi.status() != WL_CONNECTED) {
    Serial.print F(".");
    display->setFont(&asm_10x6);
    display->setTextWrap(false);
    display->setTextColor(ColorTable[col.text]);
    display->setCursor(24, 21);
    display->print(tries);
    delay(1000);
    display->fillScreen(black);
  }
  if (WiFi.status() != WL_CONNECTED) {  // Если не удалось подключиться запускаем в режиме AP
    IPAddress apIP(192, 168, 4, 1);
    IPAddress subnet(255, 255, 255, 0);
    Serial.println F("");
    Serial.print F("WiFi up ACCESS POINT: ");
    Serial.println(ssidAP);
    Serial.print F("Start Settings IP: ");
    Serial.println(apIP);
    WiFi.disconnect();                      // Отключаем WIFI
    WiFi.mode(WIFI_AP);                     // Меняем режим на режим точки доступа
    WiFi.softAPConfig(apIP, apIP, subnet);  // Задаем настройки сети
    WiFi.softAP(ssidAP, passAP);            // Включаем WIFI в режиме точки доступа с именем и паролем
    hub.onBuild(build);                     // подключаем билдер
    hub.begin();                            // запускаем систему
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println F("");
    Serial.println F("WiFi запущен");
    Serial.print("IP адрес: ");
    Serial.println(WiFi.localIP());
    if (o.mode_udp != 0) udp.begin(localPort);
    display->setFont(&asm_6x5);
    display->setCursor(4, 21);
    display->print(WiFi.localIP());
    delay(2000);
    display->fillScreen(black);
    ntp.setGMT(c.gmt);
    ntp.setHost(c.host);
    ntp.begin();
    ntp.updateNow();
    if (ntp.getUnix() > 1735397200) {
      ntp.updateNow();
      display->setCursor(20, 20);
      display->setTextColor(GREEN);
      display->print("NTP_OK");
      delay(2000);
      display->fillScreen(black);
    }
    if (ntp.getUnix() < 1735397200) {
      display->setCursor(20, 20);
      display->setTextColor(RED);
      display->print("NO_NTP");
      delay(2000);
      ESP.restart();
    }
    hub.onBuild(build);  // подключаем билдер
    hub.begin();         // запускаем систему
  }
}