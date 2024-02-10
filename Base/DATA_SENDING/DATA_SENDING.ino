#define TXPin D4

#include <Gyver433.h>

struct data{
  uint8_t adress;
  bool channel;
  uint8_t hue;
  uint8_t suturation;
  uint8_t light;
  uint8_t effectData[6];
};

Gyver433_TX<TXPin> tx;
data package;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(50);
}


void loop() {
  if (Serial.available() > 0) {
    String bufString = Serial.readString();       // читаем как строку
    byte dividerIndex = bufString.indexOf(';');   // ищем индекс разделителя
    String buf_1 = bufString.substring(0, dividerIndex);    // создаём строку с первым числом
    String buf_2 = bufString.substring(dividerIndex + 1);   // создаём строку со вторым числом
    float val_1 = buf_1.toInt();    // преобразуем во флоат
    float val_2 = buf_2.toInt();
  package = (data){
    154, false, 173, 255, 255, {0, 0, 0, 0, 0, 0}
  };
  tx.sendData(package);
  }
}
