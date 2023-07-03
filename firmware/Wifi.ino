void wifi_connected() {
  WiFi.mode(WIFI_STA);
  byte tries = 60;
  WiFi.begin(w.ssid, w.pass);
  while (--tries && WiFi.status() != WL_CONNECTED) {
    Serial.print F(".");
    display->setFont(&asm_10x6b);
    display->setTextWrap(false);
    display->setTextColor(home_col);
    display->setCursor(24, 21);
    display->print (tries);
    delay (1000);
    display->fillScreen(black);
  }
  if (WiFi.status() != WL_CONNECTED)
  {
    // Если не удалось подключиться запускаем в режиме AP
    IPAddress apIP(192, 168, 4, 1);
    IPAddress subnet(255, 255, 255, 0);
    Serial.println F("");
    Serial.print F("WiFi up ACCESS POINT: ");
    Serial.println (ssidAP);
    Serial.print F("Start Settings IP: ");
    Serial.println (apIP);
    // Отключаем WIFI
    WiFi.disconnect();
    // Меняем режим на режим точки доступа
    WiFi.mode(WIFI_AP);
    // Задаем настройки сети
    WiFi.softAPConfig(apIP, apIP, subnet);
    // Включаем WIFI в режиме точки доступа с именем и паролем
    // хранящихся в переменных _ssidAP _passwordAP
    WiFi.softAP(ssidAP, passAP);
    hub.onBuild(build);     // подключаем билдер
    hub.begin();            // запускаем систему
  }
  else {
    Serial.println F("");
    Serial.println F("WiFi запущен");
    Serial.print("IP адрес: ");
    Serial.println(WiFi.localIP());
    display->setFont(&asm_6x5);
    display->setCursor(4, 21);
    display->print (WiFi.localIP());
    delay (5000);
    display->fillScreen(black);
    ntp.setGMT(c.gmt);
    ntp.setHost(c.host);
    ntp.begin();
    ntp.updateNow();
    hub.onBuild(build);     // подключаем билдер
    hub.begin();            // запускаем систему
  }
}
