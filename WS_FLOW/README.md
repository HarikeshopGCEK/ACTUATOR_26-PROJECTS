# WS_FLOW Learning Projects

## 📚 Simple Projects for Students

All projects are **simplified** to help you understand core concepts without complexity.

---

## 🌟 Learning Path

### **1. ESP32_LED_BLINK** (Start Here!)

**Learn:** Basic digital control - turn ON and OFF

```
GPIO → LED → Done! ✓
```

- **Concepts:** digitalWrite(), delay()
- **Time:** 5 minutes to understand
- **Hardware:** LED + Resistor

---

### **2. MOTOR_DRIVER_TEST**

**Learn:** How to control DC motors

```
GPIO → TB6612FNG → Motors spin
```

- **Concepts:** Direction (IN1/IN2), Speed (PWM)
- **Key Functions:** moveForward(), moveBackward(), turnLeft(), turnRight()
- **Real Use:** Robot cars, tank treads, drones
- **Dependencies:** None

---

### **3. ULTRASONIC_TEST**

**Learn:** Measure distance with sound waves

```
Send pulse → Wait for echo → Calculate distance
```

- **Concepts:** Time measurement, Sound speed
- **Output:** Distance in centimeters
- **Sensor:** HC-SR04 (2 available)
- **Real Use:** Obstacle avoidance, proximity detection
- **Dependencies:** Core Arduino

---

### **4. IR_SENSOR_TEST**

**Learn:** Detect black/white surfaces (line following)

```
IR LED → Bounce off surface → Detect black/white
```

- **Concepts:** Digital input, Threshold (2048)
- **Output:** [●●] forward, [●○] left, [○●] right, [○○] search
- **Sensors:** IR (2 available)
- **Real Use:** Line following robots
- **Dependencies:** Core Arduino

---

### **5. GYRO_TEST**

**Learn:** Measure motion with accelerometer & gyroscope

```
Tilt phone → MPU6050 measures → Which way is up?
```

- **Concepts:** I2C communication, Acceleration, Rotation rate
- **Output:** Raw sensor values (X, Y, Z)
- **Sensor:** MPU6050 (6-axis)
- **Real Use:** Game controllers, balance detection
- **Platform:** ESP8266 NodeMCU
- **Dependencies:** Adafruit MPU6050 library

---

## 📊 Quick Reference

| Project      | Concept          | Complexity | Time  |
| ------------ | ---------------- | ---------- | ----- |
| LED_BLINK    | Digital Output   | ⭐         | 5min  |
| MOTOR_DRIVER | PWM Control      | ⭐⭐       | 15min |
| ULTRASONIC   | Timing/Distance  | ⭐⭐       | 15min |
| IR_SENSOR    | Analog Threshold | ⭐⭐       | 15min |
| GYRO_TEST    | I2C/Motion       | ⭐⭐⭐     | 20min |

---

## 🎯 For Teachers

**Recommended Teaching Order:**

1. LED_BLINK (Digital basics)
2. MOTOR_DRIVER (Control concept)
3. ULTRASONIC (Sensor reading)
4. IR_SENSOR (Threshold detection)
5. GYRO_TEST (Advanced I2C)

**Each project emphasizes:**

- ✓ What does it DO?
- ✓ How does it WORK?
- ✓ Real-world APPLICATIONS
- ✓ NO complexity (calibration, filtering, etc.)

---

## 🔧 Building Your Own Project

**Combine any sensor with motor control:**

```
IR_SENSOR → Detect line
         ↓
   MOTOR_DRIVER → Follow line
```

Example: Simple line-following robot = IR_SENSOR + MOTOR_DRIVER

---

## 📱 Serial Output Format

All projects use **115200 baud** for debugging:

```
=== PROJECT NAME ===
Reading 1: [value]
Reading 2: [value]
...
```

---

## ✅ Everything Works As-Is

- ✓ No configuration needed
- ✓ GPIO pins verified
- ✓ I2C setup correct
- ✓ Thresholds tested
- ✓ Ready to compile and upload

**Just connect hardware and press Upload!**
