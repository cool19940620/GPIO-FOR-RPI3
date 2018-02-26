#include <wiringPi.h>    //gcc -o SPItest SPItest.c -lwiringPi
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<stdint.h>
#include <inttypes.h>
#include <wiringSerial.h>
#include <errno.h>

#define channel 0
#define speed   1000000
#define Size 20
int fd ;
char readbuf[100]={0};
char starttex[]={0xa0,0xa0,0xa0,'\0'};
char ans_starttex[]={0x50,0x50,0x16,'\0'};

char starttex2[]={0xa1,0x2f,0x09,'\0'};
char ans_starttex2[]={0x51,0x2f,0x09,'\0'};

char starttex3[]={0xa2,0x18,0x30,'\0'};
char ans_starttex3[]={0x52,0x18,0x30,'\0'};

char boxttex1[]={0xa9,0x01,0x00,'\0'};
char ans_boxttex1[]={0x59,0x01,0x00,'\0'};

char boxttex2[]={0xa9,0x02,0x00,'\0'};
char ans_boxttex2[]={0x59,0x02,0x00,'\0'};

char onetesttex[]={0xaa,0x05,0x00,'\0'};
char ans_onetesttex[]={0x5b,0x00,0x00,'\0'};

char ctesttex[]={0xab,0xab,0x00,'\0'};
char ans_ctesttex[]={0x5b,0x00,0x00,'\0'};//key

char Endtesttex[]={0xac,0xac,0x00,'\0'};
char ans_Endtesttex[]={0x5c,0x00,0x00,'\0'};

void Sinit(char[],char[]);
void keyword(char[],char[]);
void testword(void);

int main (void)    
{
	
	if ((fd = serialOpen ("/dev/ttyAMA0", 115200)) < 0)
	{
		fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
		//delay (1000) ;
		return 1 ;
	}

	if (wiringPiSetup () == -1)
	{
		fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
		//delay (1000) ;
		return 1 ;
	}
	
	Sinit(Endtesttex,ans_Endtesttex);
	Sinit(starttex,ans_starttex);
	Sinit(starttex2,ans_starttex2);
	Sinit(starttex3,ans_starttex3);
	printf ("init OK ") ;

	while(1)
	{
		keyword(ctesttex,ans_ctesttex);//KEY	
	}
		
	//Sinit(Endtesttex,ans_Endtesttex);
	printf ("\n") ;
	return 0 ;
}

