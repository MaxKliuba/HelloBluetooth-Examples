/*
 * HelloBluetooth - AsyncSerialExample
 * https://github.com/MaxKliuba/HelloBluetooth-Examples
 * by MaxClub Technology, 2022
 */
 
#include <AsyncStream.h>

#define SERIAL_TYPE 1 // 0 - Serial; 1 - SoftwareSerial

#if SERIAL_TYPE == 0
#define bluetoothSerial Serial
#else
#include <SoftwareSerial.h>
#define BLUETOOTH_RX 11
#define BLUETOOTH_TX 12
SoftwareSerial softwareSerial(BLUETOOTH_RX, BLUETOOTH_TX);
#define bluetoothSerial softwareSerial
#endif

#define COMMAND_TERMINATOR '\n'

AsyncStream<100> asyncSerial(&bluetoothSerial, COMMAND_TERMINATOR);

void setup() {
  bluetoothSerial.begin(9600);
}

void loop() {
  listenBluetoothSerial();
}

void listenBluetoothSerial() {
  if (asyncSerial.available()) {
    String data = asyncSerial.buf;
    data.trim();
    parseData(data);
  }
}

void parseData(String data) {
  // TODO
}

void writeBluetoothSerial(String data) {
  bluetoothSerial.println(data);
}
