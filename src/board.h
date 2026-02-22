#pragma once

#include "screen.h"
#include "control.h"
#include "log.h"

#include "Arduino.h"

#define WIDTH 256

// Splits a string across a handful of screens and keeps them refreshed.
class Board {

public:
  Board() {}
  
  Board(Control* control) : control_(control) {
    Serial.println("board");
    clear();
  }

  void clear() {
    erase();
    fan();
  }
  
  void erase() {
    for (int i = 0; i < WIDTH; i++) {
      display_[i] = 0;
    }
    message_ = 0;
  }
    
  void display(const char* message) {
    message_ = message;
    record();
    present();
  }

  void pan(int move) {
    index_ += move;
    present();
  }

  void seek(int index) {
    index_ = index;
    present();
  }

  int index() const { return index_; }
  int width() const { return length(display_); }
  
private:
  char at(int index) {
    return display_[mod(width(), index)];;
  }
  
  void present() {
    for (int channel = 0; channel < BANDS; channel++) {
      if (Client* client = control_->clients[channel]) {
        char ch;
        for (int i = 0; i < 4; i++) {
          client->screen.put_char(i, at(i + positions_[channel] + index_));
        }
      }
    }
  }
  
  void fan() {  // Sequence channel offsets from zero.
    index_ = 0;
    for (int channel = 0; channel < BANDS; channel++) {
      positions_[channel] = 0;
    }
    int count = 0;
    for (int channel = 0; channel < BANDS; channel++) {
      if (control_->clients[channel]) {
        positions_[channel] = 4 * count++;
      }
    }
    present();
  }

  int record() {                                // may pad start/end:
    int receipt = length(message_);             // find the 0
    int length = 0;
    if (receipt and message_[0] != ' ') {
      display_[length++] = ' ';                 // left-pad
    }
    for (int i = 0; (i < receipt) and (length < WIDTH - 1);) {
      display_[length++] = message_[i++];       // copy message
    }
    while (length < 4) {                        // pad to 4
      display_[length++] = ' ';
    }
    if (display_[length-1] != ' '  and length < WIDTH - 2) {
      display_[length++] = ' ';                 // right-pad
    }      
    display_[length] = 0;                       // terminate
    Serial.print(length);
    Serial.print(" ");
    return length;
  }

  static int mod(int modulus, int value) {   // oh, C++...
    int ret = value % modulus;
    if (ret < 0) { ret += modulus; }
    return ret;
  }

  static int length(const char* str) {
    int length = 0;
    while (str and str[length]) { length++; }
    return length;
  }
  
  Control* const control_;
  const char* message_;
  char display_[WIDTH];
  int index_;
  int positions_[BANDS];
  
};
