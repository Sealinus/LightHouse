const byte pin5 = 5;
const byte pin4 = 4;

void ICACHE_RAM_ATTR ISRoutine ();

void setup () {
Serial.begin(115200);
pinMode(pin5,INPUT_PULLUP);
pinMode(LED_BUILTIN,OUTPUT);
attachInterrupt(digitalPinToInterrupt(pin5),ISRoutine,FALLING);
pinMode(pin4,INPUT);
}

void loop () {

// Repeatative code here

}

void ISRoutine () {
int value;
Serial.println("I am in ISR");
value = digitalRead(pin4);
Serial.print("Value read = ");
Serial.println(value);
digitalWrite(LED_BUILTIN,!value);
}