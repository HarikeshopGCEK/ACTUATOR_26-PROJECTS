# IR Sensor Test Project (Digital Only)

## Overview

Simple digital IR sensor testing for Black/White surface detection (line following).

## Hardware Required

- ESP32 DevKit
- IR Sensor Module (2x) - KY-033, TCRT5000, or similar
- Power Supply (5V for sensors, 3.3V logic from ESP32)

## Pin Configuration

- **Left IR Sensor:** GPIO32 (digital input)
- **Right IR Sensor:** GPIO34 (digital input)
- **Power:** 5V (from voltage regulator)
- **Ground:** GND

## Detection Logic

- **BLACK surface (Line detected):** Digital = LOW (0)
  - Sensor reads < 2048 (dark)
- **WHITE surface (No line):** Digital = HIGH (1)
  - Sensor reads > 2048 (bright)

## Line Following States

```
[●●] = BOTH ON LINE → Move Forward
[●○] = LEFT ON LINE → Turn Left
[○●] = RIGHT ON LINE → Turn Right
[○○] = NO LINE → Search
```

## Output Example

```
Raw: L=400 R=3800 | Digital: L=BLACK R=WHITE | Line: [●○]  LEFT LINE - Turn Left
```

## Simple & Reliable

- ✓ No calibration needed
- ✓ Fixed threshold (2048)
- ✓ Fast response
- ✓ Perfect for line follower robots
