# Arduino Core Test Sketches

The goal of this repository is to contain a collection of Arduino Sketches
to test an Arduino Core under development.

An [Arduino Core](https://docs.arduino.cc/learn/starting-guide/cores/) is an
implementation of the Arduino API for a specific microcontroller, family of
microcontrollers, or Arduino-compatible board/s.

The [Arduino IDE built-in examples](https://github.com/arduino/arduino-examples)
cover a lot of the Arduino API, but not all of it, so these sketches aim
to provide full public API coverage.
Some official and unofficial Arduino Cores have additional/extended APIs,
specific to that Core, these additions are out of scope for this repository.

A lot of these examples are not able to verify that the sketch code is
working correctly, as that would require additional hardware like logic
analysers, oscilloscopes, etc.
These sketches mostly test that the Arduino API is implemented correctly.
But they will test as much as they can with available Arduino Core hardware.

## Current coverage

These examples are still under development, so there is still a lot of work to do.

Any PRs adding additional examples are welcomed.

The sections follow the [Arduino Language Reference](https://www.arduino.cc/reference/en/),
minus the parts listed as out of scope below.
Not every Core implements every one of these (no DAC, no USB peripheral, ...),
so where a Core cannot support something the sketch should gate it behind a
compile-time flag rather than dropping the coverage.

- Digital I/O
    - [ ] `pinMode()`
    - [ ] `digitalWrite()`
    - [ ] `digitalRead()`
- Analog I/O
    - [ ] `analogRead()`
    - [ ] `analogReadResolution()`
    - [ ] `analogReference()`
    - [ ] `analogWrite()`
    - [ ] `analogWriteResolution()`
- Advanced I/O
    - [x] `tone()`
    - [x] `noTone()`
    - [ ] `pulseIn()`
    - [ ] `pulseInLong()`
    - [ ] `shiftIn()`
    - [ ] `shiftOut()`
- Time
    - [ ] `delay()`
    - [ ] `delayMicroseconds()`
    - [ ] `millis()`
    - [ ] `micros()`
- Random numbers
    - [x] `random()`
    - [x] `randomSeed()`
- External interrupts
    - [ ] `attachInterrupt()`
    - [ ] `detachInterrupt()`
    - [ ] `digitalPinToInterrupt()`
- Interrupts
    - [ ] `interrupts()`
    - [ ] `noInterrupts()`
- Serial
    - [x] `if (Serial)`
    - [x] `available()`
    - [x] `availableForWrite()`
    - [x] `begin()`
    - [x] `end()`
    - [x] `find()`
    - [x] `findUntil()`
    - [x] `flush()`
    - [x] `getTimeout()`
    - [x] `parseFloat()`
    - [x] `parseInt()`
    - [x] `peek()`
    - [x] `print()`
    - [x] `println()`
    - [x] `read()`
    - [x] `readBytes()`
    - [x] `readBytesUntil()`
    - [x] `readString()`
    - [x] `readStringUntil()`
    - [x] `setTimeout()`
    - [x] `write()`
    - [ ] `serialEvent()`
- SPI
    - [x] `SPISettings`
    - [x] `begin()`
    - [x] `beginTransaction()`
    - [x] `endTransaction()`
    - [x] `end()`
    - [x] `transfer()` / `transfer16()`
    - [x] `usingInterrupt()` / `notUsingInterrupt()`
    - [ ] `setBitOrder()` (deprecated, pre-transaction API)
    - [ ] `setClockDivider()` (deprecated, pre-transaction API)
    - [ ] `setDataMode()` (deprecated, pre-transaction API)
- Wire (I2C controller)
    - [x] `begin()`
    - [x] `end()`
    - [x] `setClock()`
    - [x] `beginTransmission()`
    - [x] `endTransmission()`
    - [x] `write()`
    - [x] `requestFrom()`
    - [x] `available()`
    - [x] `read()`
    - [x] `setWireTimeout()`
    - [x] `getWireTimeoutFlag()`
    - [x] `clearWireTimeoutFlag()`
- Wire (I2C peripheral)
    - [x] `begin()` with address
    - [x] `onReceive()`
    - [x] `onRequest()`
    - [x] `available()` / `read()` / `write()` inside the callbacks
- USB Keyboard
    - [ ] `Keyboard.begin()`
    - [ ] `Keyboard.end()`
    - [ ] `Keyboard.press()`
    - [ ] `Keyboard.print()`
    - [ ] `Keyboard.println()`
    - [ ] `Keyboard.release()`
    - [ ] `Keyboard.releaseAll()`
    - [ ] `Keyboard.write()`
    - [ ] Keyboard modifiers
- USB Mouse
    - [ ] `Mouse.begin()`
    - [ ] `Mouse.end()`
    - [ ] `Mouse.click()`
    - [ ] `Mouse.move()`
    - [ ] `Mouse.press()`
    - [ ] `Mouse.release()`
    - [ ] `Mouse.isPressed()`
- Other Core-provided definitions
    - [ ] `LED_BUILTIN`

## Out of scope: ArduinoCore-API

Part of the Arduino API is hardware independent and already tested as part of the
[ArduinoCore-API](https://github.com/arduino/ArduinoCore-API) repository, which
Arduino Cores are meant to include without reimplementing it.

Not covered here for that reason:

- Math & trigonometry: `abs()`, `constrain()`, `sin()`, `cos()`, etc
- Bits and bytes: `bit()`, `bitClear()`, etc
- Characters: `isAlpha()`, `isDigit()`, `isSpace()`, and the rest of `WCharacter.h`
- The `String` object, its methods and operators
- The `Print` and `Stream` base classes used by `Serial`, `Wire`, `SPI`, and other classes

The `Stream` parsers (`parseInt()`, `readBytes()`, `find()`, ...) are an
exception worth noting: they are implemented in ArduinoCore-API, but only on top
of the `read()`/`peek()`/`available()` primitives a core has to provide, so the
communication sketches exercise them as an indirect test of those primitives.

## License

Licensed CC0 1.0 Universal (CC0 1.0) Public Domain Dedication

Where sketches or other files come from a difference source with their own
license, the specific license has been captured in the file header.
