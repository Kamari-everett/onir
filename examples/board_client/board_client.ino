#include "onir.h"
#include "control.h"
#include "log.h"
#include "board.h"

#include "Wire.h"


int channels[3] = { 8, 9, 10 };
Onir onir(channels, 3);

IOState state;

const char message[16] = "ko labs -- onir --";

void setup() {
  Serial.begin(9600);
  Serial.println("start");
  log_winks = 25;
  onir.board->display(message);
  Wire.begin();
}

void policy() {
  log(state);

  // if (millis() < banner_ms) return;
  // if (millis() - last_update_ms > update_ms) {
  //   last_update_ms = millis();

  //   // get dial state from device.
  //   // client->screen.set_value(millis());
  //   client->screen.set_value(state.dial.count = client->dial.value());

  //   // vvv copy _screen's_ contents to _local iostate_ (for debugging) vvv
  //   for (int i = 0; i < 4; i++) {
  //     state.screen.chars[i] = client->screen.state.chars[i];
  //   }
  //   state.screen.point = client->screen.state.point;
  //      // ^^^ remove above once no longer needed. (ideally before it causes a time-wasting bug.). ^^^
  // }
}



void loop() {
  onir.update();
  policy();
}
