#include <Arduino.h>
#include "CommonTools.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

String oled_titleString;
uint16_t oled_lineCount = 0;

void initDisplay()
{
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_EXTERNALVCC, 0x3C))
    { // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
    }

    display.display();
    delay(2000); // Pause for 2 seconds

    // Clear the buffer
    display.clearDisplay();
}

void printTitle(String title)
{
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0, 0);             // Start at top-left corner
    display.println(title);
    display.display();
    display.setTextSize(1);
    oled_lineCount = 0;
    oled_titleString = title;
}

void printLine(String line)
{
    oled_lineCount += 1;
    if (oled_lineCount > 6)
    {
        printClear();
        printTitle(oled_titleString);
    }
    display.setTextSize(1);
    display.println(line);
    display.display();
}

void printClear()
{
    display.clearDisplay();
    display.setCursor(0, 0);
}

void WireSetup(uint16_t sda, uint16_t sclk, uint32_t freq)
{
    Wire.begin(sda, sclk);
    Wire.setClock(freq);
    pinMode(sda, INPUT_PULLUP);
    pinMode(sclk, INPUT_PULLUP);
}

void WireSetup(uint16_t sda, uint16_t sclk)
{
    WireSetup(sda, sclk, 400000U);
}

String WIFIsetup(const char *ssid, const char *pass)
{
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    return WiFi.localIP().toString();
}

int setMdnsHostname(const char *hostName)
{
    return MDNS.begin(hostName);
}