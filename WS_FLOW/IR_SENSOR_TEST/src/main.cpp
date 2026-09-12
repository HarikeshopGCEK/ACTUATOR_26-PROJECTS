#include <Arduino.h>

// ========================
// IR SENSOR PIN DEFINITIONS
// ========================

#define IR_LEFT 32  // Digital input
#define IR_RIGHT 34 // Digital input

// ========================
// CONFIGURATION
// ========================

#define THRESHOLD_DIGITAL 2048 // Threshold for 12-bit ADC (0-4095)
                               // < 2048 = BLACK (line detected, LOW)
                               // > 2048 = WHITE (no line, HIGH)

// ========================
// SETUP FUNCTION
// ========================

void setup()
{
    Serial.begin(115200);
    delay(1000); // Give serial monitor time to connect

    Serial.println("\n\n=== IR SENSOR TEST (DIGITAL ONLY) ===");
    Serial.println("Black/White Surface Detection");
    Serial.println("Left Sensor:  GPIO32");
    Serial.println("Right Sensor: GPIO34");
    Serial.println("====================================\n");

    // Configure sensor pins as inputs
    pinMode(IR_LEFT, INPUT);
    pinMode(IR_RIGHT, INPUT);

    Serial.println("Sensors initialized. Starting detection...\n");
}

// ========================
// SENSOR READING FUNCTIONS
// ========================

/**
 * Read digital value from IR sensor
 * Returns: LOW (0)  = BLACK surface (line detected)
 *          HIGH (1) = WHITE surface (no line)
 */
int readIRSensorDigital(int pin)
{
    int analog = analogRead(pin);
    // LOW = line detected (black), HIGH = no line (white)
    return (analog > THRESHOLD_DIGITAL) ? HIGH : LOW;
}

/**
 * Get surface color as text
 */
const char *getSurfaceColor(int sensorValue)
{
    return (sensorValue == LOW) ? "BLACK" : "WHITE";
}

// ========================
// LINE DETECTION LOGIC
// ========================

void detectLinePosition()
{
    int leftSensor = readIRSensorDigital(IR_LEFT);
    int rightSensor = readIRSensorDigital(IR_RIGHT);

    Serial.print("Line: ");

    // Both sensors on BLACK line
    if (leftSensor == LOW && rightSensor == LOW)
    {
        Serial.println("[●●]  CENTERED - Move Forward");
    }
    // Left on line, right on white
    else if (leftSensor == LOW && rightSensor == HIGH)
    {
        Serial.println("[●○]  LEFT LINE - Turn Left");
    }
    // Right on line, left on white
    else if (leftSensor == HIGH && rightSensor == LOW)
    {
        Serial.println("[○●]  RIGHT LINE - Turn Right");
    }
    // Both on white (line lost)
    else
    {
        Serial.println("[○○]  NO LINE - Search");
    }
}

// ========================
// MAIN LOOP
// ========================

void loop()
{
    int leftRaw = analogRead(IR_LEFT);
    int rightRaw = analogRead(IR_RIGHT);

    int leftDigital = readIRSensorDigital(IR_LEFT);
    int rightDigital = readIRSensorDigital(IR_RIGHT);

    // Display raw analog values
    Serial.print("Raw: L=");
    Serial.print(leftRaw);
    Serial.print(" R=");
    Serial.print(rightRaw);
    Serial.print(" | ");

    // Display digital detection
    Serial.print("Digital: L=");
    Serial.print(getSurfaceColor(leftDigital));
    Serial.print(" R=");
    Serial.print(getSurfaceColor(rightDigital));
    Serial.print(" | ");

    // Detect line position
    detectLinePosition();

    delay(300); // Update every 300ms
}
