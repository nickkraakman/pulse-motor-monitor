const int SWAP_INTERVAL_SECONDS = 10;  // Seconds between battery swaps
const int SWAP_DURATION_MS = 40;  // Milliseconds for relay to switch (max 30ms) + margin of safety
const int SET_PIN = 2;
const int RESET_PIN = 3;

int currentBattery = NULL;  // Which battery is currently in use

void setup() {
    Serial.begin(9600);  // initialize serial communication
    delay(10);

    pinMode(SET_PIN, OUTPUT);
    pinMode(RESET_PIN, OUTPUT);

    Serial.println("Setup DONE");
}

// Trigger the relay to swap the batteries
void swap() {
    int swap_pin = currentBattery ? RESET_PIN : SET_PIN;

    digitalWrite(swap_pin, HIGH);
    delay(SWAP_DURATION_MS);
    digitalWrite(swap_pin, LOW);
    currentBattery = !currentBattery;

    Serial.println("SWAP | Pin: " + String(swap_pin) + " | Run battery: " + String(currentBattery));
}

void loop() {
    swap();
    delay(SWAP_INTERVAL_SECONDS * 1000);
}