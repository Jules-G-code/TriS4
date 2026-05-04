
#include <Arduino.h>
#include "rgb_lcd.h"
#include <ESP32Encoder.h>
#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include <ESP32Servo.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_TCS34725 tcs;
rgb_lcd lcd;


void setup()
{
    Serial.begin(115200);
    Wire.begin(21, 22); // SDA sur 21, SCL sur 22

    pinMode(25, OUTPUT); // Bleu
    pinMode(26, OUTPUT); // Rouge
    pinMode(27, OUTPUT); // Vert

}

void loop()
{
    uint16_t r, g, b, c, color;
    tcs.getRawData(&r, &g, &b, &c);
    
    color = tcs.calculateColorTemperature_dn40(r, g, b, c);
    Serial.printf("colorTemp = %d\n", color);

    // Activation des sorties en fonction des seuils
    if (color < 100) {
        digitalWrite(25, HIGH); // Bleu
        digitalWrite(26, LOW);
        digitalWrite(27, LOW);
    } else if (color >= 1000 && color <= 2000) {
        digitalWrite(25, LOW);
        digitalWrite(26, HIGH); // Rouge
        digitalWrite(27, LOW);
    } else if (color > 5000) {
        digitalWrite(25, LOW);
        digitalWrite(26, LOW);
        digitalWrite(27, HIGH); // Vert
    } else {
        digitalWrite(25, LOW);
        digitalWrite(26, LOW);
        digitalWrite(27, LOW);
    }

    // Lire l'état des sorties
    int state25 = digitalRead(25);
    int state26 = digitalRead(26);
    int state27 = digitalRead(27);
    Serial.printf("Pin 25 (Bleu): %d, Pin 26 (Rouge): %d, Pin 27 (Vert): %d\n", state25, state26, state27);
   
    delay(400);
}




/*
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
*/