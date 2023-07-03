
void build() {
  hub.BeginWidgets();
  hub.WidgetSize(100);
  if (hub.Tabs(&tab, F("Часы,Датчики,Мониторинг"), GH_NO_LABEL)) {
    hub.refresh();  // обновить страницу
  }

  switch (tab) {
    case 0:
      {
        hub.Title(F("Настройки WiFi"));
        hub.WidgetSize(100);
        bool flag_w = 0;
        flag_w |= hub.Input(&w.ssid, GH_CSTR, F("SSID"), 32);
        flag_w |= hub.Pass(&w.pass, GH_CSTR, F("PASS"), 32);
        if (flag_w) {
          mem1.updateNow();
          ESP.restart();
        }
        bool flag_c = 0;
        bool flag_sync = 0;
        hub.Title(F("Настройки времени"));
        hub.WidgetSize(45);
        hub.Label_(F("n1"), String(ntp.timeString()), GH_NO_LABEL, GH_DEFAULT, 20);
        hub.Label(String(ntp.dateString()), GH_NO_LABEL, GH_DEFAULT, 20);
        hub.WidgetSize(10);
        flag_sync |= hub.ButtonIcon(0, F(""), GH_DEFAULT, 20);
        if (flag_sync) {
          ntp.updateNow();
        }
        hub.WidgetSize(70);
        flag_c |= hub.Input(&c.host, GH_CSTR, F("Сервер NTP"), 32);
        hub.WidgetSize(30);
        flag_c |= hub.Input(&c.gmt, GH_UINT16, F("GMT зона"), 3);
        if (flag_c) {
          mem2.updateNow();
        }
      }
      break;
    case 1:
      {
        hub.Title(F("Различные настройки"));
        hub.WidgetSize(33);
        bool flag_o = 0;
        flag_o |= hub.Switch(&o.sens_bme, F("Датчик BME"));
        flag_o |= hub.Switch(&o.auto_bright, F("Автояркость"));
        flag_o |= hub.Switch(&o.min_max, F("Инверсия яркости"));

        hub.Title(F("Яркость"));
        hub.WidgetSize(25);
        hub.Label_(F("new_bright"), String(new_bright), F("Текущая"), GH_DEFAULT, 25);
        flag_o |= hub.Spinner(&o.min_bright, GH_FLOAT, F("Минимальная"), 0, 255, 1);
        flag_o |= hub.Spinner(&o.max_bright, GH_FLOAT, F("Максимальная"), 10, 255, 1);
        flag_o |= hub.Spinner(&o.brg, GH_FLOAT, F("Задержка, в сек."), 0, 30, 1);

        hub.Title(F("Корректировка показаний"));
        hub.WidgetSize(25);
        hub.Label(String(FtempH), F("Комнатная"), GH_DEFAULT, 25);
        flag_o |= hub.Spinner(&o.cor_tempH, GH_FLOAT, GH_NO_LABEL, -9, 9, 0.1);
        hub.Label(String(FtempS), F("Уличная"), GH_DEFAULT, 25);
        flag_o |= hub.Spinner(&o.cor_tempS, GH_FLOAT, GH_NO_LABEL, -9, 9, 0.1);
        hub.WidgetSize(25);
        hub.Label(String(pres), F("Давление"), GH_DEFAULT, 25);
        flag_o |= hub.Spinner(&o.cor_pres, GH_FLOAT, GH_NO_LABEL, -9, 9, 1);
        hub.Label(String(hum), F("Влажность"), GH_DEFAULT, 25);
        flag_o |= hub.Spinner(&o.cor_hum, GH_FLOAT, GH_NO_LABEL, -9, 9, 1);
        if (flag_o) {
          mem3.updateNow();
        }
      }
      break;
    case 2:
      {
        hub.EndWidgets();
        hub.HTML(String("<a href=\"https://narodmon.ru/?invite=asm\">Народный мониторинг</a>&nbsp;&nbsp;" + WiFi.macAddress()), F("ссылка"));
        hub.BeginWidgets();
        hub.WidgetSize(50);
        bool flag_m = 0;
        flag_m |= hub.Switch(&m.Monitoring, F("Включить"));
        flag_m |= hub.Input(&m.delay_narod, GH_UINT16, F("Интервал, в сек."), 20);
        hub.WidgetSize(25);
        flag_m |= hub.Switch(&m.nm_tempH, F("Комнатная"));
        flag_m |= hub.Switch(&m.nm_tempS, F("Уличная"));
        flag_m |= hub.Switch(&m.nm_pres, F("Давление"));
        flag_m |= hub.Switch(&m.nm_hum, F("Влажность"));
        if (flag_m) {
          mem4.updateNow();
        }
      }
      break;
  }
  hub.EndWidgets();

  // M_TR(GP.LABEL(""), GP.LABEL(ntp.timeString()); GP.LABEL(ntp.dateString()); , GP.ICON_BUTTON("sync", "refresh")););
}
