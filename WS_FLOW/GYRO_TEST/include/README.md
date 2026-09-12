# MPU6050 Gyroscope Test Project

## Overview

Complete MPU6050 6-axis motion sensor measurement and gesture detection for ESP8266 NodeMCU.

## Hardware Required

- **ESP8266 NodeMCU** or similar
- **MPU6050 Sensor Module** (accelerometer + gyroscope)
- **Pull-up resistors** (optional, usually built-in on sensor modules)
- Power Supply (5V)

## I2C Pin Configuration

```
NodeMCU ESP8266:
  D1 (GPIO5)  → MPU6050 SCL (Clock)
  D2 (GPIO4)  → MPU6050 SDA (Data)
  GND         → MPU6050 GND
  3.3V/5V     → MPU6050 VCC
```

## Features

### 1. **Raw Sensor Readings**

- Accelerometer (X, Y, Z) in m/s²
- Gyroscope (X, Y, Z) in rad/s
- Temperature in °C

### 2. **Angle Calculation**

- **Accelerometer-based angles:** Pitch & Roll (static, drift-free)
- **Gyroscope-based angles:** Pitch & Roll (fast response, with drift correction)
- **Complementary Filter:** 95% gyro + 5% accelerometer

### 3. **Visual Display**

- Real-time motion bars showing pitch and roll
- Clear sensor values in terminal
- Delta time measurement

### 4. **Gesture Detection**

- Tilt forward/backward (pitch detection)
- Tilt left/right (roll detection)
- Level detection

## Sensor Specifications

- **Accelerometer Range:** ±16G (configurable)
- **Gyroscope Range:** ±500°/s (configurable)
- **Filter Bandwidth:** 21 Hz (configurable)
- **Sample Rate:** ~100Hz

## Calibration

The code automatically calibrates the gyroscope on startup:

1. Keep sensor **still** during setup
2. Program calculates gyro offset
3. Offsets are subtracted during readings

## Output Example

```
--- RAW SENSOR DATA ---
Accel: X=0.15m/s² Y=0.42m/s² Z=9.81m/s²
Gyro:  X=0.0043rad/s Y=-0.0012rad/s Z=0.0001rad/s
Temp:  28.5°C

--- CALCULATED ANGLES ---
Accel-based: Pitch=-2.5° Roll=0.9°
Gyro-based:  Pitch=-2.3° Roll=1.1°
Delta Time: 502.1ms

--- MOTION VISUALIZATION ---
Pitch: ░░░░░░░░░░░░░░░░░░█|░░░░░░░░░░░░░░░░░░░░ -2.3°
Roll:  ░░░░░░░░░░░░░░░░░░█|░░░░░░░░░░░░░░░░░░░░ 1.1°

--- GESTURE DETECTION ---
→ LEVEL
```

## Wiring Tips

- Use short wires between NodeMCU and MPU6050
- Add 100nF capacitors near VCC and GND
- Use pull-up resistors if I2C not working (typical: 4.7kΩ)
- Mount sensor on level surface during calibration

## Troubleshooting

### MPU6050 Not Found

1. Check I2C connections (SDA=D2, SCL=D1)
2. Verify VCC and GND connections
3. Check I2C address (default: 0x68)
4. Try I2C scanner sketch to confirm address

### Drifting Angles

- Complement filter ratio may need tuning
- Increase gyro sample rate
- Re-calibrate if sensor temperature changes

### Noise in Readings

- Reduce filter bandwidth to 10 Hz
- Add more averaging samples
- Shield wires from EMI sources

## Gesture Threshold Values

```
Tilt thresholds: ±10 degrees
Modify line:
    if (pitch_gyro < -10)  // Change -10 to your value
```

## Applications

- ✓ Gesture-controlled car (forward/backward/left/right tilt)
- ✓ Motion detection alarm
- ✓ IMU data logging
- ✓ Orientation sensing
- ✓ Angle measurement
- ✓ Vibration monitoring
