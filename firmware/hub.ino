void build(gh::Builder& b) {

  {
    GH::Row r(b);
    b.Tabs(&tab).text("Часы;Датчики;Мониторинг").noLabel().click();
    if (b.changed()) b.refresh();
  }

  switch (tab) {
    case 0:
      {
        bool flag_c = 0;
        b.Title(F("Настройки WiFi")).fontSize(20);
        {
          gh::Row r(b);
          b.Input(c.ssid).label("SSID").attach(&flag_c);
          b.Pass(c.pass).label("PASS").attach(&flag_c);
        }
        {
          gh::Row r(b);
          b.Input_("host", c.host).label("Сервер NTP").size(4).attach(&flag_c);
          b.Input_("gmt", &c.gmt).label("GMT зона").size(1).attach(&flag_c);
        }
        if (flag_c) {
          _clock.update();
        }

        bool flag_sync = 0;
        b.Title(F("Настройки времени")).fontSize(20);
        {
          gh::Row r(b);
          b.Label_("n1", ntp.timeString()).noLabel().fontSize(20).size(3);
          b.Label_("n2", ntp.dateString()).noLabel().fontSize(20).size(3);
          b.Button_("btnn").icon("f0e2").noLabel().size(1).fontSize(20).attach(&flag_sync);
        }
        if (flag_sync) {
          ntp.updateNow();
        }
      }
      break;

    case 1:
      {
        b.Title(F("Различные настройки")).fontSize(20);

        bool flag_o = 0;

        {
          gh::Row r(b);
          b.SwitchIcon(&o.sens_bme).label("Датчик BME").fontSize(15).attach(&flag_o);
          b.Spinner(&o.interval).label("Смена показаний, сек").fontSize(15).range(2, 60, 1).attach(&flag_o);
          b.SwitchIcon(&o.auto_bright).label("Автояркость").fontSize(15).attach(&flag_o);
          b.SwitchIcon(&o.min_max).label("Инверсия яркости").fontSize(15).attach(&flag_o);
        }
        b.Title(F("Выбор цвета")).fontSize(20);

        bool flag_color = 0;
        {
          gh::Row r(b);
          b.Color(&col.clock).label("Часы").attach(&flag_color);
          b.Color(&col.text).label("Текст").attach(&flag_color);
          b.Color(&col.home).label("Дом. темп.").attach(&flag_color);
          b.Color(&col.street).label("Ул. темп.").attach(&flag_color);
          b.Color(&col.press).label("Давление").attach(&flag_color);
          b.Color(&col.hum).label("Влажность").attach(&flag_color);
        }
        if (flag_color) {
          /*
          clock_col = display->color565(col.color_clock.r, col.color_clock.g, col.color_clock.b);      // часы
          text_col = display->color565(col.color_text.r, col.color_text.g, col.color_text.b);          // текст
          home_col = display->color565(col.color_home.r, col.color_home.g, col.color_home.b);          // дом темп-ра
          street_col = display->color565(col.color_street.r, col.color_street.g, col.color_street.b);  // уличная темп-ра
          press_col = display->color565(col.color_press.r, col.color_press.g, col.color_press.b);      // давление
          hum_col = display->color565(col.color_hum.r, col.color_hum.g, col.color_hum.b);              // влажность
*/
          _color.update();
        }

        b.Title(F("Яркость")).fontSize(20);

        {
          gh::Row r(b);
          b.Label_("new_bright", String(new_bright)).label("Текущая").fontSize(18);
          b.Spinner(&o.min_bright).label("Минимальная").range(0, o.max_bright - 1, 1).fontSize(18).attach(&flag_o);
          b.Spinner(&o.max_bright).label("Максимальная").range(o.min_bright + 1, 255, 1).fontSize(18).attach(&flag_o);
          b.Spinner(&o.brg).label("Задержка, в сек.").range(0, 30, 1).fontSize(18).attach(&flag_o);
        }

        b.Title(F("Корректировка показаний")).fontSize(20);

        {
          gh::Row r(b);
          b.Label(String(FtempH)).label("Комнатная").fontSize(18).unit("deg");
          b.Spinner(&o.cor_tempH).label(" ").range(-9, 9, 0.1, 1).fontSize(18).attach(&flag_o);
          b.Label(String(pres)).label("Давление").fontSize(18);
          b.Spinner(&o.cor_pres).label(" ").range(-9, 9, 1).fontSize(18).attach(&flag_o);
        }

        {
          gh::Row r(b);
          b.Label(String(FtempS)).label("Уличная").fontSize(18);
          b.Spinner(&o.cor_tempS).label(" ").range(-9, 9, 0.1, 1).fontSize(18).attach(&flag_o);
          b.Label(String(hum)).label("Влажность").fontSize(18);
          b.Spinner(&o.cor_hum).label(" ").range(-9, 9, 1).fontSize(18).attach(&flag_o);
        }
        if (flag_o) {
          _other.update();
        }
      }
      break;

    case 2:
      {
        {
          gh::Row r(b);
          b.HTML("<a href='https://narodmon.ru/?invite=asm'>Народный мониторинг</a>").noLabel().fontSize(18);
          b.Label(WiFi.macAddress()).noLabel().fontSize(18);
        }
        bool flag_monitor = 0;
        {
          gh::Row r(b);
          b.SwitchIcon(&m.nm_enable).label("Включить").fontSize(15).attach(&flag_monitor);
          b.Input(&m.nm_delay).label("Интервал, в сек.").attach(&flag_monitor);
          b.SwitchIcon(&m.nm_tempH).label("Комнатная").fontSize(15).attach(&flag_monitor);
          b.SwitchIcon(&m.nm_tempS).label("Уличная").fontSize(15).attach(&flag_monitor);
          b.SwitchIcon(&m.nm_pres).label("Давление").fontSize(15).attach(&flag_monitor);
          b.SwitchIcon(&m.nm_hum).label("Влажность").fontSize(15).attach(&flag_monitor);
        }
        if (flag_monitor) {
          _narod.update();
        }
      }
      break;
  }
}
