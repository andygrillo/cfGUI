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
    oldWifiStatus = wifiStatus;
    wifiStatus = status;
  }
}

void StatusBar::SetUptime(const uint32_t t) {
  if(uptime != t) {
    oldUptime = uptime;
    uptime = t;
  }
}

void StatusBar::SetDateTime(const std::string& t) {
  if(dateTime != t) {
    oldDateTime = dateTime;
    dateTime = t;
  }
}

void StatusBar::Draw() {
  if(IsHidden()) return;
  bool wasInvalidated = isInvalidated;
  Bar::Draw();

  if(wasInvalidated || (wifiStatus != oldWifiStatus)) {
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
    oldWifiStatus = wifiStatus;
  }

  if(wasInvalidated || (oldDateTime != dateTime)) {
    M5.Lcd.setTextDatum(TC_DATUM);

    M5.Lcd.setTextColor(color);
    M5.Lcd.drawString(oldDateTime.c_str(), 160, 5);

    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.drawString(dateTime.c_str(), 160, 5);

    oldDateTime = dateTime;
  }

  if(wasInvalidated || (oldUptime != uptime)) {
    char uptime_printed[16];
    const char* uptime_print_format = "UP: %ih";
    M5.Lcd.setTextDatum(TL_DATUM);

    M5.Lcd.setTextColor(color);
    snprintf(uptime_printed, sizeof(uptime_printed), uptime_print_format, oldUptime);
    M5.Lcd.drawString(uptime_printed, 1, 5);

    M5.Lcd.setTextColor(BLACK);
    snprintf(uptime_printed, sizeof(uptime_printed), uptime_print_format, uptime);
    M5.Lcd.drawString(uptime_printed, 1, 5);

    oldUptime = uptime;
  }
  isInvalidated = false;
}
