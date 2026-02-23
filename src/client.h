#include "onir.h"
#include "display.h"
#include "dial.h"

class Client {
public:
  Client(int channel);
  Client(Interface pinout);
  void update();
  Dial dial;
  Display display;
  int channel;

  IOState local_;  // for logging; use dial and display directly.
};
