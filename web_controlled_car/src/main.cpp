#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// =========================
// MOTOR PINS
// =========================

#define RC_MOTOR_STBY 23

// Left motor
#define RC_LEFT_PWM 33
#define RC_LEFT_IN1 18
#define RC_LEFT_IN2 19

// Right motor
#define RC_RIGHT_PWM 25
#define RC_RIGHT_IN1 26
#define RC_RIGHT_IN2 27

// =========================
// WIFI
// =========================

const char *SSID = "ROBOCEK-CAR";
const char *PASSWORD = "12345678";

WebServer server(80);

// =========================
// MOTOR SPEED
// =========================

int motorSpeed = 200;

// =========================
// MOTOR FUNCTIONS
// =========================

void leftMotor(int speed)
{
    if (speed > 0)
    {
        digitalWrite(RC_LEFT_IN1, HIGH);
        digitalWrite(RC_LEFT_IN2, LOW);
    }
    else if (speed < 0)
    {
        digitalWrite(RC_LEFT_IN1, LOW);
        digitalWrite(RC_LEFT_IN2, HIGH);
    }
    else
    {
        digitalWrite(RC_LEFT_IN1, LOW);
        digitalWrite(RC_LEFT_IN2, LOW);
    }

    analogWrite(RC_LEFT_PWM, abs(speed));
}

void rightMotor(int speed)
{
    if (speed > 0)
    {
        digitalWrite(RC_RIGHT_IN1, HIGH);
        digitalWrite(RC_RIGHT_IN2, LOW);
    }
    else if (speed < 0)
    {
        digitalWrite(RC_RIGHT_IN1, LOW);
        digitalWrite(RC_RIGHT_IN2, HIGH);
    }
    else
    {
        digitalWrite(RC_RIGHT_IN1, LOW);
        digitalWrite(RC_RIGHT_IN2, LOW);
    }

    analogWrite(RC_RIGHT_PWM, abs(speed));
}

void stopCar()
{
    leftMotor(0);
    rightMotor(0);
}

void forward()
{
    leftMotor(motorSpeed);
    rightMotor(motorSpeed);
}

void backward()
{
    leftMotor(-motorSpeed);
    rightMotor(-motorSpeed);
}

void left()
{
    leftMotor(-motorSpeed);
    rightMotor(motorSpeed);
}

void right()
{
    leftMotor(motorSpeed);
    rightMotor(-motorSpeed);
}

// =========================
// WEB PAGE
// =========================

const char HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no, viewport-fit=cover">
<title>ROBOCEK CAR</title>
<style>
* {
    box-sizing: border-box;
    -webkit-tap-highlight-color: transparent;
    -webkit-touch-callout: none;
    -webkit-user-select: none;
    -khtml-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
}

html, body {
    margin: 0;
    padding: 0;
    width: 100%;
    height: 100%;
    background: #090d12;
    color: #ffffff;
    font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif;
    -webkit-text-size-adjust: 100%;
    text-size-adjust: 100%;
    overflow: hidden;
}

body {
    display: flex;
    align-items: center;
    justify-content: center;
}

.container {
    width: 100%;
    max-width: 420px;
    height: 100vh;
    height: 100dvh;
    padding: 24px 20px;
    display: flex;
    flex-direction: column;
    justify-content: space-between;
    margin: auto;
}

/* HEADER */
.header {
    display: flex;
    justify-content: space-between;
    align-items: center;
}

.logo {
    font-size: 22px;
    font-weight: 800;
    letter-spacing: 1px;
    display: flex;
    align-items: center;
    gap: 8px;
}

.online {
    display: flex;
    align-items: center;
    gap: 8px;
    font-size: 12px;
    font-weight: 600;
    color: #8b96a5;
    letter-spacing: 0.5px;
}

.dot {
    width: 9px;
    height: 9px;
    border-radius: 50%;
    background: #22c55e;
    box-shadow: 0 0 10px #22c55e;
}

/* CONTROL */
.controls-wrapper {
    display: flex;
    justify-content: center;
    align-items: center;
    width: 100%;
    margin: 20px 0;
}

.controls {
    width: 100%;
    max-width: 320px;
    display: grid;
    grid-template-columns: repeat(3, 1fr);
    grid-template-rows: repeat(3, 90px);
    gap: 14px;
}

