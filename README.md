# HelloBluetooth - Examples
Приклади для застосунку [HelloBluetooth]()

## Опис
Даний застосунок дозволяє створювати та налаштовувати інтерфейс користувача для взаємодії із пристроями на платформі Arduino по Bluetooth. 
Щоб реалізувати роботу по Bluetooth зі сторони Arduino варто використовувати модулі HC-05, HC-06 та інші сумісні

## Схема підключення
Дані Bluetooth-модулі можна підключати до апаратного Serial:  
![SERIAL_TYPE](/Images/serial_type.png)    

Також є можливість емулювати програмний ```Serial``` за допомогою стандартної бібліотеки ```SoftwareSerial.h```. 
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
* [BluetoothMonitor](/Examples/BluetoothMonitor)
* [BaseExample](/Examples/BaseExample)
* [AdvancedExample](/Examples/AdvancedExample)
* [AsyncSerialExample](/Examples/AsyncSerialExample)

## Додатково
[HelloBluetooth]()
[Бібліотеки](/../../Libraries)