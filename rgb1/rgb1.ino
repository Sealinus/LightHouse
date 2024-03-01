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

hsv readdata (hsv data) {
  if (Serial.available() > 0) {
    String bufString = Serial.readString(); 
    byte dividerIndex = bufString.indexOf(';'); 

    String buf_1 = bufString.substring(0, dividerIndex); 
    String buf_2 = bufString.substring(dividerIndex + 1);

    data.h = buf_1.toDouble(); 
    data.v = buf_2.toDouble();
    data.s = 1.0;

    Serial.println(data.v);
    Serial.println(data.h);
  }

   return data;
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
  Serial.print(c);
  Serial.print(" ");
  Serial.print(x);
  Serial.print(" ");
  Serial.print(m);
  Serial.print(" ");
  Serial.print(sec);
  Serial.println();

  out.r = (interm.r + m) * 255;
  out.g = (interm.g + m) * 255;
  out.b = (interm.b + m) * 255;

  return out;
}


void loop() {
  static hsv hsvin;
  static rgb rgbout;

  hsvin = readdata (hsvin);

  /*Serial.print(hsvin.h);
  Serial.print(" ");
  Serial.print(hsvin.s);
  Serial.print(" ");
  Serial.println(hsvin.v);*/

  rgbout = hsv2rgb(hsvin);

  Serial.print(rgbout.r);
  Serial.print(" ");
  Serial.print(rgbout.g);
  Serial.print(" ");
  Serial.println(rgbout.b);

  analogWrite (9, rgbout.r);
  analogWrite (10, rgbout.g);
  analogWrite (11, rgbout.b);
}