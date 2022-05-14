#include <Arduino.h>
#include "TeensyThreads.h"

const int LED = 13;

volatile int blinkcode = 0;

void blinkthread() {
  while(true) {
    
    threads.yield();
  }
}

extern "C" int main(void)
{
	delay(1000);
	threads.addThread(blinkthread);
	while (1) {}
}
