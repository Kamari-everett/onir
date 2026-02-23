// Binds Wire callbacks to addresses in IODevice::state.

#include "Wire.h"

#include "io_device.h"
#include "uno_pinout.h"
#include "selector.h"
#include "log.h"

DisplayDevice device;
Display display;

int* pinout = set_uno_pinout(init_interface);
IODevice io;

int channel;

void on_receive(int n_bytes) {
  int n = n_bytes;
  if (n > (int)sizeof(DisplayState)){
    Serial.println("Format error!");
    n = (int)sizeof(DisplayState);
  }
  Wire.readBytes((byte*)&io.state.display, n);
}

void on_request() {
  Wire.write((byte*)&io.state.dial, sizeof(DialState));
}

void setup() {
  Serial.begin(9600);
  log_winks = 10;  // I need a second.
  Serial.println("starting io device");
  Dial dial;
  DialDevice dial_device;

  device.set_pinout(pinout);
  dial_device.set_pinout(pinout);
  dial.attach(&dial_device);
  display.attach(&device);
  display.set_point(-1);
  channel = Selector(&dial, &display).get_channel();

  Serial.print("selected: ");
  Serial.println(channel);
  io.set_pinout(pinout);

  Wire.begin(channel);
  Wire.onReceive(on_receive);
  Wire.onRequest(on_request);
}

void loop() {
  io.update();
  log(io.state);
}