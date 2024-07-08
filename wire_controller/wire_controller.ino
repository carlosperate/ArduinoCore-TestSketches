/**
 * Example trying to exercise all the Wire API for the I2C/TWI controller mode.
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
 * TODO: This could be updated, together with the wire_peripheral sketch so
 *       that they work together connecting two Arduino boards.
 */
#include <Wire.h>

#define I2C_PERIPHERAL_ADDRESS (0x90)

#if !defined(WIRE_HAS_END)
#warning "Modern Arduino Cores should implement the WIRE_HAS_END methods."
#endif
#if !defined(WIRE_HAS_TIMEOUT)
#warning "Modern Arduino Cores should implement the WIRE_HAS_TIMEOUT methods."
#endif

void setup() {
#if WIRE_HAS_END
    // The Wire.end() call should undo everything done by Wire.begin(), so
    // these two lines should cancel each other before the second Wire.begin()
    Wire.begin();
    Wire.end();
#endif
    Wire.begin();
    Wire.setClock(400000);

#if WIRE_HAS_TIMEOUT
    Wire.setWireTimeout();
#endif
}

void error() {
    // Add some kind of error handler here
}

void loop() {
    size_t sent_count = 0;
    size_t arrived_count = 0;
    uint8_t transmission_state = 0;
    uint8_t data[32] = {0x02, 0x03};

    // Write some data to the TX buffer and send it with a repeated start
    Wire.beginTransmission(I2C_PERIPHERAL_ADDRESS);
    sent_count = Wire.write(0x01);
    if (sent_count != 1) error();
    sent_count = Wire.write(data, 2);
    if (sent_count != 2) error();
    sent_count = Wire.write("some text");
    if (sent_count != 9) error();
    transmission_state = Wire.endTransmission(false);
    if (transmission_state != 0) error();

    // Read 32 bytes from a peripheral
    arrived_count = Wire.requestFrom(I2C_PERIPHERAL_ADDRESS, 32, false);
    if (arrived_count != 32) error();
    uint8_t i = 0;
    while (Wire.available()) {
        uint8_t peeked = Wire.peek();
        data[i] = Wire.read();
        if (peeked != data[i]) error();
        if (i >= 32) error();
        i++;
    }

    // Again, but the default stop bits
    Wire.beginTransmission(I2C_PERIPHERAL_ADDRESS);
    sent_count = Wire.write(data, 32);
    if (sent_count != 32) error();
    transmission_state = Wire.endTransmission();
    if (transmission_state != 0) error();
    arrived_count = Wire.requestFrom(I2C_PERIPHERAL_ADDRESS, 1);
    if (arrived_count != 1) error();

#if WIRE_HAS_TIMEOUT
    // Call the rest of the timeout methods
    if (Wire.getWireTimeoutFlag()) {
        Wire.clearWireTimeoutFlag();
    }
#endif
}
