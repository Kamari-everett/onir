#include "client.h"
#include "log.h"

#include "Arduino.h"

Client::Client(int channel) : dial(channel), screen(channel) {
}

void Client::update() {
  dial.update();
  screen.refresh();

  // copy dial and screen contents (not definitive -- just read the dial!)
  const byte* D = (byte*) &dial.state;
  byte* d_ = (byte*) &local_.dial;
  for (int i = 0; i < sizeof(DialState); i++) {
    d_[i] = D[i];
  }

  const byte* S = (byte*) &screen.state;
  byte* s_ = (byte*) &local_.screen;
  for (int i = 0; i < sizeof(ScreenState); i++) {
    s_[i] = S[i];
  }
  
}


