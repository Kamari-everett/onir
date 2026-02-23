#include "onir.h"

#include "control.h"
#include "screen.h"

#include "Arduino.h"

Interface init_interface;

int interface_size = (int)PinFunction::END;

Onir::Onir(int* channels, int count) {
  control = new Control(channels, count);
  screen = new Screen(control);
}

void Onir::set_pinout(Interface pinout) {
  control->set_pinout(pinout);
}

void Onir::display(char* message) {
  screen->display(message);
}

void Onir::act() {
  if (go()) {
    screen->pan(1);
    if (control->clients[8]) {
      log_io(control->clients[8]);
    }
  }
}

void Onir::update() {
  control->update();
  act();
  screen->present();
}

int Onir::step() {
  return millis() / step_ms_;
}

bool Onir::go() {
  int old_step = step_;
  return old_step != (step_ = step());
}
