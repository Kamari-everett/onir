#include "log.h"

#include "Arduino.h"

int wink() { return millis() / 100; }  // a blink is 1/5 s. a wink is half a blink.
// int log_winks = 600;  // give me a minute to think.

int log_winks = 10; // I need a second.

void log(const IOState& s) {
  static long log_time_winks = -log_winks;  // persists across calls
  if (wink() - log_time_winks > log_winks) {
    log_time_winks = wink();
    print_io(s);
  }
}

static char safe(char c) {
  if (c == 0) return '0';
  if (c < 32 || c == 127) return '\\';
  return c;
}

static long checksum(const IOState& s) {
  const byte* p = (const byte*)&s;
  long sum = 0;
  for (int i = 0; i < (int)sizeof(IOState); ++i)
    sum += p[i];
  return sum;
}


static bool prints(char c) {
  return (c == 0 or (c >= 32 and c < 127));
}

static void print_screen(const ScreenState& screen) {
  bool printable = true;
  for (int i = 0; i < 4; ++i) {
    if (!prints(screen.chars[i])) {
      printable = false;
      break;
    }
  }

  if (printable) {
    Serial.print("\"");
    char buf[5];
    for (int i = 0; i < 4; ++i) {
      char ch = screen.chars[i];
      buf[i] = ch ? ch : ' ';
    }
    buf[4] = '\0';
    Serial.print(buf);
    Serial.print("\"");
    return;
  }

  // mixed / non-printable case
  Serial.print('{');
  for (int i = 0; i < 4; ++i) {
    if (prints(screen.chars[i])) {
      Serial.print('\'');
      Serial.print(screen.chars[i]);
      Serial.print('\'');
    } else {
      Serial.print(String((int)(byte)screen.chars[i]));
    }

    if (i != 3) Serial.print(", ");
  }
  Serial.print('}');
}

void print_io(const IOState& state) {

  static unsigned int log_id = 0;

  Serial.print('#');
  Serial.print(log_id++);
  Serial.print(" {c: ");
  Serial.print(state.channel);
  Serial.print(", s: {m: ");
  print_screen(state.screen);
  Serial.print(", p: ");
  Serial.print(state.screen.point);
  Serial.print("}, d: {v: ");

  long v = state.dial.count;

  // left pad to width 4 incl sign
  if (v >= 0) Serial.print(' ');
  if (v > -100 && v < 100) Serial.print(' ');
  if (v > -10  && v < 10)  Serial.print(' ');

  Serial.print(v);

  Serial.print("; b: ");
  Serial.print(state.dial.button ? 1 : 0);
  Serial.print("}, #: ");
  Serial.print(checksum(state));
  Serial.print(" } (m: ");
  Serial.print(millis());
  Serial.println(")");
}

void pp(const IOState& s) { print_io(s); }

