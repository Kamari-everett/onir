#pragma once

#include "onir.h"
#include "screen_device.h"
#include "dial_device.h"

// I2C-ready device that runs a screen and dial.
//
// I2C is configured at the sketch level.
// This class knows nothing about Wire, addresses, or handlers.
//
// device:
//   - state.screen is written by transport layer (ScreenState)
//   - state.dial   is read    by transport layer (DialState)
//
// loop():
//   - refresh screen from state.screen
//   - update state.dial from hardware

class IODevice {
public:
  IODevice() {}

  void set_pinout(int* pinout) {
    pinout_ = pinout;
    screen_.set_pinout(pinout);
    dial_.set_pinout(pinout);
  }

  void update() {
    // Update dial state from hardware
    dial_.read(state.dial);

    // Push screen state to hardware (scan / refresh)
    screen_.state = state.screen;
    screen_.refresh();
  }

  IOState state;   // shared storage (transport reads/writes this)

private:
  int* pinout_ = 0;

  ScreenDevice screen_;
  DialDevice dial_;
};
