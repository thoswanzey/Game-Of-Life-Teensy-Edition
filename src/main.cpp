#include <Arduino.h>
#include "TeensyThreads.h"

const int LED = 13;

volatile int blinkcode = 0;

void blinkthread() {
  while(1) {
    if (blinkcode) {
      for (int i=0; i<blinkcode; i++) {
        digitalWrite(LED, HIGH);
        threads.delay(150);
        digitalWrite(LED, LOW);
        threads.delay(150);
      }
      blinkcode = 0;
    }
    threads.yield();
  }
}

extern "C" int main(void)
{
	delay(1000);
	pinMode(LED, OUTPUT);
	threads.addThread(blinkthread);

	int count = 0;
	while (1) {
		count++;
		blinkcode = count;
		delay(5000);
	}
}
