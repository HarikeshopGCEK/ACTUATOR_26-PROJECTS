#include <Arduino.h>

// ========================
// ULTRASONIC SENSOR PIN DEFINITIONS
// ========================

// Left Ultrasonic Sensor
#define US_LEFT_TRIG 13
#define US_LEFT_ECHO 35 // Input only pin

// Right Ultrasonic Sensor
#define US_RIGHT_TRIG 14
#define US_RIGHT_ECHO 36 // Input only pin

// ========================
// CONFIGURATION
// ========================

#define SOUND_SPEED 0.0343         // cm/µs (speed of sound in air at ~20°C)
#define SAFE_DISTANCE 20.0         // cm - threshold for obstacle detection
#define MAX_DISTANCE 400.0         // cm - maximum measurable distance
#define TIMEOUT_MICROSECONDS 30000 // 30ms timeout

#define SENSOR_SAMPLES 5 // Number of samples for averaging
#define SAMPLE_DELAY 50  // ms between samples

// ========================
// GLOBAL VARIABLES
// ========================

float leftDistances[SENSOR_SAMPLES];
float rightDistances[SENSOR_SAMPLES];
int sampleIndex = 0;

// ========================
// SETUP FUNCTION
// ========================

void setup()
{
    Serial.begin(115200);
    delay(1000); // Give serial monitor time to connect

    Serial.println("\n\n=== ULTRASONIC SENSOR TEST ===");
    Serial.println("ESP32 HC-SR04 Distance Sensor Testing");
    Serial.println("Left Sensor:  TRIG=GPIO13, ECHO=GPIO35");
    Serial.println("Right Sensor: TRIG=GPIO14, ECHO=GPIO36");
    Serial.println("================================\n");

    // Configure trigger pins as output
    pinMode(US_LEFT_TRIG, OUTPUT);
    pinMode(US_RIGHT_TRIG, OUTPUT);

    // Configure echo pins as input
    pinMode(US_LEFT_ECHO, INPUT);
    pinMode(US_RIGHT_ECHO, INPUT);

    // Initialize triggers to LOW
    digitalWrite(US_LEFT_TRIG, LOW);
    digitalWrite(US_RIGHT_TRIG, LOW);

    Serial.println("Sensors initialized. Starting measurements...\n");
}

// ========================
// DISTANCE MEASUREMENT FUNCTIONS
// ========================

/**
 * Measure distance using single ultrasonic sensor
 * Parameters:
 *   trigPin: GPIO pin connected to TRIG
 *   echoPin: GPIO pin connected to ECHO
 * Returns: Distance in centimeters (-1 if timeout)
 */
float measureDistance(int trigPin, int echoPin)
{
    // Ensure trigger pin starts LOW
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Send 10µs pulse
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Measure echo pulse duration
    long duration = pulseIn(echoPin, HIGH, TIMEOUT_MICROSECONDS);

    // Check for timeout
    if (duration == 0)
    {
        return -1.0; // Timeout - return error value
    }

    // Convert time to distance
    // Distance = (duration / 2) × speed_of_sound
    // Speed of sound = 0.0343 cm/µs
    float distance = (duration / 2.0) * SOUND_SPEED;

    // Check if distance is within measurable range
    if (distance > MAX_DISTANCE)
    {
        return -1.0; // Out of range
    }

    return distance;
}

/**
 * Get averaged distance reading
 * Parameters:
 *   trigPin: GPIO pin connected to TRIG
 *   echoPin: GPIO pin connected to ECHO
 * Returns: Averaged distance in centimeters
 */
float getAveragedDistance(int trigPin, int echoPin)
{
    float sum = 0.0;
    int validSamples = 0;

    for (int i = 0; i < SENSOR_SAMPLES; i++)
    {
        float distance = measureDistance(trigPin, echoPin);

        // Only count valid readings
        if (distance > 0)
        {
            sum += distance;
            validSamples++;
        }

        delay(SAMPLE_DELAY);
    }

    // Return average or error value
    if (validSamples > 0)
    {
        return sum / validSamples;
    }
    else
    {
        return -1.0;
    }
}

