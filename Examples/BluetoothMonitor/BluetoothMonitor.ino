/*
 * HelloBluetooth - BluetoothMonitor
 * https://github.com/MaxKliuba/HelloBluetooth-Examples
 * by MaxClub Technology, 2022
 */

#include <SoftwareSerial.h>

#define BLUETOOTH_RX 11
#define BLUETOOTH_TX 12

#define COMMAND_TERMINATOR '\n'

SoftwareSerial bluetoothSerial(BLUETOOTH_RX, BLUETOOTH_TX);

void setup() {
  Serial.begin(9600);
  Serial.println("***** [HelloBluetooth - BluetoothMonitor] *****");

  bluetoothSerial.begin(9600);
}

void loop() {
  listenBluetoothSerial();
  listenSerialMonitor();
}

void parseData(String data) {
  // TODO
}

void listenBluetoothSerial() {
  if (bluetoothSerial.available()) {
    String data = bluetoothSerial.readStringUntil(COMMAND_TERMINATOR);
    data.trim();
    writeSerialMonitor(data, false);
    parseData(data);
  }
}

void listenSerialMonitor() {
  if (Serial.available()) {
    String data = Serial.readStringUntil(COMMAND_TERMINATOR);
    data.trim();
    writeSerialMonitor(data, true);
    writeBluetoothSerial(data);
    parseData(data);
  }
}

void writeBluetoothSerial(String data) {
  bluetoothSerial.println(data);
}

void writeSerialMonitor(String data, bool output) {
  String commandStr = output ? "[<-]: " : "[->]: ";
  Serial.println(commandStr + data);
}
