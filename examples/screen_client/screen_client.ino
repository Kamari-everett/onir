#include "screen.h"
#include "Wire.h"

Screen screen(SCREEN_DEVICE_CHANNEL);

void banner() {
  screen.put_str("onir");
}

void flash() {
  screen.set_point((millis() / 1000) % 2 ? -1 : 1);
}

void setup() {
  Serial.begin(9600);
  banner();
  Wire.begin();
  Serial.println("onir");
}

void loop() {
  flash();
  screen.refresh();
}
