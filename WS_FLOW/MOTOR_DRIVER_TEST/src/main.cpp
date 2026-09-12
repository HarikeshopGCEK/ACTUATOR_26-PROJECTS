#include <Arduino.h>

// === TB6612FNG MOTOR DRIVER PINS ===
#define ENABLE 23   // Enable pin (HIGH = ON)
#define LEFT_PWM 33 // Left motor speed (0-255)
#define LEFT_IN1 18 // Left motor direction
#define LEFT_IN2 19
#define RIGHT_PWM 25 // Right motor speed (0-255)
#define RIGHT_IN1 26 // Right motor direction
#define RIGHT_IN2 27

void setup()
{
    Serial.begin(115200);
    delay(500);
    Serial.println("\n=== MOTOR DRIVER TEST ===");
    Serial.println("TB6612FNG: Controls 2 DC motors\n");

    // Set all pins as outputs
    pinMode(ENABLE, OUTPUT);
    pinMode(LEFT_PWM, OUTPUT);
    pinMode(LEFT_IN1, OUTPUT);
    pinMode(LEFT_IN2, OUTPUT);
    pinMode(RIGHT_PWM, OUTPUT);
    pinMode(RIGHT_IN1, OUTPUT);
    pinMode(RIGHT_IN2, OUTPUT);

    // Turn ON motor driver
    digitalWrite(ENABLE, HIGH);
}

void moveForward()
{
    Serial.println("FORWARD");
    digitalWrite(LEFT_IN1, HIGH);
    digitalWrite(LEFT_IN2, LOW);
    digitalWrite(RIGHT_IN1, HIGH);
    digitalWrite(RIGHT_IN2, LOW);
    analogWrite(LEFT_PWM, 200);
    analogWrite(RIGHT_PWM, 200);
}

void moveBackward()
{
    Serial.println("BACKWARD");
    digitalWrite(LEFT_IN1, LOW);
    digitalWrite(LEFT_IN2, HIGH);
    digitalWrite(RIGHT_IN1, LOW);
    digitalWrite(RIGHT_IN2, HIGH);
    analogWrite(LEFT_PWM, 200);
    analogWrite(RIGHT_PWM, 200);
}

void turnRight()
{
    Serial.println("TURN RIGHT");
    digitalWrite(LEFT_IN1, HIGH);
    digitalWrite(LEFT_IN2, LOW);
    digitalWrite(RIGHT_IN1, LOW);
    digitalWrite(RIGHT_IN2, LOW);
    analogWrite(LEFT_PWM, 200);
    analogWrite(RIGHT_PWM, 0);
}

void turnLeft()
{
    Serial.println("TURN LEFT");
    digitalWrite(LEFT_IN1, LOW);
    digitalWrite(LEFT_IN2, LOW);
    digitalWrite(RIGHT_IN1, HIGH);
    digitalWrite(RIGHT_IN2, LOW);
    analogWrite(LEFT_PWM, 0);
    analogWrite(RIGHT_PWM, 200);
}

void stopMotors()
{
    Serial.println("STOP\n");
    digitalWrite(LEFT_IN1, LOW);
    digitalWrite(LEFT_IN2, LOW);
    digitalWrite(RIGHT_IN1, LOW);
    digitalWrite(RIGHT_IN2, LOW);
    analogWrite(LEFT_PWM, 0);
    analogWrite(RIGHT_PWM, 0);
}

void loop()
{
    moveForward();
    delay(2000);
    stopMotors();
    delay(500);

    moveBackward();
    delay(2000);
    stopMotors();
    delay(500);

    turnLeft();
    delay(1500);
    stopMotors();
    delay(500);

    turnRight();
    delay(1500);
    stopMotors();
    delay(2000);
}