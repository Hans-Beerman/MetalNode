#include <ButtonDebounce.h>

#define GPIO_PIN (10)

ButtonDebounce button(GPIO_PIN);

void buttonChanged(int state){
  Serial.println("Changed: " + String(state));
}

void setup() {
  Serial.begin(115200);
  button.setCallback(buttonChanged);
}

void loop() {
}
