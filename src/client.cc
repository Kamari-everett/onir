#include "client.h"
#include "log.h"

#include "Arduino.h"

Client::Client(int channel) : channel(channel), dial(channel), display(channel) {
}

void Client::update() {
  dial.update();
  display.refresh();
}


