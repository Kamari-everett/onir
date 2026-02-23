#include "io_device.h"

IODevice::IODevice() {
  dial = new DialDevice();
  display = new DisplayDevice();

}
