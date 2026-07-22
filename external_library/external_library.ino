/*
 * Test sketch: external Arduino Library installed via the Library
 * Manager (SparkFun TMP102 Breakout, in the sketchbook libraries
 * folder).
 *
 * The TMP102 driver is a simple I2C (Wire-only) library with a single
 * .cpp/.h and architectures=*, so it exercises library detection,
 * compilation and linking without any platform-specific code.
 *
 * The external_library_vendored/ sketch compiles the exact same
 * sources vendored inside the sketch, as a control: if that one builds
 * and this one does not, the problem is the core's handling of
 * installed libraries.
 *
 * Expected behaviour: prints the TMP102 temperature reading at 115200
 * baud once per second (requires a TMP102 breakout on the I2C bus).
 */
#include <SparkFunTMP102.h>
#include <Wire.h>

TMP102 sensor;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    if (!sensor.begin()) {
        Serial.println("Could not connect to TMP102, check wiring!");
    }
}

void loop() {
    sensor.wakeup();
    float temperature = sensor.readTempC();
    sensor.sleep();
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");
    delay(1000);
}
