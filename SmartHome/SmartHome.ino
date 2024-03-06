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


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "PHomeMedia";
char pass[] = "1409290373";

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin 1
byte color[3] = {0,0,0};
byte swich;

BLYNK_WRITE(V0)
{
  byte pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  analogWrite(0, pinValue);
  color[0] = ~pinValue;
  Serial.print(color[0]);
  Serial.print(" ");
  Serial.print(color[1]);
  Serial.print(" ");
  Serial.print(color[2]);
  Serial.println(" ");
}

BLYNK_WRITE(V1)
{
  byte pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  analogWrite(2, pinValue);
  color[1] = ~pinValue;
  Serial.print(color[0]);
  Serial.print(" ");
  Serial.print(color[1]);
  Serial.print(" ");
  Serial.print(color[2]);
  Serial.println(" ");
}

BLYNK_WRITE(V2)
{
  byte pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  color[2] = ~pinValue;
  analogWrite(4, pinValue);
  Serial.print(color[0]);
  Serial.print(" ");
  Serial.print(color[1]);
  Serial.print(" ");
  Serial.print(color[2]);
  Serial.println(" ");
}

BLYNK_WRITE(V3)
{
  byte pinValue = param.asInt();
  swich = pinValue;
  if (swich == 1) {Serial.println("Power is ON"); digitalWrite(15, LOW);}
  else {Serial.print("Power is OFF"); digitalWrite(15, HIGH);}
}

void setup()
{
  // Debug console
  Serial.begin(115200);

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
