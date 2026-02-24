#include "client.h"
#include "log.h"

#include "Arduino.h"

Client::Client(int channel, const Hardware& hardware) :
  hardware(hardware), channel(channel), dial(channel), display(channel) { }
  
Client::Client(Interface pinout, const Hardware& hw) :
  hardware(hw), dial(pinout), display(pinout) { }

void Client::update() {
  dial.update();
  display.refresh();
}


