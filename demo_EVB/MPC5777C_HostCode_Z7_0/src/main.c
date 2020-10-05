/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */

#include "igf_init.h"


/* SIU macros */
#define APC 0x2000
#define OBE 0x0200
#define IBE 0x0100
#define ODE 0x0020
#define SRC 0x0004
#define WPE 0x0002
#define WPS 0x0001
#define ALT0 0x0000
#define ALT1 0x0400
#define ALT2 0x0800
#define ALT3 0x0C00

/* PCR numbers */
#define ETPUA0_pin 114
#define ETPUA1_pin 115
#define ETPUA2_pin 116
#define ETPUA3_pin 117

#define ETPUB0_pin 147
#define ETPUB1_pin 148
#define ETPUB2_pin 149
#define ETPUB3_pin 150

#define ETPUC0_pin 441
#define ETPUC1_pin 442


extern void xcptn_xmpl(void);


void fail()
{
	volatile int counter;

	/* re-configure as GPIO output */
	SIU.PCR[114].R = 0x0200; // PA = 0, OBE = 1
	SIU.GPDO[114].R = 1;

	/* Loop forever */
	while (1)
	{
		counter = 0;
		for(;;)
		{
			counter++;
			if (counter == 4000000)
				SIU.GPDO[114].R = 0;
			else if (counter == 8000000)
			{
				SIU.GPDO[114].R = 1;
				break;
			}
		}
	}
}

extern int user_main();

int g_ret_val;

int main(void)
{
	xcptn_xmpl ();              /* Configure and Enable Interrupts */

	/* initialize the portion of the IGF module that works with the eTPU */
	igf_init();

	/* initialize the pins used by this demo app */
	/* BC pins */
    SIU.PCR[ETPUA0_pin].R = (ALT1 | IBE | WPE | WPS) ;
    SIU.PCR[ETPUA1_pin].R = (ALT1 | IBE | WPE | WPS) ;
    SIU.PCR[ETPUA2_pin].R = (ALT1 | OBE | WPE | WPS) ;
    SIU.PCR[ETPUA3_pin].R = (ALT1 | OBE | WPE | WPS) ;
    /* RT pins */
    SIU.PCR[ETPUB0_pin].R = (ALT1 | IBE | WPE | WPS) ;
    SIU.PCR[ETPUB1_pin].R = (ALT1 | IBE | WPE | WPS) ;
    SIU.PCR[ETPUB2_pin].R = (ALT1 | OBE | WPE | WPS) ;
    SIU.PCR[ETPUB3_pin].R = (ALT1 | OBE | WPE | WPS) ;
    /* MT pins */
    SIU.PCR[ETPUC0_pin].R = (ALT1 | IBE | WPE | WPS) ;
    SIU.PCR[ETPUC1_pin].R = (ALT1 | IBE | WPE | WPS) ;

    g_ret_val = user_main();
	if (g_ret_val)
		fail();

	return 0;
}
