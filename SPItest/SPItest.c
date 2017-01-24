#include <wiringPi.h>    //gcc -o SPItest SPItest.c -lwiringPi
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<stdint.h>
#include <inttypes.h>
#include <wiringPiSPI.h>
#include <errno.h>

#define channel 0
#define speed   1000000
#define Size 20

int main (void)    
{
  //char *buFFer=NULL;
  //char outbuffer[Size] ;
  uint8_t *data=NULL,C=0;
  int i=0;
  data=&C;
  printf ("Raspberry Pi - Button and Blink\n") ;
  
  
  //printf ("Raspberry Pi - Button and Blink\n") ;
  //Check we have wiringPi
  if (wiringPiSetup () == -1 )
    exit (1);
  if (wiringPiSPISetup (channel, 1000000) < 0) 		//設置SPI通道 0，速率 1000000 hz
  {
	fprintf (stderr, "Unable to open SPI device 0: %s\n", strerror (errno)) ;
    exit(1);
  }
  wiringPiSetupSys() ;

  
  for (;;) 
  {
	 
	//memset(outbuffer, buFFer, Size);
	for(i=0;i<Size;i++)
	{
		*(data+i)=0x55;
	}
	//memset(data, 0x55, sizeof(data)); 
	wiringPiSPIDataRW (channel, data, Size) ;
		
		//memset(outBuffer, buFFer[a], sizeof(outBuffer));
		//wiringPiSPIDataRW (channel, outBuffer, 1) ;
	delay (1);
    //int re = wiringPiSPIDataRW (channel, buFFer, Size);
	//printf("%d\n", re);
    //all_leds_off();
    
  }
}

