/*
 * igf_init.c
 *
 *  Created on: Nov 5, 2018
 *      Author: John
 */

#include "igf_init.h"
#include "MPC577xC.h"

/* initialize the IGF module */

/* At reset, the IGF module does not let any input signals through to the eTPU channels 0-14 and */
/* TCRCLK for eTPU A, B and C.  This code enables the IGF for pass-through of all eTPU signals. */
/* Note that filtering on each input can be individually tailored if desired. */

uint32_t igf_init()
{
	// eTPU_C
	IGF_0.MCR0.R = 0x240;
	IGF_0.MCR1.R = 0x240;
	IGF_0.MCR2.R = 0x240;
	IGF_0.MCR3.R = 0x240;
	IGF_0.MCR4.R = 0x240;
	IGF_0.MCR5.R = 0x240;
	IGF_0.MCR6.R = 0x240;
	IGF_0.MCR7.R = 0x240;
	IGF_0.MCR8.R = 0x240;
	IGF_0.MCR9.R = 0x240;
	IGF_0.MCR10.R = 0x240;
	IGF_0.MCR11.R = 0x240;
	IGF_0.MCR12.R = 0x240;
	IGF_0.MCR13.R = 0x240;
	IGF_0.MCR14.R = 0x240;
	IGF_0.MCR15.R = 0x240;
	// eTPU_A
	IGF_1.MCR0.R = 0x240;
	IGF_1.MCR1.R = 0x240;
	IGF_1.MCR2.R = 0x240;
	IGF_1.MCR3.R = 0x240;
	IGF_1.MCR4.R = 0x240;
	IGF_1.MCR5.R = 0x240;
	IGF_1.MCR6.R = 0x240;
	IGF_1.MCR7.R = 0x240;
	IGF_1.MCR8.R = 0x240;
	IGF_1.MCR9.R = 0x240;
	IGF_1.MCR10.R = 0x240;
	IGF_1.MCR11.R = 0x240;
	IGF_1.MCR12.R = 0x240;
	IGF_1.MCR13.R = 0x240;
	IGF_1.MCR14.R = 0x240;
	IGF_1.MCR15.R = 0x240;
	// eTPU_B
	IGF_1.MCR16.R = 0x240;
	IGF_1.MCR17.R = 0x240;
	IGF_1.MCR18.R = 0x240;
	IGF_1.MCR19.R = 0x240;
	IGF_1.MCR20.R = 0x240;
	IGF_1.MCR21.R = 0x240;
	IGF_1.MCR22.R = 0x240;
	IGF_1.MCR23.R = 0x240;
	IGF_1.MCR24.R = 0x240;
	IGF_1.MCR25.R = 0x240;
	IGF_1.MCR26.R = 0x240;
	IGF_1.MCR27.R = 0x240;
	IGF_1.MCR28.R = 0x240;
	IGF_1.MCR29.R = 0x240;
	IGF_1.MCR30.R = 0x240;
	IGF_1.MCR31.R = 0x240;

	return 0;
}
