int ledPin=8; // PB0

void setup() {
 pinMode(ledPin,OUTPUT);
}

void loop() {
 digitalWrite(ledPin,1);
 delay(500);
 digitalWrite(ledPin,0);
 delay(500);
}
