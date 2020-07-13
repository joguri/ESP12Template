#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <Wire.h>

// TotalGym Import ... begin
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET 4 // Reset pin # (or -1 if sharing Arduino reset pin)

void initDisplay();
void printTitle(String title);
void printLine(String line);
void printClear();

// Wire Setup
void WireSetup(uint16_t sda, uint16_t sclk, uint32_t freq);
void WireSetup(uint16_t sda, uint16_t sclk);

// WiFi Setup
String WIFIsetup(const char *ssid, const char *pass);

// MDNS Setup
int setMdnsHostname(const char *hostName);