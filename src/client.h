#include "onir.h"
#include "screen.h"
#include "dial.h"

class Client {
public:
  Client(int channel);
  void update();
  void check();
  Dial dial;
  Screen screen;

  IOState local_;  // for logging; use dial and screen directly.
};
