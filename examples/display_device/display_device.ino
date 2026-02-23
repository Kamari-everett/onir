#include "display_device.h"
#include "uno_pinout.h"

#include "Wire.h"

DisplayDevice display;

void update_display(int message_size) {
  Wire.readBytes((byte*)&display.state, message_size);
}

void setup() {
  Serial.begin(9600);
  Serial.println("starting display.");
  display.set_pinout(set_uno_pinout(init_interface));

  Wire.begin(DISPLAY_DEVICE_CHANNEL);
  Wire.onReceive(update_display);
}

void loop() {
  display.refresh();
}
