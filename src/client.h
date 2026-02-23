#include "onir.h"
#include "screen.h"
#include "dial.h"

class Client {
public:
  Client(int channel);
  void update();
  Dial dial;
  Screen screen;
  int channel;

  IOState local_;  // for logging; use dial and screen directly.
};
