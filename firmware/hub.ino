void build(gh::Builder& b) {
  {
    GH::Row r(b);
    b.Tabs(&tab).text(F("WiFi;Настройки;Мониторинг")).noLabel().click();
    if (b.changed()) b.refresh();
  }
  switch (tab) {
    case 0:
      {
        bool flag_c = 0;
        b.Title(F("Настройки WiFi")).fontSize(20);
        {
          gh::Row r(b);
          b.Input(c.ssid).label(F("SSID")).attach(&flag_c);
          b.Pass(c.pass).label(F("PASS")).attach(&flag_c);
        }
        {
          gh::Row r(b);
          b.Input_("host", c.host).label(F("Сервер NTP")).size(4).attach(&flag_c);
          b.Input_("gmt", &c.gmt).label(F("GMT зона")).size(1).attach(&flag_c);
        }
        if (flag_c) {
          _clock.update();
        }
      }
      break;

    case 1:
      {
        bool flag_sync = 0;
        {
          gh::Row r(b);
          b.Label_("time", ntp.toString()).noLabel().fontSize(20).size(4);
          b.Button_("btnn").icon("f0e2").noLabel().size(1).fontSize(20).attach(&flag_sync);
        }
        if (flag_sync) {
          ntp.updateNow();
        }
        bool flag_o = 0;
        {
          gh::Row r(b);
          b.SwitchIcon(&o.sens_bme).label(F("Датчик BME")).fontSize(15).attach(&flag_o);
          b.Spinner(&o.interval).label(F("Смена показаний, сек")).fontSize(15).range(2, 60, 1).attach(&flag_o);
          b.Select(&o.mode_udp).text(F("Выключены;Прием;Отправка")).label(F("Показания DS по UDP")).attach(&flag_o);
          b.SwitchIcon(&o.new_god).label(F("Новый год!")).fontSize(15).attach(&flag_o);
        }

        b.Title(F("Выбор цвета")).fontSize(20);
        bool flag_color = 0;
        {
          gh::Row r(b);
          b.Select(&col.clock).text(F("BLUE;RED;GREEN;CYAN;ROSE;YELLOW;WHITE;GRAY")).label(F("Часы")).attach(&flag_color);
          b.Select(&col.text).text(F("BLUE;RED;GREEN;CYAN;ROSE;YELLOW;WHITE;GRAY")).label(F("Текст")).attach(&flag_color);
          b.Select(&col.home).text(F("BLUE;RED;GREEN;CYAN;ROSE;YELLOW;WHITE;GRAY")).label(F("Дом. темп.")).attach(&flag_color);
          b.Select(&col.street).text(F("BLUE;RED;GREEN;CYAN;ROSE;YELLOW;WHITE;GRAY")).label(F("Ул. темп.")).attach(&flag_color);
          b.Select(&col.press).text(F("BLUE;RED;GREEN;CYAN;ROSE;YELLOW;WHITE;GRAY")).label(F("Давление")).attach(&flag_color);
          if (o.sens_bme) b.Select(&col.hum).text(F("BLUE;RED;GREEN;CYAN;ROSE;YELLOW;WHITE;GRAY")).label(F("Влажность")).attach(&flag_color);
        }
        if (flag_color) {
          _color.update();
          b.refresh();
        }
        b.Title(F("Яркость")).fontSize(20);
        {
          gh::Row r(b);
          b.SwitchIcon(&o.auto_bright).label(F("Автояркость")).fontSize(15).attach(&flag_o);
          b.SwitchIcon(&o.min_max).label(F("Инверсия яркости")).fontSize(15).attach(&flag_o);
          b.Label_("new_bright", String(new_bright)).label(F("Текущая")).fontSize(18);
        }
        {
          gh::Row r(b);
          b.Spinner(&o.min_bright).label(F("Минимальная")).range(0, o.max_bright - 1, 1).fontSize(18).attach(&flag_o);
          b.Spinner(&o.max_bright).label(F("Максимальная")).range(o.min_bright + 1, 255, 1).fontSize(18).attach(&flag_o);
          b.Spinner(&o.brg).label(F("Задержка, в сек.")).range(0, 30, 1).fontSize(18).attach(&flag_o);
        }
        b.Title(F("Ночной режим")).fontSize(20);
        {
          gh::Row r(b);
          if (o.night_mode) b.SwitchIcon(&o.night_mode).label(F("Включен")).fontSize(15).attach(&flag_o);
          if (!o.night_mode) b.SwitchIcon(&o.night_mode).label(F("Выключен")).fontSize(15).attach(&flag_o);
          b.Spinner(&o.night_brg).label(F("Яркость")).range(0, 20, 1).fontSize(15).attach(&flag_o);
        }
        {
          gh::Row r(b);
          b.Select(&o.start_night).text(F("0;1;2;3;4;5;6;7;8;9;10;11;12;13;14;15;16;17;18;19;20;21;22;23")).label(F("Включить в")).fontSize(20).attach(&flag_o);
          b.Select(&o.stop_night).text(F("0;1;2;3;4;5;6;7;8;9;10;11;12;13;14;15;16;17;18;19;20;21;22;23")).label(F("Выключить в")).fontSize(20).attach(&flag_o);
          b.Select(&o.night_color).text(F("BLUE;FIOLET")).label(F("Цвет дисплея")).attach(&flag_o);
        }
        if (flag_o) {
          _other.update();
          b.refresh();
        }
      }
      break;

    case 2:
      {
        bool flag_monitor = 0;
        {
          gh::Row r(b);
          if (m.nm_enable) b.SwitchIcon(&m.nm_enable).label(F("Включен")).fontSize(15).size(1).attach(&flag_monitor);
          if (!m.nm_enable) b.SwitchIcon(&m.nm_enable).label(F("Выключен")).fontSize(15).size(1).attach(&flag_monitor);
          b.HTML(F("<a href='https://narodmon.ru/?invite=asm'>narodmon.ru</a>")).noLabel().fontSize(15).size(2);
          b.Input(&m.nm_delay).label(F("Интервал, в сек.")).size(1).attach(&flag_monitor);
        }
        {
          gh::Row r(b);
          b.SwitchIcon(&m.nm_tempH).label(F("Комнатная")).fontSize(15).attach(&flag_monitor);
          b.SwitchIcon(&m.nm_tempS).label(F("Уличная")).fontSize(15).attach(&flag_monitor);
          b.SwitchIcon(&m.nm_pres).label(F("Давление")).fontSize(15).attach(&flag_monitor);
          b.SwitchIcon(&m.nm_hum).label(F("Влажность")).fontSize(15).attach(&flag_monitor);
        }
        b.Title(F("Корректировка показаний")).fontSize(20);
        {
          gh::Row r(b);
          b.Label_("FtempH", String(FtempH)).label(F("Комнатная")).fontSize(20).unit("deg");
          b.Spinner(&m.cor_tempH).noLabel().range(-9, 9, 0.1, 1).fontSize(15).attach(&flag_monitor);
          b.Label_("pres", String(pres)).label(F("Давление")).fontSize(20);
          b.Spinner(&m.cor_pres).noLabel().range(-9, 9, 1).fontSize(15).attach(&flag_monitor);
        }
        {
          gh::Row r(b);
          b.Label_("FtempS", String(FtempS)).label(F("Уличная")).fontSize(20);
          b.Spinner(&m.cor_tempS).noLabel().range(-9, 9, 0.1, 1).fontSize(15).attach(&flag_monitor);
          b.Label_("hum", String(hum)).label(F("Влажность")).fontSize(20);
          b.Spinner(&m.cor_hum).noLabel().range(-9, 9, 1).fontSize(15).attach(&flag_monitor);
        }
        if (flag_monitor) {
          _narod.update();
          b.refresh();
        }
      }
      break;
  }
}
