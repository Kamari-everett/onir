#include "onir.h"

#include "control.h"
#include "board.h"

#include "Arduino.h"

Interface init_interface;

int interface_size = (int)PinFunction::END;

Onir::Onir(int* channels, int count) {
  control = new Control(channels, count);
  board = new Board(control);
}

void Onir::display(char* message) {
  board->display(message);
}

void Onir::act() {
  if (go()) {
    board->pan(1);
    if (control->clients[9]) {
      pp(control->clients[9]->local_);
    }
  }
}

void Onir::update() {
  control->update();
  act();
  board->present();
}

int Onir::step() {
  return millis() / step_ms_;
}

bool Onir::go() {
  int old_step = step_;
  return old_step != (step_ = step());
}
