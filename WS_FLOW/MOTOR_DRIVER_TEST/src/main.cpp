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

void setup()
{
    pinMode(RC_MOTOR_STBY, OUTPUT);

    // Left motor
    pinMode(RC_LEFT_PWM, OUTPUT);
    pinMode(RC_LEFT_IN1, OUTPUT);
    pinMode(RC_LEFT_IN2, OUTPUT);

    // Right motor
    pinMode(RC_RIGHT_PWM, OUTPUT);
    pinMode(RC_RIGHT_IN1, OUTPUT);
    pinMode(RC_RIGHT_IN2, OUTPUT);

    // Enable motor driver
    digitalWrite(RC_MOTOR_STBY, HIGH);
}

void loop()
{
    // Test left motor forward
    digitalWrite(RC_LEFT_IN1, HIGH);
    digitalWrite(RC_LEFT_IN2, LOW);
    analogWrite(RC_LEFT_PWM, 200);
    delay(2000);

    // Test left motor backward
    digitalWrite(RC_LEFT_IN1, LOW);
    digitalWrite(RC_LEFT_IN2, HIGH);
    analogWrite(RC_LEFT_PWM, 200);
    delay(2000);

    // Stop left motor
    digitalWrite(RC_LEFT_IN1, LOW);
    digitalWrite(RC_LEFT_IN2, LOW);
    analogWrite(RC_LEFT_PWM, 0);
    delay(1000);

    // Test right motor forward
    digitalWrite(RC_RIGHT_IN1, HIGH);
    digitalWrite(RC_RIGHT_IN2, LOW);
    analogWrite(RC_RIGHT_PWM, 200);
    delay(2000);

    // Test right motor backward
    digitalWrite(RC_RIGHT_IN1, LOW);
    digitalWrite(RC_RIGHT_IN2, HIGH);
    analogWrite(RC_RIGHT_PWM, 200);
    delay(2000);

    // Stop right motor
    digitalWrite(RC_RIGHT_IN1, LOW);
    digitalWrite(RC_RIGHT_IN2, LOW);
    analogWrite(RC_RIGHT_PWM, 0);
    delay(1000);
}