#define BLYNK_TEMPLATE_ID "TMPL4BTAXRdrg"
#define BLYNK_TEMPLATE_NAME "LightHouse"
#define BLYNK_AUTH_TOKEN "0DUAbag7PT3_QJK37k0GjLZ1fjq0Dcg2"  //настройки для коректной работы blynk
#define BLYNK_PRINT Serial

#define maxv 1.0
#define minv 0.0
#define maxh 360.0
#define minh 0.0

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>        // либы для вифи

typedef struct {
    double r;       
    double g;       //структура для хранения rgb данных
    double b;       
} rgb;

typedef struct {
    double h;       
    double s;       //структура для хранения hsv данных
    double v;       
} hsv;

char ssid[] = "PHomeMedia"; // настройки вифи
char pass[] = "1409290373";

rgb rgbdt;
hsv hsvdt;           // создаем переменные
byte swich;
double light;

BLYNK_WRITE(V0)  // обрабатываем изменение канала красного цвета (для остальных аналогично)
{
  double pinValue = param.asDouble();  // принимаем  значение
  rgbdt.r = pinValue; // пишем в структуру
  setColor(rgbdt); // обнавляем значение на ленте
}

BLYNK_WRITE(V1) // обрабатываем изменение зеленого канала
{
  double pinValue = param.asDouble();
  rgbdt.g = pinValue;
  setColor(rgbdt);
}

BLYNK_WRITE(V2) // обрабатываем изменение синего канала
{
  double pinValue = param.asDouble();
  rgbdt.b = pinValue;
  setColor(rgbdt);
}

BLYNK_WRITE(V3) // одрабатываем изменение свича вкл/выкл
{
  byte pinValue = param.asInt(); 
  swich = pinValue;
  if (swich == 1) {Serial.println("Power is ON"); digitalWrite(15, HIGH);}
  else {Serial.print("Power is OFF"); digitalWrite(15, LOW);}
}

BLYNK_WRITE(V4) // обрабатываем изменение параметра яркости
{
  double pinValue = param.asDouble();
  light = pinValue / 100.0;
  setColor(rgbdt);

}

void setColor(rgb rgbdt) // выводим цвет на ленту
{
  rgb rgbout;
  hsvdt = rgb2hsv(rgbdt); //перевод в hsv
  hsvdt.v = light; // применяем значение яркости
  rgbout = hsv2rgb(hsvdt); // обратно в rgb
  analogWrite(0, rgbout.r);
  analogWrite(2, rgbout.g); // выводим на ленту
  analogWrite(4, rgbout.b);
}

rgb hsv2rgb(hsv in){ //функция преобразования
  rgb out, interm;
  double c, x, m;
  byte sec;

  in.h = fmod(in.h, 360);
  c = in.v * in.s;
  x = c * (1 - abs(fmod((in.h / 60.0), 2) - 1));
  m = in.v - c;
  sec = (in.h / 60);

  switch (sec){
    case 0: interm.r = c; interm.g = x; interm.b = 0; break;
    case 1: interm.r = x; interm.g = c; interm.b = 0; break;
    case 2: interm.r = 0; interm.g = c; interm.b = x; break;
    case 3: interm.r = 0; interm.g = x; interm.b = c; break;
    case 4: interm.r = x; interm.g = 0; interm.b = c; break;
    case 5: interm.r = c; interm.g = 0; interm.b = x; break; 
  }

  out.r = (interm.r + m) * 255;
  out.g = (interm.g + m) * 255;
  out.b = (interm.b + m) * 255;

  return out;
}

hsv rgb2hsv(rgb in){ //функция преобразования
  hsv out;
  double cmax, cmin, delta;

  in.r = in.r / 255.0;
  in.g = in.g / 255.0;
  in.b = in.b / 255.0;
  cmax = max(max(in.r, in.g), in.b);
  cmin = min(min(in.r, in.g), in.b);
  delta = cmax - cmin;

  if (delta == 0) out.h = 0;
  else if (cmax == in.r) out.h = 60.0 * (fmod((in.g - in.b) / delta, 6));
  else if (cmax == in.g) out.h = 60.0 * ((in.b - in.r) / delta + 2);
  else if (cmax == in.b) out.h = 60.0 * ((in.r - in.g) / delta + 4);

  if (cmax == 0) out.s = 0;
  else out.s = delta / cmax;

  return out;
}

void setup()
{
  Serial.begin(115200);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(15, OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Blynk.syncAll();
}

void loop()
{
  Blynk.run();
}
