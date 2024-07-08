/**
 * Example trying to exercise all the SPI Controller API.
 *
 * This example code is not really designed to work with any specific SPI
 * device, it only exercises all relevant methods, so it's a good check
 * to see if your Arduino Core includes all SPI features.
 */
#include <SPI.h>

#define CHIPSELECT_PIN      1
#define CHIPSELECT_INACTIVE HIGH
#define CHIPSELECT_ACTIVE   LOW

#if !defined(SPI_HAS_TRANSACTION)
// #error "The SPI library must include the SPI_HAS_TRANSACTION define & methods."
#endif

void setup(void) {
    pinMode(CHIPSELECT_PIN, OUTPUT);
    digitalWrite(CHIPSELECT_PIN, CHIPSELECT_INACTIVE);

    // Have to run begin once to be able to run end, as they cancel each other
    SPI.begin();
    SPI.end();

    SPI.begin();

    SPI.usingInterrupt(5);  // Random number, but it shouldn't matter as undone next
    SPI.notUsingInterrupt(5);
}

void loop(void) {
    // Reading data
    SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
    digitalWrite(CHIPSELECT_PIN, CHIPSELECT_ACTIVE);
    // Only reading data so, don't care about sent value
    uint8_t received_byte = SPI.transfer(0);
    (void)received_byte;
    // Only reading data so, don't care about sent value
    uint16_t received_twobytes = SPI.transfer(0);
    (void)received_twobytes;
    uint8_t receive_buffer[4] = {0};
    SPI.transfer(receive_buffer, 4);  // Received data placed in buffer
    digitalWrite(CHIPSELECT_PIN, CHIPSELECT_INACTIVE);
    SPI.endTransaction();

    // Writing data
    SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
    digitalWrite(CHIPSELECT_PIN, CHIPSELECT_ACTIVE);
    SPI.transfer(0xAA);
    SPI.transfer16(0x55AA);
    uint8_t data_to_send[4] = {0, 1, 2, 3};
    SPI.transfer(data_to_send, 4);
    digitalWrite(CHIPSELECT_PIN, CHIPSELECT_INACTIVE);
    SPI.endTransaction();

    delay(100);
}
