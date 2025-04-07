
#include <ArduinoBLE.h>

BLEService test("19B10000-E8F2-537E-4F6C-D104768A1214");
BLECharacteristic sendCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify, 4);

void setup() {
  Serial.begin(9600);
  while (!Serial);

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

  // set initial value for characeristic:
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
  BLE.poll(); //necessary to be able to send values
  float sendVal = 1.0f;

  uint8_t buffer[4];
  memcpy(buffer, &sendVal, sizeof(sendVal));

  Serial.print("write value: ");
  Serial.println(sendVal);

  sendCharacteristic.writeValue(buffer, 4);

  delay(1000);
}