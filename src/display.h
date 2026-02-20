#pragma once

#include "screen.h"

// Splits a string across a handful of screens and keeps them refreshed.

class Display {

public:
  Display() {}
  
  Display(Screen* const screens[], int count)
    : screens_(screens), count_(count),
      message_(0), length_(0), shift_(0) {}
  
  void write(const char* text) {
    message_ = text;
    shift_ = 0;
    review();
  }

  void scroll(int change) {
    if (!message_) return;
    shift_ += change;
    review();
  }

  void offset(int offset) {
    shift_ = offset;
    review();
  }

  int get_offset() const { return shift_; }
    

  void refresh() {
    for (int s = 0; s < count_; s++)
      screens_[s]->refresh();
  }

private:

  void review() {
    if (!message_ || !message_[0]) {
      clear_all();
      return;
    }

    length_ = length(message_);
    int padded_len = length_ + 2;

    int global_pos = 0;
    for (int s = 0; s < count_; s++)
      global_pos = view(s, global_pos, padded_len);
  }
  
  int view(int screen_index, int global_pos, int padded_len) {
    Screen* screen = screens_[screen_index];

    for (int i = 0; i < 4; i++) {
      screen->put_char(i, at(global_pos, padded_len));
      global_pos++;
    }

    return global_pos;
  }

  // Maps integer offset into a circular view of the message_.
  char at(int global_pos, int padded_len) const {
    int index = shift_ + global_pos;

    int m = index % padded_len;  // After the end comes the beginning.
    if (m < 0) m += padded_len;

    if (m >= length_)
      return ' ';

    return message_[m];
  }

  void clear_all() {
    for (int s = 0; s < count_; s++) {
      Screen* screen = screens_[s];
      for (int i = 0; i < 4; i++)
        screen->put_char(i, ' ');
    }
  }

  static int length(const char* s) {
    int n = 0;
    while (s and s[n]) n++;
    return n;
  }

  Screen* const* screens_;
  int count_;

  const char* message_;
  int length_;
  int shift_;
};

// I used an AI assistant to draft this file. This was the first time I've gotten a positive
// result out of one of these coding tools.
// (https://chatgpt.com/share/699853fb-a1b8-8003-9d56-4e841b3d149c)
