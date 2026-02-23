#include "client.h"
#include "log.h"

#include "Arduino.h"

Client::Client(int channel) : channel(channel), dial(channel), screen(channel) {
}

void Client::update() {
  dial.update();
  screen.refresh();
}


