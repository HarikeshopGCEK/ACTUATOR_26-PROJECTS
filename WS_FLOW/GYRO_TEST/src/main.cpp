#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// === MPU6050 SENSOR OBJECT ===
Adafruit_MPU6050 mpu;

// === I2C PINS (ESP8266 NodeMCU) ===
#define SDA D2 // GPIO4
#define SCL D1 // GPIO5

void setup()
{
    Serial.begin(115200);
    delay(500);
    Serial.println("\n=== MPU6050 GYROSCOPE TEST ===");
    Serial.println("6-Axis Motion Sensor");
    Serial.println("Accelerometer + Gyroscope\n");

    // Initialize I2C
    Wire.begin(SDA, SCL);

    // Initialize MPU6050
    if (!mpu.begin())
    {
        Serial.println("ERROR: MPU6050 not found!");
        Serial.println("Check I2C wiring (SDA=D2, SCL=D1)");
        while (1)
            delay(100);
    }

    Serial.println("MPU6050 initialized!\n");
}

void loop()
{
    // Get sensor readings
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // === ACCELEROMETER (measures tilt/movement) ===
    // Units: m/s²
    // X,Y,Z range: -16 to +16 m/s²
    Serial.print("Accel [m/s²]: ");
    Serial.print("X=");
    Serial.print(a.acceleration.x, 2);
    Serial.print("  Y=");
    Serial.print(a.acceleration.y, 2);
    Serial.print("  Z=");
    Serial.print(a.acceleration.z, 2);
    Serial.print("  | ");

    // === GYROSCOPE (measures rotation speed) ===
    // Units: radians per second
    // X,Y,Z range: -500 to +500 rad/s
    Serial.print("Gyro [rad/s]: ");
    Serial.print("X=");
    Serial.print(g.gyro.x, 4);
    Serial.print("  Y=");
    Serial.print(g.gyro.y, 4);
    Serial.print("  Z=");
    Serial.print(g.gyro.z, 4);
    Serial.print("  | ");

    // === TEMPERATURE ===
    Serial.print("Temp=");
    Serial.print(temp.temperature, 1);
    Serial.println("°C");

    delay(300);
}
Serial.println("±250 °/s");
break;
case MPU6050_RANGE_500_DEG:
Serial.println("±500 °/s");
break;
case MPU6050_RANGE_1000_DEG:
Serial.println("±1000 °/s");
break;
case MPU6050_RANGE_2000_DEG:
Serial.println("±2000 °/s");
break;
}

// Set filter bandwidth
mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
Serial.print("Filter bandwidth set to: ");
switch (mpu.getFilterBandwidth())
{
case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
}

delay(1000);

// Calibrate gyroscope
Serial.println("\nCalibrating gyroscope (keep sensor still)...");
calibrateGyro();
Serial.println("✓ Gyroscope calibration complete!\n");

lastTime = millis();
}

// ========================
// GYROSCOPE CALIBRATION
// ========================

void calibrateGyro()
{
    int samples = 100;
    float sumX = 0, sumY = 0, sumZ = 0;

    for (int i = 0; i < samples; i++)
    {
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);

        sumX += g.gyro.x;
        sumY += g.gyro.y;
        sumZ += g.gyro.z;

        delay(10);
    }

    gyroOffsetX = sumX / samples;
    gyroOffsetY = sumY / samples;
    gyroOffsetZ = sumZ / samples;

    Serial.print("Gyro Offsets - X: ");
    Serial.print(gyroOffsetX, 6);
    Serial.print(" Y: ");
    Serial.print(gyroOffsetY, 6);
    Serial.print(" Z: ");
    Serial.println(gyroOffsetZ, 6);
}

// ========================
// SENSOR READING FUNCTIONS
// ========================

void readMPU6050()
{
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Accelerometer readings (m/s²)
    accelX = a.acceleration.x;
    accelY = a.acceleration.y;
    accelZ = a.acceleration.z;

    // Gyroscope readings (rad/s) - subtract offset
    gyroX = g.gyro.x - gyroOffsetX;
    gyroY = g.gyro.y - gyroOffsetY;
    gyroZ = g.gyro.z - gyroOffsetZ;

    // Temperature
    tempC = temp.temperature;
}

// ========================
// ANGLE CALCULATION FUNCTIONS
// ========================

/**
 * Calculate pitch and roll from accelerometer data
 * Pitch: rotation around Y-axis
 * Roll: rotation around X-axis
 */
void calculateAccelerometerAngles()
{
    // Convert to degrees
    pitch = atan2(accelY, sqrt(accelX * accelX + accelZ * accelZ)) * RAD_TO_DEG;
    roll = atan2(accelX, sqrt(accelY * accelY + accelZ * accelZ)) * RAD_TO_DEG;
}

