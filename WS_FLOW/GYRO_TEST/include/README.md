# MPU6050 Gyroscope Test

## What It Does

Measures motion - which way is up, how fast you're spinning.

## How It Works

```
MPU6050 = Accelerometer + Gyroscope

Accelerometer: Measures tilt (X, Y, Z direction)
Gyroscope:     Measures rotation speed (spinning)
```

## Pin Connections (ESP8266)

```
D1 (GPIO5) → SCL (clock line)
D2 (GPIO4) → SDA (data line)
GND        → GND
3.3V       → VCC
```

## What You Measure

```
Accel [m/s²]: X=0.15  Y=0.42  Z=9.81
Gyro [rad/s]: X=0.0043  Y=-0.0012  Z=0.0001
Temp: 28.5°C
```

## Sensor Values Explained

- **X axis:** Tilt left/right (roll)
- **Y axis:** Tilt forward/backward (pitch)
- **Z axis:** Vertical acceleration
- **Temp:** Internal chip temperature

## Real-World Use

- 🎮 Game controllers (motion control)
- 📱 Phone orientation
- 🚗 Tilt detection
- 🎯 Gesture recognition
- ⚖️ Balance sensors

## Simple Code

```cpp
sensors_event_t a, g, temp;
mpu.getEvent(&a, &g, &temp);

float accelX = a.acceleration.x;  // m/s²
float gyroX = g.gyro.x;           // rad/s
float tempC = temp.temperature;   // °C
```

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
