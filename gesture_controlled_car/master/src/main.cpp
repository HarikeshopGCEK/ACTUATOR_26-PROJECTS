#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#include <ESP8266WiFi.h>

// =========================
// WIFI ACCESS POINT
// =========================

const char *AP_SSID = "ROBOCEK-GESTURE";
const char *AP_PASSWORD = "12345678";

WiFiServer server(5000);
WiFiClient client;

Adafruit_MPU6050 mpu;

// =========================
// MPU6050
// =========================

// NodeMCU ESP8266
// D1 = GPIO5  -> SCL
// D2 = GPIO4  -> SDA

#define MPU_SDA D2
#define MPU_SCL D1

// =========================
// GESTURE THRESHOLDS
// =========================

// Adjust these after testing

#define TILT_FORWARD 3.0
#define TILT_BACKWARD -3.0

#define TILT_LEFT 3.0
#define TILT_RIGHT -3.0

void setup()
{
    Serial.begin(115200);

    // =========================
    // MPU6050
    // =========================

    Wire.begin(MPU_SDA, MPU_SCL);

    if (!mpu.begin())
    {
        Serial.println("MPU6050 NOT FOUND!");

        while (1)
        {
            delay(1000);
        }
    }

    Serial.println("MPU6050 OK");

    mpu.setAccelerometerRange(
        MPU6050_RANGE_8_G);

    mpu.setGyroRange(
        MPU6050_RANGE_500_DEG);

    mpu.setFilterBandwidth(
        MPU6050_BAND_21_HZ);

    // =========================
    // WIFI AP
    // =========================

    WiFi.mode(WIFI_AP);

    WiFi.softAP(
        AP_SSID,
        AP_PASSWORD);

    Serial.println();

    Serial.println("========================");
    Serial.println("GESTURE MASTER");
    Serial.println("========================");

    Serial.print("SSID: ");
    Serial.println(AP_SSID);

    Serial.print("IP: ");
    Serial.println(
        WiFi.softAPIP());

    Serial.println("Port: 5000");

    server.begin();
}

// =========================
// LOOP
// =========================

void loop()
{
    // =========================
    // WAIT FOR SLAVE
    // =========================

    if (!client || !client.connected())
    {
        client = server.available();

        if (client)
        {
            Serial.println(
                "SLAVE CONNECTED");
        }

        delay(10);

        return;
    }

    // =========================
    // READ MPU6050
    // =========================

    sensors_event_t a;
    sensors_event_t g;
    sensors_event_t temp;

    mpu.getEvent(
        &a,
        &g,
        &temp);

    float ax = a.acceleration.x;
    float ay = a.acceleration.y;
    float az = a.acceleration.z;

    // =========================
    // GESTURE
    // =========================

    char command = 'S';

    // Forward / backward

    if (ax > TILT_FORWARD)
    {
        command = 'F';
    }
    else if (ax < TILT_BACKWARD)
    {
        command = 'B';
    }

    // Left / right

    else if (ay > TILT_LEFT)
    {
        command = 'L';
    }
    else if (ay < TILT_RIGHT)
    {
        command = 'R';
    }

    else
    {
        command = 'S';
    }

    // =========================
    // SEND COMMAND
    // =========================

    client.write(command);

    Serial.print("Gesture: ");
    Serial.println(command);

    delay(50);
}