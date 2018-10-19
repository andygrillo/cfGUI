#include "StatusBar.h"

using namespace Codingfield::UI;

#include "ressources/wifi0.xbm"
#include "ressources/wifi1.xbm"
#include "ressources/wifi2.xbm"
#include "ressources/wifi3.xbm"

void StatusBar::SetWifiStatus(const StatusBar::WifiStatuses status) {
  if(wifiStatus != status) {
    wifiStatus = status;
    SetUpdateFlag();
  }
}

void StatusBar::SetUptime(const uint32_t t) {
  if(uptime != t) {
    uptime = t;
    SetUpdateFlag();
  }
}

void StatusBar::SetDateTime(const std::string& t) {
  if(dateTime != t) {
    dateTime = t;
    SetUpdateFlag();
  }
}

void StatusBar::Draw() {
  if(IsHidden()) return;
  bool oldIsUpdated = isUpdated;
  Bar::Draw();

  if(oldIsUpdated) {
    M5.Lcd.setTextColor(BLACK);

    M5.Lcd.setTextDatum(TL_DATUM);

    char uptime_printed[16];

    snprintf(uptime_printed, sizeof(uptime_printed), "UP: %ih", uptime);

    M5.Lcd.drawString(uptime_printed, 1, 5);

    M5.Lcd.setTextDatum(TC_DATUM);
    M5.Lcd.drawString(dateTime.c_str(), 160, 5);

    const uint8_t* wifibmp = wifi0_bits;
    switch(wifiStatus) {
      case WifiStatuses::Weak: wifibmp = wifi1_bits; break;
      case WifiStatuses::Medium: wifibmp = wifi2_bits; break;
      case WifiStatuses::Full: wifibmp = wifi3_bits; break;
      default:
      case WifiStatuses::No_signal:
        wifibmp = wifi0_bits;
        break;
    }
    M5.Lcd.drawXBitmap(295,0, wifibmp, 25,25, BLACK);
  }
  isUpdated = false;
}
