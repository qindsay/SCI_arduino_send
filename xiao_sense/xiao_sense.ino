
#include <ArduinoBLE.h>

BLEService test("19B10000-E8F2-537E-4F6C-D104768A1214");
BLECharacteristic sendCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify, 4);
BLECharacteristic receiveCharacteristic("20B1D001-E8F2-537E-4F6C-A104768A1517", BLEWrite | BLENotify, 4);

void setup() {
  Serial.begin(9600); //baud rate is currently 9600
  while (!Serial);

  Serial.println("Beginning setup...");
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
  test.addCharacteristic(receiveCharacteristic);

  // add service
  BLE.addService(test);

  // set initial value for characeristic:
  int16_t empty[2] = {0};
  
  sendCharacteristic.writeValue(empty, 4);
  receiveCharacteristic.writeValue(empty, 4);

  // start advertising
  BLE.advertise();
  Serial.print("BLE Address: ");
  Serial.println(BLE.address());

  Serial.println("BLE Setup Done!");
}

void loop() {
  BLE.poll(); //necessary to be able to send values

  if (receiveCharacteristic.written()) { //only sends/receives if computer writes to it
    //================= send values from arduino ================ 
    int16_t sendVal1 = random(-250, 251); //can send ints from -32,768 to 32,767
    int16_t sendVal2 = random(-250, 251);

    uint8_t buffer1[4];
    buffer1[0] = sendVal1 & 0xFF;
    buffer1[1] = (sendVal1 >> 8) & 0xFF;
    buffer1[2] = sendVal2 & 0xFF;
    buffer1[3] = (sendVal2 >> 8) & 0xFF;
    
    Serial.print("sent value: ");
    Serial.print(sendVal1);
    Serial.print(", ");
    Serial.println(sendVal2);
    sendCharacteristic.writeValue(buffer1, 4);

    //============ receiving values from computer =================

    uint8_t buffer2[4];
    receiveCharacteristic.readValue(buffer2, 4);
    int16_t receiveVal1 = (buffer2[1] << 8) | buffer2[0]; 
    int16_t receiveVal2 = (buffer2[3] << 8) | buffer2[2];

    Serial.print("received value: ");
    Serial.print(receiveVal1);
    Serial.print(", ");
    Serial.println(receiveVal2);

    delay(200); //waits 200 ms between sends/receives.
  }
}