// ========================
// DISPLAY FUNCTIONS
// ========================

void displayDistanceBar(float distance, const char *label)
{
    Serial.print(label);
    Serial.print(": ");

    if (distance < 0)
    {
        Serial.println("ERROR/TIMEOUT");
        return;
    }

    // Print numeric value
    Serial.print(distance, 1);
    Serial.print(" cm | [");

    // Print visual bar (0-100cm = 0-40 characters)
    int barLength = map(distance * 10, 0, 1000, 0, 40);
    barLength = constrain(barLength, 0, 40);

    for (int i = 0; i < 40; i++)
    {
        if (i < barLength)
            Serial.print("█");
        else
            Serial.print("░");
    }
    Serial.println("]");
}

void displaySensorStatus(float leftDist, float rightDist)
{
    Serial.print("Status: ");

    // Left sensor status
    if (leftDist < SAFE_DISTANCE && leftDist > 0)
    {
        Serial.print("LEFT-OBSTACLE ");
    }
    else if (leftDist > 0)
    {
        Serial.print("LEFT-CLEAR ");
    }
    else
    {
        Serial.print("LEFT-ERROR ");
    }

    // Right sensor status
    if (rightDist < SAFE_DISTANCE && rightDist > 0)
    {
        Serial.print("RIGHT-OBSTACLE");
    }
    else if (rightDist > 0)
    {
        Serial.print("RIGHT-CLEAR");
    }
    else
    {
        Serial.print("RIGHT-ERROR");
    }
    Serial.println();
}

void displayObstacleAvoidanceLogic(float leftDist, float rightDist)
{
    Serial.print("Action: ");

    // Both clear
    if (leftDist > SAFE_DISTANCE && rightDist > SAFE_DISTANCE)
    {
        Serial.println("→ MOVE FORWARD");
    }
    // Left blocked, right clear
    else if (leftDist < SAFE_DISTANCE && rightDist > SAFE_DISTANCE)
    {
        Serial.println("→ TURN RIGHT");
    }
    // Right blocked, left clear
    else if (leftDist > SAFE_DISTANCE && rightDist < SAFE_DISTANCE)
    {
        Serial.println("→ TURN LEFT");
    }
    // Both blocked
    else if (leftDist < SAFE_DISTANCE && rightDist < SAFE_DISTANCE)
    {
        Serial.println("→ REVERSE");
    }
    // Error condition
    else
    {
        Serial.println("→ STOP/ERROR");
    }
}

// ========================
// CALIBRATION & TESTING
// ========================

void testSingleMeasurement()
{
    Serial.println("\n--- SINGLE MEASUREMENT TEST ---");

    float leftDist = measureDistance(US_LEFT_TRIG, US_LEFT_ECHO);
    float rightDist = measureDistance(US_RIGHT_TRIG, US_RIGHT_ECHO);

    Serial.print("Left:  ");
    Serial.print(leftDist, 1);
    Serial.println(" cm");

    Serial.print("Right: ");
    Serial.print(rightDist, 1);
    Serial.println(" cm");
}

void testAveragedMeasurement()
{
    Serial.println("\n--- AVERAGED MEASUREMENT TEST (5 samples) ---");

    float leftDist = getAveragedDistance(US_LEFT_TRIG, US_LEFT_ECHO);
    float rightDist = getAveragedDistance(US_RIGHT_TRIG, US_RIGHT_ECHO);

    Serial.print("Left (avg):  ");
    Serial.print(leftDist, 1);
    Serial.println(" cm");

    Serial.print("Right (avg): ");
    Serial.print(rightDist, 1);
    Serial.println(" cm");
}

void testResponseTime()
{
    Serial.println("\n--- RESPONSE TIME TEST ---");

    unsigned long startTime = millis();
    float distance = measureDistance(US_LEFT_TRIG, US_LEFT_ECHO);
    unsigned long endTime = millis();

    Serial.print("Distance: ");
    Serial.print(distance, 1);
    Serial.print(" cm | Time: ");
    Serial.print(endTime - startTime);
    Serial.println(" ms");
}

// ========================
// MAIN LOOP
// ========================

void loop()
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
