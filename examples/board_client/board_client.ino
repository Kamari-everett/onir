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

void loop() {
  onir.update();
}
