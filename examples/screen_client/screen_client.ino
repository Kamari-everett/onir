#include "onir.h"
#include "control.h"
#include "log.h"
#include "screen.h"

#include "Wire.h"

const int N_CHANNELS = 5;
int channels[N_CHANNELS] = { 8, 9, 10, 11, 12 };
Onir onir(channels, N_CHANNELS);

IOState state;

const char message[64] = "ko labs -- onir --";

void setup() {
  Serial.begin(9600);
  Serial.println("start");
  log_winks = 25;
  onir.screen->display(message);
  Wire.begin();
}

void loop() {
  onir.update();
}
