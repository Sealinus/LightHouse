int r, g, b, h, v = 0;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(50);
}

void readhv () {
  if (Serial.available() > 0) {
    String bufString = Serial.readString(); 
    byte dividerIndex = bufString.indexOf(';'); 

    String buf_1 = bufString.substring(0, dividerIndex); 
    String buf_2 = bufString.substring(dividerIndex + 1);

    v = buf_1.toInt(); 
    h = buf_2.toInt();
    Serial.println(v);
    Serial.println(h);
  }
}

int hi (int a) {
  return ((a / 60) % 6);
}

int vinc (int a, int b) {
  return (b * ((a % 60)/60));
}

int vdec (int b, int c) {
  return (b - c);
}

void rgb (int x, int y, int z, int n) {
  switch (n) {
    case 0 :
      r = x; g = y; b = 0;
    case 1 :
      r = z; g = x; b = 0;
    case 2 :
      r = 0; g = x; b = y;
    case 3 :
      r = 0; g = z; b = x;
    case 4 :
      r = y; g = 0; b = x;
    case 5 :
      r = x; g = 0; b = z;
}
}

void loop() {
  readhv ();
  rgb (v, vinc(h,v), vdec(v, vinc(h, v)), hi(h));
  analogWrite (9, r);
  analogWrite (10, g);
  analogWrite (11, b);
  Serial.print(r);
  Serial.print(" ");
  Serial.print(g);
  Serial.print(" ");
  Serial.println(b);
}