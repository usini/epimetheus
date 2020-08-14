const bool DEBUG = true;

void debug_start() {
  if (DEBUG) {
    Serial.begin(115200);
  }
}
void debug_print(String debug_string) {
  if (DEBUG) {
    Serial.print(debug_string);
  }
}

void debug_println(String debug_string) {
  if (DEBUG) {
    Serial.println(debug_string);
  }
}
