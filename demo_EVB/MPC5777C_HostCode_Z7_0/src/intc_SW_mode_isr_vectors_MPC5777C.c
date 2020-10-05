/*****************************************************************************/
/* FILE NAME: intc_SW_mode_isr_vectors_MPC5777C.c COPYRIGHT(c) Freescale 2015*/
/*                                                      All Rights Reserved  */
/* DESCRIPTION: MPC5777C ISR vectors for INTC in software vector mode        */
/*              Based on MPC5777C ref manual rev 4 Table 4-4.                */
/* USAGE:  For desired vector #, replace "dummy" with ISR name and declare   */
/*         your isr name extern like the example below:                      */
/*                       extern void MyPeripheralISR(void);                  */
/*                                                                           */
/*****************************************************************************/	
/* REV      AUTHOR        DATE        DESCRIPTION OF CHANGE                  */
/* ---   -----------    ----------    ---------------------                  */
/* 1.0	  S Mihalik     03 Aug 2015   Initial version                        */
/*****************************************************************************/
#include "typedefs.h"
/*========================================================================*/
/*		PROTOTYPES					                                 	  */
/*========================================================================*/
void dummy 						  (void);

/*========================================================================*/
/*	GLOBAL VARIABLES						                              */
/*========================================================================*/

const uint32_t __attribute__ ((section (".intc_vector_table"))) IntcIsrVectorTable[] = {

(uint32_t) &dummy, /* Vector #   0 INTC_SSCIR0[CLR0] Software INTC software settable Clear flag 0 */
(uint32_t) &dummy, /* Vector #   1 INTC_SSCIR1[CLR1] Software INTC software settable Clear flag 1 */
(uint32_t) &dummy, /* Vector #   2 INTC_SSCIR2[CLR2] Software INTC software settable Clear flag 2 */
(uint32_t) &dummy, /* Vector #   3 INTC_SSCIR3[CLR3] Software INTC software settable Clear flag 3 */
(uint32_t) &dummy, /* Vector #   4 INTC_SSCIR4[CLR4] Software INTC software settable Clear flag 4 */
(uint32_t) &dummy, /* Vector #   5 INTC_SSCIR5[CLR5] Software INTC software settable Clear flag 5 */
(uint32_t) &dummy, /* Vector #   6 INTC_SSCIR6[CLR6] Software INTC software settable Clear flag 6 */
(uint32_t) &dummy, /* Vector #   7 INTC_SSCIR7[CLR7] Software INTC software settable Clear flag 7 */
(uint32_t) &dummy, /* Vector #   8 SWTA_IR[TIF] Watchdog A Software Watchdog A Interrupt flag */
(uint32_t) &dummy, /* Vector #   9 FCCU_IRQ_STAT[ALRM_STAT] | FCCU_IRQ_STAT[CFG_TO_STAT] FCCU FCCU ALARM state entry | FCCU CONFIG state watchdog timeout */
(uint32_t) &dummy, /* Vector #  10 EDMA_ERL[ERR31:ERR0] eDMA_A eDMA channel Error flags 0-31 */
(uint32_t) &dummy, /* Vector #  11 EDMA_IRQRL[INT00] eDMA_A eDMA channel Interrupt 0 */
(uint32_t) &dummy, /* Vector #  12 EDMA_IRQRL[INT01] eDMA_A eDMA channel Interrupt 1 */
(uint32_t) &dummy, /* Vector #  13 EDMA_IRQRL[INT02] eDMA_A eDMA channel Interrupt 2 */
(uint32_t) &dummy, /* Vector #  14 EDMA_IRQRL[INT03] eDMA_A eDMA channel Interrupt 3 */
(uint32_t) &dummy, /* Vector #  15 EDMA_IRQRL[INT04] eDMA_A eDMA channel Interrupt 4 */
(uint32_t) &dummy, /* Vector #  16 EDMA_IRQRL[INT05] eDMA_A eDMA channel Interrupt 5 */
(uint32_t) &dummy, /* Vector #  17 EDMA_IRQRL[INT06] eDMA_A eDMA channel Interrupt 6 */
(uint32_t) &dummy, /* Vector #  18 EDMA_IRQRL[INT07] eDMA_A eDMA channel Interrupt 7 */
(uint32_t) &dummy, /* Vector #  19 EDMA_IRQRL[INT08] eDMA_A eDMA channel Interrupt 8 */
(uint32_t) &dummy, /* Vector #  20 EDMA_IRQRL[INT09] eDMA_A eDMA channel Interrupt 9 */
(uint32_t) &dummy, /* Vector #  21 EDMA_IRQRL[INT10] eDMA_A eDMA channel Interrupt 10 */
(uint32_t) &dummy, /* Vector #  22 EDMA_IRQRL[INT11] eDMA_A eDMA channel Interrupt 11 */
(uint32_t) &dummy, /* Vector #  23 EDMA_IRQRL[INT12] eDMA_A eDMA channel Interrupt 12 */
(uint32_t) &dummy, /* Vector #  24 EDMA_IRQRL[INT13] eDMA_A eDMA channel Interrupt 13 */
(uint32_t) &dummy, /* Vector #  25 EDMA_IRQRL[INT14] eDMA_A eDMA channel Interrupt 14 */
(uint32_t) &dummy, /* Vector #  26 EDMA_IRQRL[INT15] eDMA_A eDMA channel Interrupt 15 */
(uint32_t) &dummy, /* Vector #  27 EDMA_IRQRL[INT16] eDMA_A eDMA channel Interrupt 16 */
(uint32_t) &dummy, /* Vector #  28 EDMA_IRQRL[INT17] eDMA_A eDMA channel Interrupt 17 */
(uint32_t) &dummy, /* Vector #  29 EDMA_IRQRL[INT18] eDMA_A eDMA channel Interrupt 18 */
(uint32_t) &dummy, /* Vector #  30 EDMA_IRQRL[INT19] eDMA_A eDMA channel Interrupt 19 */
(uint32_t) &dummy, /* Vector #  31 EDMA_IRQRL[INT20] eDMA_A eDMA channel Interrupt 20 */
(uint32_t) &dummy, /* Vector #  32 EDMA_IRQRL[INT21] eDMA_A eDMA channel Interrupt 21 */
(uint32_t) &dummy, /* Vector #  33 EDMA_IRQRL[INT22] eDMA_A eDMA channel Interrupt 22 */
(uint32_t) &dummy, /* Vector #  34 EDMA_IRQRL[INT23] eDMA_A eDMA channel Interrupt 23 */
(uint32_t) &dummy, /* Vector #  35 EDMA_IRQRL[INT24] eDMA_A eDMA channel Interrupt 24 */
(uint32_t) &dummy, /* Vector #  36 EDMA_IRQRL[INT25] eDMA_A eDMA channel Interrupt 25 */
(uint32_t) &dummy, /* Vector #  37 EDMA_IRQRL[INT26] eDMA_A eDMA channel Interrupt 26 */
(uint32_t) &dummy, /* Vector #  38 EDMA_IRQRL[INT27] eDMA_A eDMA channel Interrupt 27 */
(uint32_t) &dummy, /* Vector #  39 EDMA_IRQRL[INT28] eDMA_A eDMA channel Interrupt 28 */
(uint32_t) &dummy, /* Vector #  40 EDMA_IRQRL[INT29] eDMA_A eDMA channel Interrupt 29 */
(uint32_t) &dummy, /* Vector #  41 EDMA_IRQRL[INT30] eDMA_A eDMA channel Interrupt 30 */
(uint32_t) &dummy, /* Vector #  42 EDMA_IRQRL[INT31] eDMA_A eDMA channel Interrupt 31 */
(uint32_t) &dummy, /* Vector #  43 SIU_PCSIFR[PCSI] PCS Progressive Clock Switch Interrupt  */
(uint32_t) &dummy, /* Vector #  44 PLL0_SR[LOLF] | PLL1_SR[LOLF] PLLDIG PLL Loss of Lock Flags */
(uint32_t) &dummy, /* Vector #  45 SIU_OSR[OVF15:OVF0] SIU SIU combined overrun interrupt requests of the external interrupt Overrun Flags */
(uint32_t) &dummy, /* Vector #  46 SIU_EIISR[EIF0] SIU SIU External Interrupt Flag 0 */
(uint32_t) &dummy, /* Vector #  47 SIU_EIISR[EIF1] SIU SIU External Interrupt Flag 1 */
(uint32_t) &dummy, /* Vector #  48 SIU_EIISR[EIF2] SIU SIU External Interrupt Flag 2 */
(uint32_t) &dummy, /* Vector #  49 SIU_EIISR[EIF3] SIU SIU External Interrupt Flag 3 */
(uint32_t) &dummy, /* Vector #  50 SIU_EIISR[EIF15:EIF4] SIU SIU External Interrupt Flags 15-4 */
(uint32_t) &dummy, /* Vector #  51 eMIOS_0_GFLAG[F0] eMIOS_0 eMIOS_0 channel 0 Flag */
(uint32_t) &dummy, /* Vector #  52 eMIOS_0_GFLAG[F1] eMIOS_0 eMIOS_0 channel 1 Flag */
(uint32_t) &dummy, /* Vector #  53 eMIOS_0_GFLAG[F2] eMIOS_0 eMIOS_0 channel 2 Flag */
(uint32_t) &dummy, /* Vector #  54 eMIOS_0_GFLAG[F3] eMIOS_0 eMIOS_0 channel 3 Flag */
(uint32_t) &dummy, /* Vector #  55 eMIOS_0_GFLAG[F4] eMIOS_0 eMIOS_0 channel 4 Flag */
(uint32_t) &dummy, /* Vector #  56 eMIOS_0_GFLAG[F5] eMIOS_0 eMIOS_0 channel 5 Flag */
(uint32_t) &dummy, /* Vector #  57 eMIOS_0_GFLAG[F6] eMIOS_0 eMIOS_0 channel 6 Flag */
(uint32_t) &dummy, /* Vector #  58 eMIOS_0_GFLAG[F7] eMIOS_0 eMIOS_0 channel 7 Flag */
(uint32_t) &dummy, /* Vector #  59 eMIOS_1_GFLAG[F0] eMIOS_1 eMIOS_1 channel 0 Flag */
(uint32_t) &dummy, /* Vector #  60 eMIOS_1_GFLAG[F1] eMIOS_1 eMIOS_1 channel 1 Flag */
(uint32_t) &dummy, /* Vector #  61 eMIOS_1_GFLAG[F2] eMIOS_1 eMIOS_1 channel 2 Flag */
(uint32_t) &dummy, /* Vector #  62 eMIOS_1_GFLAG[F3] eMIOS_1 eMIOS_1 channel 3 Flag */
(uint32_t) &dummy, /* Vector #  63 eMIOS_1_GFLAG[F4] eMIOS_1 eMIOS_1 channel 4 Flag */
(uint32_t) &dummy, /* Vector #  64 eMIOS_1_GFLAG[F5] eMIOS_1 eMIOS_1 channel 5 Flag */
(uint32_t) &dummy, /* Vector #  65 eMIOS_1_GFLAG[F6] eMIOS_1 eMIOS_1 channel 6 Flag */
(uint32_t) &dummy, /* Vector #  66 eMIOS_1_GFLAG[F7] eMIOS_1 eMIOS_1 channel 7 Flag */
(uint32_t) &dummy, /* Vector #  67 ETPU_SCR_MCR[SDMERR,SSAE RR,SCMERR,WDTO1/2,MGE1/2,IL F1/2,LTO1/2,SCMMISF] and ETPU_MESR_MESR[DCERR,CCE RR] eTPU_A/B eTPU Engine A and B Global Exception */
(uint32_t) &dummy, /* Vector #  68 ETPU_CISR_A[CIS0] eTPU_A eTPU Engine A Channel 0 Interrupt Status */
(uint32_t) &dummy, /* Vector #  69 ETPU_CISR_A[CIS1] eTPU_A eTPU Engine A Channel 1 Interrupt Status */
(uint32_t) &dummy, /* Vector #  70 ETPU_CISR_A[CIS2] eTPU_A eTPU Engine A Channel 2 Interrupt Status */
(uint32_t) &dummy, /* Vector #  71 ETPU_CISR_A[CIS3] eTPU_A eTPU Engine A Channel 3 Interrupt Status */
(uint32_t) &dummy, /* Vector #  72 ETPU_CISR_A[CIS4] eTPU_A eTPU Engine A Channel 4 Interrupt Status */
(uint32_t) &dummy, /* Vector #  73 ETPU_CISR_A[CIS5] eTPU_A eTPU Engine A Channel 5 Interrupt Status */
(uint32_t) &dummy, /* Vector #  74 ETPU_CISR_A[CIS6] eTPU_A eTPU Engine A Channel 6 Interrupt Status */
(uint32_t) &dummy, /* Vector #  75 ETPU_CISR_A[CIS7] eTPU_A eTPU Engine A Channel 7 Interrupt Status */
(uint32_t) &dummy, /* Vector #  76 ETPU_CISR_A[CIS8] eTPU_A eTPU Engine A Channel 8 Interrupt Status */
(uint32_t) &dummy, /* Vector #  77 ETPU_CISR_A[CIS9] eTPU_A eTPU Engine A Channel 9 Interrupt Status */
(uint32_t) &dummy, /* Vector #  78 ETPU_CISR_A[CIS10] eTPU_A eTPU Engine A Channel 10 Interrupt Status */
(uint32_t) &dummy, /* Vector #  79 ETPU_CISR_A[CIS11] eTPU_A eTPU Engine A Channel 11 Interrupt Status */
(uint32_t) &dummy, /* Vector #  80 ETPU_CISR_A[CIS12] eTPU_A eTPU Engine A Channel 12 Interrupt Status */
(uint32_t) &dummy, /* Vector #  81 ETPU_CISR_A[CIS13] eTPU_A eTPU Engine A Channel 13 Interrupt Status */
(uint32_t) &dummy, /* Vector #  82 ETPU_CISR_A[CIS14] eTPU_A eTPU Engine A Channel 14 Interrupt Status */
(uint32_t) &dummy, /* Vector #  83 ETPU_CISR_A[CIS15] eTPU_A eTPU Engine A Channel 15 Interrupt Status */
(uint32_t) &dummy, /* Vector #  84 ETPU_CISR_A[CIS16] eTPU_A eTPU Engine A Channel 16 Interrupt Status */
(uint32_t) &dummy, /* Vector #  85 ETPU_CISR_A[CIS17] eTPU_A eTPU Engine A Channel 17 Interrupt Status */
(uint32_t) &dummy, /* Vector #  86 ETPU_CISR_A[CIS18] eTPU_A eTPU Engine A Channel 18 Interrupt Status */
(uint32_t) &dummy, /* Vector #  87 ETPU_CISR_A[CIS19] eTPU_A eTPU Engine A Channel 19 Interrupt Status */
(uint32_t) &dummy, /* Vector #  88 ETPU_CISR_A[CIS20] eTPU_A eTPU Engine A Channel 20 Interrupt Status */
(uint32_t) &dummy, /* Vector #  89 ETPU_CISR_A[CIS21] eTPU_A eTPU Engine A Channel 21 Interrupt Status */
(uint32_t) &dummy, /* Vector #  90 ETPU_CISR_A[CIS22] eTPU_A eTPU Engine A Channel 22 Interrupt Status */
(uint32_t) &dummy, /* Vector #  91 ETPU_CISR_A[CIS23] eTPU_A eTPU Engine A Channel 23 Interrupt Status */
(uint32_t) &dummy, /* Vector #  92 ETPU_CISR_A[CIS24] eTPU_A eTPU Engine A Channel 24 Interrupt Status */
(uint32_t) &dummy, /* Vector #  93 ETPU_CISR_A[CIS25] eTPU_A eTPU Engine A Channel 25 Interrupt Status */
(uint32_t) &dummy, /* Vector #  94 ETPU_CISR_A[CIS26] eTPU_A eTPU Engine A Channel 26 Interrupt Status */
(uint32_t) &dummy, /* Vector #  95 ETPU_CISR_A[CIS27] eTPU_A eTPU Engine A Channel 27 Interrupt Status */
(uint32_t) &dummy, /* Vector #  96 ETPU_CISR_A[CIS28] eTPU_A eTPU Engine A Channel 28 Interrupt Status */
(uint32_t) &dummy, /* Vector #  97 ETPU_CISR_A[CIS29] eTPU_A eTPU Engine A Channel 29 Interrupt Status */
(uint32_t) &dummy, /* Vector #  98 ETPU_CISR_A[CIS30] eTPU_A eTPU Engine A Channel 30 Interrupt Status */
(uint32_t) &dummy, /* Vector #  99 ETPU_CISR_A[CIS31] eTPU_A eTPU Engine A Channel 31 Interrupt Status */

(uint32_t) &dummy, /* Vector # 100 EQADCA_FISRx[TORF] EQADCA_FISRx[RFOF] EQADCA_FISRx[CFUF] eQADC_A eQADC combined overrun interrupt requests from all of the FIFOs: Trigger Overrun, Receive FIFO Overflow, and command FIFO Underflow */
(uint32_t) &dummy, /* Vector # 101 EQADCA_FISR0[NCF] eQADC_A eQADC command FIFO 0 Non-Coherency Flag */
(uint32_t) &dummy, /* Vector # 102 EQADCA_FISR0[PF] eQADC_A eQADC command FIFO 0 Pause Flag */
(uint32_t) &dummy, /* Vector # 103 EQADCA_FISR0[EOQF] eQADC_A eQADC command FIFO 0 command queue End of Queue Flag */
(uint32_t) &dummy, /* Vector # 104 EQADCA_FISR0[CFFF] eQADC_A eQADC Command FIFO 0 Fill Flag */
(uint32_t) &dummy, /* Vector # 105 EQADCA_FISR0[RFDF] eQADC_A eQADC Receive FIFO 0 Drain Flag */
(uint32_t) &dummy, /* Vector # 106 EQADCA_FISR1[NCF] eQADC_A eQADC command FIFO 1 Non-Coherency Flag */
(uint32_t) &dummy, /* Vector # 107 EQADCA_FISR1[PF] eQADC_A eQADC command FIFO 1 Pause Flag */
(uint32_t) &dummy, /* Vector # 108 EQADCA_FISR1[EOQF] eQADC_A eQADC command FIFO 1 command queue End of Queue Flag */
(uint32_t) &dummy, /* Vector # 109 EQADCA_FISR1[CFFF] eQADC_A eQADC Command FIFO 1 Fill Flag */
(uint32_t) &dummy, /* Vector # 110 EQADCA_FISR1[RFDF] eQADC_A eQADC Receive FIFO 1 Drain Flag */
(uint32_t) &dummy, /* Vector # 111 EQADCA_FISR2[NCF] eQADC_A eQADC command FIFO 2 Non-Coherency Flag */
(uint32_t) &dummy, /* Vector # 112 EQADCA_FISR2[PF] eQADC_A eQADC command FIFO 2 Pause Flag */
(uint32_t) &dummy, /* Vector # 113 EQADCA_FISR2[EOQF] eQADC_A eQADC command FIFO 2 command queue End of Queue Flag */
(uint32_t) &dummy, /* Vector # 114 EQADCA_FISR2[CFFF] eQADC_A eQADC Command FIFO 2 Fill Flag */
(uint32_t) &dummy, /* Vector # 115 EQADCA_FISR2[RFDF] eQADC_A eQADC Receive FIFO 2 Drain Flag */
(uint32_t) &dummy, /* Vector # 116 EQADCA_FISR3[NCF] eQADC_A eQADC command FIFO 3 Non-Coherency Flag */
(uint32_t) &dummy, /* Vector # 117 EQADCA_FISR3[PF] eQADC_A eQADC command FIFO 3 Pause Flag */
(uint32_t) &dummy, /* Vector # 118 EQADCA_FISR3[EOQF] eQADC_A eQADC command FIFO 3 command queue End of Queue Flag */
(uint32_t) &dummy, /* Vector # 119 EQADCA_FISR3[CFFF] eQADC_A eQADC Command FIFO 3 Fill Flag */
(uint32_t) &dummy, /* Vector # 120 EQADCA_FISR3[RFDF] eQADC_A eQADC Receive FIFO 3 Drain Flag */
(uint32_t) &dummy, /* Vector # 121 EQADCA_FISR4[NCF] eQADC_A eQADC command FIFO 4 Non-Coherency Flag */
(uint32_t) &dummy, /* Vector # 122 EQADCA_FISR4[PF] eQADC_A eQADC command FIFO 4 Pause Flag */
(uint32_t) &dummy, /* Vector # 123 EQADCA_FISR4[EOQF] eQADC_A eQADC command FIFO 4 command queue End of Queue Flag */
(uint32_t) &dummy, /* Vector # 124 EQADCA_FISR4[CFFF] eQADC_A eQADC Command FIFO 4 Fill Flag */
(uint32_t) &dummy, /* Vector # 125 EQADCA_FISR4[RFDF] eQADC_A eQADC Receive FIFO 4 Drain Flag */
(uint32_t) &dummy, /* Vector # 126 EQADCA_FISR5[NCF] eQADC_A eQADC command FIFO 5 Non-Coherency Flag */
(uint32_t) &dummy, /* Vector # 127 EQADCA_FISR5[PF] eQADC_A eQADC command FIFO 5 Pause Flag */
(uint32_t) &dummy, /* Vector # 128 EQADCA_FISR5[EOQF] eQADC_A eQADC command FIFO 5 command queue End of Queue Flag */
(uint32_t) &dummy, /* Vector # 129 EQADCA_FISR5[CFFF] eQADC_A eQADC Command FIFO 5 Fill Flag */
(uint32_t) &dummy, /* Vector # 130 EQADCA_FISR5[RFDF] eQADC_A eQADC Receive FIFO 5 Drain Flag */
(uint32_t) &dummy, /* Vector # 131 DSPIB_SR[TFUF] DSPIB_SR[RFOF] DSPIB_SR[SPEF] DSPIB_SR[DPEF] DSPI_B DSPI_B combined overrun and parity error interrupt requests: Transmit FIFO Underflow/Receive FIFO Overflow SPI Parity Error/DSI Parity Error */
(uint32_t) &dummy, /* Vector # 132 DSPIB_SR[EOQF] DSPI_B DSPI_B transmit FIFO End of Queue Flag */
(uint32_t) &dummy, /* Vector # 133 DSPIB_SR[TFFF] DSPI_B DSPI_B Transmit FIFO Fill Flag */
(uint32_t) &dummy, /* Vector # 134 DSPIB_SR[TCF] | DSPIB_SR[DDIF] DSPI_B DSPI_B Transfer Complete/DSI Data Match Flag */
(uint32_t) &dummy, /* Vector # 135 DSPIB_SR[RFDF] DSPI_B DSPI_B Receive FIFO Drain Flag */
(uint32_t) &dummy, /* Vector # 136 DSPIC_SR[TFUF] DSPIC_SR[RFOF] DSPIC_SR[SPEF] DSPIC_SR[DPEF] DSPI_C DSPI_C combined overrun and parity error interrupt requests: Transmit FIFO Underflow/Receive FIFO Overflow SPI Parity Error/DSI Parity Error */
(uint32_t) &dummy, /* Vector # 137 DSPIC_SR[EOQF] DSPI_C DSPI_C transmit FIFO End of Queue Flag */
(uint32_t) &dummy, /* Vector # 138 DSPIC_SR[TFFF] DSPI_C DSPI_C Transmit FIFO Fill Flag */
(uint32_t) &dummy, /* Vector # 139 DSPIC_SR[TCF] | DSPIC_SR[DDIF] DSPI_C DSPI_C Transfer Complete/DSI Data Match Flag */
(uint32_t) &dummy, /* Vector # 140 DSPIC_SR[RFDF] DSPI_C DSPI_C Receive FIFO Drain Flag */
(uint32_t) &dummy, /* Vector # 141 DSPID_SR[TFUF] DSPID_SR[RFOF] DSPID_SR[SPEF] DSPID_SR[DPEF] DSPI_D DSPI_D combined overrun and parity error interrupt requests: Transmit FIFO Underflow/Receive FIFO Overflow SPI Parity Error/DSI Parity Error */
(uint32_t) &dummy, /* Vector # 142 DSPID_SR[EOQF] DSPI_D DSPI_D transmit FIFO End of Queue Flag */
(uint32_t) &dummy, /* Vector # 143 DSPID_SR[TFFF] DSPI_D DSPI_D Transmit FIFO Fill Flag */
(uint32_t) &dummy, /* Vector # 144 DSPID_SR[TCF] | DSPID_SR[DDIF] DSPI_D DSPI_D Transfer Complete/DSI Data Match Flag */
(uint32_t) &dummy, /* Vector # 145 DSPID_SR[RFDF] DSPI_D DSPI_D Receive FIFO Drain Flag */
(uint32_t) &dummy, /* Vector # 146 ESCIA_SR[TDRE] ESCIA_SR[TC] ESCIA_SR[RDRF] ESCIA_SR[IDLE] ESCIA_SR[OR] ESCIA_SR[NF] ESCIA_SR[FE] ESCIA_SR[PF] ESCIA_SR[BERR] ESCIA_SR[RXRDY] ESCIA_SR[TXRDY] ESCIA_SR[LWAKE] ESCIA_SR[STO] ESCIA_SR[PBERR] ESCIA_SR[CERR] ESCIA_SR[CKERR] ESCIA_SR[FRC] ESCIA_SR[OVFL] eSCI_A Combined Interrupt Requests of ESCI Module A: Transmit Data Register Empty, Transmit Complete, Receive Data Register Full, Idle line, Overrun, Noise Flag, Framing Error Flag, and Parity Error Flag interrupt requests, SCI Status Register 2 Bit Error interrupt request, LIN Status Register 1 Receive Data Ready, Transmit Data Ready, Received LIN Wakeup Signal, Slave TimeOut, Physical Bus Error, CRC Error, Checksum Error, Frame Complete interrupts requests, and LIN Status Register 2 Receive Register Overflow */
(uint32_t) &dummy, /* Vector # 147 Master0 Snoop ipi_int PCU PCU_IR0[OIF] | PCU_IR0[EIF] */
(uint32_t) &dummy, /* Vector # 148 Master1 Snoop ipi_int PCU PCU_IR1[OIF] | PCU_IR1[EIF] */
(uint32_t) &dummy, /* Vector # 149 ESCIB_SR[TDRE] ESCIB_SR[TC] ESCIB_SR[RDRF] ESCIB_SR[IDLE] ESCIB_SR[OR] ESCIB_SR[NF] ESCIB_SR[FE] ESCIB_SR[PF] ESCIB_SR[BERR] ESCIB_SR[RXRDY] ESCIB_SR[TXRDY] ESCIB_SR[LWAKE] ESCIB_SR[STO] ESCIB_SR[PBERR] ESCIB_SR[CERR] ESCIB_SR[CKERR] ESCIB_SR[FRC] ESCIB_SR[OVFL] eSCI_B Combined Interrupt Requests of ESCI Module B: Transmit Data Register Empty, Transmit Complete, Receive Data Register Full, Idle line, Overrun, Noise Flag, Framing Error Flag, and Parity Error Flag interrupt requests, SCI Status Register 2 Bit Error interrupt request, LIN Status Register 1 Receive Data Ready, Transmit Data Ready, Received LIN Wakeup Signal, Slave TimeOut, Physical Bus Error, CRC Error, Checksum Error, Frame Complete interrupts requests, and LIN Status Register 2 Receive Register Overflow */
(uint32_t) &dummy, /* Vector # 150 PSI5_0_CH_0_DSR[IS_DMA_TF_P M_DS] | [IS_DMA_TF_SF] | [IS_DMA_PM_DS_FIF O_FULL] | [IS_DMA_SFUF] | [IS_DMA_PM_DS_UF] | NDSR[NDS31:0] | OWSR[NDS31:0] | EISR[NDS31:0] PSI5_0 PSI5_0 DMA Status, New data, OverWrite, Error interrupts */
(uint32_t) &dummy, /* Vector # 151 PSI5_1_CH_0_DSR[IS_DMA_TF_P M_DS] | [IS_DMA_TF_SF] |[IS_DMA_PM_DS_FIF O_FULL] | [IS_DMA_SFUF] | [IS_DMA_PM_DS_UF] | NDSR[NDS31:0] | OWSR[NDS31:0] | EISR[NDS31:0] PSI5_1 PSI5_1 DMA Status, New data, OverWrite, Error interrupts */
(uint32_t) &dummy, /* Vector # 152 CANA_ESR1[BOFF_INT] | [TWRNINT] | [RWRNINT] FlexCAN_A FlexCAN_A Bus Off, Transmit Warning, Receive Warning */
(uint32_t) &dummy, /* Vector # 153 CANA_ESR1[ERR_INT] | CANA_ERRSR[ECC_CE_INT] | CANA_ERRSR[ECC_HANCE_INT] | CANA_ERRSR[ECC_FANCE_INT] FlexCAN_A FlexCAN_A Error, FlexCAN_A ECC Correctable Error, FlexCAN_A ECC Host Access Non-Correctable Error, FlexCAN_A ECC CAN Access Non-Correctable Error */
(uint32_t) &dummy, /* Vector # 154 Reserved FlexCAN_A Reserved */
(uint32_t) &dummy, /* Vector # 155 CANA_IFRL[BUF0] FlexCAN_A FlexCAN_A Buffer 0 Interrupt */
(uint32_t) &dummy, /* Vector # 156 CANA_IFRL[BUF1] FlexCAN_A FlexCAN_A Buffer 1 Interrupt */
(uint32_t) &dummy, /* Vector # 157 CANA_IFRL[BUF2] FlexCAN_A FlexCAN_A Buffer 2 Interrupt */
(uint32_t) &dummy, /* Vector # 158 CANA_IFRL[BUF3] FlexCAN_A FlexCAN_A Buffer 3 Interrupt */
(uint32_t) &dummy, /* Vector # 159 CANA_IFRL[BUF4] FlexCAN_A FlexCAN_A Buffer 4 Interrupt */
(uint32_t) &dummy, /* Vector # 160 CANA_IFRL[BUF5] FlexCAN_A FlexCAN_A Buffer 5 Interrupt */
(uint32_t) &dummy, /* Vector # 161 CANA_IFRL[BUF6] FlexCAN_A FlexCAN_A Buffer 6 Interrupt */
(uint32_t) &dummy, /* Vector # 162 CANA_IFRL[BUF7] FlexCAN_A FlexCAN_A Buffer 7 Interrupt */
(uint32_t) &dummy, /* Vector # 163 CANA_IFRL[BUF8] FlexCAN_A FlexCAN_A Buffer 8 Interrupt */
(uint32_t) &dummy, /* Vector # 164 CANA_IFRL[BUF9] FlexCAN_A FlexCAN_A Buffer 9 Interrupt */
(uint32_t) &dummy, /* Vector # 165 CANA_IFRL[BUF10] FlexCAN_A FlexCAN_A Buffer 10 Interrupt */
(uint32_t) &dummy, /* Vector # 166 CANA_IFRL[BUF11] FlexCAN_A FlexCAN_A Buffer 11 Interrupt */
(uint32_t) &dummy, /* Vector # 167 CANA_IFRL[BUF12] FlexCAN_A FlexCAN_A Buffer 12 Interrupt */
(uint32_t) &dummy, /* Vector # 168 CANA_IFRL[BUF13] FlexCAN_A FlexCAN_A Buffer 13 Interrupt */
(uint32_t) &dummy, /* Vector # 169 CANA_IFRL[BUF14] FlexCAN_A FlexCAN_A Buffer 14 Interrupt */
(uint32_t) &dummy, /* Vector # 170 CANA_IFRL[BUF15] FlexCAN_A FlexCAN_A Buffer 15 Interrupt */
(uint32_t) &dummy, /* Vector # 171 CANA_IFRL[BUF31:BUF16] FlexCAN_A FlexCAN_A Buffers 31-16 Interrupts */
(uint32_t) &dummy, /* Vector # 172 CANA_IFRH[BUF63:BUF32] FlexCAN_A FlexCAN_A Buffers 63-32 Interrupts */
(uint32_t) &dummy, /* Vector # 173 CANC_ESR1[BOFF_INT] | [TWRNINT] | [RWRNINT] FlexCAN_C FlexCAN_C Bus Off, Transmit Warning, Receive Warning */
(uint32_t) &dummy, /* Vector # 174 CANC_ESR1[ERR_INT] | CANC_ERRSR[ECC_CE_INT] | CANC_ERRSR[ECC_HANCE_INT] | CANC_ERRSR[ECC_FANCE_INT] FlexCAN_C FlexCAN_C Error, FlexCAN_C ECC Correctable Error, FlexCAN_C ECC Host Access Non-Correctable Error, FlexCAN_C ECC CAN Access Non-Correctable Error */
(uint32_t) &dummy, /* Vector # 175 Reserved FlexCAN_C Reserved */
(uint32_t) &dummy, /* Vector # 176 CANC_IFRL[BUF0] FlexCAN_C FlexCAN_C Buffer 0 Interrupt */
(uint32_t) &dummy, /* Vector # 177 CANC_IFRL[BUF1] FlexCAN_C FlexCAN_C Buffer 1 Interrupt */
(uint32_t) &dummy, /* Vector # 178 CANC_IFRL[BUF2] FlexCAN_C FlexCAN_C Buffer 2 Interrupt */
(uint32_t) &dummy, /* Vector # 179 CANC_IFRL[BUF3] FlexCAN_C FlexCAN_C Buffer 3 Interrupt */
(uint32_t) &dummy, /* Vector # 180 CANC_IFRL[BUF4] FlexCAN_C FlexCAN_C Buffer 4 Interrupt */
(uint32_t) &dummy, /* Vector # 181 CANC_IFRL[BUF5] FlexCAN_C FlexCAN_C Buffer 5 Interrupt */
(uint32_t) &dummy, /* Vector # 182 CANC_IFRL[BUF6] FlexCAN_C FlexCAN_C Buffer 6 Interrupt */
(uint32_t) &dummy, /* Vector # 183 CANC_IFRL[BUF7] FlexCAN_C FlexCAN_C Buffer 7 Interrupt */
(uint32_t) &dummy, /* Vector # 184 CANC_IFRL[BUF8] FlexCAN_C FlexCAN_C Buffer 8 Interrupt */
(uint32_t) &dummy, /* Vector # 185 CANC_IFRL[BUF9] FlexCAN_C FlexCAN_C Buffer 9 Interrupt */
(uint32_t) &dummy, /* Vector # 186 CANC_IFRL[BUF10] FlexCAN_C FlexCAN_C Buffer 10 Interrupt */
(uint32_t) &dummy, /* Vector # 187 CANC_IFRL[BUF11] FlexCAN_C FlexCAN_C Buffer 11 Interrupt */
(uint32_t) &dummy, /* Vector # 188 CANC_IFRL[BUF12] FlexCAN_C FlexCAN_C Buffer 12 Interrupt */
(uint32_t) &dummy, /* Vector # 189 CANC_IFRL[BUF13] FlexCAN_C FlexCAN_C Buffer 13 Interrupt */
(uint32_t) &dummy, /* Vector # 190 CANC_IFRL[BUF14] FlexCAN_C FlexCAN_C Buffer 14 Interrupt */
(uint32_t) &dummy, /* Vector # 191 CANC_IFRL[BUF15] FlexCAN_C FlexCAN_C Buffer 15 Interrupt */
(uint32_t) &dummy, /* Vector # 192 CANC_IFRL[BUF31:BUF16] FlexCAN_C FlexCAN_C Buffers 31-16 Interrupts */
(uint32_t) &dummy, /* Vector # 193 CANC_IFRH[BUF63:BUF32] FlexCAN_C FlexCAN_C Buffers 63-32 Interrupts */
(uint32_t) &dummy, /* Vector # 194 EIR[TXF] FEC FEC Transmit Frame flag */
(uint32_t) &dummy, /* Vector # 195 EIR[RXF] FEC FEC Receive Frame flag */
(uint32_t) &dummy, /* Vector # 196 EIR[HBERR] | EIR[BABR] | EIR[BABT] | EIR[GRA] | EIR[TXB] | EIR[RXB] | EIR[MII] | EIR[EBERR] | EIR[LC] | EIR[RL] | EIR[UN] FEC Combined Interrupt Requests of the FEC Ethernet Interrupt Event Register: Heartbeat Error, Babbling Receive Error, Babbling Transmit Error, Graceful Stop Complete, Transmit Buffer, Receive Buffer, Media Independent Interface, Ethernet Bus Error, Late Collision, Collision Retry Limit, and Transmit FIFO Underrun */
(uint32_t) &dummy, /* Vector # 197 DECFILTER_MSR_A[IDF] DEC_A Decimation A Input (Fill) */
(uint32_t) &dummy, /* Vector # 198 DECFILTER_MSR_A[ODF||SDF] DEC_A Decimation A Output/Integ (Drain/Integ) */
(uint32_t) &dummy, /* Vector # 199 DECFILTER A ERRORS DEC_A Decimation A Error */

(uint32_t) &dummy, /* Vector # 200 STM_CIR0[CIF] STM System Timer Module Interrupt 0 */
(uint32_t) &dummy, /* Vector # 201 STM_CIR1[CIF], STM_CIR2[CIF], STM_CIR3[CIF] STM System Timer Module Interrupts 1, 2, 3 */
(uint32_t) &dummy, /* Vector # 202 eMIOS_0_GFLAG[F16] eMIOS_0 eMIOS_0 channel 16 Flag */
(uint32_t) &dummy, /* Vector # 203 eMIOS_0_GFLAG[F17] eMIOS_0 eMIOS_0 channel 17 Flag */
(uint32_t) &dummy, /* Vector # 204 eMIOS_0_GFLAG[F18] eMIOS_0 eMIOS_0 channel 18 Flag */
(uint32_t) &dummy, /* Vector # 205 eMIOS_0_GFLAG[F19] eMIOS_0 eMIOS_0 channel 19 Flag */
(uint32_t) &dummy, /* Vector # 206 eMIOS_0_GFLAG[F20] eMIOS_0 eMIOS_0 channel 20 Flag */
(uint32_t) &dummy, /* Vector # 207 eMIOS_0_GFLAG[F21] eMIOS_0 eMIOS_0 channel 21 Flag */
(uint32_t) &dummy, /* Vector # 208 eMIOS_0_GFLAG[F22] eMIOS_0 eMIOS_0 channel 22 Flag */
(uint32_t) &dummy, /* Vector # 209 eMIOS_0_GFLAG[F23] eMIOS_0 eMIOS_0 channel 23 Flag */
(uint32_t) &dummy, /* Vector # 210 EDMAA_ERRH[ERR63:ERR32] eDMA_A eDMA channel Error flags 32-63 */
(uint32_t) &dummy, /* Vector # 211 EDMAA_IRQRH[INT32] eDMA_A eDMA channel Interrupt 32 */
(uint32_t) &dummy, /* Vector # 212 EDMAA_IRQRH[INT33] eDMA_A eDMA channel Interrupt 33 */
(uint32_t) &dummy, /* Vector # 213 EDMAA_IRQRH[INT34] eDMA_A eDMA channel Interrupt 34 */
(uint32_t) &dummy, /* Vector # 214 EDMAA_IRQRH[INT35] eDMA_A eDMA channel Interrupt 35 */
(uint32_t) &dummy, /* Vector # 215 EDMAA_IRQRH[INT36] eDMA_A eDMA channel Interrupt 36 */
(uint32_t) &dummy, /* Vector # 216 EDMAA_IRQRH[INT37] eDMA_A eDMA channel Interrupt 37 */
(uint32_t) &dummy, /* Vector # 217 EDMAA_IRQRH[INT38] eDMA_A eDMA channel Interrupt 38 */
(uint32_t) &dummy, /* Vector # 218 EDMAA_IRQRH[INT39] eDMA_A eDMA channel Interrupt 39 */
(uint32_t) &dummy, /* Vector # 219 EDMAA_IRQRH[INT40] eDMA_A eDMA channel Interrupt 40 */
(uint32_t) &dummy, /* Vector # 220 EDMAA_IRQRH[INT41] eDMA_A eDMA channel Interrupt 41 */
(uint32_t) &dummy, /* Vector # 221 EDMAA_IRQRH[INT42] eDMA_A eDMA channel Interrupt 42 */
(uint32_t) &dummy, /* Vector # 222 EDMAA_IRQRH[INT43] eDMA_A eDMA channel Interrupt 43 */
(uint32_t) &dummy, /* Vector # 223 EDMAA_IRQRH[INT44] eDMA_A eDMA channel Interrupt 44 */
(uint32_t) &dummy, /* Vector # 224 EDMAA_IRQRH[INT45] eDMA_A eDMA channel Interrupt 45 */
(uint32_t) &dummy, /* Vector # 225 EDMAA_IRQRH[INT46] eDMA_A eDMA channel Interrupt 46 */
(uint32_t) &dummy, /* Vector # 226 EDMAA_IRQRH[INT47] eDMA_A eDMA channel Interrupt 47 */
(uint32_t) &dummy, /* Vector # 227 EDMAA_IRQRH[INT48] eDMA_A eDMA channel Interrupt 48 */
(uint32_t) &dummy, /* Vector # 228 EDMAA_IRQRH[INT49] eDMA_A eDMA channel Interrupt 49 */
(uint32_t) &dummy, /* Vector # 229 EDMAA_IRQRH[INT50] eDMA_A eDMA channel Interrupt 50 */
(uint32_t) &dummy, /* Vector # 230 EDMAA_IRQRH[INT51] eDMA_A eDMA channel Interrupt 51 */
(uint32_t) &dummy, /* Vector # 231 EDMAA_IRQRH[INT52] eDMA_A eDMA channel Interrupt 52 */
(uint32_t) &dummy, /* Vector # 232 EDMAA_IRQRH[INT53] eDMA_A eDMA channel Interrupt 53 */
(uint32_t) &dummy, /* Vector # 233 EDMAA_IRQRH[INT54] eDMA_A eDMA channel Interrupt 54 */
(uint32_t) &dummy, /* Vector # 234 EDMAA_IRQRH[INT55] eDMA_A eDMA channel Interrupt 55 */
(uint32_t) &dummy, /* Vector # 235 EDMAA_IRQRH[INT56] eDMA_A eDMA channel Interrupt 56 */
(uint32_t) &dummy, /* Vector # 236 EDMAA_IRQRH[INT57] eDMA_A eDMA channel Interrupt 57 */
(uint32_t) &dummy, /* Vector # 237 EDMAA_IRQRH[INT58] eDMA_A eDMA channel Interrupt 58 */
(uint32_t) &dummy, /* Vector # 238 EDMAA_IRQRH[INT59] eDMA_A eDMA channel Interrupt 59 */
(uint32_t) &dummy, /* Vector # 239 EDMAA_IRQRH[INT60] eDMA_A eDMA channel Interrupt 60 */
(uint32_t) &dummy, /* Vector # 240 EDMAA_IRQRH[INT61] eDMA_A eDMA channel Interrupt 61 */
(uint32_t) &dummy, /* Vector # 241 EDMAA_IRQRH[INT62] eDMA_A eDMA channel Interrupt 62 */
(uint32_t) &dummy, /* Vector # 242 EDMAA_IRQRH[INT63] eDMA_A eDMA channel Interrupt 63 */
(uint32_t) &dummy, /* Vector # 243 ETPU_CISR_B[CIS0] eTPU_B eTPU Engine B Channel 0 Interrupt Status */
(uint32_t) &dummy, /* Vector # 244 ETPU_CISR_B[CIS1] eTPU_B eTPU Engine B Channel 1 Interrupt Status */
(uint32_t) &dummy, /* Vector # 245 ETPU_CISR_B[CIS2] eTPU_B eTPU Engine B Channel 2 Interrupt Status */
(uint32_t) &dummy, /* Vector # 246 ETPU_CISR_B[CIS3] eTPU_B eTPU Engine B Channel 3 Interrupt Status */
(uint32_t) &dummy, /* Vector # 247 ETPU_CISR_B[CIS4] eTPU_B eTPU Engine B Channel 4 Interrupt Status */
(uint32_t) &dummy, /* Vector # 248 ETPU_CISR_B[CIS5] eTPU_B eTPU Engine B Channel 5 Interrupt Status */
(uint32_t) &dummy, /* Vector # 249 ETPU_CISR_B[CIS6] eTPU_B eTPU Engine B Channel 6 Interrupt Status */
(uint32_t) &dummy, /* Vector # 250 ETPU_CISR_B[CIS7] eTPU_B eTPU Engine B Channel 7 Interrupt Status */
(uint32_t) &dummy, /* Vector # 251 ETPU_CISR_B[CIS8] eTPU_B eTPU Engine B Channel 8 Interrupt Status */
(uint32_t) &dummy, /* Vector # 252 ETPU_CISR_B[CIS9] eTPU_B eTPU Engine B Channel 9 Interrupt Status */
(uint32_t) &dummy, /* Vector # 253 ETPU_CISR_B[CIS10] eTPU_B eTPU Engine B Channel 10 Interrupt Status */
(uint32_t) &dummy, /* Vector # 254 ETPU_CISR_B[CIS11] eTPU_B eTPU Engine B Channel 11 Interrupt Status */
(uint32_t) &dummy, /* Vector # 255 ETPU_CISR_B[CIS12] eTPU_B eTPU Engine B Channel 12 Interrupt Status */
(uint32_t) &dummy, /* Vector # 256 ETPU_CISR_B[CIS13] eTPU_B eTPU Engine B Channel 13 Interrupt Status */
(uint32_t) &dummy, /* Vector # 257 ETPU_CISR_B[CIS14] eTPU_B eTPU Engine B Channel 14 Interrupt Status */
(uint32_t) &dummy, /* Vector # 258 ETPU_CISR_B[CIS15] eTPU_B eTPU Engine B Channel 15 Interrupt Status */
(uint32_t) &dummy, /* Vector # 259 ETPU_CISR_B[CIS16] eTPU_B eTPU Engine B Channel 16 Interrupt Status */
(uint32_t) &dummy, /* Vector # 260 ETPU_CISR_B[CIS17] eTPU_B eTPU Engine B Channel 17 Interrupt Status */
(uint32_t) &dummy, /* Vector # 261 ETPU_CISR_B[CIS18] eTPU_B eTPU Engine B Channel 18 Interrupt Status */
(uint32_t) &dummy, /* Vector # 262 ETPU_CISR_B[CIS19] eTPU_B eTPU Engine B Channel 19 Interrupt Status */
(uint32_t) &dummy, /* Vector # 263 ETPU_CISR_B[CIS20] eTPU_B eTPU Engine B Channel 20 Interrupt Status */
(uint32_t) &dummy, /* Vector # 264 ETPU_CISR_B[CIS21] eTPU_B eTPU Engine B Channel 21 Interrupt Status */
(uint32_t) &dummy, /* Vector # 265 ETPU_CISR_B[CIS22] eTPU_B eTPU Engine B Channel 22 Interrupt Status */
(uint32_t) &dummy, /* Vector # 266 ETPU_CISR_B[CIS23] eTPU_B eTPU Engine B Channel 23 Interrupt Status */
(uint32_t) &dummy, /* Vector # 267 ETPU_CISR_B[CIS24] eTPU_B eTPU Engine B Channel 24 Interrupt Status */
(uint32_t) &dummy, /* Vector # 268 ETPU_CISR_B[CIS25] eTPU_B eTPU Engine B Channel 25 Interrupt Status */
(uint32_t) &dummy, /* Vector # 269 ETPU_CISR_B[CIS26] eTPU_B eTPU Engine B Channel 26 Interrupt Status */
(uint32_t) &dummy, /* Vector # 270 ETPU_CISR_B[CIS27] eTPU_B eTPU Engine B Channel 27 Interrupt Status */
(uint32_t) &dummy, /* Vector # 271 ETPU_CISR_B[CIS28] eTPU_B eTPU Engine B Channel 28 Interrupt Status */
(uint32_t) &dummy, /* Vector # 272 ETPU_CISR_B[CIS29] eTPU_B eTPU Engine B Channel 29 Interrupt Status */
(uint32_t) &dummy, /* Vector # 273 ETPU_CISR_B[CIS30] eTPU_B eTPU Engine B Channel 30 Interrupt Status */
(uint32_t) &dummy, /* Vector # 274 ETPU_CISR_B[CIS31] eTPU_B eTPU Engine B Channel 31 Interrupt Status */
(uint32_t) &dummy, /* Vector # 275 DSPIA_SR[TFUF] DSPIA_SR[RFOF] DSPIA_SR[SPEF] DSPIA_SR[DPEF] DSPI_A DSPI_A combined overrun and parity error interrupt requests: Transmit FIFO Underflow/Receive FIFO Overflow SPI Parity Error/DSI Parity Error */
(uint32_t) &dummy, /* Vector # 276 DSPIA_SR[EOQF] DSPI_A DSPI_A transmit FIFO End of Queue Flag */
(uint32_t) &dummy, /* Vector # 277 DSPIA_SR[TFFF] DSPI_A DSPI_A Transmit FIFO Fill Flag */
(uint32_t) &dummy, /* Vector # 278 DSPIA_SR[TCF] | DSPIA_SR[DDIF] DSPI_A DSPI_A Transfer Complete/DSI Data Match Flag */
(uint32_t) &dummy, /* Vector # 279 DSPIA_SR[RFDF] DSPI_A DSPI_A Receive FIFO Drain Flag */
(uint32_t) &dummy, /* Vector # 280 CANB_ESR1[BOFF_INT] | [TWRNINT] | [RWRNINT] FlexCAN_B FlexCAN_B Bus Off, Transmit Warning, Receive Warning */
(uint32_t) &dummy, /* Vector # 281 CANB_ESR1[ERR_INT] | CANB_ERRSR[ECC_CE_INT] | CANB_ERRSR[ECC_HANCE_INT] | CANB_ERRSR[ECC_FANCE_INT] FlexCAN_B FlexCAN_B Error, FlexCAN_B ECC Correctable Error, FlexCAN_B ECC Host Access Non-Correctable Error, FlexCAN_B ECC CAN Access Non-Correctable Error */
(uint32_t) &dummy, /* Vector # 282 Reserved FlexCAN_B Reserved */
(uint32_t) &dummy, /* Vector # 283 CANB_IFRL[BUF0] FlexCAN_B FlexCAN_B Buffer 0 Interrupt */
(uint32_t) &dummy, /* Vector # 284 CANB_IFRL[BUF1] FlexCAN_B FlexCAN_B Buffer 1 Interrupt */
(uint32_t) &dummy, /* Vector # 285 CANB_IFRL[BUF2] FlexCAN_B FlexCAN_B Buffer 2 Interrupt */
(uint32_t) &dummy, /* Vector # 286 CANB_IFRL[BUF3] FlexCAN_B FlexCAN_B Buffer 3 Interrupt */
(uint32_t) &dummy, /* Vector # 287 CANB_IFRL[BUF4] FlexCAN_B FlexCAN_B Buffer 4 Interrupt */
(uint32_t) &dummy, /* Vector # 288 CANB_IFRL[BUF5] FlexCAN_B FlexCAN_B Buffer 5 Interrupt */
(uint32_t) &dummy, /* Vector # 289 CANB_IFRL[BUF6] FlexCAN_B FlexCAN_B Buffer 6 Interrupt */
(uint32_t) &dummy, /* Vector # 290 CANB_IFRL[BUF7] FlexCAN_B FlexCAN_B Buffer 7 Interrupt */
(uint32_t) &dummy, /* Vector # 291 CANB_IFRL[BUF8] FlexCAN_B FlexCAN_B Buffer 8 Interrupt */
(uint32_t) &dummy, /* Vector # 292 CANB_IFRL[BUF9] FlexCAN_B FlexCAN_B Buffer 9 Interrupt */
(uint32_t) &dummy, /* Vector # 293 CANB_IFRL[BUF10] FlexCAN_B FlexCAN_B Buffer 10 Interrupt */
(uint32_t) &dummy, /* Vector # 294 CANB_IFRL[BUF11] FlexCAN_B FlexCAN_B Buffer 11 Interrupt */
(uint32_t) &dummy, /* Vector # 295 CANB_IFRL[BUF12] FlexCAN_B FlexCAN_B Buffer 12 Interrupt */
(uint32_t) &dummy, /* Vector # 296 CANB_IFRL[BUF13] FlexCAN_B FlexCAN_B Buffer 13 Interrupt */
(uint32_t) &dummy, /* Vector # 297 CANB_IFRL[BUF14] FlexCAN_B FlexCAN_B Buffer 14 Interrupt */
(uint32_t) &dummy, /* Vector # 298 CANB_IFRL[BUF15] FlexCAN_B FlexCAN_B Buffer 15 Interrupt */
(uint32_t) &dummy, /* Vector # 299 CANB_IFRL[BUF31:BUF16] FlexCAN_B FlexCAN_B Buffers 31-16 Interrupts */

(uint32_t) &dummy, /* Vector # 300 CANB_IFRH[BUF63:BUF32] FlexCAN_B FlexCAN_B Buffers 63-32 Interrupts */
(uint32_t) &dummy, /* Vector # 301 PIT_TFLG0[TIF] PIT_RTI Periodic Interrupt Timer Interrupt 0 */
(uint32_t) &dummy, /* Vector # 302 PIT_TFLG1[TIF] PIT_RTI Periodic Interrupt Timer Interrupt 1 */
(uint32_t) &dummy, /* Vector # 303 PIT_TFLG2[TIF] PIT_RTI Periodic Interrupt Timer Interrupt 2 */
(uint32_t) &dummy, /* Vector # 304 PIT_TFLG3[TIF] PIT_RTI Periodic Interrupt Timer Interrupt 3 */
(uint32_t) &dummy, /* Vector # 305 PIT_RTI_TFLG[TIF] PIT_RTI Real Time Interrupt Interrupt */
(uint32_t) &dummy, /* Vector # 306 Reserved — Reserved */
(uint32_t) &dummy, /* Vector # 307 MCR[DONE] C55FMC Flash memory program/erase complete */
(uint32_t) &dummy, /* Vector # 308 CAND_ESR1[BOFF_INT] | [TWRNINT] | [RWRNINT] FlexCAN_D FlexCAN_D Bus Off, Transmit Warning, Receive Warning */
(uint32_t) &dummy, /* Vector # 309 CAND_ESR1[ERR_INT] | CAND_ERRSR[ECC_CE_INT] | CAND_ERRSR[ECC_HANCE_INT] | CAND_ERRSR[ECC_FANCE_INT] FlexCAN_D FlexCAN_D Error, FlexCAN_D ECC Correctable Error, FlexCAN_D ECC Host Access Non-Correctable Error, FlexCAN_D ECC CAN Access Non-Correctable Error */
(uint32_t) &dummy, /* Vector # 310 Reserved FlexCAN_D Reserved */
(uint32_t) &dummy, /* Vector # 311 CAND_IFRL[BUF0] FlexCAN_D FlexCAN_D buffer 0 */
(uint32_t) &dummy, /* Vector # 312 CAND_IFRL[BUF1] FlexCAN_D FlexCAN_D buffer 1 */
(uint32_t) &dummy, /* Vector # 313 CAND_IFRL[BUF2] FlexCAN_D FlexCAN_D buffer 2 */
(uint32_t) &dummy, /* Vector # 314 CAND_IFRL[BUF3] FlexCAN_D FlexCAN_D buffer 3 */
(uint32_t) &dummy, /* Vector # 315 CAND_IFRL[BUF4] FlexCAN_D FlexCAN_D buffer 4 */
(uint32_t) &dummy, /* Vector # 316 CAND_IFRL[BUF5] FlexCAN_D FlexCAN_D buffer 5 */
(uint32_t) &dummy, /* Vector # 317 CAND_IFRL[BUF6] FlexCAN_D FlexCAN_D buffer 6 */
(uint32_t) &dummy, /* Vector # 318 CAND_IFRL[BUF7] FlexCAN_D FlexCAN_D buffer 7 */
(uint32_t) &dummy, /* Vector # 319 CAND_IFRL[BUF8] FlexCAN_D FlexCAN_D buffer 8 */
(uint32_t) &dummy, /* Vector # 320 CAND_IFRL[BUF9] FlexCAN_D FlexCAN_D buffer 9 */
(uint32_t) &dummy, /* Vector # 321 CAND_IFRL[BUF10] FlexCAN_D FlexCAN_D buffer 10 */
(uint32_t) &dummy, /* Vector # 322 CAND_IFRL[BUF11] FlexCAN_D FlexCAN_D buffer 11 */
(uint32_t) &dummy, /* Vector # 323 CAND_IFRL[BUF12] FlexCAN_D FlexCAN_D buffer 12 */
(uint32_t) &dummy, /* Vector # 324 CAND_IFRL[BUF13] FlexCAN_D FlexCAN_D buffer 13 */
(uint32_t) &dummy, /* Vector # 325 CAND_IFRL[BUF14] FlexCAN_D FlexCAN_D buffer 14 */
(uint32_t) &dummy, /* Vector # 326 CAND_IFRL[BUF15] FlexCAN_D FlexCAN_D buffer 15 */
(uint32_t) &dummy, /* Vector # 327 CAND_IFRL[BUF31:BUF16] FlexCAN_D FlexCAN_D buffer 16-31 */
(uint32_t) &dummy, /* Vector # 328 CAND_IFRH[BUF63:BUF32] FlexCAN_D FlexCAN_D buffer 32-63 */
(uint32_t) &dummy, /* Vector # 329 SENT_0_GBL_STATUS[FMDU] | SENT_0_GBL_STATUS[SMDU] | SENT_0_GBL_STATUS[FMFO] | all sources of vectors 330-335 SRX_0 SENT_0 Module Interrupts */
(uint32_t) &dummy, /* Vector # 330 SENT_0_CH0_STATUS[CAL_RESYNC| CAL_20_50|SMSG_OFLW| FMSG_OFLW| NUM_EDGES_ERR| FMSG_CRC_ERR| SMSG_CRC_ERR|NIB_VAL_ERR| CAL_DIAG_ERR|CAL_LEN_ERR| PP_DIAG_ERR] | SENT_0_FMSG_RDY[0] | SENT_0_SMSG_RDY[0] SRX_0 SENT_0_CH0 Interrupts */
(uint32_t) &dummy, /* Vector # 331 SENT_0_CH1_STATUS[CAL_RESYNC| CAL_20_50|SMSG_OFLW| FMSG_OFLW| NUM_EDGES_ERR| FMSG_CRC_ERR| SMSG_CRC_ERR|NIB_VAL_ERR| CAL_DIAG_ERR|CAL_LEN_ERR| PP_DIAG_ERR] | SENT_0_FMSG_RDY[1] | SENT_0_SMSG_RDY[1] SRX_0 SENT_0_CH1 Interrupts */
(uint32_t) &dummy, /* Vector # 332 SENT_0_CH2_STATUS[CAL_RESYNC| CAL_20_50|SMSG_OFLW| FMSG_OFLW| NUM_EDGES_ERR| FMSG_CRC_ERR| SMSG_CRC_ERR|NIB_VAL_ERR| CAL_DIAG_ERR|CAL_LEN_ERR| PP_DIAG_ERR] | SENT_0_FMSG_RDY[2] | SENT_0_SMSG_RDY[2] SRX_0 SENT_0_CH2 Interrupts */
(uint32_t) &dummy, /* Vector # 333 SENT_0_CH3_STATUS[CAL_RESYNC| CAL_20_50|SMSG_OFLW| FMSG_OFLW| NUM_EDGES_ERR| FMSG_CRC_ERR| SMSG_CRC_ERR|NIB_VAL_ERR| CAL_DIAG_ERR|CAL_LEN_ERR| PP_DIAG_ERR] | SENT_0_FMSG_RDY[3] | SENT_0_SMSG_RDY[3] SRX_0 SENT_0_CH3 Interrupts */
(uint32_t) &dummy, /* Vector # 334 SENT_0_CH4_STATUS[CAL_RESYNC| CAL_20_50|SMSG_OFLW| FMSG_OFLW| NUM_EDGES_ERR| FMSG_CRC_ERR| SMSG_CRC_ERR|NIB_VAL_ERR| CAL_DIAG_ERR|CAL_LEN_ERR| PP_DIAG_ERR] | SENT_0_FMSG_RDY[4] | SENT_0_SMSG_RDY[4] SRX_0 SENT_0_CH4 Interrupts */
(uint32_t) &dummy, /* Vector # 335 SENT_0_CH5_STATUS[CAL_RESYNC| CAL_20_50|SMSG_OFLW| FMSG_OFLW| NUM_EDGES_ERR| FMSG_CRC_ERR| SMSG_CRC_ERR|NIB_VAL_ERR| CAL_DIAG_ERR|CAL_LEN_ERR| PP_DIAG_ERR] | SENT_0_FMSG_RDY[5] | SENT_0_SMSG_RDY[5] SRX_0 SENT_0_CH5 Interrupts */
(uint32_t) &dummy, /* Vector # 336 SENT_1_GBL_STATUS[FMDU] | SENT_1_GBL_STATUS[SMDU] | SENT_1_GBL_STATUS[FMFO] | all sources of vectors 337-342 SRX_1 SENT_1 Module Interrupts */
(uint32_t) &dummy, /* Vector # 337 SENT_1_CH0_STATUS[CAL_RESYNC| CAL_20_50|SMSG_OFLW| FMSG_OFLW| NUM_EDGES_ERR| FMSG_CRC_ERR| SMSG_CRC_ERR|NIB_VAL_ERR| CAL_DIAG_ERR|CAL_LEN_ERR| PP_DIAG_ERR] | SENT_1_FMSG_RDY[0] | SENT_1_SMSG_RDY[0] SRX_1 SENT_1_CH0 Interrupts */
(uint32_t) &dummy, /* Vector # 338 SENT_1_CH1_STATUS[CAL_RESYNC| CAL_20_50|SMSG_OFLW| FMSG_OFLW| NUM_EDGES_ERR| FMSG_CRC_ERR| SMSG_CRC_ERR|NIB_VAL_ERR| CAL_DIAG_ERR|CAL_LEN_ERR| PP_DIAG_ERR] | SENT_1_FMSG_RDY[1] | SENT_1_SMSG_RDY[1] SRX_1 SENT_1_CH1 Interrupts */
(uint32_t) &dummy, /* Vector # 339 SENT_1_CH2_STATUS[CAL_RESYNC| CAL_20_50|SMSG_OFLW| FMSG_OFLW| NUM_EDGES_ERR| FMSG_CRC_ERR| SMSG_CRC_ERR|NIB_VAL_ERR| CAL_DIAG_ERR|CAL_LEN_ERR| PP_DIAG_ERR] | SENT_1_FMSG_RDY[2] | SENT_1_SMSG_RDY[2] SRX_1 SENT_1_CH2 Interrupts */
(uint32_t) &dummy, /* Vector # 340 SENT_1_CH3_STATUS[CAL_RESYNC| CAL_20_50|SMSG_OFLW| FMSG_OFLW| NUM_EDGES_ERR| FMSG_CRC_ERR| SMSG_CRC_ERR|NIB_VAL_ERR| CAL_DIAG_ERR|CAL_LEN_ERR| PP_DIAG_ERR] | SENT_1_FMSG_RDY[3] | SENT_1_SMSG_RDY[3] SRX_1 SENT_1_CH3 Interrupts */
(uint32_t) &dummy, /* Vector # 341 SENT_1_CH4_STATUS[CAL_RESYNC| CAL_20_50|SMSG_OFLW| FMSG_OFLW| NUM_EDGES_ERR| FMSG_CRC_ERR| SMSG_CRC_ERR|NIB_VAL_ERR| CAL_DIAG_ERR|CAL_LEN_ERR| PP_DIAG_ERR] | SENT_1_FMSG_RDY[4] | SENT_1_SMSG_RDY[4] SRX_1 SENT_1_CH4 Interrupts */
(uint32_t) &dummy, /* Vector # 342 SENT_1_CH5_STATUS[CAL_RESYNC| CAL_20_50|SMSG_OFLW| FMSG_OFLW| NUM_EDGES_ERR| FMSG_CRC_ERR| SMSG_CRC_ERR|NIB_VAL_ERR| CAL_DIAG_ERR|CAL_LEN_ERR| PP_DIAG_ERR] | SENT_1_FMSG_RDY[5] | SENT_1_SMSG_RDY[5] SRX_1 SENT_1_CH5 Interrupts */
(uint32_t) &dummy, /* Vector # 343 HVD_FLASH, HVD_HV, HVD_CORE, LVD_CORE_COLD of PMC_LVD_HVD_EVENT_STATUS PMC Power Management Controller Interrupts */
(uint32_t) &dummy, /* Vector # 344 TEMP0_0, TEMP0_2, TEMP0_3, TEMP1_0, TEMP1_2, TEMP1_3 of PMC_ESR_TD PMC Temp Temperature Sensor Interrupts */
(uint32_t) &dummy, /* Vector # 345 JDC_MSR[JIN_INT] | JDC_MSR[JOUT_INT] JDC JDC Interrupts */
(uint32_t) &dummy, /* Vector # 346 SIPI_ERR | SIPI_SR | SIPI_CSR0 SIPI_0 SIPI Combined Interrupts */
(uint32_t) &dummy, /* Vector # 347 LFAST_0_TISR | LFAST_0_RISR | LFAST_0_RIISR LFAST LFAST Combined Interrupts */
(uint32_t) &dummy, /* Vector # 348 m_can0_int0 | m_can0_int1 | m_can1_int0 | m_can1_int1 M_CAN M_CAN0_0, M_CAN0_1, M_CAN1_0, M_CAN1_1 Combined Interrupts */
(uint32_t) &dummy, /* Vector # 349 Single bit Correction | Multi bit Detection ERM ERM Combined Interrupts */
(uint32_t) &dummy, /* Vector # 350 CMU_0_ISR[FHHI|FLLI|OLRI] | CMU_1_ISR[FHHI|FLLI] CMU CMU_0, CMU_1 Clock Error Interrupts */
(uint32_t) &dummy, /* Vector # 351 CMU_2_ISR[FHHI|FLLI] | CMU_3_ISR[FHHI|FLLI] CMU CMU_2, CMU_3 Clock Error Interrupts */
(uint32_t) &dummy, /* Vector # 352 CMU_4_ISR[FHHI|FLLI] | CMU_5_ISR[FHHI|FLLI] CMU CMU_4, CMU_5 Clock Error Interrupts */
(uint32_t) &dummy, /* Vector # 353 CMU_6_ISR[FHHI|FLLI] | CMU_7_ISR[FHHI|FLLI] CMU CMU_6, CMU_7 Clock Error Interrupts */
(uint32_t) &dummy, /* Vector # 354 CMU_8_ISR[FHHI|FLLI] CMU CMU_8 Clock Error Interrupts */
(uint32_t) &dummy, /* Vector # 355 Reserved CMU Reserved */
(uint32_t) &dummy, /* Vector # 356 Reserved CMU Reserved */
(uint32_t) &dummy, /* Vector # 357 Reserved CMU Reserved */
(uint32_t) &dummy, /* Vector # 358 REACM_GEFR[OVR|EF7:0] Reaction Channels Reaction Module Global Interrupt */
(uint32_t) &dummy, /* Vector # 359 REACM_CHSR_0[MAXL|OCDF| SCDF|TAER|SQER] | REACM_CHSR_1[MAXL|OCDF| SCDF|TAER|SQER] Reaction Channels Reaction Channel 0 and Reaction Channel 1 Combined Interrupts */
(uint32_t) &dummy, /* Vector # 360 REACM_CHSR_2[MAXL|OCDF| SCDF|TAER|SQER] | REACM_CHSR_3[MAXL|OCDF| SCDF|TAER|SQER] Reaction Channels Reaction Channel 2 and Reaction Channel 3 Combined Interrupts */
(uint32_t) &dummy, /* Vector # 361 REACM_CHSR_4[MAXL|OCDF| SCDF|TAER|SQER] | REACM_CHSR_5[MAXL|OCDF| SCDF|TAER|SQER] Reaction Channels Reaction Channel 4 and Reaction Channel 5 Combined Interrupts */
(uint32_t) &dummy, /* Vector # 362 REACM_CHSR_6[MAXL|OCDF| SCDF|TAER|SQER] | REACM_CHSR_7[MAXL|OCDF| SCDF|TAER|SQER] Reaction Channels Reaction Channel 6 and Reaction Channel 7 Combined Interrupts */
(uint32_t) &dummy, /* Vector # 363 REACM_CHSR_8[MAXL|OCDF| SCDF|TAER|SQER] | REACM_CHSR_9[MAXL|OCDF| SCDF|TAER|SQER] Reaction Channels Reaction Channel 8 and Reaction Channel 9 Combined Interrupts */
(uint32_t) &dummy, /* Vector # 364 Reserved Reaction Channels Reserved */
(uint32_t) &dummy, /* Vector # 365 Reserved Reaction Channels Reserved */
(uint32_t) &dummy, /* Vector # 366 DECFILTER_MSR_B[IDF] DEC_B Decimation B Input (Fill) */
(uint32_t) &dummy, /* Vector # 367 DECFILTER_MSR_B[ODF||SDF] DEC_B Decimation B Output/Integ (Drain/Integ) */
(uint32_t) &dummy, /* Vector # 368 DECFILTER B ERRORS DEC_B Decimation B Error */
(uint32_t) &dummy, /* Vector # 369 ETPU_SCR_MCR[SDMERR,SSAE RR,SCMERR,WDTO1,MGE1,ILF1,L TO1,SCMMISF] and ETPU_MESR_MESR[DCERR,CCE RR]eTPU_C eTPU Engine C Global Exception */
(uint32_t) &dummy, /* Vector # 370 ETPU_CISR_C[CIS0] eTPU_C eTPU Engine C Channel 0 Interrupt Status */
(uint32_t) &dummy, /* Vector # 371 ETPU_CISR_C[CIS1] eTPU_C eTPU Engine C Channel 1 Interrupt Status */
(uint32_t) &dummy, /* Vector # 372 ETPU_CISR_C[CIS2] eTPU_C eTPU Engine C Channel 2 Interrupt Status */
(uint32_t) &dummy, /* Vector # 373 ETPU_CISR_C[CIS3] eTPU_C eTPU Engine C Channel 3 Interrupt Status */
(uint32_t) &dummy, /* Vector # 374 ETPU_CISR_C[CIS4] eTPU_C eTPU Engine C Channel 4 Interrupt Status */
(uint32_t) &dummy, /* Vector # 375 ETPU_CISR_C[CIS5] eTPU_C eTPU Engine C Channel 5 Interrupt Status */
(uint32_t) &dummy, /* Vector # 376 ETPU_CISR_C[CIS6] eTPU_C eTPU Engine C Channel 6 Interrupt Status */
(uint32_t) &dummy, /* Vector # 377 ETPU_CISR_C[CIS7] eTPU_C eTPU Engine C Channel 7 Interrupt Status */
(uint32_t) &dummy, /* Vector # 378 ETPU_CISR_C[CIS8] eTPU_C eTPU Engine C Channel 8 Interrupt Status */
(uint32_t) &dummy, /* Vector # 379 ETPU_CISR_C[CIS9] eTPU_C eTPU Engine C Channel 9 Interrupt Status */
(uint32_t) &dummy, /* Vector # 380 ETPU_CISR_C[CIS10] eTPU_C eTPU Engine C Channel 10 Interrupt Status */
(uint32_t) &dummy, /* Vector # 381 ETPU_CISR_C[CIS11] eTPU_C eTPU Engine C Channel 11 Interrupt Status */
(uint32_t) &dummy, /* Vector # 382 ETPU_CISR_C[CIS12] eTPU_C eTPU Engine C Channel 12 Interrupt Status */
(uint32_t) &dummy, /* Vector # 383 ETPU_CISR_C[CIS13] eTPU_C eTPU Engine C Channel 13 Interrupt Status */
(uint32_t) &dummy, /* Vector # 384 ETPU_CISR_C[CIS14] eTPU_C eTPU Engine C Channel 14 Interrupt Status */
(uint32_t) &dummy, /* Vector # 385 ETPU_CISR_C[CIS15] eTPU_C eTPU Engine C Channel 15 Interrupt Status */
(uint32_t) &dummy, /* Vector # 386 ETPU_CISR_C[CIS16] eTPU_C eTPU Engine C Channel 16 Interrupt Status */
(uint32_t) &dummy, /* Vector # 387 ETPU_CISR_C[CIS17] eTPU_C eTPU Engine C Channel 17 Interrupt Status */
(uint32_t) &dummy, /* Vector # 388 ETPU_CISR_C[CIS18] eTPU_C eTPU Engine C Channel 18 Interrupt Status */
(uint32_t) &dummy, /* Vector # 389 ETPU_CISR_C[CIS19] eTPU_C eTPU Engine C Channel 19 Interrupt Status */
(uint32_t) &dummy, /* Vector # 390 ETPU_CISR_C[CIS20] eTPU_C eTPU Engine C Channel 20 Interrupt Status */
(uint32_t) &dummy, /* Vector # 391 ETPU_CISR_C[CIS21] eTPU_C eTPU Engine C Channel 21 Interrupt Status */
(uint32_t) &dummy, /* Vector # 392 ETPU_CISR_C[CIS22] eTPU_C eTPU Engine C Channel 22 Interrupt Status */
(uint32_t) &dummy, /* Vector # 393 ETPU_CISR_C[CIS23] eTPU_C eTPU Engine C Channel 23 Interrupt Status */
(uint32_t) &dummy, /* Vector # 394 EQADCB_FISRx[TORF] EQADCB_FISRx[RFOF] EQADCB_FISRx[CFUF] eQADC_B eQADC combined overrun interrupt requests from all of the FIFOs: Trigger Overrun, Receive FIFO Overflow, and command FIFO Underflow */
(uint32_t) &dummy, /* Vector # 395 EQADCB_FISR0[NCF] eQADC_B eQADC command FIFO 0 Non-Coherency Flag */
(uint32_t) &dummy, /* Vector # 396 EQADCB_FISR0[PF] eQADC_B eQADC command FIFO 0 Pause Flag */
(uint32_t) &dummy, /* Vector # 397 EQADCB_FISR0[EOQF] eQADC_B eQADC command FIFO 0 command queue End of Queue Flag */
(uint32_t) &dummy, /* Vector # 398 EQADCB_FISR0[CFFF] eQADC_B eQADC Command FIFO 0 Fill Flag */
(uint32_t) &dummy, /* Vector # 399 EQADCB_FISR0[RFDF] eQADC_B eQADC Receive FIFO 0 Drain Flag */

(uint32_t) &dummy, /* Vector # 400 EQADCB_FISR1[NCF] eQADC_B eQADC command FIFO 1 Non-Coherency Flag */
(uint32_t) &dummy, /* Vector # 401 EQADCB_FISR1[PF] eQADC_B eQADC command FIFO 1 Pause Flag */
(uint32_t) &dummy, /* Vector # 402 EQADCB_FISR1[EOQF] eQADC_B eQADC command FIFO 1 command queue End of Queue Flag */
(uint32_t) &dummy, /* Vector # 403 EQADCB_FISR1[CFFF] eQADC_B eQADC Command FIFO 1 Fill Flag */
(uint32_t) &dummy, /* Vector # 404 EQADCB_FISR1[RFDF] eQADC_B eQADC Receive FIFO 1 Drain Flag */
(uint32_t) &dummy, /* Vector # 405 EQADCB_FISR2[NCF] eQADC_B eQADC command FIFO 2 Non-Coherency Flag */
(uint32_t) &dummy, /* Vector # 406 EQADCB_FISR2[PF] eQADC_B eQADC command FIFO 2 Pause Flag */
(uint32_t) &dummy, /* Vector # 407 EQADCB_FISR2[EOQF] eQADC_B eQADC command FIFO 2 command queue End of Queue Flag */
(uint32_t) &dummy, /* Vector # 408 EQADCB_FISR2[CFFF] eQADC_B eQADC Command FIFO 2 Fill Flag */
(uint32_t) &dummy, /* Vector # 409 EQADCB_FISR2[RFDF] eQADC_B eQADC Receive FIFO 2 Drain Flag */
(uint32_t) &dummy, /* Vector # 410 EQADCB_FISR3[NCF] eQADC_B eQADC command FIFO 3 Non-Coherency Flag */
(uint32_t) &dummy, /* Vector # 411 EQADCB_FISR3[PF] eQADC_B eQADC command FIFO 3 Pause Flag */
(uint32_t) &dummy, /* Vector # 412 EQADCB_FISR3[EOQF] eQADC_B eQADC command FIFO 3 command queue End of Queue Flag */
(uint32_t) &dummy, /* Vector # 413 EQADCB_FISR3[CFFF] eQADC_B eQADC Command FIFO 3 Fill Flag */
(uint32_t) &dummy, /* Vector # 414 EQADCB_FISR3[RFDF] eQADC_B eQADC Receive FIFO 3 Drain Flag */
(uint32_t) &dummy, /* Vector # 415 EQADCB_FISR4[NCF] eQADC_B eQADC command FIFO 4 Non-Coherency Flag */
(uint32_t) &dummy, /* Vector # 416 EQADCB_FISR4[PF] eQADC_B eQADC command FIFO 4 Pause Flag */
(uint32_t) &dummy, /* Vector # 417 EQADCB_FISR4[EOQF] eQADC_B eQADC command FIFO 4 command queue End of Queue Flag */
(uint32_t) &dummy, /* Vector # 418 EQADCB_FISR4[CFFF] eQADC_B eQADC Command FIFO 4 Fill Flag */
(uint32_t) &dummy, /* Vector # 419 EQADCB_FISR4[RFDF] eQADC_B eQADC Receive FIFO 4 Drain Flag */
(uint32_t) &dummy, /* Vector # 420 EQADCB_FISR5[NCF] eQADC_B eQADC command FIFO 5 Non-Coherency Flag */
(uint32_t) &dummy, /* Vector # 421 EQADCB_FISR5[PF] eQADC_B eQADC command FIFO 5 Pause Flag */
(uint32_t) &dummy, /* Vector # 422 EQADCB_FISR5[EOQF] eQADC_B eQADC command FIFO 5 command queue End of Queue Flag */
(uint32_t) &dummy, /* Vector # 423 EQADCB_FISR5[CFFF] eQADC_B eQADC Command FIFO 5 Fill Flag */
(uint32_t) &dummy, /* Vector # 424 EQADCB_FISR5[RFDF] eQADC_B eQADC Receive FIFO 5 Drain Flag */
(uint32_t) &dummy, /* Vector # 425 EDMAB_ERRH[ERR31:ERR0] eDMA_B eDMA channel Error flags 0-31 */
(uint32_t) &dummy, /* Vector # 426 EDMAB_IRQRH[INT0] eDMA_B eDMA channel Interrupt 0 */
(uint32_t) &dummy, /* Vector # 427 EDMAB_IRQRH[INT1] eDMA_B eDMA channel Interrupt 1 */
(uint32_t) &dummy, /* Vector # 428 EDMAB_IRQRH[INT2] eDMA_B eDMA channel Interrupt 2 */
(uint32_t) &dummy, /* Vector # 429 EDMAB_IRQRH[INT3] eDMA_B eDMA channel Interrupt 3 */
(uint32_t) &dummy, /* Vector # 430 EDMAB_IRQRH[INT4] eDMA_B eDMA channel Interrupt 4 */
(uint32_t) &dummy, /* Vector # 431 EDMAB_IRQRH[INT5] eDMA_B eDMA channel Interrupt 5 */
(uint32_t) &dummy, /* Vector # 432 EDMAB_IRQRH[INT6] eDMA_B eDMA channel Interrupt 6 */
(uint32_t) &dummy, /* Vector # 433 EDMAB_IRQRH[INT7] eDMA_B eDMA channel Interrupt 7 */
(uint32_t) &dummy, /* Vector # 434 EDMAB_IRQRH[INT8] eDMA_B eDMA channel Interrupt 8 */
(uint32_t) &dummy, /* Vector # 435 EDMAB_IRQRH[INT9] eDMA_B eDMA channel Interrupt 9 */
(uint32_t) &dummy, /* Vector # 436 EDMAB_IRQRH[INT10] eDMA_B eDMA channel Interrupt 10 */
(uint32_t) &dummy, /* Vector # 437 EDMAB_IRQRH[INT11] eDMA_B eDMA channel Interrupt 11 */
(uint32_t) &dummy, /* Vector # 438 EDMAB_IRQRH[INT12] eDMA_B eDMA channel Interrupt 12 */
(uint32_t) &dummy, /* Vector # 439 EDMAB_IRQRH[INT13] eDMA_B eDMA channel Interrupt 13 */
(uint32_t) &dummy, /* Vector # 440 EDMAB_IRQRH[INT14] eDMA_B eDMA channel Interrupt 14 */
(uint32_t) &dummy, /* Vector # 441 EDMAB_IRQRH[INT15] eDMA_B eDMA channel Interrupt 15 */
(uint32_t) &dummy, /* Vector # 442 EDMAB_IRQRH[INT16] eDMA_B eDMA channel Interrupt 16 */
(uint32_t) &dummy, /* Vector # 443 EDMAB_IRQRH[INT17] eDMA_B eDMA channel Interrupt 17 */
(uint32_t) &dummy, /* Vector # 444 EDMAB_IRQRH[INT18] eDMA_B eDMA channel Interrupt 18 */
(uint32_t) &dummy, /* Vector # 445 EDMAB_IRQRH[INT19] eDMA_B eDMA channel Interrupt 19 */
(uint32_t) &dummy, /* Vector # 446 EDMAB_IRQRH[INT20] eDMA_B eDMA channel Interrupt 20 */
(uint32_t) &dummy, /* Vector # 447 EDMAB_IRQRH[INT21] eDMA_B eDMA channel Interrupt 21 */
(uint32_t) &dummy, /* Vector # 448 EDMAB_IRQRH[INT22] eDMA_B eDMA channel Interrupt 22 */
(uint32_t) &dummy, /* Vector # 449 EDMAB_IRQRH[INT23] eDMA_B eDMA channel Interrupt 23 */
(uint32_t) &dummy, /* Vector # 450 EDMAB_IRQRH[INT24] eDMA_B eDMA channel Interrupt 24 */
(uint32_t) &dummy, /* Vector # 451 EDMAB_IRQRH[INT25] eDMA_B eDMA channel Interrupt 25 */
(uint32_t) &dummy, /* Vector # 452 EDMAB_IRQRH[INT26] eDMA_B eDMA channel Interrupt 26 */
(uint32_t) &dummy, /* Vector # 453 EDMAB_IRQRH[INT27] eDMA_B eDMA channel Interrupt 27 */
(uint32_t) &dummy, /* Vector # 454 EDMAB_IRQRH[INT28] eDMA_B eDMA channel Interrupt 28 */
(uint32_t) &dummy, /* Vector # 455 EDMAB_IRQRH[INT29] eDMA_B eDMA channel Interrupt 29 */
(uint32_t) &dummy, /* Vector # 456 EDMAB_IRQRH[INT30] eDMA_B eDMA channel Interrupt 30 */
(uint32_t) &dummy, /* Vector # 457 EDMAB_IRQRH[INT31] eDMA_B eDMA channel Interrupt 31 */
(uint32_t) &dummy, /* Vector # 458 SD_ADC1 | SD_ADC2 | SD_ADC3 | SD_ADC4 SDADC SDADC1 to SDADC4 Interrupts */
(uint32_t) &dummy, /* Vector # 459 eMIOS_1_GFLAG[F16] eMIOS_1 eMIOS_1 channel 16 Flag */
(uint32_t) &dummy, /* Vector # 460 eMIOS_1_GFLAG[F17] eMIOS_1 eMIOS_1 channel 17 Flag */
(uint32_t) &dummy, /* Vector # 461 eMIOS_1_GFLAG[F18] eMIOS_1 eMIOS_1 channel 18 Flag */
(uint32_t) &dummy, /* Vector # 462 eMIOS_1_GFLAG[F19] eMIOS_1 eMIOS_1 channel 19 Flag */
(uint32_t) &dummy, /* Vector # 463 eMIOS_1_GFLAG[F20] eMIOS_1 eMIOS_1 channel 20 Flag */
(uint32_t) &dummy, /* Vector # 464 eMIOS_1_GFLAG[F21] eMIOS_1 eMIOS_1 channel 21 Flag */
(uint32_t) &dummy, /* Vector # 465 eMIOS_1_GFLAG[F22] eMIOS_1 eMIOS_1 channel 22 Flag */
(uint32_t) &dummy, /* Vector # 466 eMIOS_1_GFLAG[F23] eMIOS_1 eMIOS_1 channel 23 Flag */
(uint32_t) &dummy, /* Vector # 467 DECFILTER_MSR_C[IDF] DEC_C Decimation C Input (Fill) */
(uint32_t) &dummy, /* Vector # 468 DECFILTER_MSR_C[ODF||SDF] DEC_C Decimation C Output/Integ (Drain/Integ) */
(uint32_t) &dummy, /* Vector # 469 DECFILTER C ERRORS DEC_C Decimation C Error */
(uint32_t) &dummy, /* Vector # 470 DECFILTER_MSR_D[IDF] DEC_D Decimation D Input (Fill) */
(uint32_t) &dummy, /* Vector # 471 DECFILTER_MSR_D[ODF||SDF] DEC_D Decimation D Output/Integ (Drain/Integ) */
(uint32_t) &dummy, /* Vector # 472 DECFILTER D ERRORS DEC_D Decimation D Error */

};


void dummy (void) {   /* Dummy ISR vector to trap undefined ISRs */
    while (1) {};  /* Wait forever or for watchdog timeout */
}

