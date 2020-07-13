#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

void OTAsetup(const char *deviceName, const char *devicePassword);
void OTAloop();