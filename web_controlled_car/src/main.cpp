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

<html>

<head>

<meta name="viewport"
      content="width=device-width,
               initial-scale=1,
               maximum-scale=1,
               user-scalable=no">

<title>ROBOCEK CAR</title>

<style>

* {
    box-sizing: border-box;
    -webkit-tap-highlight-color: transparent;
}

body {
    margin: 0;
    background: #090d12;
    color: white;
    font-family: Arial, sans-serif;
    overflow: hidden;
}

.container {
    max-width: 500px;
    min-height: 100vh;
    margin: auto;
    padding: 20px;
}

/* HEADER */

.header {
    display: flex;
    justify-content: space-between;
    align-items: center;
    margin-bottom: 35px;
}

.logo {
    font-size: 23px;
    font-weight: 800;
    letter-spacing: 1px;
}

.online {
    display: flex;
    align-items: center;
    gap: 7px;
    font-size: 12px;
    color: #8b96a5;
}

.dot {
    width: 9px;
    height: 9px;
    border-radius: 50%;
    background: #22c55e;
    box-shadow: 0 0 12px #22c55e;
}

/* CONTROL */

.controls {
    width: 100%;
    display: grid;

    grid-template-columns:
        1fr 1fr 1fr;

    grid-template-rows:
        90px 90px 90px;

    gap: 14px;
}

button {
    border: none;
    color: white;
    font-weight: bold;
    touch-action: manipulation;
}

.control {
    background: #151b23;

    border: 1px solid #26303c;

    border-radius: 22px;

    font-size: 32px;

    box-shadow:
        0 8px 20px rgba(0,0,0,.3);

    transition: .08s;
}

.control:active {
    transform: scale(.93);
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

    font-size: 17px;

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
    margin-top: 35px;

    background: #121820;

    border: 1px solid #202a35;

    border-radius: 18px;

    padding: 20px;
}

.speed-header {
    display: flex;
    justify-content: space-between;

    margin-bottom: 15px;
}

.speed-title {
    font-size: 12px;
    color: #7f8a98;
    letter-spacing: 1px;
}

.speed-value {
    font-weight: bold;
}

input[type="range"] {
    width: 100%;

    accent-color: #38bdf8;
}

/* KEYBOARD */

.keyboard {
    text-align: center;

    margin-top: 18px;

    color: #4f5a68;

    font-size: 11px;
}

</style>

</head>

<body>

<div class="container">

    <div class="header">

        <div class="logo">
            🤖 ROBOCEK
        </div>

        <div class="online">
            <span class="dot"></span>
            CONNECTED
        </div>

    </div>


    <div class="controls">

        <button
            class="control forward"
            ontouchstart="start('forward')"
            ontouchend="stop()"
            onmousedown="start('forward')"
            onmouseup="stop()">

            ▲

        </button>


        <button
            class="control left"
            ontouchstart="start('left')"
            ontouchend="stop()"
            onmousedown="start('left')"
            onmouseup="stop()">

            ◀

        </button>


        <button
            class="control stop"
            onclick="stop()">

            STOP

        </button>


        <button
            class="control right"
            ontouchstart="start('right')"
            ontouchend="stop()"
            onmousedown="start('right')"
            onmouseup="stop()">

            ▶

        </button>


        <button
            class="control backward"
            ontouchstart="start('backward')"
            ontouchend="stop()"
            onmousedown="start('backward')"
            onmouseup="stop()">

            ▼

        </button>

    </div>


    <div class="speed-card">

        <div class="speed-header">

            <span class="speed-title">
                SPEED
            </span>

            <span class="speed-value">
                <span id="speedValue">200</span>
            </span>

        </div>

        <input
            id="speed"
            type="range"
            min="0"
            max="255"
            value="200"
            oninput="changeSpeed(this.value)">

    </div>


    <div class="keyboard">
        W A S D / ARROW KEYS
    </div>

</div>


<script>

let active = false;


// =========================
// SEND COMMAND
// =========================

function start(direction)
{
    active = true;

    fetch("/move?dir=" + direction);
}


function stop()
{
    if (!active)
        return;

    active = false;

    fetch("/move?dir=stop");
}


// =========================
// SPEED
// =========================

function changeSpeed(value)
{
    document.getElementById("speedValue").innerText = value;

    fetch("/speed?value=" + value);
}


// =========================
// KEYBOARD
// =========================

document.addEventListener("keydown", function(e)
{
    if (e.repeat)
        return;

    if (e.key === "ArrowUp" || e.key === "w")
        start("forward");

    else if (e.key === "ArrowDown" || e.key === "s")
        start("backward");

    else if (e.key === "ArrowLeft" || e.key === "a")
        start("left");

    else if (e.key === "ArrowRight" || e.key === "d")
        start("right");

    else if (e.key === " ")
        stop();
});


document.addEventListener("keyup", function(e)
{
    if (
        e.key === "ArrowUp" ||
        e.key === "ArrowDown" ||
        e.key === "ArrowLeft" ||
        e.key === "ArrowRight" ||
        e.key === "w" ||
        e.key === "a" ||
        e.key === "s" ||
        e.key === "d"
    )
    {
        stop();
    }
});


// Prevent scrolling while controlling

document.addEventListener(
    "touchmove",
    function(e)
    {
        e.preventDefault();
    },
    { passive: false }
);

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