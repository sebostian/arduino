byte OUTPUT_PIN = 9;

void setup() {
	// 10 бит 1 562,5 Гц
	TCCR1A = TCCR1A & 0xe0 | 3;
	TCCR1B = TCCR1B & 0xe0 | 0x09;
}

void loop() {
	for (int i=0; i < 1024; i++){ 
		analogWrite(OUTPUT_PIN, i); 
		delay(100);
	}
}
