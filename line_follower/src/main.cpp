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
}

void loop()
{
    int leftSensorValue = digitalRead(RC_IR_LEFT);
    int rightSensorValue = digitalRead(RC_IR_RIGHT);

    if (leftSensorValue == LOW && rightSensorValue == LOW)
    {
        // Both sensors detect the line, move forward
        digitalWrite(RC_LEFT_IN1, HIGH);
        digitalWrite(RC_LEFT_IN2, LOW);
        analogWrite(RC_LEFT_PWM, 255);

        digitalWrite(RC_RIGHT_IN1, HIGH);
        digitalWrite(RC_RIGHT_IN2, LOW);
        analogWrite(RC_RIGHT_PWM, 255);
    }
    else if (leftSensorValue == LOW && rightSensorValue == HIGH)
    {
        // Left sensor detects the line, turn left
        digitalWrite(RC_LEFT_IN1, LOW);
        digitalWrite(RC_LEFT_IN2, LOW);
        analogWrite(RC_LEFT_PWM, 0);

        digitalWrite(RC_RIGHT_IN1, HIGH);
        digitalWrite(RC_RIGHT_IN2, LOW);
        analogWrite(RC_RIGHT_PWM, 255);
    }
    else if (leftSensorValue == HIGH && rightSensorValue == LOW)
    {
        // Right sensor detects the line, turn right
        digitalWrite(RC_LEFT_IN1, HIGH);
        digitalWrite(RC_LEFT_IN2, LOW);
        analogWrite(RC_LEFT_PWM, 255);

        digitalWrite(RC_RIGHT_IN1, LOW);
        digitalWrite(RC_RIGHT_IN2, LOW);
        analogWrite(RC_RIGHT_PWM, 0);
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
    }
}