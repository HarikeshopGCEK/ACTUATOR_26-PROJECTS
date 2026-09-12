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

#define SPEED 100

#include <Arduino.h>

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
    pinMode(RC_IR_LEFT, INPUT);
    pinMode(RC_IR_RIGHT, INPUT);
    digitalWrite(RC_MOTOR_STBY,HIGH);
}

void loop()
{
    int leftSensorValue = digitalRead(RC_IR_LEFT);
    int rightSensorValue = digitalRead(RC_IR_RIGHT);
    Serial.print("LEFT IR: ");
    Serial.println(leftSensorValue);
    Serial.print("RIGHT IR: ");
    Serial.println(rightSensorValue);

    if (leftSensorValue == LOW && rightSensorValue == LOW)
    {
        // Both sensors detect the line, move forward
        digitalWrite(RC_LEFT_IN1, HIGH);
        digitalWrite(RC_LEFT_IN2, LOW);
        analogWrite(RC_LEFT_PWM, SPEED);

        digitalWrite(RC_RIGHT_IN1, HIGH);
        digitalWrite(RC_RIGHT_IN2, LOW);
        analogWrite(RC_RIGHT_PWM, SPEED);
        Serial.println("Moving forward");
    }
    else if (leftSensorValue == HIGH && rightSensorValue == LOW)
    {
        // Left sensor detects the line, turn left
        digitalWrite(RC_LEFT_IN1, LOW);
        digitalWrite(RC_LEFT_IN2, LOW);
        analogWrite(RC_LEFT_PWM, 0);

        digitalWrite(RC_RIGHT_IN1, HIGH);
        digitalWrite(RC_RIGHT_IN2, LOW);
        analogWrite(RC_RIGHT_PWM, SPEED);
        Serial.println("Turning left");
    }
    else if (leftSensorValue == LOW && rightSensorValue == HIGH)
    {
        // Right sensor detects the line, turn right
        digitalWrite(RC_LEFT_IN1, HIGH);
        digitalWrite(RC_LEFT_IN2, LOW);
        analogWrite(RC_LEFT_PWM, SPEED);

        digitalWrite(RC_RIGHT_IN1, LOW);
        digitalWrite(RC_RIGHT_IN2, LOW);
        analogWrite(RC_RIGHT_PWM, 0);
        Serial.println("Turning right");
    }
    else
    {
        // No sensors detect the line, stop
        digitalWrite(RC_LEFT_IN1, LOW);
        digitalWrite(RC_LEFT_IN2, LOW);
        analogWrite(RC_LEFT_PWM, 0);

        digitalWrite(RC_RIGHT_IN1, LOW);
        digitalWrite(RC_RIGHT_IN2, LOW);
        analogWrite(RC_RIGHT_PWM, 0);
        Serial.println("Stopping");
    }
    delay(100); // Add a small delay to avoid overwhelming the serial output
}