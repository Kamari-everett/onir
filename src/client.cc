#include "client.h"
#include "log.h"

#include "Arduino.h"

Client::Client(int channel, const Hardware& hardware) :
  hardware(hardware), channel(channel), dial(channel), display(channel) { }
  
Client::Client(Interface pinout, const Hardware& hardware) :
  hardware(hardware), dial(pinout, hardware), display(pinout) { }

void Client::update() {
  dial.update();
  display.refresh();
}


