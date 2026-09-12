#include <Arduino.h>

// === PIN DEFINITION ===
// Built-in LED on most ESP32 boards
#define LED_PIN 2 // GPIO2

void setup()
{
    Serial.begin(115200);
    delay(500);
    Serial.println("\n=== LED BLINK TEST ===");
    Serial.println("GPIO2 LED\n");

    // Set LED pin as output
    pinMode(LED_PIN, OUTPUT);
}

void loop()
{
    // Turn LED ON
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED: ON");
    delay(1000); // Wait 1 second

    // Turn LED OFF
    digitalWrite(LED_PIN, LOW);
    Serial.println("LED: OFF");
    delay(1000); // Wait 1 second
}
