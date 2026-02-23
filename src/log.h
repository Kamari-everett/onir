#include "onir.h"


void log(const IOState& s);

void print_io(const IOState& s);

void print_display(const DisplayState& display);

class Client;
void log_io(Client* client);

extern int log_winks;
