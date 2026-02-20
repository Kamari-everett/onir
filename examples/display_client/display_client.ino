#include "display.h"

#include "dial.h"
#include "uno_pinout.h"  // for dial

#include "Wire.h"

Dial dial;
Display display;

const int n_channels = 3;
int channels[n_channels] = { 9, 10, 11 };
Screen* screens[n_channels] = { 0, 0, 0 };

void setup() {
  Serial.begin(9600);
  Wire.begin();
  for (int i = 0; i < n_channels; i++) {
    screens[i] = new Screen(channels[i]);
  }
  dial = Dial(set_uno_pinout(init_interface));
  display = Display(screens, n_channels);
  display.write("onir -- ko labs --");
}

int offset = 0;
void loop() {
  dial.update();
  int prior_offset = offset;
  offset = millis() / 1000 + dial.value();
  if (prior_offset != offset) {
    display.offset(offset);
  }
  display.refresh();
}
