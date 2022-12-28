/** Example to exercise the random functions. */

#define ARRAY_SIZE 20

void setup() {
    Serial.begin(115200);
    while (!Serial) continue;

    Serial.println("On startup this initial set of numbers should always be the same:");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        Serial.println(random(256));
    }

    randomSeed(analogRead(0));
    Serial.println("\nShould be different on every run, as they are 'randomly' seeded:");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        Serial.println(random(256));
    }

    uint8_t array_first[ARRAY_SIZE];
    randomSeed(0x12345);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array_first[i] = random(100, 256);
    }

    uint8_t array_second[ARRAY_SIZE];
    randomSeed(0x12345);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array_second[i] = random(100, 256);
    }

    // Print both arrays side to side
    Serial.println("\nThe following pairs should always be the same to each other:");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        Serial.print(array_first[i]);
        Serial.print(", ");
        Serial.print(array_second[i]);
        Serial.print('\n');
    }
}

void loop() {
    delay(1000);
}
