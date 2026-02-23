#include "client.h"
#include "log.h"

#include "Arduino.h"

Client::Client(int channel) : channel(channel), dial(channel), display(channel) {
}

Client::Client(Interface pinout) : dial(pinout), display(pinout) { }

void Client::update() {
  dial.update();
  display.refresh();
}


