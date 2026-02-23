#include "onir.h"
#include "control.h"
#include "log.h"
#include "screen.h"
#include "uno_pinout.h"

#include "Wire.h"

const int N_CHANNELS = 5;
int channels[N_CHANNELS] = { 8, 9, 10, 11, 12 };
Onir onir(channels, N_CHANNELS);


int* pinout = set_uno_pinout(init_interface);

IOState state;

const char message[64] = "ko labs -- onir --";

void setup() {
  Serial.begin(9600);
  Serial.println("start");
  log_winks = 25;
  onir.screen->display(message);
  onir.set_pinout(pinout);
  Wire.begin();
}

void loop() {
  onir.update();
}
