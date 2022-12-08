const int rpmPin = 2;  // digital pin for measuring RPM
const int sampleTime = 100;  // sample time in milliseconds

unsigned long lastRpmTime = 0;  // last time the RPM was measured
unsigned long pulseCount = 0;  // number of pulses counted

void setup() {
  pinMode(rpmPin, INPUT);  // set the rpmPin as an input
  attachInterrupt(digitalPinToInterrupt(rpmPin), countPulse, RISING);  // attach an interrupt to the rpmPin
  Serial.begin(9600);  // initialize serial communication
}

void loop() {
  if (millis() - lastRpmTime >= sampleTime) {
    // calculate RPM
    float rpm = (pulseCount / 2) * (60000 / sampleTime);

    // reset pulse count
    pulseCount = 0;
    lastRpmTime = millis();

    // print RPM to the serial monitor
    Serial.println(rpm);
  }
}

// interrupt routine to count pulses
void countPulse() {
  pulseCount++;
}
