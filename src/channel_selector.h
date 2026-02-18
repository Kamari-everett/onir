#include <Arduino.h>

#include "onir.h"

#include "dial.h"
#include "char_device.h"

// uses a dial and screen to select a numerical I2C channel (int).
class ChannelSelector {
public:
  ChannelSelector(Dial* d, CharDevice* s) {
    dial = d;
    screen = s;
    channel = 9;  // a dial gets channel 8 by default.
  }

  int get_channel();


private:
  int channel;

  Dial* dial;
  CharDevice* screen;
  
  const int min_channel = 0x08;        // = 8 -- https://i2cdevices.org/addresses
  const int max_channel = 0x77;        // 0x77 = 119
  // note: 192 - 8 = 184 = 8x23 => 32x23 char 'screen'


  char hex_digit(int value);

  void display_channel();


  void channel_up();
  void channel_down();

};

