const unsigned long SWAP_INTERVAL_SECONDS = 20 * 60;  // Seconds between battery swaps
const int SWAP_DURATION_MS = 40;  // Milliseconds for relay to switch (max 30ms) + margin of safety
const int SET_PIN = 2;
const int RESET_PIN = 3;

int charge_battery = -1;  // Which battery is currently in use, init as -1
unsigned long last_swap_ms;

unsigned long last_print_ms;

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  delay(1000);
  Serial.println("\n\n*** Battery Swapper by Waveguide ***\n\n");

  pinMode(SET_PIN, OUTPUT);
  pinMode(RESET_PIN, OUTPUT);

  Serial.println("Setup DONE");
}

// Trigger the relay to swap the batteries
void swap() {
  if (millis() - last_swap_ms > 1000)  // 1 second debounce to prevent double triggers
  {
    int swap_pin = charge_battery ? RESET_PIN : SET_PIN;

    last_swap_ms = millis();

    charge_battery = !charge_battery;

    digitalWrite(swap_pin, HIGH);
    delay(SWAP_DURATION_MS);
    digitalWrite(swap_pin, LOW);

    Serial.println("SWAP | Pin: " + String(swap_pin) + " | Charge battery: " + String(charge_battery));
  }
}

void loop() {
  if (millis() - last_print_ms > 1000)
  {
    Serial.println("Secs till next swap: " + String(SWAP_INTERVAL_SECONDS - ((millis() - last_swap_ms) / 1000)));

    last_print_ms = millis();
  }
  
  // Non-blocking check to see if we need to swap batteries or not
  if (millis() - last_swap_ms >= SWAP_INTERVAL_SECONDS * 1000 || charge_battery == -1) {
      swap();
  }
}
