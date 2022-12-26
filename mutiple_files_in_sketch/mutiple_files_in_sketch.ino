#include "header_top_dir.h"

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println(func_without_declaration(2));
}

int func_without_declaration(int numb) {
  // This function will multiply by 3
  return multiply(numb);
}

void loop() {
  delay(1000);
}
