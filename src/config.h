#include <FS.h>
#include <ArduinoJson.h>

bool loadWiFiConfig();

void saveWifiConfig(String ssid, String password);

String getSsid();

String getPassword();