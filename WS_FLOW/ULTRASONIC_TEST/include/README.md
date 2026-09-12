# Ultrasonic Sensor Test Project

## Overview

Testing Ultrasonic sensors (HC-SR04) for distance measurement and obstacle detection.

## Hardware Required

- ESP32 DevKit
- Ultrasonic Sensor Module (HC-SR04)
- Power Supply (5V for sensor, 3.3V logic from ESP32)
- Resistor network for level shifting (5V to 3.3V)

## Pin Configuration

- Left Ultrasonic TRIG: GPIO13
- Left Ultrasonic ECHO: GPIO35 (input only)
- Right Ultrasonic TRIG: GPIO14
- Right Ultrasonic ECHO: GPIO36 (input only)
- Power: 5V (from voltage regulator)
- Ground: GND

## Features Tested

- Single distance measurement
- Dual sensor reading
- Distance averaging for noise reduction
- Obstacle detection
- Dead zone detection
