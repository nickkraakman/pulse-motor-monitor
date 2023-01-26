const unsigned long SWAP_INTERVAL_SECONDS = 20 * 60;  // Seconds between battery swaps
const int SWAP_DURATION_MS = 40;  // Milliseconds for relay to switch (max 30ms) + margin of safety
const int SET_PIN = 2;
const int RESET_PIN = 3;

int charge_battery = NULL;  // Which battery is currently in use
unsigned long last_swap_ms;


void setup() {
  Serial.begin(9600);  // Initialize serial communication
  delay(10);

  pinMode(SET_PIN, OUTPUT);
  pinMode(RESET_PIN, OUTPUT);

  Serial.println("Setup DONE");
}


// Trigger the relay to swap the batteries
void swap() {
  int swap_pin = charge_battery ? RESET_PIN : SET_PIN;

  digitalWrite(swap_pin, HIGH);
  delay(SWAP_DURATION_MS);
  digitalWrite(swap_pin, LOW);
  
  charge_battery = !charge_battery;

  last_swap_ms = millis();

  Serial.println("SWAP | Pin: " + String(swap_pin) + " | Run battery: " + String(charge_battery));
}


void loop() {
  // Non-blocking check to see if we need to swap batteries or not
  if (charge_battery == NULL || millis() - last_swap_ms >= SWAP_INTERVAL_SECONDS * 1000) {
      swap();
  }
}
