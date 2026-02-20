#pragma once

#include "onir.h"

class DialDevice {
public:
  DialDevice() {}
  DialDevice(int p[(int)PinFunction::END]);

  void set_pinout(int* p) { pinout = p; };
  void init();
  void read(DialState& state);

private:
  int* pinout = nullptr;

  bool clock = true;  // this pin is HIGH by default

  bool clock_pin() const;
  bool data_pin() const;
  bool switch_pressed() const;
};
