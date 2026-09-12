#include <Arduino.h>

// ========================
// IR SENSOR PIN DEFINITIONS
// ========================

#define IR_LEFT 32  // Digital input
#define IR_RIGHT 34 // Digital input

// ========================
// SETUP FUNCTION
// ========================

void setup()
{
    Serial.begin(115200);
    delay(1000); // Give serial monitor time to connect

    Serial.println("\n\n=== IR SENSOR DIGITAL READ TEST ===");
    Serial.println("Left Sensor:  GPIO32");
    Serial.println("Right Sensor: GPIO34");
    Serial.println("====================================\n");

    // Configure sensor pins as inputs
    pinMode(IR_LEFT, INPUT);
    pinMode(IR_RIGHT, INPUT);

    Serial.println("Sensors initialized. Reading digital values...\n");
}

// ========================
// MAIN LOOP
// ========================

void loop()
{
    int leftSensor = digitalRead(IR_LEFT);
    int rightSensor = digitalRead(IR_RIGHT);

    Serial.print("Left: ");
    Serial.print(leftSensor);
    Serial.print(" | Right: ");
    Serial.println(rightSensor);

    delay(300); // Update every 300ms
}
