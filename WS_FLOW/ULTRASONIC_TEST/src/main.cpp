#include <Arduino.h>

// === ULTRASONIC SENSOR HC-SR04 PINS ===
#define TRIG_LEFT 13  // Left sensor trigger
#define ECHO_LEFT 35  // Left sensor echo
#define TRIG_RIGHT 14 // Right sensor trigger
#define ECHO_RIGHT 36 // Right sensor echo

#define SAFE_DISTANCE 20 // Alert if closer than 20cm

void setup()
{
    Serial.begin(115200);
    delay(500);
    Serial.println("\n=== ULTRASONIC SENSOR TEST ===");
    Serial.println("HC-SR04: Measures distance with sound waves\n");

    // Trigger = output (sends pulses)
    // Echo = input (receives bounced sound)
    pinMode(TRIG_LEFT, OUTPUT);
    pinMode(ECHO_LEFT, INPUT);
    pinMode(TRIG_RIGHT, OUTPUT);
    pinMode(ECHO_RIGHT, INPUT);
}

// === FUNCTION: Measure distance ===
// Returns: distance in centimeters
float getDistance(int trigPin, int echoPin)
{
    // Step 1: Send 10 microsecond pulse
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Step 2: Measure echo pulse time
    // (how long ECHO pin stays HIGH)
    long duration = pulseIn(echoPin, HIGH, 30000);

    if (duration == 0)
        return -1; // Error

    // Step 3: Calculate distance
    // Sound = 0.0343 cm per microsecond
    // We divide by 2 (sound goes out AND back)
    float distance = (duration / 2.0) * 0.0343;

    return distance;
}

void loop()
{
    // Read both sensors
    float distLeft = getDistance(TRIG_LEFT, ECHO_LEFT);
    float distRight = getDistance(TRIG_RIGHT, ECHO_RIGHT);

    // Display results
    Serial.print("LEFT: ");
    if (distLeft > 0)
    {
        Serial.print(distLeft, 1);
        Serial.print(" cm");
    }
    else
    {
        Serial.print("ERROR");
    }

    Serial.print("  |  RIGHT: ");
    if (distRight > 0)
    {
        Serial.print(distRight, 1);
        Serial.print(" cm");
    }
    else
    {
        Serial.print("ERROR");
    }

    // Obstacle warning
    Serial.print("  |  ");
    if (distLeft > 0 && distLeft < SAFE_DISTANCE)
    {
        Serial.print("LEFT-OBSTACLE ");
    }
    if (distRight > 0 && distRight < SAFE_DISTANCE)
    {
        Serial.print("RIGHT-OBSTACLE");
    }
    if ((distLeft < 0 || distLeft >= SAFE_DISTANCE) &&
        (distRight < 0 || distRight >= SAFE_DISTANCE))
    {
        Serial.print("CLEAR");
    }

    Serial.println();
    delay(500);
}
{
    // Get current readings
    float leftDistance = measureDistance(US_LEFT_TRIG, US_LEFT_ECHO);
    float rightDistance = measureDistance(US_RIGHT_TRIG, US_RIGHT_ECHO);

    // Display distance bars
    displayDistanceBar(leftDistance, "LEFT ");
    displayDistanceBar(rightDistance, "RIGHT");

    // Display sensor status
    displaySensorStatus(leftDistance, rightDistance);

    // Display obstacle avoidance logic
    displayObstacleAvoidanceLogic(leftDistance, rightDistance);

    // Separator
    Serial.println("==========================================");

    // Update every 500ms
    delay(500);
}

// ========================
// OPTIONAL: CALIBRATION MODE
// ========================

/*
 * To use calibration mode, uncomment below and call in setup()
 *
void calibrateUltrasonicSensors() {
    Serial.println("\n--- ULTRASONIC CALIBRATION ---");
    Serial.println("Hold object at 10cm from LEFT sensor...");
    delay(3000);

    float reading10cm = getAveragedDistance(US_LEFT_TRIG, US_LEFT_ECHO);
    Serial.print("10cm reading: ");
    Serial.println(reading10cm, 1);

    Serial.println("\nHold object at 50cm from LEFT sensor...");
    delay(3000);

    float reading50cm = getAveragedDistance(US_LEFT_TRIG, US_LEFT_ECHO);
    Serial.print("50cm reading: ");
    Serial.println(reading50cm, 1);

    Serial.println("\nCalibration complete.");
    Serial.print("Accuracy: ");
    float accuracy = ((reading10cm + reading50cm) / 2) / 30.0 * 100;
    Serial.print(accuracy, 1);
    Serial.println("%");
}
*/
