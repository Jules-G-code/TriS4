
#include <Arduino.h>
#include "rgb_lcd.h"
#include <ESP32Encoder.h>
#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include <ESP32Servo.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_TCS34725 tcs;

void setup()
{
    Serial.begin(115200);
    Wire.begin(21, 22); // SDA sur 21, SCL sur 22

    if (tcs.begin()) {
        Serial.println("Capteur TCS34725 trouvé");
    } else {
        Serial.println("Aucun TCS34725 trouvé ... vérifiez vos connexions");
        while (1); // Arrêt
    }
}

void loop()
{
    uint16_t r, g, b, c;

    tcs.getRawData(&r, &g, &b, &c);

    Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
    Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
    Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
    Serial.print("C: "); Serial.print(c, DEC); Serial.println(" ");

    delay(1000);
}
