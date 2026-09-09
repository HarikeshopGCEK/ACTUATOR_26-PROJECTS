#include <Arduino.h>
#define RC_MOTOR_STBY 23

// Left motor
#define RC_LEFT_PWM 33
#define RC_LEFT_IN1 18
#define RC_LEFT_IN2 19

// Right motor
#define RC_RIGHT_PWM 25
#define RC_RIGHT_IN1 26
#define RC_RIGHT_IN2 27

#define RC_IR_LEFT 32
#define RC_IR_RIGHT 34
// Left Ultrasonic
#define RC_US_LEFT_TRIG 13
#define RC_US_LEFT_ECHO 35

// Right Ultrasonic
#define RC_US_RIGHT_TRIG 14
#define RC_US_RIGHT_ECHO 36

#define THRESHOLD_DISTANCE 20.0 // Distance threshold in cm
void setup()
{
    Serial.begin(115200);
    pinMode(RC_MOTOR_STBY, OUTPUT);
    pinMode(RC_LEFT_PWM, OUTPUT);
    pinMode(RC_LEFT_IN1, OUTPUT);
    pinMode(RC_LEFT_IN2, OUTPUT);
    pinMode(RC_RIGHT_PWM, OUTPUT);
    pinMode(RC_RIGHT_IN1, OUTPUT);
    pinMode(RC_RIGHT_IN2, OUTPUT);

    pinMode(RC_US_LEFT_TRIG, OUTPUT);
    pinMode(RC_US_LEFT_ECHO, INPUT);
    pinMode(RC_US_RIGHT_TRIG, OUTPUT);
    pinMode(RC_US_RIGHT_ECHO, INPUT);
}
float measureDistance(int trigPin, int echoPin)
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    float distance = (duration * 0.0343) / 2; // Convert to cm
    return distance;
}
void loop()
{
    float leftDistance = measureDistance(RC_US_LEFT_TRIG, RC_US_LEFT_ECHO);
    float rightDistance = measureDistance(RC_US_RIGHT_TRIG, RC_US_RIGHT_ECHO);

    if (leftDistance < THRESHOLD_DISTANCE && rightDistance < THRESHOLD_DISTANCE)
    {
        // Both sensors detect an obstacle, stop
        digitalWrite(RC_LEFT_IN1, LOW);
        digitalWrite(RC_LEFT_IN2, LOW);
        analogWrite(RC_LEFT_PWM, 0);

        digitalWrite(RC_RIGHT_IN1, LOW);
        digitalWrite(RC_RIGHT_IN2, LOW);
        analogWrite(RC_RIGHT_PWM, 0);
    }
    else if (leftDistance < THRESHOLD_DISTANCE)
    {
        // Left sensor detects an obstacle, turn right
        digitalWrite(RC_LEFT_IN1, LOW);
        digitalWrite(RC_LEFT_IN2, LOW);
        analogWrite(RC_LEFT_PWM, 0);

        digitalWrite(RC_RIGHT_IN1, HIGH);
        digitalWrite(RC_RIGHT_IN2, LOW);
        analogWrite(RC_RIGHT_PWM, 255);
    }
    else if (rightDistance < THRESHOLD_DISTANCE)
    {
        // Right sensor detects an obstacle, turn left
        digitalWrite(RC_LEFT_IN1, HIGH);
        digitalWrite(RC_LEFT_IN2, LOW);
        analogWrite(RC_LEFT_PWM, 255);

        digitalWrite(RC_RIGHT_IN1, HIGH);
        digitalWrite(RC_RIGHT_IN2, LOW);
        analogWrite(RC_RIGHT_PWM, 255);
    }
    else
    {
        // No sensors detect an obstacle, move forward
        digitalWrite(RC_LEFT_IN1, HIGH);
        digitalWrite(RC_LEFT_IN2, LOW);
        analogWrite(RC_LEFT_PWM, 255);

        digitalWrite(RC_RIGHT_IN1, HIGH);
        digitalWrite(RC_RIGHT_IN2, LOW);
        analogWrite(RC_RIGHT_PWM, 255);
    }
}