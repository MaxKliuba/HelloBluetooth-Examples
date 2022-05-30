/*
 * HelloBluetooth - AdvancedExample
 * https://github.com/MaxKliuba/HelloBluetooth-Examples
 * by MaxClub Technology, 2022
 */

#include <AsyncStream.h>
#include <EncButton.h>
#include <Servo.h>
#include <TimerMs.h>

#define bluetoothSerial Serial

#define BUTTON_PIN 3
#define RED_LED_PWM_PIN 5
#define YELLOW_LED_PIN 6
#define GREEN_LED_PIN 7
#define SERVO_PIN 8
#define LIGHT_SENSOR_ANALOG_PIN A0

#define COMMAND_TERMINATOR '\n'
#define TAG_TERMINATOR '#'

#define SYNC_TAG "sync"
#define GREEN_LED_TAG "green"
#define YELLOW_LED_TAG "yellow"
#define RED_LED_TAG "red"
#define LIGHT_SENSOR_TAG "light"
#define SERVO_TAG "servo"
#define VOICE_TAG "voice"

int redLedPwmValue = 0;

AsyncStream<100> asyncSerial(&bluetoothSerial, COMMAND_TERMINATOR);
EncButton<EB_TICK, BUTTON_PIN> button(INPUT_PULLUP);
Servo servo;
TimerMs lightSensorCheckTimer(1000, 1, 0);

void setup() {
  bluetoothSerial.begin(9600);

  servo.attach(SERVO_PIN);
  servo.write(0);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PWM_PIN, OUTPUT);
}

void loop() {
  listenBluetoothSerial();

  checkButtonState();
  if (lightSensorCheckTimer.tick()) {
    checkLightSensorState();
  }
}

void checkButtonState() {
  button.tick();

  if (button.hasClicks()) {
    switch (button.clicks) {
      case 1: {
          setGreenLedState(!digitalRead(GREEN_LED_PIN));
          break;
        }
      case 2: {
          setYellowLedState(!digitalRead(YELLOW_LED_PIN));
          break;
        }
      case 3: {
          setRedLedState(redLedPwmValue == 0);
          break;
        }
    }
  }

  static int direction = 1;
  byte valueFrom = 0;
  byte valueTo = 180;
  byte stepSize = 10;
  if (button.step()) {
    int servoPosition = constrain(servo.read() + stepSize * direction, valueFrom, valueTo);
    servo.write(servoPosition);
    String command = createCommand(SERVO_TAG, (String)servoPosition);
    writeBluetoothSerial(command);
  }
  if (button.releaseStep()) {
    direction = -direction;
  }
}

void checkLightSensorState() {
  static int lastValue = -1;
  int fromLow = 0;
  int fromHigh = 1024;
  int toLow = 0;
  int toHigh = 100;
  int value = getLightSensorValue();

  if (lastValue != value) {
    lastValue = value;
    String command = createCommand(LIGHT_SENSOR_TAG, (String)value + '%');
    writeBluetoothSerial(command);
  }
}

int getLightSensorValue() {
  int fromLow = 0;
  int fromHigh = 1024;
  int toLow = 0;
  int toHigh = 100;
  int value = analogRead(LIGHT_SENSOR_ANALOG_PIN);
  return constrain(map(value, fromLow, fromHigh, toLow, toHigh), toLow, toHigh);
}

void setGreenLedState(bool state) {
  digitalWrite(GREEN_LED_PIN, state);
  String command = createCommand(GREEN_LED_TAG, (String)state);
  writeBluetoothSerial(command);
}

void setYellowLedState(bool state) {
  digitalWrite(YELLOW_LED_PIN, state);
  String command = createCommand(YELLOW_LED_TAG, (String)state);
  writeBluetoothSerial(command);
}

void setRedLedState(bool state) {
  digitalWrite(RED_LED_PWM_PIN, state);
  redLedPwmValue = state * 255;
  String command = createCommand(RED_LED_TAG, (String)redLedPwmValue);
  writeBluetoothSerial(command);
}

void parseCommand(String command) {
  int tagIndex = command.indexOf(TAG_TERMINATOR);
  String tag = command.substring(0, tagIndex);
  String data = command.substring(tagIndex + 1);

  if (tag.equals(SYNC_TAG)) {
    writeBluetoothSerial(createCommand(GREEN_LED_TAG, (String)digitalRead(GREEN_LED_PIN)));
    writeBluetoothSerial(createCommand(YELLOW_LED_TAG, (String)digitalRead(YELLOW_LED_PIN)));
    writeBluetoothSerial(createCommand(RED_LED_TAG, (String)redLedPwmValue));
    writeBluetoothSerial(createCommand(LIGHT_SENSOR_TAG, (String)getLightSensorValue() + '%'));
    writeBluetoothSerial(createCommand(SERVO_TAG, (String)servo.read()));
  } else if (tag.equals(GREEN_LED_TAG)) {
    byte ledState = data.length() > 0 && !data.equals("0");
    digitalWrite(GREEN_LED_PIN, ledState);
  } else if (tag.equals(YELLOW_LED_TAG)) {
    byte ledState = data.length() > 0 && !data.equals("0");
    digitalWrite(YELLOW_LED_PIN, ledState);
  } else if (tag.equals(RED_LED_TAG)) {
    redLedPwmValue = data.toInt();
    analogWrite(RED_LED_PWM_PIN, redLedPwmValue);
  } else if (tag.equals(SERVO_TAG)) {
    int servoPosition = data.toInt();
    servo.write(servoPosition);
  } else if (tag.equals(VOICE_TAG)) {
    data.toLowerCase();
    if (data.indexOf("green") >= 0) {
      setGreenLedState(!digitalRead(GREEN_LED_PIN));
    }
    if (data.indexOf("yellow") >= 0) {
      setYellowLedState(!digitalRead(YELLOW_LED_PIN));
    }
    if (data.indexOf("red") >= 0) {
      setRedLedState(redLedPwmValue == 0);
    }
  } else {
    // TODO
  }
}

void listenBluetoothSerial() {
  if (asyncSerial.available()) {
    String command = asyncSerial.buf;
    command.trim();
    parseCommand(command);
  }
}

void writeBluetoothSerial(String command) {
  bluetoothSerial.println(command);
}

String createCommand(String tag, String data) {
  return tag + TAG_TERMINATOR + data;
}
