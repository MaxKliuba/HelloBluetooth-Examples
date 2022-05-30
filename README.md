# HelloBluetooth - Examples
Приклади для роботи із застосунком [HelloBluetooth]()

## Опис
Даний застосунок дозволяє створювати та налаштовувати інтерфейс користувача для взаємодії із пристроями на платформі Arduino по Bluetooth. 
Щоб реалізувати роботу по Bluetooth зі сторони Arduino варто використовувати модулі HC-05, HC-06 та інші сумісні

## Схема підключення
Дані Bluetooth-модулі можна підключати до апаратного ```Serial```:  
![SERIAL_TYPE](/Images/serial_type.png)    

Також є можливість реалізувати програмний ```Serial``` за допомогою стандартної бібліотеки [SoftwareSerial](https://docs.arduino.cc/learn/built-in-libraries/software-serial). 
При такому типі з'єднання модуль можна під'єднати до будь-яких двох цифрових пінів Arduino, які додатково потрібно зазначити у коді програми:  
```c++
#include <SoftwareSerial.h>

#define BLUETOOTH_RX 11
#define BLUETOOTH_TX 12

SoftwareSerial bluetoothSerial(BLUETOOTH_RX, BLUETOOTH_TX);

void setup() {
  bluetoothSerial.begin(9600);
  
  // TODO
}

void loop() {
  // TODO
}
```  

![SOFTSERIAL_TYPE](/Images/softserial_type.png)  

## Приклади
* [BaseExample](/Examples/BaseExample)
* [AdvancedExample](/Examples/AdvancedExample)
* [BluetoothMonitor](/Examples/BluetoothMonitor)
* [AsyncSerialExample](/Examples/AsyncSerialExample)

## Додатково
* Застосунок [HelloBluetooth]()
* [Бібліотеки](/Libraries)