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


// Left Ultrasonic
#define RC_TRIG 32
#define RC_ECHO 35

#define THRESHOLD_DISTANCE 20.0 // Distance threshold in cm

#define SPEED 100
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

    pinMode(RC_TRIG, OUTPUT);
    pinMode(RC_ECHO, INPUT);

    digitalWrite(RC_MOTOR_STBY,HIGH);
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
    float distance = measureDistance(RC_TRIG, RC_ECHO);
    Serial.print("Distance: ");
    Serial.println(distance);

    if(distance > THRESHOLD_DISTANCE)
    {
        digitalWrite(RC_LEFT_IN1, HIGH);
        digitalWrite(RC_LEFT_IN2, LOW);
        analogWrite(RC_LEFT_PWM, SPEED);

        digitalWrite(RC_RIGHT_IN1, HIGH);
        digitalWrite(RC_RIGHT_IN2, LOW);
        analogWrite(RC_RIGHT_PWM, SPEED);
    }
    else
    {
        digitalWrite(RC_LEFT_IN1, HIGH);
        digitalWrite(RC_LEFT_IN2, LOW);
        analogWrite(RC_LEFT_PWM, SPEED);

        digitalWrite(RC_RIGHT_IN1, LOW);
        digitalWrite(RC_RIGHT_IN2, HIGH);
        analogWrite(RC_RIGHT_PWM, SPEED);
    }
    delay(1000);
    
}