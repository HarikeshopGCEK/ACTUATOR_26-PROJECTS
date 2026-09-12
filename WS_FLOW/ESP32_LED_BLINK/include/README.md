# ESP32 LED Blink Test

## Overview

Simplest electronics project - turn an LED ON and OFF using GPIO.

## Hardware Required

- ESP32 DevKit
- LED (any color)
- Resistor 220Ω (to limit current)
- Power supply

## Wiring

```
GPIO2 ─→ Resistor 220Ω ─→ LED Anode (long leg)
                           LED Cathode (short leg) ─→ GND
```

## What It Does

- Turns LED ON for 1 second
- Turns LED OFF for 1 second
- Repeats forever

## Concepts Learned

- Digital OUTPUT
- GPIO control
- Timing with delay()
- Serial output

**This is the "Hello World" of electronics!**