button {
    border: none;
    outline: none;
    color: white;
    font-weight: bold;
    touch-action: none;
    display: flex;
    align-items: center;
    justify-content: center;
    cursor: pointer;
    line-height: 1;
    -webkit-touch-callout: none;
    -webkit-user-select: none;
    user-select: none;
}

.control {
    background: #151b23;
    border: 1px solid #26303c;
    border-radius: 22px;
    font-size: 32px;
    box-shadow: 0 8px 20px rgba(0,0,0,.3);
    transition: transform 0.08s ease, background 0.08s ease;
}

.control:active {
    transform: scale(0.93);
    background: #27313e;
}

/* POSITIONS */
.forward {
    grid-column: 2;
    grid-row: 1;
}

.left {
    grid-column: 1;
    grid-row: 2;
}

.stop {
    grid-column: 2;
    grid-row: 2;
    background: #351a1e;
    color: #ff5964;
    font-size: 16px;
    letter-spacing: 1px;
    border: 1px solid #57262d;
}

.stop:active {
    background: #57262d;
}

.right {
    grid-column: 3;
    grid-row: 2;
}

.backward {
    grid-column: 2;
    grid-row: 3;
}

/* SPEED */
.speed-card {
    background: #121820;
    border: 1px solid #202a35;
    border-radius: 18px;
    padding: 18px 20px;
}

.speed-header {
    display: flex;
    justify-content: space-between;
    align-items: center;
    margin-bottom: 14px;
}

.speed-title {
    font-size: 12px;
    font-weight: 700;
    color: #7f8a98;
    letter-spacing: 1px;
}

.speed-value {
    font-weight: 700;
    font-size: 16px;
    color: #38bdf8;
}

input[type="range"] {
    width: 100%;
    height: 6px;
    border-radius: 3px;
    background: #26303c;
    accent-color: #38bdf8;
    cursor: pointer;
}

/* KEYBOARD */
.keyboard {
    text-align: center;
    color: #4f5a68;
    font-size: 11px;
    font-weight: 600;
    letter-spacing: 0.5px;
}
</style>
</head>
<body oncontextmenu="return false;">

<div class="container">
    <div class="header">
        <div class="logo">🤖 ROBOCEK</div>
        <div class="online">
            <span class="dot"></span>
            CONNECTED
        </div>
    </div>

    <div class="controls-wrapper">
        <div class="controls">
            <button class="control forward"
                ontouchstart="handleTouchStart(event, 'forward')" ontouchend="handleTouchEnd(event)" ontouchcancel="handleTouchEnd(event)"
                onmousedown="handleMouseDown('forward')" onmouseup="handleMouseUp()" onmouseleave="handleMouseUp()">
                ▲
            </button>

            <button class="control left"
                ontouchstart="handleTouchStart(event, 'left')" ontouchend="handleTouchEnd(event)" ontouchcancel="handleTouchEnd(event)"
                onmousedown="handleMouseDown('left')" onmouseup="handleMouseUp()" onmouseleave="handleMouseUp()">
                ◀
            </button>

            <button class="control stop"
                ontouchstart="handleTouchStart(event, 'stop')" ontouchend="handleTouchEnd(event)"
                onclick="stop()">
                STOP
            </button>

            <button class="control right"
                ontouchstart="handleTouchStart(event, 'right')" ontouchend="handleTouchEnd(event)" ontouchcancel="handleTouchEnd(event)"
                onmousedown="handleMouseDown('right')" onmouseup="handleMouseUp()" onmouseleave="handleMouseUp()">
                ▶
            </button>

            <button class="control backward"
                ontouchstart="handleTouchStart(event, 'backward')" ontouchend="handleTouchEnd(event)" ontouchcancel="handleTouchEnd(event)"
                onmousedown="handleMouseDown('backward')" onmouseup="handleMouseUp()" onmouseleave="handleMouseUp()">
                ▼
            </button>
        </div>
    </div>

    <div class="speed-card">
        <div class="speed-header">
            <span class="speed-title">SPEED</span>
            <span class="speed-value"><span id="speedValue">200</span></span>
        </div>
        <input id="speed" type="range" min="0" max="255" value="200" oninput="changeSpeed(this.value)">
    </div>

    <div class="keyboard">
        W A S D / ARROW KEYS
    </div>
