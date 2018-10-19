#include "StatusBar.h"

using namespace Codingfield::UI;

#include "ressources/wifi_full.xbm"
#include "ressources/wifi_medium.xbm"
#include "ressources/wifi_weak.xbm"
#include "ressources/wifi_none.xbm"
#include "ressources/wifi_off.xbm"
#include "ressources/wifi_warn.xbm"
#include "ressources/wifi_warn_filled.xbm"


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

    const uint8_t* wifibmp;
    switch(wifiStatus) {
      case WifiStatuses::Weak: wifibmp = wifi_weak_bits; break;
      case WifiStatuses::Medium: wifibmp = wifi_medium_bits; break;
      case WifiStatuses::Full: wifibmp = wifi_full_bits; break;
      case WifiStatuses::Warning: wifibmp = wifi_warn_bits; break;
      case WifiStatuses::WarningFilled: wifibmp = wifi_warn_filled_bits; break;
      case WifiStatuses::Off: wifibmp = wifi_off_bits; break;
      default:
      case WifiStatuses::No_signal:
        wifibmp = wifi_none_bits;
        break;
    }
    M5.Lcd.drawXBitmap(295,0, wifibmp, 25,25, BLACK);
  }
  isUpdated = false;
}
