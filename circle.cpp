#include "Watchy_circle.h"

#define DARKMODE false
const uint8_t* tagx[] = { xsun, xmon, xtue, xwed, xthu, xfri, xsat, xsun };
const uint8_t* monx[] = { xjan, xfeb, xmar, xapr, xmay, xjun, xjul, xaug, xsep, xoct, xnov, xdec };

void Watchycircle::drawWatchFace(){
//time adjustment start
    //if you don't need a time adjustment, just delete all lines between time adjustment start and end
    //my watchy runs too fast (15 seconds and 500 ms a day), this code set back time each day by 15 seconds and 500 ms
    
	if (currentTime.Hour == 00 && currentTime.Minute == 30){
        
        RTC.read(currentTime);
        int8_t sekunde = currentTime.Second;
        int8_t minute = currentTime.Minute;
        int8_t hour = currentTime.Hour;
        int8_t day = currentTime.Day;
        int8_t month = currentTime.Month;
        int8_t year = tmYearToY2k(currentTime.Year);

        delay(15500);

        tmElements_t tm;
        tm.Month = month;
        tm.Day = day;
        tm.Year = y2kYearToTm(year);
        tm.Hour = hour;
        tm.Minute = minute ;
        tm.Second = sekunde;

        RTC.set(tm);     
         }

    // time adjustment end
        
    display.fillScreen(DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    display.setTextColor(DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);

    int WTag, n;
    int16_t  x, y, xc, yc;
    uint16_t wc, hc;
    float radi = 0.0174532925;
    float m = currentTime.Minute;
    float h = currentTime.Hour;
    float mx = m*6;
    float mp = (m + 5) * 6;
    float hx = (h + (m / 60))*30;
    float hp = (h + ((m + 30) / 60)) * 30;
    
    display.drawCircle(100, 100, 99, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
    display.drawCircle(100, 100, 73, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
    
    display.setFont(&FreeSansBold9pt7b);

    // reset step counter at midnight
    if (currentTime.Hour == 00 && currentTime.Minute == 00){
      sensor.resetStepCounter();
              //turn off radios
      WiFi.mode(WIFI_OFF);
      btStop();   
          }
          
    
    for ( n = 1; n <= 12; n++) {
        x = 100 + 86 * sin((n * 30.0 - hx) * radi);
        y = 112 - 86 * cos((n * 30.0 - hx) * radi);
        display.getTextBounds(String(n), 100, 100, &xc, &yc, &wc, &hc);
        display.setCursor(x - wc / 2, y - hc / 2);
        display.println(n);
        x = 100 + 86 * sin((n * 30.0 - hp) * radi);
        y = 100 - 86 * cos((n * 30.0 - hp) * radi);
        display.drawCircle(x, y, 2, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);

    }

    display.drawCircle(100, 100, 46, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
    
    for (int n = 0; n < 60; n = n + 10) {
        x = 100 + 58 * sin((n * 6 - mx) * radi);
        y = 112 - 58 * cos((n * 6 - mx) * radi);
        display.getTextBounds(String(n), 100, 100, &xc, &yc, &wc, &hc);
        display.setCursor(x - wc / 2, y - hc / 2);
        display.println(n);
        x = 100 + 58 * sin((n * 30 - mp) * radi);
        y = 100 - 58 * cos((n * 30 - mp) * radi);
        display.drawCircle(x, y, 2, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
      
    }

    display.writeFastVLine(100, 1, 54, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);

    
    display.setTextColor(DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
    display.setCursor(5, 15);
    WTag = currentTime.Day;
    WTag = WTag / 10;
    display.println(WTag);
    WTag = currentTime.Day - (WTag * 10);
    display.setCursor(185, 15);
    display.println(WTag);

    display.getTextBounds(String("Bat"), 100, 105, &xc, &yc, &wc, &hc); 
    display.setCursor(100 - wc / 2, 85 - hc / 2);
    display.println("Bat");
    float VBAT = getBatteryVoltage();
    int batLev = min<int>(100 - ((4.15 - VBAT) * 100), 100);
    batLev = max<int>(batLev, 0);
    display.getTextBounds(String(batLev), 100, 100, &xc, &yc, &wc, &hc);
    display.setCursor(100 - wc / 2, 100 - hc / 2);
    display.println(batLev);
    batLev = sensor.getCounter();
    display.getTextBounds(String("Steps"), 100, 100, &xc, &yc, &wc, &hc);
    display.setCursor(100 - wc / 2, 120 - hc / 2);
    display.println("Steps");
    display.getTextBounds(String(batLev), 100, 100, &xc, &yc, &wc, &hc); 
    display.setCursor(100 - wc / 2, 135 - hc / 2);
    display.println(batLev);

    WTag = currentTime.Wday - 1;
    display.drawBitmap(0, 156, tagx[WTag], 45, 45, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);

    WTag = currentTime.Month - 1;
    display.drawBitmap(155, 156, monx[WTag], 45, 45, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);

}