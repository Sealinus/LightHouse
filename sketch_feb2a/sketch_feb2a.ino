#define R_PWM_PIN   2
#define G_PWM_PIN   3
#define B_PWM_PIN   4

void setup() {
  pinMode(R_PWM_PIN, OUTPUT);                     // Настраиваем пины с ШИМ на выход
  pinMode(G_PWM_PIN, OUTPUT);
  pinMode(B_PWM_PIN, OUTPUT);
  Serial.begin(9600);

  //TCCR0B = (TCCR0B & 0b11111000) | 1;             // ШИМ 16 кгц для таймера 0
  //TCCR1 = (TCCR1 & 0b11110000) | 1;               // ШИМ 16 кгц для таймера 1
}

void loop() {

  analogWrite(R_PWM_PIN, 255);                  // Генерируем ШИМ сигналы
  analogWrite(G_PWM_PIN, 0);
  analogWrite(B_PWM_PIN, 0);

  delay(500);

  analogWrite(R_PWM_PIN, 0);                  // Генерируем ШИМ сигналы
  analogWrite(G_PWM_PIN, 255);
  analogWrite(B_PWM_PIN, 0);

  delay(500);
  analogWrite(R_PWM_PIN, 0);                  // Генерируем ШИМ сигналы
  analogWrite(G_PWM_PIN, 0);
  analogWrite(B_PWM_PIN, 255);

  delay(500);
   
}