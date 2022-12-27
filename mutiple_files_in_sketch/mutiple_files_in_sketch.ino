/**
 * Check that additional .hpp/.cpp/.h/.c files in the sketch are compiled.
 *
 * Files in the sketch root should all be compiled, but for subdirectories,
 * only files inside a `src` folder are recursively included:
 * https://arduino.github.io/arduino-cli/0.20/sketch-specification/#src-subfolder
 *
 * Additionally, the .ino sketch uses functions without forward declaration,
 * which checks the Arduino Core build system pre-processes the sketch to
 * add the function prototypes.
 */
#include "header_top_dir.hpp"

int func_without_declaration(int numb);

void setup() {
    Serial.begin(115200);
    while (!Serial) continue;
    Serial.println(func_without_declaration(2));
}

int func_without_declaration(int numb) {
    // This function will multiply by 3
    return multiply(numb);
}

void loop() {
    delay(1000);
}
