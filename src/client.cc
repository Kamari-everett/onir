#include "client.h"
#include "log.h"
#include "dial_device.h"

#include "Arduino.h"

Client::Client(int channel, const Hardware& hardware) :
  hardware(hardware), channel(channel), dial(channel), display(channel) { }
  
Client::Client(Interface pinout, const Hardware& hardware) :
  hardware(hardware), dial(hardware), display(pinout, hardware) {
  dial.attach(new DialDevice(hardware));
}

void Client::update() {
  dial.update();
  display.refresh();
}


