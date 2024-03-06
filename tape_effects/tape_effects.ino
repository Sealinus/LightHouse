#define maxv 1.0
#define minv 0.0
#define maxh 360.0
#define minh 0.0

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

void readdata (hsv& data) {
  if (Serial.available() > 0) {
    String bufString = Serial.readString(); 
    byte dividerIndex = bufString.indexOf(';'); 

    String buf_h = bufString.substring(0, dividerIndex); 
    String buf_v = bufString.substring(dividerIndex + 1);

    if (buf_h.toDouble() >= minh && buf_h.toDouble() <= maxh) data.h = buf_h.toDouble();
    if (buf_v.toDouble() >= minv && buf_v.toDouble() <= maxv) data.v = buf_v.toDouble();

    if DebugModeON {
      Serial.println(data.h);
      Serial.println(data.v);
    }
    
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

  in.r = in.r / 255;
  in.g = in.g / 255;
  in.b = in.b / 255;
  cmax = max(max(in.r, in.g), in.b);
  cmin = min(min(in.r, in.g), in.b);
  delta = cmax - cmin;

  if (delta == 0) out.h = 0;
  else if (cmax == in.r) out.h = 60.0 * (fmod((in.g - in.b) / delta, 6));
  else if (cmax == in.g) out.h = 60.0 * ((in.b - in.r) / delta + 2);
  else if (cmax == in.b) out.h = 60.0 * ((in.r - in.g) / delta + 4);

  if (cmax = 0) out.s = 0;
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

void loop() {
  static hsv hsvin;
  static rgb rgbout;

  hsvin.s = 1.0;
  readdata(hsvin);

  /*Serial.print(hsvin.h);
  Serial.print(" ");
  Serial.print(hsvin.s);
  Serial.print(" ");
  Serial.println(hsvin.v);*/

  rgbout = hsv2rgb(hsvin);

  if DebugModeON {
    Serial.print(rgbout.r);
    Serial.print(" ");
    Serial.print(rgbout.g);
    Serial.print(" ");
    Serial.println(rgbout.b);
  }

  analogWrite (9, rgbout.r);
  analogWrite (10, rgbout.g);
  analogWrite (11, rgbout.b);
}