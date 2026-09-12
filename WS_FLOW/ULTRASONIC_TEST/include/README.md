# Ultrasonic Sensor (HC-SR04) Test

## What It Does

Measures distance using sound waves - like how bats navigate!

## How It Works

```
1. Send sound pulse from TRIG pin
2. Sound bounces off object
3. Receive echo on ECHO pin
4. Calculate: distance = (time / 2) × sound_speed
```

## Pin Connections

```
Left Sensor:
  GPIO13 → TRIG (trigger pulse out)
  GPIO35 → ECHO (echo pulse in)

Right Sensor:
  GPIO14 → TRIG (trigger pulse out)
  GPIO36 → ECHO (echo pulse in)

Power: 5V (from voltage regulator)
```

## What You Get

```
LEFT: 25.3 cm  |  RIGHT: 180.5 cm  |  CLEAR
```

## Detection Ranges

- Obstacle alert if < 20 cm
- Maximum range ~400 cm
- Blind spot < 2 cm

## Real-World Use

- 🚗 Robot obstacle avoidance
- 🚪 Door sensors
- 🤖 Parking assistance
- 🎯 Proximity alarms

## Important Note

- Needs 5V power (not 3.3V!)
- Use level shifter for ECHO pin
- Keep sensor clean
