# Motor Driver (TB6612FNG) Test

## What It Does

Controls 2 DC motors - makes them go forward, backward, left, and right.

## How It Works

```
ESP32 sends signals → TB6612FNG chip → Motors spin
```

## Pin Connections

```
GPIO23 → STBY (Enable/Disable driver)

Motor A (Left):
  GPIO18 → IN1 (direction)
  GPIO19 → IN2 (direction)
  GPIO33 → PWM (speed 0-255)

Motor B (Right):
  GPIO26 → IN1 (direction)
  GPIO27 → IN2 (direction)
  GPIO25 → PWM (speed 0-255)
```

## Motor Commands

- **Forward:** Both motors spin forward
- **Backward:** Both motors spin backward
- **Turn Left:** Left motor stops, right motor goes
- **Turn Right:** Right motor stops, left motor goes
- **Stop:** Both motors off

## Simple Code Example

```cpp
// Go forward at speed 200
digitalWrite(LEFT_IN1, HIGH);
digitalWrite(LEFT_IN2, LOW);
analogWrite(LEFT_PWM, 200);  // 0-255 speed
```

## Real-World Use

- 🚗 Robot cars
- 🤖 Autonomous vehicles
- 🎮 Remote control toys
