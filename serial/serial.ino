/**
 * Serial (UART) API test — meant to be generic across Arduino cores. Open the
 * Serial Monitor at 115200 baud and send any character to start. It:
 *   - checks the config/lifecycle API;
 *   - applies several begin() framing configs (8N1, 8N2, 8E1, 8O1, 7E1, 7O1);
 *   - prints each output-API value and asks you to confirm it looks right;
 *   - has you type known values so the Stream parsers can be checked;
 *   - echoes what you type back, checking peek()==read() on every byte.
 * Any failed check prints a loud banner and halts, so nothing scrolls past it.
 *
 * Some cores only support SERIAL_8N1 (e.g. the micro:bit core panics on any
 * other framing). Set TEST_SERIAL_CONFIGS to 0 to skip the non-8N1 configs when
 * testing such a core; everything else still runs.
 */
#define TEST_SERIAL_CONFIGS 0

// Loud, terminal failure: print a banner naming the check and halt, so a failure
// stops right here instead of scrolling past.
void fail(const char* label) {
    Serial.println();
    Serial.println("  !!!!");
    Serial.print("  !!!! FAILED: ");
    Serial.println(label);
    Serial.println("  !!!!");
    while (true);
}

// Pass prints [ok]; failure hands off to fail(), which never returns.
void check(bool ok, const char* label) {
    if (!ok) {
        fail(label);
    }
    Serial.print("  [ok]  ");
    Serial.println(label);
}

// Block until the user types, then let the rest of the line arrive.
void waitForLine() {
    while (Serial.available() == 0);
    delay(20);
}

// Discard whatever is left on the current line (e.g. a trailing newline).
void clearLine() {
    delay(20);
    while (Serial.available() > 0) {
        Serial.read();
    }
}

// Ask the user whether the value just printed looks right, stops on first failure.
void confirm(const char* label, const char* expected) {
    Serial.print("  <- do you see '");
    Serial.print(expected);
    Serial.print("'? (y/n) ");
    waitForLine();
    int answer = Serial.read();
    clearLine();
    Serial.println();
    if (answer == 'y' || answer == 'Y') {
        check(true, label);
    } else {
        String msg = String(label) + ": '" + expected + "' not shown correctly";
        fail(msg.c_str());
    }
}

void setup() {
    // First bring it up with the default config, then explicitly with 8N1.
    Serial.begin(115200);
    while (!Serial);
    Serial.begin(115200, SERIAL_8N1);
    while (!Serial);

    // Reprint until the user reacts, so the results below aren't missed when the
    // monitor is opened after boot.
    while (Serial.available() == 0) {
        Serial.println("\nSerial API test will require user input, press any key to start...");
        delay(1500);
    }
    clearLine();

    Serial.println("\n=== config / lifecycle ===");
    check(Serial, "bool operator true after begin()");
    Serial.setTimeout(1234);
    check(Serial.getTimeout() == 1234, "getTimeout() matches setTimeout()");
    Serial.flush();  // reaching the next line proves flush() did not panic
    check(true, "flush() returned");
    Serial.end();
    Serial.begin(115200);
    check(Serial, "usable after end() + begin()");

    Serial.println("\n=== begin(config) framing ===");
#if TEST_SERIAL_CONFIGS
    // The monitor's framing is fixed, so bytes sent mid-switch would be garbled;
    // apply each config (confirming begin() accepts it), then restore 8N1 before
    // printing the result.
    const uint16_t configs[] = {
        SERIAL_5N1, SERIAL_6N1, SERIAL_7N1, SERIAL_8N1,
        SERIAL_5N2, SERIAL_6N2, SERIAL_7N2, SERIAL_8N2,
        SERIAL_5E1, SERIAL_6E1, SERIAL_7E1, SERIAL_8E1,
        SERIAL_5E2, SERIAL_6E2, SERIAL_7E2, SERIAL_8E2,
        SERIAL_5O1, SERIAL_6O1, SERIAL_7O1, SERIAL_8O1,
        SERIAL_5O2, SERIAL_6O2, SERIAL_7O2, SERIAL_8O2
    };
    for (unsigned i = 0; i < sizeof(configs) / sizeof(configs[0]); i++) {
        Serial.begin(115200, configs[i]);
    }
    Serial.begin(115200);  // restore default config
    Serial.println("  applied variants:\n    5N1 6N1 7N1 8N1 5N2 6N2 7N2 8N2"
                   "\n    5E1 6E1 7E1 8E1 5E2 6E2 7E2 8E2"
                   "\n    5O1 6O1 7O1 8O1 5O2 6O2 7O2 8O2");
#else
    Serial.println("  skipped (TEST_SERIAL_CONFIGS=0)");
#endif

    Serial.println("\n=== output API (confirm each value) ===");
    Serial.print("  byte write: ");
    Serial.write('W');
    confirm("byte write", "W");
    Serial.print("  buffer write: ");
    Serial.write((const uint8_t*)"buf", 3);
    confirm("buffer write", "buf");
    Serial.print("  cstr write: ");
    Serial.write("cstr");
    confirm("cstr write", "cstr");
    Serial.print("  print char: ");
    Serial.print('c');
    confirm("print char", "c");
    Serial.print("  print string: ");
    Serial.print("a string");
    confirm("print string", "a string");
    Serial.print("  print int: ");
    Serial.print(-12345);
    confirm("print int", "-12345");
    Serial.print("  print unsigned: ");
    Serial.print(3000000000U);
    confirm("print unsigned", "3000000000");
    Serial.print("  print long: ");
    Serial.print(-2000000000L);
    confirm("print long", "-2000000000");
    Serial.print("  print float: ");
    Serial.print(3.14159);
    confirm("print float", "3.14");
    Serial.print("  print float 4dp: ");
    Serial.print(3.14159, 4);
    confirm("print float 4dp", "3.1416");
    Serial.print("  number bases: ");
    Serial.print(255, DEC);
    Serial.print(' ');
    Serial.print(255, HEX);
    Serial.print(' ');
    Serial.print(255, OCT);
    Serial.print(' ');
    Serial.print(255, BIN);
    confirm("number bases", "255 FF 377 11111111");

    Serial.println("\n=== parsers (type each requested value) ===");
    Serial.print("  type the number 42: ");
    waitForLine();
    long n = Serial.parseInt();
    clearLine();
    Serial.println(n);
    check(n == 42, "parseInt");
    Serial.print("  type the number 3.5: ");
    waitForLine();
    float f = Serial.parseFloat();
    clearLine();
    Serial.println(f);
    check(f > 3.49f && f < 3.51f, "parseFloat");
    Serial.print("  type the word hello: ");
    waitForLine();
    String w = Serial.readStringUntil('\n');
    w.trim();
    clearLine();
    Serial.println(w);
    check(w == "hello", "readStringUntil");

    Serial.println("\n  -> all checks passed");

    Serial.println("\n=== echo (type anything) ===");
}

void loop() {
    if (Serial.available() <= 0) {
        return;
    }
    // peek() must return the same byte read() then consumes; echo it straight back.
    int peeked = Serial.peek();
    int c = Serial.read();
    if (peeked != c) {
        fail("peek() != read()");
    }
    Serial.write((uint8_t)c);
}
