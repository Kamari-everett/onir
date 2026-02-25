#include "display.h"

#include "Arduino.h"
#include "Wire.h"

#include "display_device.h"

Display::Display(const Hardware& hardware) : hardware(hardware) {
  clear();
}

Display::Display(int ch, const Hardware& hardware) : channel(ch), hardware(hardware) {
  clear();
}

void Display::refresh() {
  if ((long)millis() - last_update > UPDATE_MILLIS) {
    last_update = millis();
    send_update();
    update_local();
  }
  if (device) {
    device->refresh();
  }
}

String chars(DisplayState state) {
  char result[5];
  for (int i = 0; i < 4; i++) {
    result[i] = (char)state.chars[i];
  }
  result[5] = 0;
  return String(result);
}

void Display::send_update() {
  if (channel < 0) return;
  Wire.beginTransmission(channel);
  Wire.write((const byte*) &state, (int)sizeof(DisplayState));
  Wire.endTransmission();
}


void Display::update_local() {
  if (device){
    device->update(state);  
  }
}
