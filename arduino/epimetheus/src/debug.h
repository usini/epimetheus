unsigned long debug_start;
unsigned long debug_end;
unsigned long debug_delta;

void debug_serial_start() {
    debug_start = millis();
}

void debug_serial_end(String function_name) {
    debug_end = millis();
    debug_delta = debug_end - debug_start;
    Serial.print("[DEBUG] " + function_name);
    Serial.print("() - ");
    Serial.print(debug_delta);
    Serial.print("  ms");
    Serial.print(" - CORE:");
    Serial.println(xPortGetCoreID());
}