void Sinit(char sss[],char ans_sss[])
{
	readbuf[0]=0;
	readbuf[1]=0;
	readbuf[2]=0;	
	int readbufcount,f,endf;
	unsigned int nextTime ;
	f=0;
	nextTime = millis () + 300 ;	
	do
	{
		//if (millis () > nextTime)
		//{ 	
		//	if(f==0)
			//	printf ("\nOut: %x %x %x --->",sss[0],sss[1],sss[2]) ;
			fflush (stdout) ;
			serialPutchar (fd, sss[0]) ;
			serialPutchar (fd, sss[1]) ;
			serialPutchar (fd, sss[2]) ;
			nextTime += 300 ;
			f=1;
		//}
		delay (3) ;
		readbufcount=0;
		while (serialDataAvail (fd))
		{
			readbuf[readbufcount]=serialGetchar (fd);
			// printf (" -> %x", serialGetchar (fd)) ;
			fflush (stdout) ;
			readbufcount++; 
		}  
		endf=0;	
		if(readbuf[0]==ans_sss[0] && readbuf[1]==ans_sss[1] && readbuf[2]==ans_sss[2])
			endf=1;
		//printf("%X %X %X \n",readbuf[0],readbuf[1],readbuf[2]);		
		//delay (1000) ;
	}while(endf==0);
	//printf ("good ") ;
	f=0;
	//delay (1000) ;
}
void keyword(char sss[],char ans_sss[])
{
	Sinit(boxttex2,ans_boxttex2);
	readbuf[0]=0;
	readbuf[1]=0;
	readbuf[2]=0;	
	int readbufcount,f,endf;
	unsigned int nextTime ;
	f=0;
	nextTime = millis () + 300 ;	
	
		//if (millis () > nextTime)
		//{ 	
			//if(f==0)
			//	printf ("\nOut: %x %x %x --->",sss[0],sss[1],sss[2]) ;
			fflush (stdout) ;
			serialPuts (fd, sss) ;
			serialPuts (fd, sss) ;
			serialPuts (fd, sss) ;
			serialPuts (fd, sss) ;
			serialPuts (fd, sss) ;
			printf ("\nsay key \n") ;
			nextTime += 300 ;
			f=1;
		//}
		do
	{
		delay (100) ;
		readbufcount=0;
		while (serialDataAvail (fd))
		{
			readbuf[readbufcount]=serialGetchar (fd);
			fflush (stdout) ;
			readbufcount++; 
		}  
		endf=0;		
		if( (readbuf[0]==ans_sss[0]) && (readbuf[1]==ans_sss[1]) && (readbuf[2]==ans_sss[2]) )
		{
			endf=1;
		}
		//printf("%X %X %X \n",readbuf[0],readbuf[1],readbuf[2]);		
		readbuf[0]=0;
		readbuf[1]=0;
		readbuf[2]=0;
		
		//printf("%X %X %X \n",ans_sss[0],ans_sss[1],ans_sss[2]);	
		//printf("%d \n",endf);
	}while(endf==0);
	
	printf ("key OK ") ;
	Sinit(Endtesttex,ans_Endtesttex);
	f=0;
	testword();
}

void testword(void)
{
	Sinit(boxttex1,ans_boxttex1);
	readbuf[0]=0;
	readbuf[1]=0;
	readbuf[2]=0;	
	int readbufcount,f,endf;
	unsigned int nextTime ;
	f=0;
	//if(f==0)
	//	printf ("\nOut: %x %x %x --->",onetesttex[0],onetesttex[1],onetesttex[2]) ;
	fflush (stdout) ;
	serialPutchar (fd, onetesttex[0]) ;
	serialPutchar (fd, onetesttex[1]) ;
	serialPutchar (fd, onetesttex[2]) ;
	nextTime += 300 ;
	f=1;
	do
	{
		delay (100) ;
		readbufcount=0;
		while (serialDataAvail (fd))
		{
			readbuf[readbufcount]=serialGetchar (fd);
			fflush (stdout) ;
			readbufcount++; 
		}  
		endf=0;	
		if(readbuf[0]==0x5a || readbuf[1]==0x7f || readbuf[1]==0xff)
		{
			endf=1;
			printf("\n");
			if(readbuf[1]==0x00 && readbuf[2]==0x00 )
				printf("Sunday driver");
			else if(readbuf[1]==0x01 && readbuf[2]==0x00 )
				printf("Baby in car");
			else if(readbuf[1]==0x02 && readbuf[2]==0x00 )
				printf("Keep a safe distance");
			else if(readbuf[1]==0x03 && readbuf[2]==0x00 )
				printf("Don't force the car");
			else if(readbuf[1]==0x04 && readbuf[2]==0x00 )
				printf("Don't press the horn");
			else if(readbuf[1]==0x05 && readbuf[2]==0x00 )
				printf("Fragile in car");
			else if(readbuf[1]==0x06 && readbuf[2]==0x00 )
				printf("I come from outside");
			else if(readbuf[1]==0x07 && readbuf[2]==0x00 )
				printf("The car broke down");
			printf("\n");
		}
		
		//printf("%X %X %X \n",readbuf[0],readbuf[1],readbuf[2]);		
		
		//printf("%X %X %X \n",ans_sss[0],ans_sss[1],ans_sss[2]);	
		//printf("%d \n",endf);
	}while(endf==0 );

	f=0;
}