/*************************************************************

  You can use this sketch as a debug tool that prints all incoming values
  sent by a widget connected to a Virtual Pin 1 in the Blynk App.

  App dashboard setup:
    Slider widget (0...100) on V1
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL4BTAXRdrg"
#define BLYNK_TEMPLATE_NAME "LightHouse"
#define BLYNK_AUTH_TOKEN "0DUAbag7PT3_QJK37k0GjLZ1fjq0Dcg2"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#define maxc 255.0
#define minc 0.0

#define DebugModeON (true)


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


typedef struct {
    double r;
    double g;
    double b;
} rgb;

typedef struct {
    double h;
    double s;
    double v;
} hsv;

// Set password to "" for open networks.
char ssid[] = "PHomeMedia";
char pass[] = "1409290373";

byte color[3] = {0,0,0};
byte swich;

void readdata (rgb& data) {
  if (Serial.available() > 0) {
    String bufString = Serial.readString(); 
    byte dividerIndex = bufString.indexOf(';'); 

    String buf_r = bufString.substring(0, dividerIndex); 
    String buf_b = bufString.substring(dividerIndex + 1);

    if (data.r >= minc && data.r <= maxc) data.r = buf_r.toDouble();
    data.g = 255.0;
    if (data.b >= minc && data.b <= maxc) data.b = buf_b.toDouble();
  }
}

rgb hsv2rgb(hsv in){
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

hsv rgb2hsv(rgb in){
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

  out.v = cmax;

  return out;
}

void LightControl(double in, float target){
  if (target >= 0.0 && target <= 1.0) in = ((long)target * 255 * target * 255 + 255) >> 8;
}

void debugPrint(){
  Serial.print(color[0]);
  Serial.print(" ");
  Serial.print(color[1]);
  Serial.print(" ");
  Serial.print(color[2]);
  Serial.println(" ");
}

BLYNK_WRITE(V0)
{
  byte pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  analogWrite(0, pinValue);
  color[0] = ~pinValue;
  debugPrint();
}

BLYNK_WRITE(V1)
{
  byte pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  analogWrite(2, pinValue);
  color[1] = ~pinValue;
  debugPrint();
}

BLYNK_WRITE(V2)
{
  byte pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  color[2] = ~pinValue;
  analogWrite(4, pinValue);
  debugPrint();
}

BLYNK_WRITE(V3)
{
  byte pinValue = param.asInt();
  swich = pinValue;
  if (swich == 101) digitalWrite(15, LOW);
  else {
    //value changing;
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  Serial.setTimeout(50);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(15, OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Blynk.syncAll();
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
}
