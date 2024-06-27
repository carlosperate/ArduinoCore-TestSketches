# ArduinoCore-TestSketches

The goal of this repository is to contain a collection of Arduino Sketches that
cover all of the Arduino API, as a way to test an Arduino Core under development.

The aim of these examples is not to verify the sketch code is working
correctly, but if everything compiles it would indicate all the Arduino API
has been correctly implemented in an Arduino Core (an Arduino Core is an
Arduino port to a specific platform or board).

The Arduino IDE [built-in examples](https://github.com/arduino/arduino-examples)
covers a lot of the Arduino API, but not all of it, so the sketches here will
aim to have full coverage.

## Current status

These examples are still under development, so there is still a work to do.

Any PRs adding additional examples are welcomed.

- [ ] Digital read pin functions
- [ ] Digital write pin functions
- [ ] Analog read pin functions
- [ ] Analog write pin functions
- [ ] Tone pin functions
- [ ] Pulse pin functions
- [ ] Shift functions
- [ ] Delay() functions
- [x] Random number generator functions
- [ ] External interrupt functions
- [ ] Serial class methods
- [x] SPI class methods
- [x] I2C controller Wire methods
- [x] I2C peripheral Wire methods
- [ ] USB Keyboard
- [ ] USB Mouse

## License

Licensed CC0 1.0 Universal (CC0 1.0) Public Domain Dedication

Where sketches or other files come from a difference source with their own
license, the specific license has been captured in the file header.
