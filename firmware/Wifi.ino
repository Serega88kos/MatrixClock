void wifi_connected() {
  WiFi.mode(WIFI_STA);
  byte tries = 30;
  WiFi.begin(c.ssid, c.pass);
  while (--tries && WiFi.status() != WL_CONNECTED) {
    Serial.print F(".");
    display->setFont(&asm_10x6);
    display->setTextWrap(false);
    display->setTextColor(col.text);
    display->setCursor(24, 21);
    display->print(tries);
    delay(1000);
    display->fillScreen(col.black);
  }
  if (WiFi.status() != WL_CONNECTED) {      // Если не удалось подключиться запускаем в режиме AP
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
  } else {
    Serial.println F("");
    Serial.println F("WiFi запущен");
    Serial.print("IP адрес: ");
    Serial.println(WiFi.localIP());
    display->setFont(&asm_6x5);
    display->setCursor(4, 21);
    display->print(WiFi.localIP());
    delay(5000);
    display->fillScreen(col.black);
    ntp.setGMT(c.gmt);
    ntp.setHost(c.host);
    ntp.begin();
    ntp.updateNow();
    hub.onBuild(build);                     // подключаем билдер
    hub.begin();                            // запускаем систему
  }
}