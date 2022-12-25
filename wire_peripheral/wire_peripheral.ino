#include <Wire.h>

#define I2C_PERIPHERAL_ADDRESS (0x90)

void setup() {
    Wire.begin();
    // Wire.end() should undo everything done by Wire.begin()
    Wire.end();
    // So calling Wire.begin() again should still work the same
    // as not having done the two lines above
    Wire.begin(I2C_PERIPHERAL_ADDRESS);
    Wire.setWireTimeout();

    // Should this work in peripheral mode???
    Wire.setClock(400000);

    Wire.onReceive(peripheralReceiveHandler);
    Wire.onRequest(peripheralSendHandler);
}

void error() {
    // Add some kind of error handler here
}

void peripheralReceiveHandler(int count) {
    uint8_t data[32] = {0};
    while (Wire.available()) {
        // These two should be the same value
        data[0] = Wire.peek();
        data[1] = Wire.read();
        if (Wire.getWireTimeoutFlag()) {
            Wire.clearWireTimeoutFlag();
        }
    }

}

void peripheralSendHandler() {
    size_t sent_count = 0;
    uint8_t data[32] = {0x02, 0x03};

    sent_count = Wire.write(0x01);
    if (sent_count != 1) error();
    sent_count = Wire.write(data, 2);
    if (sent_count != 2) error();
    sent_count = Wire.write("some text");
    if (sent_count != 9) error();
}

void loop() {
    size_t arrived_count = 0;
    uint8_t transmission_state = 0;
    uint8_t data[32] = {0x02, 0x03};

    transmission_state = Wire.endTransmission(false);
    if (transmission_state != 0) error();

    // Read 32 bytes from a peripheral
    arrived_count = Wire.requestFrom(I2C_PERIPHERAL_ADDRESS, 32, false);
    if (arrived_count != 32) error();


    // Again, but the default stop bits
    Wire.beginTransmission(I2C_PERIPHERAL_ADDRESS);
    sent_count = Wire.write(data, 32);
    if (sent_count != 32) error();
    transmission_state = Wire.endTransmission();
    if (transmission_state != 0) error();
    arrived_count = Wire.requestFrom(I2C_PERIPHERAL_ADDRESS, 1);
    if (arrived_count != 1) error();
}
