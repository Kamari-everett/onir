#pragma once

#include "onir.h"

class DialDevice {
public:
  DialDevice(const Hardware& hardware = no_hardware) : hardware(hardware) {}
  DialDevice(Interface p, const Hardware& hardware = no_hardware);
  void set_pinout(Interface p);

  void init();
  void read(DialState& state);

private:
  int* pinout = nullptr;

  bool clock = true;  // this pin is HIGH by default

  bool clock_pin() const;
  bool data_pin() const;
  bool switch_pressed() const;

  const Hardware& hardware;
};
