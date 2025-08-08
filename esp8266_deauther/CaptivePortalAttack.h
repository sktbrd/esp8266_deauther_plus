#pragma once
#include <Arduino.h>

namespace CaptivePortalAttack {
  void start(const String& ssid, bool open_ap = true, const String& pass = "");
  void stop();
  void loop();
  bool running();
}
