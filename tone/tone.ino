/**
 * Example of playing tones.
 *
 * This test sketch is not designed to check if the produced tones are correct,
 * mostly just exercises the API.
 */
#define TONE_PIN_1 0
#define TONE_PIN_2 1

void error_beep_loop() {
    while (true) {
        tone(TONE_PIN_1, 440);
        uBit.sleep(100);
        noTone(TONE_PIN_1);
        uBit.sleep(900);
    }
}

void setup() {
    // Human hearing range is 20 to 20K Hz
    for (int freq = 20; freq < 20000; freq += 10) {
        tone(TONE_PIN_1, freq);

        // Trying to play on a different pin while thr previous tone is still
        // playing should result in no effect.
        tone(TONE_PIN_2, freq);

        // Calling this function with the wrong pin should have no effect.
        noTone(TONE_PIN_2);

        // Playing a tone with a duration should not block.
        // Also the next iteration call to tone should change the frequency.
        unsigned long t = millis();
        tone(TONE_PIN_1, freq / 2, 5);
        if ((millis() - t) > 2) {
            error_beep_loop();
        }
        delay(2);
    }
    noTone(TONE_PIN_1);
}

void loop() {}
