# IR Sensor Test

## What It Does

Reads the digital output of two IR sensors and prints their values.

## How It Works

```
The sensor module decides whether the surface is detected.
The ESP32 only reads the module's digital output.
```

## Pin Connections

```
Left Sensor:  GPIO32 (digital input)
Right Sensor: GPIO34 (digital input)

Power: 5V (from voltage regulator)
```

## Output

```
Left: 0 | Right: 1
```

`0` means LOW and `1` means HIGH. The meaning of LOW or HIGH
depends on the IR sensor module.

## Code Idea

```
int leftSensor = digitalRead(IR_LEFT);
int rightSensor = digitalRead(IR_RIGHT);
```

No `analogRead()`, threshold, color detection, or line-following logic is used.
