/*
 * HelloBluetooth - BaseExample
 * https://github.com/MaxKliuba/HelloBluetooth-Examples
 * by MaxClub Technology, 2022
 */
 
#define SERIAL_TYPE 0 // 0 - Serial; 1 - SoftwareSerial

#if SERIAL_TYPE == 0
#define bluetoothSerial Serial
#else
#include <SoftwareSerial.h>
#define BLUETOOTH_RX 11
#define BLUETOOTH_TX 12
SoftwareSerial softwareSerial(BLUETOOTH_RX, BLUETOOTH_TX);
#define bluetoothSerial softwareSerial
#endif

#define BUTTON_PIN 3
#define LED_PIN 13

#define COMMAND_TERMINATOR '\n'
#define TAG_TERMINATOR '#'

#define SYNC_TAG "sync"
#define LED_TAG "led"

void setup() {
  bluetoothSerial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  listenBluetoothSerial();

  checkButtonState();
}

void checkButtonState() {
  static byte lastState = LOW;
  byte currentState = !digitalRead(BUTTON_PIN);

  if (lastState != currentState) {
    lastState = currentState;
    digitalWrite(LED_PIN, lastState);

    String command = createCommand(LED_TAG, (String)currentState);
    writeBluetoothSerial(command);
  }
}

void parseCommand(String command) {
  int tagIndex = command.indexOf(TAG_TERMINATOR);
  String tag = command.substring(0, tagIndex);
  String data = command.substring(tagIndex + 1);

  if (tag.equals(SYNC_TAG)) {
    byte ledState = digitalRead(LED_PIN);
    String command = createCommand(LED_TAG, (String)ledState);
    writeBluetoothSerial(command);
  } else if (tag.equals(LED_TAG)) {
    byte ledState = data.length() > 0 && !data.equals("0");
    digitalWrite(LED_PIN, ledState);
  } else {
    // TODO
  }
}

void listenBluetoothSerial() {
  if (bluetoothSerial.available()) {
    String command = bluetoothSerial.readStringUntil(COMMAND_TERMINATOR);
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
