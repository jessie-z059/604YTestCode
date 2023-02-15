#include "main.h"
#include "time.hpp"

using namespace pros;


int start_times[20] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};




void startTimer(int slot) {
  start_times[slot] = millis();
}



int getTime(int slot) {
  return (millis() - start_times[slot]);
}

