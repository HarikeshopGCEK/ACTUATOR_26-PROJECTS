#define RC_MOTOR_STBY 23

#define RC_LEFT_PWM 33
#define RC_LEFT_IN1 18
#define RC_LEFT_IN2 19

#define RC_RIGHT_PWM 25
#define RC_RIGHT_IN1 26
#define RC_RIGHT_IN2 27

#include <Arduino.h>
#include <WiFi.h>

// =========================
// WIFI
// =========================

const char *WIFI_SSID = "ROBOCEK-GESTURE";
const char *WIFI_PASSWORD = "12345678";

const char *MASTER_IP = "192.168.4.1";

#define MASTER_PORT 5000

WiFiClient client;

// =========================
// MOTOR PINS
// =========================

#define RC_MOTOR_STBY 23

// Left motor

#define RC_LEFT_PWM 33
#define RC_LEFT_IN1 18
#define RC_LEFT_IN2 19

// Right motor

#define RC_RIGHT_PWM 25
#define RC_RIGHT_IN1 26
#define RC_RIGHT_IN2 27

int motorSpeed = 200;

// =========================
// MOTOR CONTROL
// =========================

void leftMotor(int speed)
{
    if (speed > 0)
    {
        digitalWrite(
            RC_LEFT_IN1,
            HIGH);

        digitalWrite(
            RC_LEFT_IN2,
            LOW);
    }

    else if (speed < 0)
    {
        digitalWrite(
            RC_LEFT_IN1,
            LOW);

        digitalWrite(
            RC_LEFT_IN2,
            HIGH);
    }

    else
    {
        digitalWrite(
            RC_LEFT_IN1,
            LOW);

        digitalWrite(
            RC_LEFT_IN2,
            LOW);
    }

    analogWrite(
        RC_LEFT_PWM,
        abs(speed));
}

void rightMotor(int speed)
{
    if (speed > 0)
    {
        digitalWrite(
            RC_RIGHT_IN1,
            HIGH);

        digitalWrite(
            RC_RIGHT_IN2,
            LOW);
    }

    else if (speed < 0)
    {
        digitalWrite(
            RC_RIGHT_IN1,
            LOW);

        digitalWrite(
            RC_RIGHT_IN2,
            HIGH);
    }

    else
    {
        digitalWrite(
            RC_RIGHT_IN1,
            LOW);

        digitalWrite(
            RC_RIGHT_IN2,
            LOW);
    }

    analogWrite(
        RC_RIGHT_PWM,
        abs(speed));
}

void stopCar()
{
    leftMotor(0);
    rightMotor(0);
}

void forward()
{
    leftMotor(motorSpeed);
    rightMotor(motorSpeed);
}

void backward()
{
    leftMotor(-motorSpeed);
    rightMotor(-motorSpeed);
}

void turnLeft()
{
    leftMotor(-motorSpeed);
    rightMotor(motorSpeed);
}

void turnRight()
{
    leftMotor(motorSpeed);
    rightMotor(-motorSpeed);
}

// =========================
// WIFI CONNECTION
// =========================

void connectToMaster()
{
    Serial.println(
        "Connecting to MASTER...");

    WiFi.mode(WIFI_STA);

    WiFi.begin(
        WIFI_SSID,
        WIFI_PASSWORD);

    while (
        WiFi.status() != WL_CONNECTED)
    {
        delay(500);

        Serial.print(".");
    }

    Serial.println();

    Serial.println(
        "Connected to MASTER");

    Serial.print(
        "ESP32 IP: ");

    Serial.println(
        WiFi.localIP());

    // =========================
    // TCP CONNECTION
    // =========================

    while (
        !client.connect(
            MASTER_IP,
            MASTER_PORT))
    {
        Serial.println(
            "TCP connection failed");

        delay(1000);
    }

    Serial.println(
        "MASTER LINK ESTABLISHED");
}

// =========================
// SETUP
// =========================

void setup()
{
    Serial.begin(115200);

    // Motor pins

    pinMode(
        RC_MOTOR_STBY,
        OUTPUT);

    pinMode(
        RC_LEFT_PWM,
        OUTPUT);

    pinMode(
        RC_LEFT_IN1,
        OUTPUT);

    pinMode(
        RC_LEFT_IN2,
        OUTPUT);

    pinMode(
        RC_RIGHT_PWM,
        OUTPUT);

    pinMode(
        RC_RIGHT_IN1,
        OUTPUT);

    pinMode(
        RC_RIGHT_IN2,
        OUTPUT);

    // Enable motor driver

    digitalWrite(
        RC_MOTOR_STBY,
        HIGH);

    stopCar();

    // Connect WiFi

    connectToMaster();
}

// =========================
// LOOP
// =========================

void loop()
{
    // Reconnect if WiFi disappears

    if (
        WiFi.status() != WL_CONNECTED)
    {
        stopCar();

        connectToMaster();
    }

    // Reconnect TCP

    if (!client.connected())
    {
        stopCar();

        Serial.println(
            "MASTER DISCONNECTED");

        delay(1000);

        connectToMaster();

        return;
    }

    // =========================
    // RECEIVE COMMAND
    // =========================

    if (client.available())
    {
        char command =
            client.read();

        Serial.print(
            "Command: ");

        Serial.println(
            command);

        switch (command)
        {
        case 'F':
            forward();
            break;

        case 'B':
            backward();
            break;

        case 'L':
            turnLeft();
            break;

        case 'R':
            turnRight();
            break;

        case 'S':
            stopCar();
            break;

        default:
            stopCar();
            break;
        }
    }
}