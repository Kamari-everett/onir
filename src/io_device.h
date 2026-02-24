#pragma once

#include "onir.h"
#include "display_device.h"
#include "dial_device.h"
#include "selector.h"

// I2C-ready device that runs a display and dial.
//
// I2C is configured at the sketch level.
// This class knows nothing about Wire, addresses, or handlers.
//
// device:
//   - state.display is written by transport layer (DisplayState)
//   - state.dial   is read    by transport layer (DialState)
//
// loop():
//   - refresh display from state.display
//   - update state.dial from hardware

class IODevice {
public:
  IODevice();

  void set_pinout(int* p) {
    pinout = p;
    display->set_pinout(pinout);
    dial->set_pinout(pinout);
  }

  int reboot_channel = -1;

  void update() {
    // Update dial state from hardware
    dial->read(state.dial);

    // Push display state to hardware (scan / refresh)
    display->state = state.display;
    display->refresh();

    // if (state.dial.button) {
    // nope!  Selector selector(&pinout);
    //   selector.set_button(state.dial.button);
    //   reboot_channel = selector.get_channel();
    // }
  }

  IOState state;   // shared storage (transport reads/writes this)

private:
  int* pinout = 0;
  
  DialDevice* dial;
  DisplayDevice* display;
  
};
