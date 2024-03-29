#define maxc 255.0
#define minc 0.0

#define DebugModeON (true)

typedef struct {
    double r;       // a fraction between 0 and 1
    double g;       // a fraction between 0 and 1
    double b;       // a fraction between 0 and 1
} rgb;

typedef struct {
    double h;       // angle in degrees
    double s;       // a fraction between 0 and 1
    double v;       // a fraction between 0 and 1
} hsv;


void setup() {
  Serial.begin(9600);
  Serial.setTimeout(50);
}

void readdata (rgb& data, hsv& in, hsv& cur, float& lim) {
  if (Serial.available() > 0) {
    String bufString = Serial.readString(); 
    byte dividerIndex = bufString.indexOf(';'); 

    String buf_r = bufString.substring(0, dividerIndex); 
    String buf_l = bufString.substring(dividerIndex + 1);

    if (data.r >= minc && data.r <= maxc) data.r = buf_r.toDouble();
    data.g = 255.0;
    data.b = 0.0;
    lim = buf_l.toDouble();

    in = rgb2hsv(data);
    cur = in;
    /*if DebugModeON {
      Serial.println(data.r);
      Serial.println(data.g);
      Serial.println(data.b);
    }*/
    
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

  if DebugModeON {
    Serial.print(c);
    Serial.print(" ");
    Serial.print(x);
    Serial.print(" ");
    Serial.print(m);
    Serial.print(" ");
    Serial.print(sec);
    Serial.println();
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

  if DebugModeON {
    Serial.print(cmax);
    Serial.print(" ");
    Serial.print(cmin);
    Serial.print(" ");
    Serial.print(delta);
    Serial.println();
  }

  return out;
}

void LightControl(hsv& in, float target){
  if (target >= 0.0 && target <= 1.0) in.v = target; //crt in future
}

double breath (double in, double cur, int& dir, float lim) {
  uint8_t period = 200;
  static uint64_t time = millis();

  if (abs(cur - in) > lim - 0.01) dir = dir * -1;

  if(millis() - time >= period) {
      cur = cur + dir*0.01; // нужно добавить crt
  }

  return cur;
}

void loop() {

  static hsv hsvin, hsvcur;
  static rgb rgbin, rgbout;
  static int dir = 1;
  static float lim = 0.0;

  readdata (rgbin, lim);

  if (lim != 0.0) hsvcur.v = breath (hsvin.v, hsvcur.v, dir, lim);
  

}