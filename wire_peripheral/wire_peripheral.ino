/**
 * Example trying to exercise all the Wire API for the I2C/TWI peripheral mode.
 *
 * This example code is not really designed to work with any specific I2C
 * controller, it only exercises all relevant the methods, so it's a good check
 * to see if your Arduino Core compiles all the features.
 *
 * There are two Wire features that indicate their availability via macros:
 *   - WIRE_HAS_END -> Wire.end()
 *   - WIRE_HAS_TIMEOUT -> Wire.setWireTimeout(), Wire.getWireTimeoutFlag(),
 *                         Wire.clearWireTimeoutFlag()
 *
 * TODO: This could be updated, together with the wire_controller sketch so
 *       that they work together connecting two Arduino boards.
 */
#include <Wire.h>

#define I2C_PERIPHERAL_ADDRESS (0x90)

void setup() {
#if WIRE_HAS_END
    // Wire.end() should undo everything done by Wire.begin()
    // So these two lines should have no effect on the following Wire.begin()
    Wire.begin();
    Wire.end();
#endif
    Wire.begin(I2C_PERIPHERAL_ADDRESS);
    Wire.onReceive(peripheralReceiveHandler);
    Wire.onRequest(peripheralSendHandler);

    // Should this work in peripheral mode???
    Wire.setClock(400000);

#if WIRE_HAS_TIMEOUT
    Wire.setWireTimeout();
#endif
}

void error() {
    // Add some kind of error handler here
}

void peripheralReceiveHandler(int count) {
    if (count >= 32) error();

    uint8_t data[32] = {0};
    uint8_t i = 0;
    while (Wire.available()) {
        uint8_t peeked = Wire.peek();
        data[i] = Wire.read();
        if (peeked != data[i]) error();
        if (i >= count) error();
        i++;
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
#if WIRE_HAS_TIMEOUT
    if (Wire.getWireTimeoutFlag()) {
        Wire.clearWireTimeoutFlag();
    }
#endif

    delay(50);
}
