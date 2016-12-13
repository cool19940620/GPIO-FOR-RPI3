#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>

#define LED     1         //wiringPi pin 1 is BCM_GPIO 18.
#define BUTTON  6  //wiringPi pin 6 is BCM_GPIO 22 25.
void all_leds_off();
void init_pins();

int main (void) {
  printf ("Raspberry Pi - Button and Blink\n") ;
  //Check we have wiringPi
  if (wiringPiSetup () == -1 ) exit (1);
  init_pins();
  all_leds_off();
  int i = 0;
  for (;;) {
    if (digitalRead (BUTTON) == 0 ) {
        i++;
        printf ("Button pressed (%d)\n", i) ;
        digitalWrite (LED,1);
        delay (100);
    }
    all_leds_off();
    delay (50);
  }
}

void init_pins() {
  //set led as outputs...
  printf ("Setup Pin 12 is Output...\n") ;
  pinMode(LED, OUTPUT);

  // set button as an input...
  printf ("Setup Pin 22 is Input..\n") ;
  pinMode(BUTTON, INPUT);
}

void all_leds_off() {
    digitalWrite (LED,0);
}