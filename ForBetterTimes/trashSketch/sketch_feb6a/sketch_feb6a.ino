#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL4YnrPIMvg"
#define BLYNK_TEMPLATE_NAME "LED ESP32"
//#define BLYNK_AUTH_TOKEN "LN3NX-_zRBTWiUJxUbEGpiiDuO5h4S_o"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define APP_DEBUG

#include "BlynkEdgent.h"

#define LED_PIN 2  // Use pin 2 for LED (change it, if your board uses another pin)


// V0 is a datastream used to transfer and store LED switch state.
// Evey time you use the LED switch in the app, this function
// will listen and update the state on device
BLYNK_WRITE(V0)
{
  // Local variable `value` stores the incoming LED switch state (1 or 0)
  // Based on this value, the physical LED on the board will be on or off:
  int value = param.asInt();

  if (value == 1) {
    digitalWrite(LED_PIN, HIGH);
    Serial.print("value =");
    Serial.println(value);
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.print("value = ");
    Serial.println(value);
  }
}
void setup()
{
  pinMode(LED_PIN, OUTPUT);

  // Debug console. Make sure you have the same baud rate selected in your serial monitor
  Serial.begin(115200);
  delay(100);

  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
  delay(10);
}