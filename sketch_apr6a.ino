
#include <ArduinoBLE.h>

BLEService test("19B10000-E8F2-537E-4F6C-D104768A1214");
BLECharacteristic sendCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify, 4);

// const int ledPin = LED_BUILTIN; // pin to use for the LED

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // set LED pin to output mode
  // pinMode(ledPin, OUTPUT);

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");
    while (1);
  }

  // set advertised local name and service UUID:
  BLE.setLocalName("MyTest");
  BLE.setAdvertisedService(test);

  // add the characteristic to the service
  test.addCharacteristic(sendCharacteristic);

  // add service
  BLE.addService(test);

  // set the initial value for the characeristic:
  float empty = 0.0f;
  uint8_t buffer[4];
  memcpy(buffer, &empty, sizeof(empty));
  sendCharacteristic.writeValue(buffer, 4);

  // start advertising
  BLE.advertise();
  Serial.println(BLE.address());


  Serial.println("BLE Setup Done");
 
}

void loop() {
  // listen for Bluetooth® Low Energy peripherals to connect:
  // BLEDevice central = BLE.central();
  float sendVal = 1.0f;

  uint8_t buffer[4];
  memcpy(buffer, &sendVal, sizeof(sendVal));

  // if a central is connected to peripheral:
  // if (central) {
  Serial.print("write value: ");
  Serial.println(sendVal);
  // print the central's MAC address:
  // Serial.println(central.address());
  sendCharacteristic.writeValue(buffer, 4);
  //}

  delay(1000);
}

// #include <ArduinoBLE.h>

// BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // Bluetooth® Low Energy LED Service

// // Bluetooth® Low Energy LED Switch Characteristic - custom 128-bit UUID, read and writable by central
// BLEByteCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

// const int ledPin = LED_BUILTIN; // pin to use for the LED

// void setup() {
//   Serial.begin(9600);
//   while (!Serial);

//   // set LED pin to output mode
//   pinMode(ledPin, OUTPUT);

//   // begin initialization
//   if (!BLE.begin()) {
//     Serial.println("starting Bluetooth® Low Energy module failed!");

//     while (1);
//   }

//   // set advertised local name and service UUID:
//   BLE.setLocalName("LED");
//   BLE.setAdvertisedService(ledService);

//   // add the characteristic to the service
//   ledService.addCharacteristic(switchCharacteristic);

//   // add service
//   BLE.addService(ledService);

//   // set the initial value for the characeristic:
//   switchCharacteristic.writeValue(0);

//   // start advertising
//   BLE.advertise();

//   Serial.println("BLE LED Peripheral");
// }

// void loop() {
//   // listen for Bluetooth® Low Energy peripherals to connect:
//   BLEDevice central = BLE.central();

//   // if a central is connected to peripheral:
//   if (central) {
//     Serial.print("Connected to central: ");
//     // print the central's MAC address:
//     Serial.println(central.address());

//     // while the central is still connected to peripheral:
//   while (central.connected()) {
//         if (switchCharacteristic.written()) {
//           if (switchCharacteristic.value()) {   
//             Serial.println("LED on");
//             digitalWrite(ledPin, LOW); // changed from HIGH to LOW       
//           } else {                              
//             Serial.println(F("LED off"));
//             digitalWrite(ledPin, HIGH); // changed from LOW to HIGH     
//           }
//         }
//       }

//     // when the central disconnects, print it out:
//     Serial.print(F("Disconnected from central: "));
//     Serial.println(central.address());
//   }
// }