</div>

<script>
let active = false;
let isTouch = false;

function start(direction) {
    if (direction === 'stop') {
        stop();
        return;
    }
    active = true;
    fetch("/move?dir=" + direction);
}

function stop() {
    if (!active) return;
    active = false;
    fetch("/move?dir=stop");
}

function handleTouchStart(e, direction) {
    if (e) e.preventDefault();
    isTouch = true;
    start(direction);
}

function handleTouchEnd(e) {
    if (e) e.preventDefault();
    stop();
}

function handleMouseDown(direction) {
    if (isTouch) return;
    start(direction);
}

function handleMouseUp() {
    if (isTouch) return;
    stop();
}

function changeSpeed(value) {
    document.getElementById("speedValue").innerText = value;
    fetch("/speed?value=" + value);
}

document.addEventListener("contextmenu", function(e) {
    e.preventDefault();
    return false;
}, false);

document.addEventListener("selectstart", function(e) {
    e.preventDefault();
    return false;
}, false);

document.addEventListener("keydown", function(e) {
    if (e.repeat) return;
    if (e.key === "ArrowUp" || e.key === "w" || e.key === "W") start("forward");
    else if (e.key === "ArrowDown" || e.key === "s" || e.key === "S") start("backward");
    else if (e.key === "ArrowLeft" || e.key === "a" || e.key === "A") start("left");
    else if (e.key === "ArrowRight" || e.key === "d" || e.key === "D") start("right");
    else if (e.key === " ") stop();
});

document.addEventListener("keyup", function(e) {
    if (["ArrowUp","ArrowDown","ArrowLeft","ArrowRight","w","a","s","d","W","A","S","D"].includes(e.key)) {
        stop();
    }
});

document.addEventListener("touchmove", function(e) {
    e.preventDefault();
}, { passive: false });
</script>
</body>
</html>
)rawliteral";

// =========================
// HTTP HANDLERS
// =========================

void handleRoot()
{
    server.send_P(
        200,
        "text/html",
        HTML);
}

void handleMove()
{
    String direction = server.arg("dir");

    if (direction == "forward")
        forward();

    else if (direction == "backward")
        backward();

    else if (direction == "left")
        left();

    else if (direction == "right")
        right();

    else
        stopCar();

    server.send(
        200,
        "text/plain",
        "OK");
}

void handleSpeed()
{
    if (server.hasArg("value"))
    {
        motorSpeed =
            constrain(
                server.arg("value").toInt(),
                0,
                255);
    }

    server.send(
        200,
        "text/plain",
        "OK");
}

// =========================
// SETUP
// =========================

void setup()
{
    Serial.begin(115200);

    // Motor pins

    pinMode(
        RC_MOTOR_STBY,
        OUTPUT);

    pinMode(
        RC_LEFT_PWM,
        OUTPUT);

    pinMode(
        RC_LEFT_IN1,
        OUTPUT);

    pinMode(
        RC_LEFT_IN2,
        OUTPUT);

    pinMode(
        RC_RIGHT_PWM,
        OUTPUT);

    pinMode(
        RC_RIGHT_IN1,
        OUTPUT);

    pinMode(
        RC_RIGHT_IN2,
        OUTPUT);

    // Enable motor driver

    digitalWrite(
        RC_MOTOR_STBY,
        HIGH);

    stopCar();

    // =========================
    // ACCESS POINT
    // =========================

    WiFi.mode(WIFI_AP);

    WiFi.softAP(
        SSID,
        PASSWORD);

    Serial.println();
    Serial.println("==========================");
    Serial.println("ROBOCEK CAR");
    Serial.println("==========================");

    Serial.print("WiFi: ");
    Serial.println(SSID);

    Serial.print("IP: ");
    Serial.println(
        WiFi.softAPIP());

    // =========================
    // SERVER
    // =========================

    server.on(
        "/",
        handleRoot);

    server.on(
        "/move",
        handleMove);

    server.on(
        "/speed",
        handleSpeed);

    server.begin();

    Serial.println(
        "Web controller ready");
}

// =========================
// LOOP
// =========================

void loop()
{
    server.handleClient();
}