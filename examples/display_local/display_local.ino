#include "display.h"
#include "display_device.h"
#include "uno_pinout.h"

Display display;
DisplayDevice device;

void banner() {
  display.put_str("onir");
  display.set_point(1);
  Serial.println("onir");
}

void setup() {
  Serial.begin(9600);
  device.set_pinout(set_uno_pinout(init_interface));
  display.attach(&device);
  banner();
}

void loop() {
  display.refresh();
}