/**
 * Update pitch and roll using gyroscope integration
 * Uses complementary filter: 95% gyro + 5% accelerometer
 */
void calculateGyroAngles()
{
    // Calculate delta time
    unsigned long currentTime = millis();
    dt = (currentTime - lastTime) / 1000.0; // Convert to seconds
    lastTime = currentTime;

    // Prevent dt from being too large (recovery from delay)
    if (dt > 0.1)
        dt = 0.01;

    // Convert gyro angular velocity (rad/s) to degrees/s
    float gyroPitch = gyroY * RAD_TO_DEG; // Rotation around Y-axis
    float gyroRoll = gyroX * RAD_TO_DEG;  // Rotation around X-axis

    // Get accelerometer angles
    calculateAccelerometerAngles();

    // Complementary filter
    // Weight: 95% from gyroscope integration, 5% from accelerometer
    pitch_gyro = 0.95 * (pitch_gyro + gyroPitch * dt) + 0.05 * pitch;
    roll_gyro = 0.95 * (roll_gyro + gyroRoll * dt) + 0.05 * roll;
}

// ========================
// DISPLAY FUNCTIONS
// ========================

void displayRawData()
{
    Serial.println("\n--- RAW SENSOR DATA ---");

    Serial.print("Accel: X=");
    Serial.print(accelX, 2);
    Serial.print("m/s² Y=");
    Serial.print(accelY, 2);
    Serial.print("m/s² Z=");
    Serial.print(accelZ, 2);
    Serial.println("m/s²");

    Serial.print("Gyro:  X=");
    Serial.print(gyroX, 4);
    Serial.print("rad/s Y=");
    Serial.print(gyroY, 4);
    Serial.print("rad/s Z=");
    Serial.print(gyroZ, 4);
    Serial.println("rad/s");

    Serial.print("Temp:  ");
    Serial.print(tempC, 1);
    Serial.println("°C");
}

void displayAngles()
{
    Serial.println("\n--- CALCULATED ANGLES ---");

    Serial.print("Accel-based: Pitch=");
    Serial.print(pitch, 1);
    Serial.print("° Roll=");
    Serial.print(roll, 1);
    Serial.println("°");

    Serial.print("Gyro-based:  Pitch=");
    Serial.print(pitch_gyro, 1);
    Serial.print("° Roll=");
    Serial.print(roll_gyro, 1);
    Serial.println("°");

    Serial.print("Delta Time: ");
    Serial.print(dt * 1000, 1);
    Serial.println("ms");
}

void displayVisualBars()
{
    Serial.println("\n--- MOTION VISUALIZATION ---");

    // Pitch visualization (-90 to +90 degrees)
    Serial.print("Pitch: ");
    int pitchBar = map(pitch_gyro * 10, -900, 900, 0, 40);
    pitchBar = constrain(pitchBar, 0, 40);
    for (int i = 0; i < 40; i++)
    {
        if (i == 20)
            Serial.print("|");
        else if (i < pitchBar)
            Serial.print("█");
        else if (i > pitchBar)
            Serial.print("▌");
        else
            Serial.print("█");
    }
    Serial.print(" ");
    Serial.print(pitch_gyro, 1);
    Serial.println("°");

    // Roll visualization (-90 to +90 degrees)
    Serial.print("Roll:  ");
    int rollBar = map(roll_gyro * 10, -900, 900, 0, 40);
    rollBar = constrain(rollBar, 0, 40);
    for (int i = 0; i < 40; i++)
    {
        if (i == 20)
            Serial.print("|");
        else if (i < rollBar)
            Serial.print("█");
        else if (i > rollBar)
            Serial.print("▌");
        else
            Serial.print("█");
    }
    Serial.print(" ");
    Serial.print(roll_gyro, 1);
    Serial.println("°");
}

void displayGestureDetection()
{
    Serial.println("\n--- GESTURE DETECTION ---");

    // Tilt forward
    if (pitch_gyro < -10)
        Serial.println("→ TILTED FORWARD");
    // Tilt backward
    else if (pitch_gyro > 10)
        Serial.println("→ TILTED BACKWARD");
    // Tilt left
    else if (roll_gyro < -10)
        Serial.println("→ TILTED LEFT");
    // Tilt right
    else if (roll_gyro > 10)
        Serial.println("→ TILTED RIGHT");
    else
        Serial.println("→ LEVEL");
}

// ========================
// MAIN LOOP
// ========================

void loop()
{
    // Read sensors
    readMPU6050();

    // Calculate angles
    calculateGyroAngles();

    // Display all data
    displayRawData();
    displayAngles();
    displayVisualBars();
    displayGestureDetection();

    Serial.println("========================================");

    delay(500); // Update every 500ms
}