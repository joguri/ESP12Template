// --------------------------------------
// i2c_scanner
//
// Version 1
//    This program (or code that looks like it)
//    can be found in many places.
//    For example on the Arduino.cc forum.
//    The original author is not know.
// Version 2, Juni 2012, Using Arduino 1.0.1
//     Adapted to be as simple as possible by Arduino.cc user Krodal
// Version 3, Feb 26  2013
//    V3 by louarnold
// Version 4, March 3, 2013, Using Arduino 1.0.3
//    by Arduino.cc user Krodal.
//    Changes by louarnold removed.
//    Scanning addresses changed from 0...127 to 1...119,
//    according to the i2c scanner by Nick Gammon
//    https://www.gammon.com.au/forum/?id=10896
// Version 5, March 28, 2013
//    As version 4, but address scans now to 127.
//    A sensor seems to use address 120.
// Version 6, November 27, 2015.
//    Added waiting for the Leonardo serial communication.
//
//
// This sketch tests the standard 7-bit addresses
// Devices with higher bit address might not be seen properly.
//
#include <Arduino.h>
#include "OTALib.h"
#include "CommonTools.h"

void blinkLED(int count);

void setup()
{
    Serial.begin(115200);
    Serial.println("Setup Starting...");

    pinMode(LED_BUILTIN, OUTPUT);
    blinkLED(3);

    OTAsetup("ESP12B1", "Iwiwaomw17");
    Serial.println("OTA Setup is Finished");
}


int cnt = 0;

void loop()
{
    Serial.println("Looping... Version 1.4");

    String countStr = "Count: ";
    cnt += 1;

    Serial.println("Scanning..." + cnt);
    // printTitle("Loopin...");
    blinkLED(5);

    delay(2000); // Wait 5 seconds for next scan

    OTAloop();
}

void blinkLED(int count)
{
    for (int i = 0; i < count; ++i)
    {
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
    }
    delay(1000);
}

void loopLEDScan()
{
    int nDevices = 0;
    for (byte address = 1; address < 127; ++address)
    {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        byte error = Wire.endTransmission();

        if (error == 0)
        {
            Serial.print("I2C device found at address 0x");
            if (address < 16)
            {
                Serial.print("0");
            }
            Serial.print(address, HEX);
            Serial.println("  !");

            ++nDevices;
        }
        else if (error == 4)
        {
            Serial.print("Unknown error at address 0x");
            if (address < 16)
            {
                Serial.print("0");
            }
            Serial.println(address, HEX);
        }
    }
    if (nDevices == 0)
    {
        Serial.println("No I2C devices found :( \n");
    }
    else
    {
        Serial.println("done :) \n");
    }
}
