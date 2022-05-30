# AsyhcSerialExample
Приклад асинхронного читання послідовного порту

## Опис
Реалізовано за допомогою бібліотеки [AsyncStream.h](https://github.com/GyverLibs/AsyncStream)

## Схема підключення
Підключення до апаратного ```Serial```:  
```c++
#define SERIAL_TYPE 0
```  
![SERIAL_TYPE](/../../Images/base_example_serial.png)  

Підключення до програмного ```SoftwareSerial```:  
```c++
#define SERIAL_TYPE 1
```  
![SERIAL_TYPE](/../../Images/base_example_softserial.png) 

## Додатково
[HelloBluetooth]()
[Бібліотеки](/../../Libraries)