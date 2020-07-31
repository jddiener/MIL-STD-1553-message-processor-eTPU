/**************************************************************************/
/* FILE NAME: mpc5554.h                      COPYRIGHT (c) Freescale 2005 */
/* VERSION:  1.1                                  All Rights Reserved     */
/*                                                                        */
/* DESCRIPTION:                                                           */
/* This file contain all of the register and bit field definitions for    */
/* MPC5554.                                                               */
/*========================================================================*/
/* UPDATE HISTORY                                                         */
/* REV      AUTHOR      DATE       DESCRIPTION OF CHANGE                  */
/* ---   -----------  ---------    ---------------------                  */
/* 0.01  J. Loeliger  03/Mar/03    Initial version of file for MPC5554.   */
/*                                  Based on SoC version 0.7.             */
/* 0.02  J. Loeliger  05/Mar/03    All registers and bit fields now       */
/*                                  defined.                              */
/* 0.03  J. Loeliger  05/May/03    Updated to current spec., fixed several*/
/*                                   bugs and naming/formating issues.    */
/* 0.04  J. Loeliger  16/May/03    More fixes and naming/formating issues.*/
/* 0.05  J. Loeliger  19/Aug/03    Updated for latest documentation.      */
/* 0.06  J. Loeliger  03/Sep/03    Changed to include motint.h            */
/*                                  Updated many register names.          */
/* 0.07  J. Loeliger  04/Nov/03    Changed to include typedefs.h and more */
/*                                  register name updates.                */
/* 0.08  J. Loeliger  25/Feb/04    Added MetroWerks #pragmas.             */
/*                                  Updated for user manual 1.0           */
/* 0.09  J. Loeliger  27/Feb/04    Updated eDMA tcd section and some more */
/*                                  bit field names to match user's man.  */
/* 0.10  J. Loeliger  01/Apr/04    Fixed register spacing in ADC and eTpu */
/* 0.11  J. Loeliger  16/Jun/04    Many fixes and updated to user's       */
/*                                  manual, also some testing done.       */
/* 0.12  J. Loeliger  25/Jun/04    Fixed problems in edma and eTpu.       */
/* 0.13  J. Loeliger  16/Jul/04    Fixed mistake in FlexCAN TIMER size and*/
/*                                  changed eTpu memory defs to start with*/
/*                                  ETPU_                                 */
/* 0.14  J. Loeliger  17/Nov/04    Added ETPU_CODE_RAM definition.        */
/*                                  All code moved to CVS repository.     */
/*                                  Updated copyright to Freescale.       */
/*                                  Added new SCMOFFDATAR register to eTpu*/
/*                                  Fixed REDCR_A&B bit fields in eTpu.   */
/*                                  Added new DBR bit in CTAR for DSPI.   */
/* 0.15  J. Loeliger  29/Nov/04    Added support for new eTpu util funcs. */
/*                                  Added bit fields for FlexCAN buffer ID*/
/* 0.16  J. Loeliger  01/Dec/04    Corrected comments in  release 0.16.   */
/* 0.17  J. Loeliger  02/Dec/04    Moved eTpu variable definitions to a   */
/*                                   seperate new file.                   */
/*                                   Removed SIU variable the GPIO        */
/*                                   routines do not need it.             */
/* 1.0  G.Emerson     22/Feb/05    No real changes to this file.          */
/*                                 Joint generation with mpc5553.h        */
/* 1.1   G. Emerson   6/Jun/05     Changes to SIU to allow for upward     */
/*                                 expansion of PCR/GPDI/GPDO             */
/*                                 Added #defines for memory sizes etc    */
/**************************************************************************/
/*>>>>NOTE! this file is auto-generated please do not edit it!<<<<*/

#ifndef _MPC5554_H_
#define _MPC5554_H_

#include "typedefs.h"

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef __MWERKS__
#pragma push
#pragma ANSI_strict off
#endif

/****************************************************************************/
/*                          MODULE : PBRIDGE_A Peripheral Bridge            */
/****************************************************************************/
    struct PBRIDGE_A_tag {
        union {
            vuint32_t R;
            struct {
                vuint32_t MBW0:1;
                vuint32_t MTR0:1;
                vuint32_t MTW0:1;
                vuint32_t MPL0:1;
                vuint32_t MBW1:1;
                vuint32_t MTR1:1;
                vuint32_t MTW1:1;
                vuint32_t MPL1:1;
                vuint32_t MBW2:1;
                vuint32_t MTR2:1;
                vuint32_t MTW2:1;
                vuint32_t MPL2:1;
                vuint32_t MBW3:1;
                vuint32_t MTR3:1;
                vuint32_t MTW3:1;
                vuint32_t MPL3:1;
                  vuint32_t:16;
            } B;
        } MPCR;                 /* Master Privilege Control Register */

        uint32_t pbridge_a_reserved2[7];

        union {
            vuint32_t R;
            struct {
                vuint32_t BW0:1;
                vuint32_t SP0:1;
                vuint32_t WP0:1;
                vuint32_t TP0:1;
                  vuint32_t:28;
            } B;
        } PACR0;

        uint32_t pbridge_a_reserved3[7];

        union {
            vuint32_t R;
            struct {
                vuint32_t BW0:1;
                vuint32_t SP0:1;
                vuint32_t WP0:1;
                vuint32_t TP0:1;
                vuint32_t BW1:1;
                vuint32_t SP1:1;
                vuint32_t WP1:1;
                vuint32_t TP1:1;
                vuint32_t BW2:1;
                vuint32_t SP2:1;
                vuint32_t WP2:1;
                vuint32_t TP2:1;
                  vuint32_t:4;
                vuint32_t BW4:1;
                vuint32_t SP4:1;
                vuint32_t WP4:1;
                vuint32_t TP4:1;
                  vuint32_t:12;
            } B;
        } OPACR0;

        union {
            vuint32_t R;
            struct {
                vuint32_t BW8:1;
                vuint32_t SP8:1;
                vuint32_t WP8:1;
                vuint32_t TP8:1;
                  vuint32_t:28;
            } B;
        } OPACR1;

        union {
            vuint32_t R;
            struct {
                vuint32_t BW16:1;
                vuint32_t SP16:1;
                vuint32_t WP16:1;
                vuint32_t TP16:1;
                  vuint32_t:4;
                vuint32_t BW18:1;
                vuint32_t SP18:1;
                vuint32_t WP18:1;
                vuint32_t TP18:1;
                vuint32_t BW19:1;
                vuint32_t SP19:1;
                vuint32_t WP19:1;
                vuint32_t TP19:1;
                vuint32_t BW20:1;
                vuint32_t SP20:1;
                vuint32_t WP20:1;
                vuint32_t TP20:1;
                  vuint32_t:12;
            } B;
        } OPACR2;

    };

/****************************************************************************/
/*                          MODULE : PBRIDGE_B Peripheral Bridge            */
/****************************************************************************/
    struct PBRIDGE_B_tag {
        union {
            vuint32_t R;
            struct {
                vuint32_t MBW0:1;
                vuint32_t MTR0:1;
                vuint32_t MTW0:1;
                vuint32_t MPL0:1;
                vuint32_t MBW1:1;
                vuint32_t MTR1:1;
                vuint32_t MTW1:1;
                vuint32_t MPL1:1;
                vuint32_t MBW2:1;
                vuint32_t MTR2:1;
                vuint32_t MTW2:1;
                vuint32_t MPL2:1;
                vuint32_t MBW3:1;
                vuint32_t MTR3:1;
                vuint32_t MTW3:1;
                vuint32_t MPL3:1;
                  vuint32_t:16;
            } B;
        } MPCR;                 /* Master Privilege Control Register */

        uint32_t pbridge_b_reserved2[7];

        union {
            vuint32_t R;
            struct {
                vuint32_t BW0:1;
                vuint32_t SP0:1;
                vuint32_t WP0:1;
                vuint32_t TP0:1;
                vuint32_t BW1:1;
                vuint32_t SP1:1;
                vuint32_t WP1:1;
                vuint32_t TP1:1;
                  vuint32_t:24;
            } B;
        } PACR0;

        uint32_t pbridge_b_reserved3;

        union {
            vuint32_t R;
            struct {
                vuint32_t BW16:1;
                vuint32_t SP16:1;
                vuint32_t WP16:1;
                vuint32_t TP16:1;
                vuint32_t BW17:1;
                vuint32_t SP17:1;
                vuint32_t WP17:1;
                vuint32_t TP17:1;
                vuint32_t BW18:1;
                vuint32_t SP18:1;
                vuint32_t WP18:1;
                vuint32_t TP18:1;
                  vuint32_t:20;
            } B;
        } PACR2;

        uint32_t pbridge_b_reserved4[5];

        union {
            vuint32_t R;
            struct {
                vuint32_t BW0:1;
                vuint32_t SP0:1;
                vuint32_t WP0:1;
                vuint32_t TP0:1;
                  vuint32_t:12;
                vuint32_t BW4:1;
                vuint32_t SP4:1;
                vuint32_t WP4:1;
                vuint32_t TP4:1;
                vuint32_t BW5:1;
                vuint32_t SP5:1;
                vuint32_t WP5:1;
                vuint32_t TP5:1;
                vuint32_t BW6:1;
                vuint32_t SP6:1;
                vuint32_t WP6:1;
                vuint32_t TP6:1;
                vuint32_t BW7:1;
                vuint32_t SP7:1;
                vuint32_t WP7:1;
                vuint32_t TP7:1;
            } B;
        } OPACR0;

        union {
            vuint32_t R;
            struct {
                vuint32_t:16;
                vuint32_t BW12:1;
                vuint32_t SP12:1;
                vuint32_t WP12:1;
                vuint32_t TP12:1;
                vuint32_t BW13:1;
                vuint32_t SP13:1;
                vuint32_t WP13:1;
                vuint32_t TP13:1;
                  vuint32_t:8;
            } B;
        } OPACR1;

        union {
            vuint32_t R;
            struct {
                vuint32_t BW16:1;
                vuint32_t SP16:1;
                vuint32_t WP16:1;
                vuint32_t TP16:1;
                vuint32_t BW17:1;
                vuint32_t SP17:1;
                vuint32_t WP17:1;
                vuint32_t TP17:1;
                vuint32_t BW18:1;
                vuint32_t SP18:1;
                vuint32_t WP18:1;
                vuint32_t TP18:1;
                  vuint32_t:20;
            } B;
        } OPACR2;

        union {
            vuint32_t R;
            struct {
                vuint32_t:28;
                vuint32_t BW31:1;
                vuint32_t SP31:1;
                vuint32_t WP31:1;
                vuint32_t TP31:1;
            } B;
        } OPACR3;

    };
/****************************************************************************/
/*                     MODULE : FMPLL                                       */
/****************************************************************************/
    struct FMPLL_tag {
        union {
            vuint32_t R;
            struct {
                vuint32_t:1;
                vuint32_t PREDIV:3;
                vuint32_t MFD:5;
                  vuint32_t:1;
                vuint32_t RFD:3;
                vuint32_t LOCEN:1;
                vuint32_t LOLRE:1;
                vuint32_t LOCRE:1;
                vuint32_t DISCLK:1;
                vuint32_t LOLIRQ:1;
                vuint32_t LOCIRQ:1;
                vuint32_t RATE:1;
                vuint32_t DEPTH:2;
                vuint32_t EXP:10;
            } B;
        } SYNCR;

        union {
            vuint32_t R;
            struct {
                vuint32_t:22;
                vuint32_t LOLF:1;
                vuint32_t LOC:1;
                vuint32_t MODE:1;
                vuint32_t PLLSEL:1;
                vuint32_t PLLREF:1;
                vuint32_t LOCKS:1;
                vuint32_t LOCK:1;
                vuint32_t LOCF:1;
                vuint32_t CALDONE:1;
                vuint32_t CALPASS:1;
            } B;
        } SYNSR;

    };
/****************************************************************************/
/*                     MODULE : External Bus Interface (EBI)                */
/****************************************************************************/
    struct CS_tag {
        union {                 /* Base Register Bank */
            vuint32_t R;
            struct {
                vuint32_t BA:17;
                  vuint32_t:3;
                vuint32_t PS:1;
                  vuint32_t:4;
                vuint32_t BL:1;
                vuint32_t WEBS:1;
                vuint32_t TBDIP:1;
                  vuint32_t:2;
                vuint32_t BI:1;
                vuint32_t V:1;
            } B;
        } BR;

        union {                 /* Option Register Bank */
            vuint32_t R;
            struct {
                vuint32_t AM:17;
                  vuint32_t:7;
                vuint32_t SCY:4;
                  vuint32_t:1;
                vuint32_t BSCY:2;
                  vuint32_t:1;
            } B;
        } OR;
    };
    struct EBI_tag {
        union {                 /* Module Configuration Register */
            vuint32_t R;
            struct {
                vuint32_t:5;
                vuint32_t SIZEEN:1;
                vuint32_t SIZE:2;
                  vuint32_t:8;
                vuint32_t ACGE:1;
                vuint32_t EXTM:1;
                vuint32_t EARB:1;
                vuint32_t EARP:2;
                  vuint32_t:4;
                vuint32_t MDIS:1;
                  vuint32_t:5;
                vuint32_t DBM:1;
            } B;
        } MCR;

        uint32_t EBI_reserved1;

        union {                 /* Transfer Error Status Register */
            vuint32_t R;
            struct {
                vuint32_t:30;
                vuint32_t TEAF:1;
                vuint32_t BMTF:1;
            } B;
        } TESR;

        union {                 /* Bus Monitor Control Register */
            vuint32_t R;
            struct {
                vuint32_t:16;
                vuint32_t BMT:8;
                vuint32_t BME:1;
                  vuint32_t:7;
            } B;
        } BMCR;

        struct CS_tag CS[4];

    };
/****************************************************************************/
/*                     MODULE : FLASH                                       */
/****************************************************************************/
    struct FLASH_tag {
        union {                 /* Module Configuration Register */
            vuint32_t R;
            struct {
                vuint32_t:4;
                vuint32_t SIZE:4;
                  vuint32_t:1;
                vuint32_t LAS:3;
                  vuint32_t:3;
                vuint32_t MAS:1;
                vuint32_t EER:1;
                vuint32_t RWE:1;
                vuint32_t BBEPE:1;
                vuint32_t EPE:1;
                vuint32_t PEAS:1;
                vuint32_t DONE:1;
                vuint32_t PEG:1;
                  vuint32_t:2;
                vuint32_t STOP:1;
                  vuint32_t:1;
                vuint32_t PGM:1;
                vuint32_t PSUS:1;
                vuint32_t ERS:1;
                vuint32_t ESUS:1;
                vuint32_t EHV:1;
            } B;
        } MCR;

        union {                 /* LML Register */
            vuint32_t R;
            struct {
                vuint32_t LME:1;
                  vuint32_t:10;
                vuint32_t SLOCK:1;
                vuint32_t MLOCK:4;
                vuint32_t LLOCK:16;
            } B;
        } LMLR;

        union {                 /* HL Register */
            vuint32_t R;
            struct {
                vuint32_t HBE:1;
                  vuint32_t:3;
                vuint32_t HBLOCK:28;
            } B;
        } HLR;

        union {                 /* SLML Register */
            vuint32_t R;
            struct {
                vuint32_t SLE:1;
                  vuint32_t:10;
                vuint32_t SSLOCK:1;
                vuint32_t SMLOCK:4;
                vuint32_t SLLOCK:16;
            } B;
        } SLMLR;

        union {                 /* LMS Register */
            vuint32_t R;
            struct {
                vuint32_t:12;
                vuint32_t MSEL:4;
                vuint32_t LSEL:16;
            } B;
        } LMSR;

        union {
            vuint32_t R;
            struct {
                vuint32_t:4;
                vuint32_t HBSEL:28;
            } B;
        } HSR;

        union {
            vuint32_t R;
            struct {
                vuint32_t:10;
                vuint32_t ADDR:19;
                  vuint32_t:3;
            } B;
        } AR;

        union {
            vuint32_t R;
            struct {
                vuint32_t:12;   /* Master ID 15-4 not used on MPC5554 */
                vuint32_t M3PFE:1;
                vuint32_t M2PFE:1;
                vuint32_t M1PFE:1;
                vuint32_t M0PFE:1;
                vuint32_t APC:3;
                vuint32_t WWSC:2;
                vuint32_t RWSC:3;
                vuint32_t DPFEN:2;
                vuint32_t IPFEN:2;
                vuint32_t PFLIM:3;
                vuint32_t BFEN:1;
            } B;
        } BIUCR;

        union {
            vuint32_t R;
            struct {
                vuint32_t:24;   /* Master ID 15-4 not used on MPC5554 */
                vuint32_t M3AP:2;
                vuint32_t M2AP:2;
                vuint32_t M1AP:2;
                vuint32_t M0AP:2;
            } B;
        } BIUAPR;
    };
/****************************************************************************/
/*                     MODULE : SIU                                         */
/****************************************************************************/
    struct SIU_tag {
        int32_t SIU_reserved0;

        union {                 /* MCU ID Register */
            vuint32_t R;
            struct {
                vuint32_t PARTNUM:16;
                vuint32_t MASKNUM:16;
            } B;
        } MIDR;
        int32_t SIU_reserved00;

        union {                 /* Reset Status Register */
            vuint32_t R;
            struct {
                vuint32_t PORS:1;
                vuint32_t ERS:1;
                vuint32_t LLRS:1;
                vuint32_t LCRS:1;
                vuint32_t WDRS:1;
                vuint32_t CRS:1;
                  vuint32_t:8;
                vuint32_t SSRS:1;
                vuint32_t SERF:1;
                vuint32_t WKPCFG:1;
                  vuint32_t:12;
                vuint32_t BOOTCFG:2;
                vuint32_t RGF:1;
            } B;
        } RSR;

        union {                 /* System Reset Control Register */
            vuint32_t R;
            struct {
                vuint32_t SSR:1;
                vuint32_t SER:1;
                  vuint32_t:14;
                vuint32_t CRE:1;
                  vuint32_t:15;
            } B;
        } SRCR;

        union {                 /* External Interrupt Status Register */
            vuint32_t R;
            struct {
                vuint32_t:16;
                vuint32_t EIF15:1;
                vuint32_t EIF14:1;
                vuint32_t EIF13:1;
                vuint32_t EIF12:1;
                vuint32_t EIF11:1;
                vuint32_t EIF10:1;
                vuint32_t EIF9:1;
                vuint32_t EIF8:1;
                vuint32_t EIF7:1;
                vuint32_t EIF6:1;
                vuint32_t EIF5:1;
                vuint32_t EIF4:1;
                vuint32_t EIF3:1;
                vuint32_t EIF2:1;
                vuint32_t EIF1:1;
                vuint32_t EIF0:1;
            } B;
        } EISR;

        union {                 /* DMA/Interrupt Request Enable Register */
            vuint32_t R;
            struct {
                vuint32_t:16;
                vuint32_t EIRE15:1;
                vuint32_t EIRE14:1;
                vuint32_t EIRE13:1;
                vuint32_t EIRE12:1;
                vuint32_t EIRE11:1;
                vuint32_t EIRE10:1;
                vuint32_t EIRE9:1;
                vuint32_t EIRE8:1;
                vuint32_t EIRE7:1;
                vuint32_t EIRE6:1;
                vuint32_t EIRE5:1;
                vuint32_t EIRE4:1;
                vuint32_t EIRE3:1;
                vuint32_t EIRE2:1;
                vuint32_t EIRE1:1;
                vuint32_t EIRE0:1;
            } B;
        } DIRER;

        union {                 /* DMA/Interrupt Select Register */
            vuint32_t R;
            struct {
                vuint32_t:28;
                vuint32_t DIRS3:1;
                vuint32_t DIRS2:1;
                vuint32_t DIRS1:1;
                vuint32_t DIRS0:1;
            } B;
        } DIRSR;

        union {                 /* Overrun Status Register */
            vuint32_t R;
            struct {
                vuint32_t:16;
                vuint32_t OVF15:1;
                vuint32_t OVF14:1;
                vuint32_t OVF13:1;
                vuint32_t OVF12:1;
                vuint32_t OVF11:1;
                vuint32_t OVF10:1;
                vuint32_t OVF9:1;
                vuint32_t OVF8:1;
                vuint32_t OVF7:1;
                vuint32_t OVF6:1;
                vuint32_t OVF5:1;
                vuint32_t OVF4:1;
                vuint32_t OVF3:1;
                vuint32_t OVF2:1;
                vuint32_t OVF1:1;
                vuint32_t OVF0:1;
            } B;
        } OSR;

        union {                 /* Overrun Request Enable Register */
            vuint32_t R;
            struct {
                vuint32_t:16;
                vuint32_t ORE15:1;
                vuint32_t ORE14:1;
                vuint32_t ORE13:1;
                vuint32_t ORE12:1;
                vuint32_t ORE11:1;
                vuint32_t ORE10:1;
                vuint32_t ORE9:1;
                vuint32_t ORE8:1;
                vuint32_t ORE7:1;
                vuint32_t ORE6:1;
                vuint32_t ORE5:1;
                vuint32_t ORE4:1;
                vuint32_t ORE3:1;
                vuint32_t ORE2:1;
                vuint32_t ORE1:1;
                vuint32_t ORE0:1;
            } B;
        } ORER;

        union {                 /* External IRQ Rising-Edge Event Enable Register */
            vuint32_t R;
            struct {
                vuint32_t:16;
                vuint32_t IREE15:1;
                vuint32_t IREE14:1;
                vuint32_t IREE13:1;
                vuint32_t IREE12:1;
                vuint32_t IREE11:1;
                vuint32_t IREE10:1;
                vuint32_t IREE9:1;
                vuint32_t IREE8:1;
                vuint32_t IREE7:1;
                vuint32_t IREE6:1;
                vuint32_t IREE5:1;
                vuint32_t IREE4:1;
                vuint32_t IREE3:1;
                vuint32_t IREE2:1;
                vuint32_t IREE1:1;
                vuint32_t IREE0:1;
            } B;
        } IREER;

        union {                 /* External IRQ Falling-Edge Event Enable Register */
            vuint32_t R;
            struct {
                vuint32_t:16;
                vuint32_t IFEE15:1;
                vuint32_t IFEE14:1;
                vuint32_t IFEE13:1;
                vuint32_t IFEE12:1;
                vuint32_t IFEE11:1;
                vuint32_t IFEE10:1;
                vuint32_t IFEE9:1;
                vuint32_t IFEE8:1;
                vuint32_t IFEE7:1;
                vuint32_t IFEE6:1;
                vuint32_t IFEE5:1;
                vuint32_t IFEE4:1;
                vuint32_t IFEE3:1;
                vuint32_t IFEE2:1;
                vuint32_t IFEE1:1;
                vuint32_t IFEE0:1;
            } B;
        } IFEER;

        union {                 /* External IRQ Digital Filter Register */
            vuint32_t R;
            struct {
                vuint32_t:28;
                vuint32_t DFL:4;
            } B;
        } IDFR;

        int32_t SIU_reserved1[3];

        union {                 /* Pad Configuration Registers */
            vuint16_t R;
            struct {
                vuint16_t:3;
                vuint16_t PA:3;
                vuint16_t OBE:1;
                vuint16_t IBE:1;
                vuint16_t DSC:2;
                vuint16_t ODE:1;
                vuint16_t HYS:1;
                vuint16_t SRC:2;
                vuint16_t WPE:1;
                vuint16_t WPS:1;
            } B;
        } PCR[512];

        int16_t SIU_reserved_0[224];

        union {                 /* GPIO Pin Data Output Registers */
            vuint8_t R;
            struct {
                vuint8_t:7;
                vuint8_t PDO:1;
            } B;
        } GPDO[256];

        int32_t SIU_reserved_3[64];

        union {                 /* GPIO Pin Data Input Registers */
            vuint8_t R;
            struct {
                vuint8_t:7;
                vuint8_t PDI:1;
            } B;
        } GPDI[256];

        union {                 /* IMUX Register */
            vuint32_t R;
            struct {
                vuint32_t TSEL5:2;
                vuint32_t TSEL4:2;
                vuint32_t TSEL3:2;
                vuint32_t TSEL2:2;
                vuint32_t TSEL1:2;
                vuint32_t TSEL0:2;
                  vuint32_t:20;
            } B;
        } ETISR;

        union {                 /* IMUX Register */
            vuint32_t R;
            struct {
                vuint32_t ESEL15:2;
                vuint32_t ESEL14:2;
                vuint32_t ESEL13:2;
                vuint32_t ESEL12:2;
                vuint32_t ESEL11:2;
                vuint32_t ESEL10:2;
                vuint32_t ESEL9:2;
                vuint32_t ESEL8:2;
                vuint32_t ESEL7:2;
                vuint32_t ESEL6:2;
                vuint32_t ESEL5:2;
                vuint32_t ESEL4:2;
                vuint32_t ESEL3:2;
                vuint32_t ESEL2:2;
                vuint32_t ESEL1:2;
                vuint32_t ESEL0:2;
            } B;
        } EIISR;

        union {                 /* IMUX Register */
            vuint32_t R;
            struct {
                vuint32_t SINSELA:2;
                vuint32_t SSSELA:2;
                vuint32_t SCKSELA:2;
                vuint32_t TRIGSELA:2;
                vuint32_t SINSELB:2;
                vuint32_t SSSELB:2;
                vuint32_t SCKSELB:2;
                vuint32_t TRIGSELB:2;
                vuint32_t SINSELC:2;
                vuint32_t SSSELC:2;
                vuint32_t SCKSELC:2;
                vuint32_t TRIGSELC:2;
                vuint32_t SINSELD:2;
                vuint32_t SSSELD:2;
                vuint32_t SCKSELD:2;
                vuint32_t TRIGSELD:2;
            } B;
        } DISR;

        int32_t SIU_reserved2[29];

        union {                 /* Chip Configuration Register Register */
            vuint32_t R;
            struct {
                vuint32_t:14;
                vuint32_t MATCH:1;
                vuint32_t DISNEX:1;
                  vuint32_t:16;
            } B;
        } CCR;

        union {                 /* External Clock Configuration Register Register */
            vuint32_t R;
            struct {
                vuint32_t:18;
                vuint32_t ENGDIV:6;
                  vuint32_t:4;
                vuint32_t EBTS:1;
                  vuint32_t:1;
                vuint32_t EBDF:2;
            } B;
        } ECCR;

        union {
            vuint32_t R;
        } CARH;

        union {
            vuint32_t R;
        } CARL;

        union {
            vuint32_t R;
        } CBRH;

        union {
            vuint32_t R;
        } CBRL;

    };
/****************************************************************************/
/*                          MODULE : EMIOS                                  */
/****************************************************************************/
    struct EMIOS_tag {
        union {
            vuint32_t R;
            struct {
                vuint32_t:1;
                vuint32_t MDIS:1;
                vuint32_t FRZ:1;
                vuint32_t GTBE:1;
                vuint32_t ETB:1;
                vuint32_t GPREN:1;
                  vuint32_t:6;
                vuint32_t SRV:4;
                vuint32_t GPRE:8;
                  vuint32_t:8;
            } B;
        } MCR;                  /* Module Configuration Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t:8;
                vuint32_t F23:1;
                vuint32_t F22:1;
                vuint32_t F21:1;
                vuint32_t F20:1;
                vuint32_t F19:1;
                vuint32_t F18:1;
                vuint32_t F17:1;
                vuint32_t F16:1;
                vuint32_t F15:1;
                vuint32_t F14:1;
                vuint32_t F13:1;
                vuint32_t F12:1;
                vuint32_t F11:1;
                vuint32_t F10:1;
                vuint32_t F9:1;
                vuint32_t F8:1;
                vuint32_t F7:1;
                vuint32_t F6:1;
                vuint32_t F5:1;
                vuint32_t F4:1;
                vuint32_t F3:1;
                vuint32_t F2:1;
                vuint32_t F1:1;
                vuint32_t F0:1;
            } B;
        } GFR;                  /* Global FLAG Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t:8;
                vuint32_t OU23:1;
                vuint32_t OU22:1;
                vuint32_t OU21:1;
                vuint32_t OU20:1;
                vuint32_t OU19:1;
                vuint32_t OU18:1;
                vuint32_t OU17:1;
                vuint32_t OU16:1;
                vuint32_t OU15:1;
                vuint32_t OU14:1;
                vuint32_t OU13:1;
                vuint32_t OU12:1;
                vuint32_t OU11:1;
                vuint32_t OU10:1;
                vuint32_t OU9:1;
                vuint32_t OU8:1;
                vuint32_t OU7:1;
                vuint32_t OU6:1;
                vuint32_t OU5:1;
                vuint32_t OU4:1;
                vuint32_t OU3:1;
                vuint32_t OU2:1;
                vuint32_t OU1:1;
                vuint32_t OU0:1;
            } B;
        } OUDR;                 /* Output Update Disable Register */

        uint32_t emios_reserved[5];

        struct {
            union {
                vuint32_t R;    /* Channel A Data Register */
            } CADR;

            union {
                vuint32_t R;    /* Channel B Data Register */
            } CBDR;

            union {
                vuint32_t R;    /* Channel Counter Register */
            } CCNTR;

            union {
                vuint32_t R;
                struct {
                    vuint32_t FREN:1;
                    vuint32_t ODIS:1;
                    vuint32_t ODISSL:2;
                    vuint32_t UCPRE:2;
                    vuint32_t UCPREN:1;
                    vuint32_t DMA:1;
                      vuint32_t:1;
                    vuint32_t IF:4;
                    vuint32_t FCK:1;
                    vuint32_t FEN:1;
                      vuint32_t:3;
                    vuint32_t FORCMA:1;
                    vuint32_t FORCMB:1;
                      vuint32_t:1;
                    vuint32_t BSL:2;
                    vuint32_t EDSEL:1;
                    vuint32_t EDPOL:1;
                    vuint32_t MODE:7;
                } B;
            } CCR;              /* Channel Control Register */

            union {
                vuint32_t R;
                struct {
                    vuint32_t OVR:1;
                      vuint32_t:15;
                    vuint32_t OVFL:1;
                      vuint32_t:12;
                    vuint32_t UCIN:1;
                    vuint32_t UCOUT:1;
                    vuint32_t FLAG:1;
                } B;
            } CSR;              /* Channel Status Register */

            uint32_t emios_channel_reserved[3];
        } CH[24];

    };
/****************************************************************************/
/*                              MODULE :ETPU                                */
/****************************************************************************/

/***************************Configuration Registers**************************/

    struct ETPU_tag {
        union {                 /* MODULE CONFIGURATION REGISTER */
            vuint32_t R;
            struct {
                vuint32_t GEC:1;        /* Global Exception Clear */
                  vuint32_t:3;
                vuint32_t MGE1:1;       /* Microcode Global Exception-ETPU_A */

                vuint32_t MGE2:1;       /* Microcode Global Exception-ETPU_B */

                vuint32_t ILF1:1;       /* Illegal Instruction Flag-ETPU_A */

                vuint32_t ILF2:1;       /* Illegal Instruction Flag-ETPU_B */

                  vuint32_t:3;
                vuint32_t SCMSIZE:5;    /* Shared Code Memory size */
                  vuint32_t:5;
                vuint32_t SCMMISF:1;    /* SCM MISC Flag */
                vuint32_t SCMMISEN:1;   /* SCM MISC Enable */
                  vuint32_t:2;
                vuint32_t VIS:1;        /* SCM Visability */
                  vuint32_t:5;
                vuint32_t GTBE:1;       /* Global Time Base Enable */
            } B;
        } MCR;

        union {                 /* COHERENT DUAL-PARAMETER CONTROL */
            vuint32_t R;
            struct {
                vuint32_t STS:1;        /* Start Status bit */
                vuint32_t CTBASE:5;     /* Channel Transfer Base */
                vuint32_t PBASE:10;     /* Parameter Buffer Base Address */
                vuint32_t PWIDTH:1;     /* Parameter Width */
                vuint32_t PARAM0:7;     /* Channel Parameter 0 */
                vuint32_t WR:1;
                vuint32_t PARAM1:7;     /* Channel Parameter 1 */
            } B;
        } CDCR;

        uint32_t etpu_reserved1;

        union {                 /* MISC Compare Register */
            uint32_t R;
        } MISCCMPR;

        union {                 /* SCM off-range Date Register */
            uint32_t R;
        } SCMOFFDATAR;

        union {                 /* ETPU_A Configuration Register */
            vuint32_t R;
            struct {
                vuint32_t FEND:1;       /* Force END */
                vuint32_t MDIS:1;       /* Low power Stop */
                  vuint32_t:1;
                vuint32_t STF:1;        /* Stop Flag */
                  vuint32_t:4;
                vuint32_t HLTF:1;       /* Halt Mode Flag */
                  vuint32_t:4;
                vuint32_t FPSCK:3;      /* Filter Prescaler Clock Control */
                vuint32_t CDFC:2;
                  vuint32_t:9;
                vuint32_t ETB:5;        /* Entry Table Base */
            } B;
        } ECR_A;

        union {                 /* ETPU_B Configuration Register */
            vuint32_t R;
            struct {
                vuint32_t FEND:1;       /* Force END */
                vuint32_t MDIS:1;       /* Low power Stop */
                  vuint32_t:1;
                vuint32_t STF:1;        /* Stop Flag */
                  vuint32_t:4;
                vuint32_t HLTF:1;       /* Halt Mode Flag */
                  vuint32_t:4;
                vuint32_t FPSCK:3;      /* Filter Prescaler Clock Control */
                vuint32_t CDFC:2;
                  vuint32_t:9;
                vuint32_t ETB:5;        /* Entry Table Base */
            } B;
        } ECR_B;

        uint32_t etpu_reserved4;

        union {                 /* ETPU_A Timebase Configuration Register */
            uint32_t R;
            struct {
                uint32_t TCR2CTL:3;     /* TCR2 Clock/Gate Control */
                uint32_t TCRCF:2;       /* TCRCLK Signal Filter Control */
                  uint32_t:1;
                uint32_t AM:1;  /* Angle Mode */
                  uint32_t:3;
                uint32_t TCR2P:6;       /* TCR2 Prescaler Control */
                uint32_t TCR1CTL:2;     /* TCR1 Clock/Gate Control */
                  uint32_t:6;
                uint32_t TCR1P:8;       /* TCR1 Prescaler Control */
            } B;
        } TBCR_A;

        union {                 /* ETPU_A TCR1 Visibility Register */
            vuint32_t R;
        } TB1R_A;

        union {                 /* ETPU_A TCR2 Visibility Register */
            vuint32_t R;
        } TB2R_A;

        union {                 /* ETPU_A STAC Configuration Register */
            vuint32_t R;
            struct {
                vuint32_t REN1:1;       /* Resource Enable TCR1 */
                vuint32_t RSC1:1;       /* Resource Control TCR1 */
                  vuint32_t:2;
                vuint32_t SERVER_ID1:4;
                  vuint32_t:4;
                vuint32_t SRV1:4;       /* Resource Server Slot */
                vuint32_t REN2:1;       /* Resource Enable TCR2 */
                vuint32_t RSC2:1;       /* Resource Control TCR2 */
                  vuint32_t:2;
                vuint32_t SERVER_ID2:4;
                  vuint32_t:4;
                vuint32_t SRV2:4;       /* Resource Server Slot */
            } B;
        } REDCR_A;

        uint32_t etpu_reserved5[4];

        union {                 /* ETPU_B Timebase Configuration Register */
            uint32_t R;
            struct {
                uint32_t TCR2CTL:3;     /* TCR2 Clock/Gate Control */
                uint32_t TCRCF:2;       /* TCRCLK Signal Filter Control */
                  uint32_t:1;
                uint32_t AM:1;  /* Angle Mode */
                  uint32_t:3;
                uint32_t TCR2P:6;       /* TCR2 Prescaler Control */
                uint32_t TCR1CTL:2;     /* TCR1 Clock/Gate Control */
                  uint32_t:6;
                uint32_t TCR1P:8;       /* TCR1 Prescaler Control */
            } B;
        } TBCR_B;

        union {                 /* ETPU_B TCR1 Visibility Register */
            vuint32_t R;
        } TB1R_B;

        union {                 /* ETPU_B TCR2 Visibility Register */
            vuint32_t R;
        } TB2R_B;

        union {                 /* ETPU_B STAC Configuration Register */
            vuint32_t R;
            struct {
                vuint32_t REN1:1;       /* Resource Enable TCR1 */
                vuint32_t RSC1:1;       /* Resource Control TCR1 */
                  vuint32_t:2;
                vuint32_t SERVER_ID1:4;
                  vuint32_t:4;
                vuint32_t SRV1:4;       /* Resource Server Slot */
                vuint32_t REN2:1;       /* Resource Enable TCR2 */
                vuint32_t RSC2:1;       /* Resource Control TCR2 */
                  vuint32_t:2;
                vuint32_t SERVER_ID2:4;
                  vuint32_t:4;
                vuint32_t SRV2:4;       /* Resource Server Slot */
            } B;
        } REDCR_B;

        uint32_t etpu_reserved7[108];

/*****************************Status and Control Registers**************************/

        union {                 /* ETPU_A Channel Interrut Status */
            vuint32_t R;
            struct {
                vuint32_t CIS31:1;      /* Channel 31 Interrut Status */
                vuint32_t CIS30:1;      /* Channel 30 Interrut Status */
                vuint32_t CIS29:1;      /* Channel 29 Interrut Status */
                vuint32_t CIS28:1;      /* Channel 28 Interrut Status */
                vuint32_t CIS27:1;      /* Channel 27 Interrut Status */
                vuint32_t CIS26:1;      /* Channel 26 Interrut Status */
                vuint32_t CIS25:1;      /* Channel 25 Interrut Status */
                vuint32_t CIS24:1;      /* Channel 24 Interrut Status */
                vuint32_t CIS23:1;      /* Channel 23 Interrut Status */
                vuint32_t CIS22:1;      /* Channel 22 Interrut Status */
                vuint32_t CIS21:1;      /* Channel 21 Interrut Status */
                vuint32_t CIS20:1;      /* Channel 20 Interrut Status */
                vuint32_t CIS19:1;      /* Channel 19 Interrut Status */
                vuint32_t CIS18:1;      /* Channel 18 Interrut Status */
                vuint32_t CIS17:1;      /* Channel 17 Interrut Status */
                vuint32_t CIS16:1;      /* Channel 16 Interrut Status */
                vuint32_t CIS15:1;      /* Channel 15 Interrut Status */
                vuint32_t CIS14:1;      /* Channel 14 Interrut Status */
                vuint32_t CIS13:1;      /* Channel 13 Interrut Status */
                vuint32_t CIS12:1;      /* Channel 12 Interrut Status */
                vuint32_t CIS11:1;      /* Channel 11 Interrut Status */
                vuint32_t CIS10:1;      /* Channel 10 Interrut Status */
                vuint32_t CIS9:1;       /* Channel 9 Interrut Status */
                vuint32_t CIS8:1;       /* Channel 8 Interrut Status */
                vuint32_t CIS7:1;       /* Channel 7 Interrut Status */
                vuint32_t CIS6:1;       /* Channel 6 Interrut Status */
                vuint32_t CIS5:1;       /* Channel 5 Interrut Status */
                vuint32_t CIS4:1;       /* Channel 4 Interrut Status */
                vuint32_t CIS3:1;       /* Channel 3 Interrut Status */
                vuint32_t CIS2:1;       /* Channel 2 Interrut Status */
                vuint32_t CIS1:1;       /* Channel 1 Interrut Status */
                vuint32_t CIS0:1;       /* Channel 0 Interrut Status */
            } B;
        } CISR_A;

        union {                 /* ETPU_B Channel Interruput Status */
            vuint32_t R;
            struct {
                vuint32_t CIS31:1;      /* Channel 31 Interrut Status */
                vuint32_t CIS30:1;      /* Channel 30 Interrut Status */
                vuint32_t CIS29:1;      /* Channel 29 Interrut Status */
                vuint32_t CIS28:1;      /* Channel 28 Interrut Status */
                vuint32_t CIS27:1;      /* Channel 27 Interrut Status */
                vuint32_t CIS26:1;      /* Channel 26 Interrut Status */
                vuint32_t CIS25:1;      /* Channel 25 Interrut Status */
                vuint32_t CIS24:1;      /* Channel 24 Interrut Status */
                vuint32_t CIS23:1;      /* Channel 23 Interrut Status */
                vuint32_t CIS22:1;      /* Channel 22 Interrut Status */
                vuint32_t CIS21:1;      /* Channel 21 Interrut Status */
                vuint32_t CIS20:1;      /* Channel 20 Interrut Status */
                vuint32_t CIS19:1;      /* Channel 19 Interrut Status */
                vuint32_t CIS18:1;      /* Channel 18 Interrut Status */
                vuint32_t CIS17:1;      /* Channel 17 Interrut Status */
                vuint32_t CIS16:1;      /* Channel 16 Interrut Status */
                vuint32_t CIS15:1;      /* Channel 15 Interrut Status */
                vuint32_t CIS14:1;      /* Channel 14 Interrut Status */
                vuint32_t CIS13:1;      /* Channel 13 Interrut Status */
                vuint32_t CIS12:1;      /* Channel 12 Interrut Status */
                vuint32_t CIS11:1;      /* Channel 11 Interrut Status */
                vuint32_t CIS10:1;      /* Channel 10 Interrut Status */
                vuint32_t CIS9:1;       /* Channel 9 Interrut Status */
                vuint32_t CIS8:1;       /* Channel 8 Interrut Status */
                vuint32_t CIS7:1;       /* Channel 7 Interrut Status */
                vuint32_t CIS6:1;       /* Channel 6 Interrut Status */
                vuint32_t CIS5:1;       /* Channel 5 Interrut Status */
                vuint32_t CIS4:1;       /* Channel 4 Interrut Status */
                vuint32_t CIS3:1;       /* Channel 3 Interrut Status */
                vuint32_t CIS2:1;       /* Channel 2 Interrut Status */
                vuint32_t CIS1:1;       /* Channel 1 Interrupt Status */
                vuint32_t CIS0:1;       /* Channel 0 Interrupt Status */
            } B;
        } CISR_B;

        uint32_t etpu_reserved9[2];

        union {                 /* ETPU_A Data Transfer Request Status */
            vuint32_t R;
            struct {
                vuint32_t DTRS31:1;     /* Channel 31 Data Transfer Request Status */
                vuint32_t DTRS30:1;     /* Channel 30 Data Transfer Request Status */
                vuint32_t DTRS29:1;     /* Channel 29 Data Transfer Request Status */
                vuint32_t DTRS28:1;     /* Channel 28 Data Transfer Request Status */
                vuint32_t DTRS27:1;     /* Channel 27 Data Transfer Request Status */
                vuint32_t DTRS26:1;     /* Channel 26 Data Transfer Request Status */
                vuint32_t DTRS25:1;     /* Channel 25 Data Transfer Request Status */
                vuint32_t DTRS24:1;     /* Channel 24 Data Transfer Request Status */
                vuint32_t DTRS23:1;     /* Channel 23 Data Transfer Request Status */
                vuint32_t DTRS22:1;     /* Channel 22 Data Transfer Request Status */
                vuint32_t DTRS21:1;     /* Channel 21 Data Transfer Request Status */
                vuint32_t DTRS20:1;     /* Channel 20 Data Transfer Request Status */
                vuint32_t DTRS19:1;     /* Channel 19 Data Transfer Request Status */
                vuint32_t DTRS18:1;     /* Channel 18 Data Transfer Request Status */
                vuint32_t DTRS17:1;     /* Channel 17 Data Transfer Request Status */
                vuint32_t DTRS16:1;     /* Channel 16 Data Transfer Request Status */
                vuint32_t DTRS15:1;     /* Channel 15 Data Transfer Request Status */
                vuint32_t DTRS14:1;     /* Channel 14 Data Transfer Request Status */
                vuint32_t DTRS13:1;     /* Channel 13 Data Transfer Request Status */
                vuint32_t DTRS12:1;     /* Channel 12 Data Transfer Request Status */
                vuint32_t DTRS11:1;     /* Channel 11 Data Transfer Request Status */
                vuint32_t DTRS10:1;     /* Channel 10 Data Transfer Request Status */
                vuint32_t DTRS9:1;      /* Channel 9 Data Transfer Request Status */
                vuint32_t DTRS8:1;      /* Channel 8 Data Transfer Request Status */
                vuint32_t DTRS7:1;      /* Channel 7 Data Transfer Request Status */
                vuint32_t DTRS6:1;      /* Channel 6 Data Transfer Request Status */
                vuint32_t DTRS5:1;      /* Channel 5 Data Transfer Request Status */
                vuint32_t DTRS4:1;      /* Channel 4 Data Transfer Request Status */
                vuint32_t DTRS3:1;      /* Channel 3 Data Transfer Request Status */
                vuint32_t DTRS2:1;      /* Channel 2 Data Transfer Request Status */
                vuint32_t DTRS1:1;      /* Channel 1 Data Transfer Request Status */
                vuint32_t DTRS0:1;      /* Channel 0 Data Transfer Request Status */
            } B;
        } CDTRSR_A;

        union {                 /* ETPU_B Data Transfer Request Status */
            vuint32_t R;
            struct {
                vuint32_t DTRS31:1;     /* Channel 31 Data Transfer Request Status */
                vuint32_t DTRS30:1;     /* Channel 30 Data Transfer Request Status */
                vuint32_t DTRS29:1;     /* Channel 29 Data Transfer Request Status */
                vuint32_t DTRS28:1;     /* Channel 28 Data Transfer Request Status */
                vuint32_t DTRS27:1;     /* Channel 27 Data Transfer Request Status */
                vuint32_t DTRS26:1;     /* Channel 26 Data Transfer Request Status */
                vuint32_t DTRS25:1;     /* Channel 25 Data Transfer Request Status */
                vuint32_t DTRS24:1;     /* Channel 24 Data Transfer Request Status */
                vuint32_t DTRS23:1;     /* Channel 23 Data Transfer Request Status */
                vuint32_t DTRS22:1;     /* Channel 22 Data Transfer Request Status */
                vuint32_t DTRS21:1;     /* Channel 21 Data Transfer Request Status */
                vuint32_t DTRS20:1;     /* Channel 20 Data Transfer Request Status */
                vuint32_t DTRS19:1;     /* Channel 19 Data Transfer Request Status */
                vuint32_t DTRS18:1;     /* Channel 18 Data Transfer Request Status */
                vuint32_t DTRS17:1;     /* Channel 17 Data Transfer Request Status */
                vuint32_t DTRS16:1;     /* Channel 16 Data Transfer Request Status */
                vuint32_t DTRS15:1;     /* Channel 15 Data Transfer Request Status */
                vuint32_t DTRS14:1;     /* Channel 14 Data Transfer Request Status */
                vuint32_t DTRS13:1;     /* Channel 13 Data Transfer Request Status */
                vuint32_t DTRS12:1;     /* Channel 12 Data Transfer Request Status */
                vuint32_t DTRS11:1;     /* Channel 11 Data Transfer Request Status */
                vuint32_t DTRS10:1;     /* Channel 10 Data Transfer Request Status */
                vuint32_t DTRS9:1;      /* Channel 9 Data Transfer Request Status */
                vuint32_t DTRS8:1;      /* Channel 8 Data Transfer Request Status */
                vuint32_t DTRS7:1;      /* Channel 7 Data Transfer Request Status */
                vuint32_t DTRS6:1;      /* Channel 6 Data Transfer Request Status */
                vuint32_t DTRS5:1;      /* Channel 5 Data Transfer Request Status */
                vuint32_t DTRS4:1;      /* Channel 4 Data Transfer Request Status */
                vuint32_t DTRS3:1;      /* Channel 3 Data Transfer Request Status */
                vuint32_t DTRS2:1;      /* Channel 2 Data Transfer Request Status */
                vuint32_t DTRS1:1;      /* Channel 1 Data Transfer Request Status */
                vuint32_t DTRS0:1;      /* Channel 0 Data Transfer Request Status */
            } B;
        } CDTRSR_B;

        uint32_t etpu_reserved11[2];

        union {                 /* ETPU_A Interruput Overflow Status */
            vuint32_t R;
            struct {
                vuint32_t CIOS31:1;     /* Channel 31 Interruput Overflow Status */
                vuint32_t CIOS30:1;     /* Channel 30 Interruput Overflow Status */
                vuint32_t CIOS29:1;     /* Channel 29 Interruput Overflow Status */
                vuint32_t CIOS28:1;     /* Channel 28 Interruput Overflow Status */
                vuint32_t CIOS27:1;     /* Channel 27 Interruput Overflow Status */
                vuint32_t CIOS26:1;     /* Channel 26 Interruput Overflow Status */
                vuint32_t CIOS25:1;     /* Channel 25 Interruput Overflow Status */
                vuint32_t CIOS24:1;     /* Channel 24 Interruput Overflow Status */
                vuint32_t CIOS23:1;     /* Channel 23 Interruput Overflow Status */
                vuint32_t CIOS22:1;     /* Channel 22 Interruput Overflow Status */
                vuint32_t CIOS21:1;     /* Channel 21 Interruput Overflow Status */
                vuint32_t CIOS20:1;     /* Channel 20 Interruput Overflow Status */
                vuint32_t CIOS19:1;     /* Channel 19 Interruput Overflow Status */
                vuint32_t CIOS18:1;     /* Channel 18 Interruput Overflow Status */
                vuint32_t CIOS17:1;     /* Channel 17 Interruput Overflow Status */
                vuint32_t CIOS16:1;     /* Channel 16 Interruput Overflow Status */
                vuint32_t CIOS15:1;     /* Channel 15 Interruput Overflow Status */
                vuint32_t CIOS14:1;     /* Channel 14 Interruput Overflow Status */
                vuint32_t CIOS13:1;     /* Channel 13 Interruput Overflow Status */
                vuint32_t CIOS12:1;     /* Channel 12 Interruput Overflow Status */
                vuint32_t CIOS11:1;     /* Channel 11 Interruput Overflow Status */
                vuint32_t CIOS10:1;     /* Channel 10 Interruput Overflow Status */
                vuint32_t CIOS9:1;      /* Channel 9 Interruput Overflow Status */
                vuint32_t CIOS8:1;      /* Channel 8 Interruput Overflow Status */
                vuint32_t CIOS7:1;      /* Channel 7 Interruput Overflow Status */
                vuint32_t CIOS6:1;      /* Channel 6 Interruput Overflow Status */
                vuint32_t CIOS5:1;      /* Channel 5 Interruput Overflow Status */
                vuint32_t CIOS4:1;      /* Channel 4 Interruput Overflow Status */
                vuint32_t CIOS3:1;      /* Channel 3 Interruput Overflow Status */
                vuint32_t CIOS2:1;      /* Channel 2 Interruput Overflow Status */
                vuint32_t CIOS1:1;      /* Channel 1 Interruput Overflow Status */
                vuint32_t CIOS0:1;      /* Channel 0 Interruput Overflow Status */
            } B;
        } CIOSR_A;

        union {                 /* ETPU_B Interruput Overflow Status */
            vuint32_t R;
            struct {
                vuint32_t CIOS31:1;     /* Channel 31 Interruput Overflow Status */
                vuint32_t CIOS30:1;     /* Channel 30 Interruput Overflow Status */
                vuint32_t CIOS29:1;     /* Channel 29 Interruput Overflow Status */
                vuint32_t CIOS28:1;     /* Channel 28 Interruput Overflow Status */
                vuint32_t CIOS27:1;     /* Channel 27 Interruput Overflow Status */
                vuint32_t CIOS26:1;     /* Channel 26 Interruput Overflow Status */
                vuint32_t CIOS25:1;     /* Channel 25 Interruput Overflow Status */
                vuint32_t CIOS24:1;     /* Channel 24 Interruput Overflow Status */
                vuint32_t CIOS23:1;     /* Channel 23 Interruput Overflow Status */
                vuint32_t CIOS22:1;     /* Channel 22 Interruput Overflow Status */
                vuint32_t CIOS21:1;     /* Channel 21 Interruput Overflow Status */
                vuint32_t CIOS20:1;     /* Channel 20 Interruput Overflow Status */
                vuint32_t CIOS19:1;     /* Channel 19 Interruput Overflow Status */
                vuint32_t CIOS18:1;     /* Channel 18 Interruput Overflow Status */
                vuint32_t CIOS17:1;     /* Channel 17 Interruput Overflow Status */
                vuint32_t CIOS16:1;     /* Channel 16 Interruput Overflow Status */
                vuint32_t CIOS15:1;     /* Channel 15 Interruput Overflow Status */
                vuint32_t CIOS14:1;     /* Channel 14 Interruput Overflow Status */
                vuint32_t CIOS13:1;     /* Channel 13 Interruput Overflow Status */
                vuint32_t CIOS12:1;     /* Channel 12 Interruput Overflow Status */
                vuint32_t CIOS11:1;     /* Channel 11 Interruput Overflow Status */
                vuint32_t CIOS10:1;     /* Channel 10 Interruput Overflow Status */
                vuint32_t CIOS9:1;      /* Channel 9 Interruput Overflow Status */
                vuint32_t CIOS8:1;      /* Channel 8 Interruput Overflow Status */
                vuint32_t CIOS7:1;      /* Channel 7 Interruput Overflow Status */
                vuint32_t CIOS6:1;      /* Channel 6 Interruput Overflow Status */
                vuint32_t CIOS5:1;      /* Channel 5 Interruput Overflow Status */
                vuint32_t CIOS4:1;      /* Channel 4 Interruput Overflow Status */
                vuint32_t CIOS3:1;      /* Channel 3 Interruput Overflow Status */
                vuint32_t CIOS2:1;      /* Channel 2 Interruput Overflow Status */
                vuint32_t CIOS1:1;      /* Channel 1 Interruput Overflow Status */
                vuint32_t CIOS0:1;      /* Channel 0 Interruput Overflow Status */
            } B;
        } CIOSR_B;

        uint32_t etpu_reserved13[2];

        union {                 /* ETPU_A Data Transfer Overflow Status */
            vuint32_t R;
            struct {
                vuint32_t DTROS31:1;    /* Channel 31 Data Transfer Overflow Status */
                vuint32_t DTROS30:1;    /* Channel 30 Data Transfer Overflow Status */
                vuint32_t DTROS29:1;    /* Channel 29 Data Transfer Overflow Status */
                vuint32_t DTROS28:1;    /* Channel 28 Data Transfer Overflow Status */
                vuint32_t DTROS27:1;    /* Channel 27 Data Transfer Overflow Status */
                vuint32_t DTROS26:1;    /* Channel 26 Data Transfer Overflow Status */
                vuint32_t DTROS25:1;    /* Channel 25 Data Transfer Overflow Status */
                vuint32_t DTROS24:1;    /* Channel 24 Data Transfer Overflow Status */
                vuint32_t DTROS23:1;    /* Channel 23 Data Transfer Overflow Status */
                vuint32_t DTROS22:1;    /* Channel 22 Data Transfer Overflow Status */
                vuint32_t DTROS21:1;    /* Channel 21 Data Transfer Overflow Status */
                vuint32_t DTROS20:1;    /* Channel 20 Data Transfer Overflow Status */
                vuint32_t DTROS19:1;    /* Channel 19 Data Transfer Overflow Status */
                vuint32_t DTROS18:1;    /* Channel 18 Data Transfer Overflow Status */
                vuint32_t DTROS17:1;    /* Channel 17 Data Transfer Overflow Status */
                vuint32_t DTROS16:1;    /* Channel 16 Data Transfer Overflow Status */
                vuint32_t DTROS15:1;    /* Channel 15 Data Transfer Overflow Status */
                vuint32_t DTROS14:1;    /* Channel 14 Data Transfer Overflow Status */
                vuint32_t DTROS13:1;    /* Channel 13 Data Transfer Overflow Status */
                vuint32_t DTROS12:1;    /* Channel 12 Data Transfer Overflow Status */
                vuint32_t DTROS11:1;    /* Channel 11 Data Transfer Overflow Status */
                vuint32_t DTROS10:1;    /* Channel 10 Data Transfer Overflow Status */
                vuint32_t DTROS9:1;     /* Channel 9 Data Transfer Overflow Status */
                vuint32_t DTROS8:1;     /* Channel 8 Data Transfer Overflow Status */
                vuint32_t DTROS7:1;     /* Channel 7 Data Transfer Overflow Status */
                vuint32_t DTROS6:1;     /* Channel 6 Data Transfer Overflow Status */
                vuint32_t DTROS5:1;     /* Channel 5 Data Transfer Overflow Status */
                vuint32_t DTROS4:1;     /* Channel 4 Data Transfer Overflow Status */
                vuint32_t DTROS3:1;     /* Channel 3 Data Transfer Overflow Status */
                vuint32_t DTROS2:1;     /* Channel 2 Data Transfer Overflow Status */
                vuint32_t DTROS1:1;     /* Channel 1 Data Transfer Overflow Status */
                vuint32_t DTROS0:1;     /* Channel 0 Data Transfer Overflow Status */
            } B;
        } CDTROSR_A;

        union {                 /* ETPU_B Data Transfer Overflow Status */
            vuint32_t R;
            struct {
                vuint32_t DTROS31:1;    /* Channel 31 Data Transfer Overflow Status */
                vuint32_t DTROS30:1;    /* Channel 30 Data Transfer Overflow Status */
                vuint32_t DTROS29:1;    /* Channel 29 Data Transfer Overflow Status */
                vuint32_t DTROS28:1;    /* Channel 28 Data Transfer Overflow Status */
                vuint32_t DTROS27:1;    /* Channel 27 Data Transfer Overflow Status */
                vuint32_t DTROS26:1;    /* Channel 26 Data Transfer Overflow Status */
                vuint32_t DTROS25:1;    /* Channel 25 Data Transfer Overflow Status */
                vuint32_t DTROS24:1;    /* Channel 24 Data Transfer Overflow Status */
                vuint32_t DTROS23:1;    /* Channel 23 Data Transfer Overflow Status */
                vuint32_t DTROS22:1;    /* Channel 22 Data Transfer Overflow Status */
                vuint32_t DTROS21:1;    /* Channel 21 Data Transfer Overflow Status */
                vuint32_t DTROS20:1;    /* Channel 20 Data Transfer Overflow Status */
                vuint32_t DTROS19:1;    /* Channel 19 Data Transfer Overflow Status */
                vuint32_t DTROS18:1;    /* Channel 18 Data Transfer Overflow Status */
                vuint32_t DTROS17:1;    /* Channel 17 Data Transfer Overflow Status */
                vuint32_t DTROS16:1;    /* Channel 16 Data Transfer Overflow Status */
                vuint32_t DTROS15:1;    /* Channel 15 Data Transfer Overflow Status */
                vuint32_t DTROS14:1;    /* Channel 14 Data Transfer Overflow Status */
                vuint32_t DTROS13:1;    /* Channel 13 Data Transfer Overflow Status */
                vuint32_t DTROS12:1;    /* Channel 12 Data Transfer Overflow Status */
                vuint32_t DTROS11:1;    /* Channel 11 Data Transfer Overflow Status */
                vuint32_t DTROS10:1;    /* Channel 10 Data Transfer Overflow Status */
                vuint32_t DTROS9:1;     /* Channel 9 Data Transfer Overflow Status */
                vuint32_t DTROS8:1;     /* Channel 8 Data Transfer Overflow Status */
                vuint32_t DTROS7:1;     /* Channel 7 Data Transfer Overflow Status */
                vuint32_t DTROS6:1;     /* Channel 6 Data Transfer Overflow Status */
                vuint32_t DTROS5:1;     /* Channel 5 Data Transfer Overflow Status */
                vuint32_t DTROS4:1;     /* Channel 4 Data Transfer Overflow Status */
                vuint32_t DTROS3:1;     /* Channel 3 Data Transfer Overflow Status */
                vuint32_t DTROS2:1;     /* Channel 2 Data Transfer Overflow Status */
                vuint32_t DTROS1:1;     /* Channel 1 Data Transfer Overflow Status */
                vuint32_t DTROS0:1;     /* Channel 0 Data Transfer Overflow Status */
            } B;
        } CDTROSR_B;

        uint32_t etpu_reserved15[2];

        union {                 /* ETPU_A Channel Interruput Enable */
            vuint32_t R;
            struct {
                vuint32_t CIE31:1;      /* Channel 31 Interruput Enable */
                vuint32_t CIE30:1;      /* Channel 30 Interruput Enable */
                vuint32_t CIE29:1;      /* Channel 29 Interruput Enable */
                vuint32_t CIE28:1;      /* Channel 28 Interruput Enable */
                vuint32_t CIE27:1;      /* Channel 27 Interruput Enable */
                vuint32_t CIE26:1;      /* Channel 26 Interruput Enable */
                vuint32_t CIE25:1;      /* Channel 25 Interruput Enable */
                vuint32_t CIE24:1;      /* Channel 24 Interruput Enable */
                vuint32_t CIE23:1;      /* Channel 23 Interruput Enable */
                vuint32_t CIE22:1;      /* Channel 22 Interruput Enable */
                vuint32_t CIE21:1;      /* Channel 21 Interruput Enable */
                vuint32_t CIE20:1;      /* Channel 20 Interruput Enable */
                vuint32_t CIE19:1;      /* Channel 19 Interruput Enable */
                vuint32_t CIE18:1;      /* Channel 18 Interruput Enable */
                vuint32_t CIE17:1;      /* Channel 17 Interruput Enable */
                vuint32_t CIE16:1;      /* Channel 16 Interruput Enable */
                vuint32_t CIE15:1;      /* Channel 15 Interruput Enable */
                vuint32_t CIE14:1;      /* Channel 14 Interruput Enable */
                vuint32_t CIE13:1;      /* Channel 13 Interruput Enable */
                vuint32_t CIE12:1;      /* Channel 12 Interruput Enable */
                vuint32_t CIE11:1;      /* Channel 11 Interruput Enable */
                vuint32_t CIE10:1;      /* Channel 10 Interruput Enable */
                vuint32_t CIE9:1;       /* Channel 9 Interruput Enable */
                vuint32_t CIE8:1;       /* Channel 8 Interruput Enable */
                vuint32_t CIE7:1;       /* Channel 7 Interruput Enable */
                vuint32_t CIE6:1;       /* Channel 6 Interruput Enable */
                vuint32_t CIE5:1;       /* Channel 5 Interruput Enable */
                vuint32_t CIE4:1;       /* Channel 4 Interruput Enable */
                vuint32_t CIE3:1;       /* Channel 3 Interruput Enable */
                vuint32_t CIE2:1;       /* Channel 2 Interruput Enable */
                vuint32_t CIE1:1;       /* Channel 1 Interruput Enable */
                vuint32_t CIE0:1;       /* Channel 0 Interruput Enable */
            } B;
        } CIER_A;

        union {                 /* ETPU_B Channel Interruput Enable */
            vuint32_t R;
            struct {
                vuint32_t CIE31:1;      /* Channel 31 Interruput Enable */
                vuint32_t CIE30:1;      /* Channel 30 Interruput Enable */
                vuint32_t CIE29:1;      /* Channel 29 Interruput Enable */
                vuint32_t CIE28:1;      /* Channel 28 Interruput Enable */
                vuint32_t CIE27:1;      /* Channel 27 Interruput Enable */
                vuint32_t CIE26:1;      /* Channel 26 Interruput Enable */
                vuint32_t CIE25:1;      /* Channel 25 Interruput Enable */
                vuint32_t CIE24:1;      /* Channel 24 Interruput Enable */
                vuint32_t CIE23:1;      /* Channel 23 Interruput Enable */
                vuint32_t CIE22:1;      /* Channel 22 Interruput Enable */
                vuint32_t CIE21:1;      /* Channel 21 Interruput Enable */
                vuint32_t CIE20:1;      /* Channel 20 Interruput Enable */
                vuint32_t CIE19:1;      /* Channel 19 Interruput Enable */
                vuint32_t CIE18:1;      /* Channel 18 Interruput Enable */
                vuint32_t CIE17:1;      /* Channel 17 Interruput Enable */
                vuint32_t CIE16:1;      /* Channel 16 Interruput Enable */
                vuint32_t CIE15:1;      /* Channel 15 Interruput Enable */
                vuint32_t CIE14:1;      /* Channel 14 Interruput Enable */
                vuint32_t CIE13:1;      /* Channel 13 Interruput Enable */
                vuint32_t CIE12:1;      /* Channel 12 Interruput Enable */
                vuint32_t CIE11:1;      /* Channel 11 Interruput Enable */
                vuint32_t CIE10:1;      /* Channel 10 Interruput Enable */
                vuint32_t CIE9:1;       /* Channel 9 Interruput Enable */
                vuint32_t CIE8:1;       /* Channel 8 Interruput Enable */
                vuint32_t CIE7:1;       /* Channel 7 Interruput Enable */
                vuint32_t CIE6:1;       /* Channel 6 Interruput Enable */
                vuint32_t CIE5:1;       /* Channel 5 Interruput Enable */
                vuint32_t CIE4:1;       /* Channel 4 Interruput Enable */
                vuint32_t CIE3:1;       /* Channel 3 Interruput Enable */
                vuint32_t CIE2:1;       /* Channel 2 Interruput Enable */
                vuint32_t CIE1:1;       /* Channel 1 Interruput Enable */
                vuint32_t CIE0:1;       /* Channel 0 Interruput Enable */
            } B;
        } CIER_B;

        uint32_t etpu_reserved17[2];

        union {                 /* ETPU_A Channel Data Transfer Request Enable */
            vuint32_t R;
            struct {
                vuint32_t DTRE31:1;     /* Channel 31 Data Transfer Request Enable */
                vuint32_t DTRE30:1;     /* Channel 30 Data Transfer Request Enable */
                vuint32_t DTRE29:1;     /* Channel 29 Data Transfer Request Enable */
                vuint32_t DTRE28:1;     /* Channel 28 Data Transfer Request Enable */
                vuint32_t DTRE27:1;     /* Channel 27 Data Transfer Request Enable */
                vuint32_t DTRE26:1;     /* Channel 26 Data Transfer Request Enable */
                vuint32_t DTRE25:1;     /* Channel 25 Data Transfer Request Enable */
                vuint32_t DTRE24:1;     /* Channel 24 Data Transfer Request Enable */
                vuint32_t DTRE23:1;     /* Channel 23 Data Transfer Request Enable */
                vuint32_t DTRE22:1;     /* Channel 22 Data Transfer Request Enable */
                vuint32_t DTRE21:1;     /* Channel 21 Data Transfer Request Enable */
                vuint32_t DTRE20:1;     /* Channel 20 Data Transfer Request Enable */
                vuint32_t DTRE19:1;     /* Channel 19 Data Transfer Request Enable */
                vuint32_t DTRE18:1;     /* Channel 18 Data Transfer Request Enable */
                vuint32_t DTRE17:1;     /* Channel 17 Data Transfer Request Enable */
                vuint32_t DTRE16:1;     /* Channel 16 Data Transfer Request Enable */
                vuint32_t DTRE15:1;     /* Channel 15 Data Transfer Request Enable */
                vuint32_t DTRE14:1;     /* Channel 14 Data Transfer Request Enable */
                vuint32_t DTRE13:1;     /* Channel 13 Data Transfer Request Enable */
                vuint32_t DTRE12:1;     /* Channel 12 Data Transfer Request Enable */
                vuint32_t DTRE11:1;     /* Channel 11 Data Transfer Request Enable */
                vuint32_t DTRE10:1;     /* Channel 10 Data Transfer Request Enable */
                vuint32_t DTRE9:1;      /* Channel 9 Data Transfer Request Enable */
                vuint32_t DTRE8:1;      /* Channel 8 Data Transfer Request Enable */
                vuint32_t DTRE7:1;      /* Channel 7 Data Transfer Request Enable */
                vuint32_t DTRE6:1;      /* Channel 6 Data Transfer Request Enable */
                vuint32_t DTRE5:1;      /* Channel 5 Data Transfer Request Enable */
                vuint32_t DTRE4:1;      /* Channel 4 Data Transfer Request Enable */
                vuint32_t DTRE3:1;      /* Channel 3 Data Transfer Request Enable */
                vuint32_t DTRE2:1;      /* Channel 2 Data Transfer Request Enable */
                vuint32_t DTRE1:1;      /* Channel 1 Data Transfer Request Enable */
                vuint32_t DTRE0:1;      /* Channel 0 Data Transfer Request Enable */
            } B;
        } CDTRER_A;

        union {                 /* ETPU_B Channel Data Transfer Request Enable */
            vuint32_t R;
            struct {
                vuint32_t DTRE31:1;     /* Channel 31 Data Transfer Request Enable */
                vuint32_t DTRE30:1;     /* Channel 30 Data Transfer Request Enable */
                vuint32_t DTRE29:1;     /* Channel 29 Data Transfer Request Enable */
                vuint32_t DTRE28:1;     /* Channel 28 Data Transfer Request Enable */
                vuint32_t DTRE27:1;     /* Channel 27 Data Transfer Request Enable */
                vuint32_t DTRE26:1;     /* Channel 26 Data Transfer Request Enable */
                vuint32_t DTRE25:1;     /* Channel 25 Data Transfer Request Enable */
                vuint32_t DTRE24:1;     /* Channel 24 Data Transfer Request Enable */
                vuint32_t DTRE23:1;     /* Channel 23 Data Transfer Request Enable */
                vuint32_t DTRE22:1;     /* Channel 22 Data Transfer Request Enable */
                vuint32_t DTRE21:1;     /* Channel 21 Data Transfer Request Enable */
                vuint32_t DTRE20:1;     /* Channel 20 Data Transfer Request Enable */
                vuint32_t DTRE19:1;     /* Channel 19 Data Transfer Request Enable */
                vuint32_t DTRE18:1;     /* Channel 18 Data Transfer Request Enable */
                vuint32_t DTRE17:1;     /* Channel 17 Data Transfer Request Enable */
                vuint32_t DTRE16:1;     /* Channel 16 Data Transfer Request Enable */
                vuint32_t DTRE15:1;     /* Channel 15 Data Transfer Request Enable */
                vuint32_t DTRE14:1;     /* Channel 14 Data Transfer Request Enable */
                vuint32_t DTRE13:1;     /* Channel 13 Data Transfer Request Enable */
                vuint32_t DTRE12:1;     /* Channel 12 Data Transfer Request Enable */
                vuint32_t DTRE11:1;     /* Channel 11 Data Transfer Request Enable */
                vuint32_t DTRE10:1;     /* Channel 10 Data Transfer Request Enable */
                vuint32_t DTRE9:1;      /* Channel 9 Data Transfer Request Enable */
                vuint32_t DTRE8:1;      /* Channel 8 Data Transfer Request Enable */
                vuint32_t DTRE7:1;      /* Channel 7 Data Transfer Request Enable */
                vuint32_t DTRE6:1;      /* Channel 6 Data Transfer Request Enable */
                vuint32_t DTRE5:1;      /* Channel 5 Data Transfer Request Enable */
                vuint32_t DTRE4:1;      /* Channel 4 Data Transfer Request Enable */
                vuint32_t DTRE3:1;      /* Channel 3 Data Transfer Request Enable */
                vuint32_t DTRE2:1;      /* Channel 2 Data Transfer Request Enable */
                vuint32_t DTRE1:1;      /* Channel 1 Data Transfer Request Enable */
                vuint32_t DTRE0:1;      /* Channel 0 Data Transfer Request Enable */
            } B;
        } CDTRER_B;

        uint32_t etpu_reserved20[10];
        union {                 /* ETPU_A Channel Pending Service Status */
            vuint32_t R;
            struct {
                vuint32_t SR31:1;       /* Channel 31 Pending Service Status */
                vuint32_t SR30:1;       /* Channel 30 Pending Service Status */
                vuint32_t SR29:1;       /* Channel 29 Pending Service Status */
                vuint32_t SR28:1;       /* Channel 28 Pending Service Status */
                vuint32_t SR27:1;       /* Channel 27 Pending Service Status */
                vuint32_t SR26:1;       /* Channel 26 Pending Service Status */
                vuint32_t SR25:1;       /* Channel 25 Pending Service Status */
                vuint32_t SR24:1;       /* Channel 24 Pending Service Status */
                vuint32_t SR23:1;       /* Channel 23 Pending Service Status */
                vuint32_t SR22:1;       /* Channel 22 Pending Service Status */
                vuint32_t SR21:1;       /* Channel 21 Pending Service Status */
                vuint32_t SR20:1;       /* Channel 20 Pending Service Status */
                vuint32_t SR19:1;       /* Channel 19 Pending Service Status */
                vuint32_t SR18:1;       /* Channel 18 Pending Service Status */
                vuint32_t SR17:1;       /* Channel 17 Pending Service Status */
                vuint32_t SR16:1;       /* Channel 16 Pending Service Status */
                vuint32_t SR15:1;       /* Channel 15 Pending Service Status */
                vuint32_t SR14:1;       /* Channel 14 Pending Service Status */
                vuint32_t SR13:1;       /* Channel 13 Pending Service Status */
                vuint32_t SR12:1;       /* Channel 12 Pending Service Status */
                vuint32_t SR11:1;       /* Channel 11 Pending Service Status */
                vuint32_t SR10:1;       /* Channel 10 Pending Service Status */
                vuint32_t SR9:1;        /* Channel 9 Pending Service Status */
                vuint32_t SR8:1;        /* Channel 8 Pending Service Status */
                vuint32_t SR7:1;        /* Channel 7 Pending Service Status */
                vuint32_t SR6:1;        /* Channel 6 Pending Service Status */
                vuint32_t SR5:1;        /* Channel 5 Pending Service Status */
                vuint32_t SR4:1;        /* Channel 4 Pending Service Status */
                vuint32_t SR3:1;        /* Channel 3 Pending Service Status */
                vuint32_t SR2:1;        /* Channel 2 Pending Service Status */
                vuint32_t SR1:1;        /* Channel 1 Pending Service Status */
                vuint32_t SR0:1;        /* Channel 0 Pending Service Status */
            } B;
        } CPSSR_A;

        union {                 /* ETPU_B Channel Pending Service Status */
            vuint32_t R;
            struct {
                vuint32_t SR31:1;       /* Channel 31 Pending Service Status */
                vuint32_t SR30:1;       /* Channel 30 Pending Service Status */
                vuint32_t SR29:1;       /* Channel 29 Pending Service Status */
                vuint32_t SR28:1;       /* Channel 28 Pending Service Status */
                vuint32_t SR27:1;       /* Channel 27 Pending Service Status */
                vuint32_t SR26:1;       /* Channel 26 Pending Service Status */
                vuint32_t SR25:1;       /* Channel 25 Pending Service Status */
                vuint32_t SR24:1;       /* Channel 24 Pending Service Status */
                vuint32_t SR23:1;       /* Channel 23 Pending Service Status */
                vuint32_t SR22:1;       /* Channel 22 Pending Service Status */
                vuint32_t SR21:1;       /* Channel 21 Pending Service Status */
                vuint32_t SR20:1;       /* Channel 20 Pending Service Status */
                vuint32_t SR19:1;       /* Channel 19 Pending Service Status */
                vuint32_t SR18:1;       /* Channel 18 Pending Service Status */
                vuint32_t SR17:1;       /* Channel 17 Pending Service Status */
                vuint32_t SR16:1;       /* Channel 16 Pending Service Status */
                vuint32_t SR15:1;       /* Channel 15 Pending Service Status */
                vuint32_t SR14:1;       /* Channel 14 Pending Service Status */
                vuint32_t SR13:1;       /* Channel 13 Pending Service Status */
                vuint32_t SR12:1;       /* Channel 12 Pending Service Status */
                vuint32_t SR11:1;       /* Channel 11 Pending Service Status */
                vuint32_t SR10:1;       /* Channel 10 Pending Service Status */
                vuint32_t SR9:1;        /* Channel 9 Pending Service Status */
                vuint32_t SR8:1;        /* Channel 8 Pending Service Status */
                vuint32_t SR7:1;        /* Channel 7 Pending Service Status */
                vuint32_t SR6:1;        /* Channel 6 Pending Service Status */
                vuint32_t SR5:1;        /* Channel 5 Pending Service Status */
                vuint32_t SR4:1;        /* Channel 4 Pending Service Status */
                vuint32_t SR3:1;        /* Channel 3 Pending Service Status */
                vuint32_t SR2:1;        /* Channel 2 Pending Service Status */
                vuint32_t SR1:1;        /* Channel 1 Pending Service Status */
                vuint32_t SR0:1;        /* Channel 0 Pending Service Status */
            } B;
        } CPSSR_B;

        uint32_t etpu_reserved20a[2];

        union {                 /* ETPU_A Channel Service Status */
            vuint32_t R;
            struct {
                vuint32_t SS31:1;       /* Channel 31 Service Status */
                vuint32_t SS30:1;       /* Channel 30 Service Status */
                vuint32_t SS29:1;       /* Channel 29 Service Status */
                vuint32_t SS28:1;       /* Channel 28 Service Status */
                vuint32_t SS27:1;       /* Channel 27 Service Status */
                vuint32_t SS26:1;       /* Channel 26 Service Status */
                vuint32_t SS25:1;       /* Channel 25 Service Status */
                vuint32_t SS24:1;       /* Channel 24 Service Status */
                vuint32_t SS23:1;       /* Channel 23 Service Status */
                vuint32_t SS22:1;       /* Channel 22 Service Status */
                vuint32_t SS21:1;       /* Channel 21 Service Status */
                vuint32_t SS20:1;       /* Channel 20 Service Status */
                vuint32_t SS19:1;       /* Channel 19 Service Status */
                vuint32_t SS18:1;       /* Channel 18 Service Status */
                vuint32_t SS17:1;       /* Channel 17 Service Status */
                vuint32_t SS16:1;       /* Channel 16 Service Status */
                vuint32_t SS15:1;       /* Channel 15 Service Status */
                vuint32_t SS14:1;       /* Channel 14 Service Status */
                vuint32_t SS13:1;       /* Channel 13 Service Status */
                vuint32_t SS12:1;       /* Channel 12 Service Status */
                vuint32_t SS11:1;       /* Channel 11 Service Status */
                vuint32_t SS10:1;       /* Channel 10 Service Status */
                vuint32_t SS9:1;        /* Channel 9 Service Status */
                vuint32_t SS8:1;        /* Channel 8 Service Status */
                vuint32_t SS7:1;        /* Channel 7 Service Status */
                vuint32_t SS6:1;        /* Channel 6 Service Status */
                vuint32_t SS5:1;        /* Channel 5 Service Status */
                vuint32_t SS4:1;        /* Channel 4 Service Status */
                vuint32_t SS3:1;        /* Channel 3 Service Status */
                vuint32_t SS2:1;        /* Channel 2 Service Status */
                vuint32_t SS1:1;        /* Channel 1 Service Status */
                vuint32_t SS0:1;        /* Channel 0 Service Status */
            } B;
        } CSSR_A;

        union {                 /* ETPU_B Channel Service Status */
            vuint32_t R;
            struct {
                vuint32_t SS31:1;       /* Channel 31 Service Status */
                vuint32_t SS30:1;       /* Channel 30 Service Status */
                vuint32_t SS29:1;       /* Channel 29 Service Status */
                vuint32_t SS28:1;       /* Channel 28 Service Status */
                vuint32_t SS27:1;       /* Channel 27 Service Status */
                vuint32_t SS26:1;       /* Channel 26 Service Status */
                vuint32_t SS25:1;       /* Channel 25 Service Status */
                vuint32_t SS24:1;       /* Channel 24 Service Status */
                vuint32_t SS23:1;       /* Channel 23 Service Status */
                vuint32_t SS22:1;       /* Channel 22 Service Status */
                vuint32_t SS21:1;       /* Channel 21 Service Status */
                vuint32_t SS20:1;       /* Channel 20 Service Status */
                vuint32_t SS19:1;       /* Channel 19 Service Status */
                vuint32_t SS18:1;       /* Channel 18 Service Status */
                vuint32_t SS17:1;       /* Channel 17 Service Status */
                vuint32_t SS16:1;       /* Channel 16 Service Status */
                vuint32_t SS15:1;       /* Channel 15 Service Status */
                vuint32_t SS14:1;       /* Channel 14 Service Status */
                vuint32_t SS13:1;       /* Channel 13 Service Status */
                vuint32_t SS12:1;       /* Channel 12 Service Status */
                vuint32_t SS11:1;       /* Channel 11 Service Status */
                vuint32_t SS10:1;       /* Channel 10 Service Status */
                vuint32_t SS9:1;        /* Channel 9 Service Status */
                vuint32_t SS8:1;        /* Channel 8 Service Status */
                vuint32_t SS7:1;        /* Channel 7 Service Status */
                vuint32_t SS6:1;        /* Channel 6 Service Status */
                vuint32_t SS5:1;        /* Channel 5 Service Status */
                vuint32_t SS4:1;        /* Channel 4 Service Status */
                vuint32_t SS3:1;        /* Channel 3 Service Status */
                vuint32_t SS2:1;        /* Channel 2 Service Status */
                vuint32_t SS1:1;        /* Channel 1 Service Status */
                vuint32_t SS0:1;        /* Channel 0 Service Status */
            } B;
        } CSSR_B;

        uint32_t etpu_reserved23[90];

/*****************************Channels********************************/

        struct {
            union {
                vuint32_t R;    /* Channel Configuration Register */
                struct {
                    vuint32_t CIE:1;    /* Channel Interruput Enable */
                    vuint32_t DTRE:1;   /* Data Transfer Request Enable */
                    vuint32_t CPR:2;    /* Channel Priority */
                      vuint32_t:3;
                    vuint32_t ETCS:1;   /* Entry Table Condition Select */
                      vuint32_t:3;
                    vuint32_t CFS:5;    /* Channel Function Select */
                    vuint32_t ODIS:1;   /* Output disable */
                    vuint32_t OPOL:1;   /* output polarity */
                      vuint32_t:3;
                    vuint32_t CPBA:11;  /* Channel Parameter Base Address */
                } B;
            } CR;
            union {
                vuint32_t R;    /* Channel Status Control Register */
                struct {
                    vuint32_t CIS:1;    /* Channel Interruput Status */
                    vuint32_t CIOS:1;   /* Channel Interruput Overflow Status */
                      vuint32_t:6;
                    vuint32_t DTRS:1;   /* Data Transfer Status */
                    vuint32_t DTROS:1;  /* Data Transfer Overflow Status */
                      vuint32_t:6;
                    vuint32_t IPS:1;    /* Input Pin State */
                    vuint32_t OPS:1;    /* Output Pin State */
                    vuint32_t OBE:1;    /* Output Buffer Enable */
                      vuint32_t:11;
                    vuint32_t FM1:1;    /* Function mode */
                    vuint32_t FM0:1;    /* Function mode */
                } B;
            } SCR;
            union {
                vuint32_t R;    /* Channel Host Service Request Register */
                struct {
                    vuint32_t:29;       /* Host Service Request */
                    vuint32_t HSR:3;
                } B;
            } HSRR;
            uint32_t etpu_reserved23;
        } CHAN[127];

    };
/****************************************************************************/
/*                          MODULE : XBAR CrossBar                          */
/****************************************************************************/

/* MPC5554 has a 3 x 5 (master x slave) CrossBar */

    struct XBAR_tag {

        union {
            vuint32_t R;
            struct {
                vuint32_t:21;
                vuint32_t MSTR2:3;
                  vuint32_t:1;
                vuint32_t MSTR1:3;
                  vuint32_t:1;
                vuint32_t MSTR0:3;
            } B;
        } MPR0;                 /* Master Priority Register for Slave Port 0 */
        uint32_t xbar_reserved1[3];

        union {
            vuint32_t R;
            struct {
                vuint32_t RO:1;
                  vuint32_t:21;
                vuint32_t ARB:2;
                  vuint32_t:2;
                vuint32_t PCTL:2;
                  vuint32_t:1;
                vuint32_t PARK:3;
            } B;
        } SGPCR0;               /* General Purpose Control Register for Slave Port 0 */

        uint32_t xbar_reserved2[59];

        union {
            vuint32_t R;
            struct {
                vuint32_t:21;
                vuint32_t MSTR2:3;
                  vuint32_t:1;
                vuint32_t MSTR1:3;
                  vuint32_t:1;
                vuint32_t MSTR0:3;
            } B;
        } MPR1;                 /* Master Priority Register for Slave Port 1 */
        uint32_t xbar_reserved3[3];

        union {
            vuint32_t R;
            struct {
                vuint32_t RO:1;
                  vuint32_t:21;
                vuint32_t ARB:2;
                  vuint32_t:2;
                vuint32_t PCTL:2;
                  vuint32_t:1;
                vuint32_t PARK:3;
            } B;
        } SGPCR1;               /* General Purpose Control Register for Slave Port 1 */

        uint32_t xbar_reserved4[123];

        union {
            vuint32_t R;
            struct {
                vuint32_t:21;
                vuint32_t MSTR2:3;
                  vuint32_t:1;
                vuint32_t MSTR1:3;
                  vuint32_t:1;
                vuint32_t MSTR0:3;
            } B;
        } MPR3;                 /* Master Priority Register for Slave Port 3 */
        uint32_t xbar_reserved5[3];

        union {
            vuint32_t R;
            struct {
                vuint32_t RO:1;
                  vuint32_t:21;
                vuint32_t ARB:2;
                  vuint32_t:2;
                vuint32_t PCTL:2;
                  vuint32_t:1;
                vuint32_t PARK:3;
            } B;
        } SGPCR3;               /* General Purpose Control Register for Slave Port 3 */

        uint32_t xbar_reserved6[187];

        union {
            vuint32_t R;
            struct {
                vuint32_t:21;
                vuint32_t MSTR2:3;
                  vuint32_t:1;
                vuint32_t MSTR1:3;
                  vuint32_t:1;
                vuint32_t MSTR0:3;
            } B;
        } MPR6;                 /* Master Priority Register for Slave Port 6 */
        uint32_t xbar_reserved7[3];

        union {
            vuint32_t R;
            struct {
                vuint32_t RO:1;
                  vuint32_t:21;
                vuint32_t ARB:2;
                  vuint32_t:2;
                vuint32_t PCTL:2;
                  vuint32_t:1;
                vuint32_t PARK:3;
            } B;
        } SGPCR6;               /* General Purpose Control Register for Slave Port 6 */

        uint32_t xbar_reserved8[59];

        union {
            vuint32_t R;
            struct {
                vuint32_t:21;
                vuint32_t MSTR2:3;
                  vuint32_t:1;
                vuint32_t MSTR1:3;
                  vuint32_t:1;
                vuint32_t MSTR0:3;
            } B;
        } MPR7;                 /* Master Priority Register for Slave Port 7 */
        uint32_t xbar_reserved9[3];

        union {
            vuint32_t R;
            struct {
                vuint32_t RO:1;
                  vuint32_t:21;
                vuint32_t ARB:2;
                  vuint32_t:2;
                vuint32_t PCTL:2;
                  vuint32_t:1;
                vuint32_t PARK:3;
            } B;
        } SGPCR7;               /* General Purpose Control Register for Slave Port 7 */

    };
/****************************************************************************/
/*                     MODULE : ECSM                                        */
/****************************************************************************/
    struct ECSM_tag {

        uint32_t ecsm_reserved1[5];

        uint16_t ecsm_reserved2;

        union {
            vuint16_t R;
        } SWTCR;                //Software Watchdog Timer Control

        uint8_t ecsm_reserved3[3];

        union {
            vuint8_t R;
        } SWTSR;                //SWT Service Register

        uint8_t ecsm_reserved4[3];

        union {
            vuint8_t R;
        } SWTIR;                //SWT Interrupt Register
        uint32_t ecsm_reserved5[8];

        uint8_t ecsm_reserved6[3];

        union {
            vuint8_t R;
            struct {
                vuint8_t:6;
                vuint8_t ERNCR:1;
                vuint8_t EFNCR:1;
            } B;
        } ECR;                  //ECC Configuration Register

        uint8_t mcm_reserved8[3];

        union {
            vuint8_t R;
            struct {
                vuint8_t:6;
                vuint8_t RNCE:1;
                vuint8_t FNCE:1;
            } B;
        } ESR;                  //ECC Status Register

        uint16_t ecsm_reserved9;

        union {
            vuint16_t R;
            struct {
                vuint16_t:6;
                vuint16_t FRCNCI:1;
                vuint16_t FR1NCI:1;
                  vuint16_t:1;
                vuint16_t ERRBIT:7;
            } B;
        } EEGR;                 //ECC Error Generation Register

        uint32_t ecsm_reserved10;

        union {
            vuint32_t R;
            struct {
                vuint32_t FEAR:32;
            } B;
        } FEAR;                 //Flash ECC Address Register

        uint16_t ecsm_reserved11;

        union {
            vuint8_t R;
            struct {
                vuint8_t:4;
                vuint8_t FEMR:4;
            } B;
        } FEMR;                 //Flash ECC Master Register

        union {
            vuint8_t R;
            struct {
                vuint8_t WRITE:1;
                vuint8_t SIZE:3;
                vuint8_t PROT0:1;
                vuint8_t PROT1:1;
                vuint8_t PROT2:1;
                vuint8_t PROT3:1;
            } B;
        } FEAT;                 //Flash ECC Attributes Register

        union {
            vuint32_t R;
            struct {
                vuint32_t FEDH:32;
            } B;
        } FEDRH;                //Flash ECC Data High Register

        union {
            vuint32_t R;
            struct {
                vuint32_t FEDL:32;
            } B;
        } FEDRL;                //Flash ECC Data Low Register

        union {
            vuint32_t R;
            struct {
                vuint32_t REAR:32;
            } B;
        } REAR;                 //RAM ECC Address

        uint8_t ecsm_reserved12[2];

        union {
            vuint8_t R;
            struct {
                vuint8_t:4;
                vuint8_t REMR:4;
            } B;
        } REMR;                 //RAM ECC Master

        union {
            vuint8_t R;
            struct {
                vuint8_t WRITE:1;
                vuint8_t SIZE:3;
                vuint8_t PROT0:1;
                vuint8_t PROT1:1;
                vuint8_t PROT2:1;
                vuint8_t PROT3:1;
            } B;
        } REAT;                 // RAM ECC Attributes Register

        union {
            vuint32_t R;
            struct {
                vuint32_t REDH:32;
            } B;
        } REDRH;                //RAM ECC Data High Register

        union {
            vuint32_t R;
            struct {
                vuint32_t REDL:32;
            } B;
        } REDRL;                //RAMECC Data Low Register

    };
/****************************************************************************/
/*                          MODULE : eDMA                                   */
/****************************************************************************/
    struct EDMA_tag {
        union {
            vuint32_t R;
            struct {
                vuint32_t:16;
                vuint32_t GRP3PRI:2;
                vuint32_t GRP2PRI:2;
                vuint32_t GRP1PRI:2;
                vuint32_t GRP0PRI:2;
                  vuint32_t:4;
                vuint32_t ERGA:1;
                vuint32_t ERCA:1;
                vuint32_t EDBG:1;
                vuint32_t EBW:1;
            } B;
        } CR;                   /* Control Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t VLD:1;
                  vuint32_t:15;
                vuint32_t GPE:1;
                vuint32_t CPE:1;
                vuint32_t ERRCHN:6;
                vuint32_t SAE:1;
                vuint32_t SOE:1;
                vuint32_t DAE:1;
                vuint32_t DOE:1;
                vuint32_t NCE:1;
                vuint32_t SGE:1;
                vuint32_t SBE:1;
                vuint32_t DBE:1;
            } B;
        } ESR;                  /* Error Status Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t ERQ63:1;
                vuint32_t ERQ62:1;
                vuint32_t ERQ61:1;
                vuint32_t ERQ60:1;
                vuint32_t ERQ59:1;
                vuint32_t ERQ58:1;
                vuint32_t ERQ57:1;
                vuint32_t ERQ56:1;
                vuint32_t ERQ55:1;
                vuint32_t ERQ54:1;
                vuint32_t ERQ53:1;
                vuint32_t ERQ52:1;
                vuint32_t ERQ51:1;
                vuint32_t ERQ50:1;
                vuint32_t ERQ49:1;
                vuint32_t ERQ48:1;
                vuint32_t ERQ47:1;
                vuint32_t ERQ46:1;
                vuint32_t ERQ45:1;
                vuint32_t ERQ44:1;
                vuint32_t ERQ43:1;
                vuint32_t ERQ42:1;
                vuint32_t ERQ41:1;
                vuint32_t ERQ40:1;
                vuint32_t ERQ39:1;
                vuint32_t ERQ38:1;
                vuint32_t ERQ37:1;
                vuint32_t ERQ36:1;
                vuint32_t ERQ35:1;
                vuint32_t ERQ34:1;
                vuint32_t ERQ33:1;
                vuint32_t ERQ32:1;
            } B;
        } ERQRH;                /* DMA Enable Request Register High */

        union {
            vuint32_t R;
            struct {
                vuint32_t ERQ31:1;
                vuint32_t ERQ30:1;
                vuint32_t ERQ29:1;
                vuint32_t ERQ28:1;
                vuint32_t ERQ27:1;
                vuint32_t ERQ26:1;
                vuint32_t ERQ25:1;
                vuint32_t ERQ24:1;
                vuint32_t ERQ23:1;
                vuint32_t ERQ22:1;
                vuint32_t ERQ21:1;
                vuint32_t ERQ20:1;
                vuint32_t ERQ19:1;
                vuint32_t ERQ18:1;
                vuint32_t ERQ17:1;
                vuint32_t ERQ16:1;
                vuint32_t ERQ15:1;
                vuint32_t ERQ14:1;
                vuint32_t ERQ13:1;
                vuint32_t ERQ12:1;
                vuint32_t ERQ11:1;
                vuint32_t ERQ10:1;
                vuint32_t ERQ09:1;
                vuint32_t ERQ08:1;
                vuint32_t ERQ07:1;
                vuint32_t ERQ06:1;
                vuint32_t ERQ05:1;
                vuint32_t ERQ04:1;
                vuint32_t ERQ03:1;
                vuint32_t ERQ02:1;
                vuint32_t ERQ01:1;
                vuint32_t ERQ00:1;
            } B;
        } ERQRL;                /* DMA Enable Request Register Low */

        union {
            vuint32_t R;
            struct {
                vuint32_t EEI63:1;
                vuint32_t EEI62:1;
                vuint32_t EEI61:1;
                vuint32_t EEI60:1;
                vuint32_t EEI59:1;
                vuint32_t EEI58:1;
                vuint32_t EEI57:1;
                vuint32_t EEI56:1;
                vuint32_t EEI55:1;
                vuint32_t EEI54:1;
                vuint32_t EEI53:1;
                vuint32_t EEI52:1;
                vuint32_t EEI51:1;
                vuint32_t EEI50:1;
                vuint32_t EEI49:1;
                vuint32_t EEI48:1;
                vuint32_t EEI47:1;
                vuint32_t EEI46:1;
                vuint32_t EEI45:1;
                vuint32_t EEI44:1;
                vuint32_t EEI43:1;
                vuint32_t EEI42:1;
                vuint32_t EEI41:1;
                vuint32_t EEI40:1;
                vuint32_t EEI39:1;
                vuint32_t EEI38:1;
                vuint32_t EEI37:1;
                vuint32_t EEI36:1;
                vuint32_t EEI35:1;
                vuint32_t EEI34:1;
                vuint32_t EEI33:1;
                vuint32_t EEI32:1;
            } B;
        } EEIRH;                /* DMA Enable Error Interrupt Register High */

        union {
            vuint32_t R;
            struct {
                vuint32_t EEI31:1;
                vuint32_t EEI30:1;
                vuint32_t EEI29:1;
                vuint32_t EEI28:1;
                vuint32_t EEI27:1;
                vuint32_t EEI26:1;
                vuint32_t EEI25:1;
                vuint32_t EEI24:1;
                vuint32_t EEI23:1;
                vuint32_t EEI22:1;
                vuint32_t EEI21:1;
                vuint32_t EEI20:1;
                vuint32_t EEI19:1;
                vuint32_t EEI18:1;
                vuint32_t EEI17:1;
                vuint32_t EEI16:1;
                vuint32_t EEI15:1;
                vuint32_t EEI14:1;
                vuint32_t EEI13:1;
                vuint32_t EEI12:1;
                vuint32_t EEI11:1;
                vuint32_t EEI10:1;
                vuint32_t EEI09:1;
                vuint32_t EEI08:1;
                vuint32_t EEI07:1;
                vuint32_t EEI06:1;
                vuint32_t EEI05:1;
                vuint32_t EEI04:1;
                vuint32_t EEI03:1;
                vuint32_t EEI02:1;
                vuint32_t EEI01:1;
                vuint32_t EEI00:1;
            } B;
        } EEIRL;                /* DMA Enable Error Interrupt Register Low */

        union {
            vuint8_t R;
            vuint8_t B;
        } SERQR;                /* DMA Set Enable Request Register */

        union {
            vuint8_t R;
            vuint8_t B;
        } CERQR;                /* DMA Clear Enable Request Register */

        union {
            vuint8_t R;
            vuint8_t B;
        } SEEIR;                /* DMA Set Enable Error Interrupt Register */

        union {
            vuint8_t R;
            vuint8_t B;
        } CEEIR;                /* DMA Clear Enable Error Interrupt REgister */

        union {
            vuint8_t R;
            vuint8_t B;
        } CIRQR;                /* DMA Clear Interrupt Request Register */

        union {
            vuint8_t R;
            vuint8_t B;
        } CER;                  /* DMA Clear error Register */

        union {
            vuint8_t R;
            vuint8_t B;
        } SSBR;                 /* Set Start Bit Register */

        union {
            vuint8_t R;
            vuint8_t B;
        } CDSBR;                /* Clear Done Status Bit Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t INT63:1;
                vuint32_t INT62:1;
                vuint32_t INT61:1;
                vuint32_t INT60:1;
                vuint32_t INT59:1;
                vuint32_t INT58:1;
                vuint32_t INT57:1;
                vuint32_t INT56:1;
                vuint32_t INT55:1;
                vuint32_t INT54:1;
                vuint32_t INT53:1;
                vuint32_t INT52:1;
                vuint32_t INT51:1;
                vuint32_t INT50:1;
                vuint32_t INT49:1;
                vuint32_t INT48:1;
                vuint32_t INT47:1;
                vuint32_t INT46:1;
                vuint32_t INT45:1;
                vuint32_t INT44:1;
                vuint32_t INT43:1;
                vuint32_t INT42:1;
                vuint32_t INT41:1;
                vuint32_t INT40:1;
                vuint32_t INT39:1;
                vuint32_t INT38:1;
                vuint32_t INT37:1;
                vuint32_t INT36:1;
                vuint32_t INT35:1;
                vuint32_t INT34:1;
                vuint32_t INT33:1;
                vuint32_t INT32:1;
            } B;
        } IRQRH;                /* DMA Interrupt Request High */

        union {
            vuint32_t R;
            struct {
                vuint32_t INT31:1;
                vuint32_t INT30:1;
                vuint32_t INT29:1;
                vuint32_t INT28:1;
                vuint32_t INT27:1;
                vuint32_t INT26:1;
                vuint32_t INT25:1;
                vuint32_t INT24:1;
                vuint32_t INT23:1;
                vuint32_t INT22:1;
                vuint32_t INT21:1;
                vuint32_t INT20:1;
                vuint32_t INT19:1;
                vuint32_t INT18:1;
                vuint32_t INT17:1;
                vuint32_t INT16:1;
                vuint32_t INT15:1;
                vuint32_t INT14:1;
                vuint32_t INT13:1;
                vuint32_t INT12:1;
                vuint32_t INT11:1;
                vuint32_t INT10:1;
                vuint32_t INT09:1;
                vuint32_t INT08:1;
                vuint32_t INT07:1;
                vuint32_t INT06:1;
                vuint32_t INT05:1;
                vuint32_t INT04:1;
                vuint32_t INT03:1;
                vuint32_t INT02:1;
                vuint32_t INT01:1;
                vuint32_t INT00:1;
            } B;
        } IRQRL;                /* DMA Interrupt Request Low */

        union {
            vuint32_t R;
            struct {
                vuint32_t ERR63:1;
                vuint32_t ERR62:1;
                vuint32_t ERR61:1;
                vuint32_t ERR60:1;
                vuint32_t ERR59:1;
                vuint32_t ERR58:1;
                vuint32_t ERR57:1;
                vuint32_t ERR56:1;
                vuint32_t ERR55:1;
                vuint32_t ERR54:1;
                vuint32_t ERR53:1;
                vuint32_t ERR52:1;
                vuint32_t ERR51:1;
                vuint32_t ERR50:1;
                vuint32_t ERR49:1;
                vuint32_t ERR48:1;
                vuint32_t ERR47:1;
                vuint32_t ERR46:1;
                vuint32_t ERR45:1;
                vuint32_t ERR44:1;
                vuint32_t ERR43:1;
                vuint32_t ERR42:1;
                vuint32_t ERR41:1;
                vuint32_t ERR40:1;
                vuint32_t ERR39:1;
                vuint32_t ERR38:1;
                vuint32_t ERR37:1;
                vuint32_t ERR36:1;
                vuint32_t ERR35:1;
                vuint32_t ERR34:1;
                vuint32_t ERR33:1;
                vuint32_t ERR32:1;
            } B;
        } ERH;                  /* DMA Error High */

        union {
            vuint32_t R;
            struct {
                vuint32_t ERR31:1;
                vuint32_t ERR30:1;
                vuint32_t ERR29:1;
                vuint32_t ERR28:1;
                vuint32_t ERR27:1;
                vuint32_t ERR26:1;
                vuint32_t ERR25:1;
                vuint32_t ERR24:1;
                vuint32_t ERR23:1;
                vuint32_t ERR22:1;
                vuint32_t ERR21:1;
                vuint32_t ERR20:1;
                vuint32_t ERR19:1;
                vuint32_t ERR18:1;
                vuint32_t ERR17:1;
                vuint32_t ERR16:1;
                vuint32_t ERR15:1;
                vuint32_t ERR14:1;
                vuint32_t ERR13:1;
                vuint32_t ERR12:1;
                vuint32_t ERR11:1;
                vuint32_t ERR10:1;
                vuint32_t ERR09:1;
                vuint32_t ERR08:1;
                vuint32_t ERR07:1;
                vuint32_t ERR06:1;
                vuint32_t ERR05:1;
                vuint32_t ERR04:1;
                vuint32_t ERR03:1;
                vuint32_t ERR02:1;
                vuint32_t ERR01:1;
                vuint32_t ERR00:1;
            } B;
        } ERL;                  /* DMA Error Low */

        uint32_t edma_reserved1[52];

        union {
            vuint8_t R;
            struct {
                vuint8_t ECP:1;
                  vuint8_t:1;
                vuint8_t GRPPRI:2;
                vuint8_t CHPRI:4;
            } B;
        } CPR[64];

        uint32_t edma_reserved2[944];

/****************************************************************************/
/*       DMA2 Transfer Control Descriptor                                   */
/****************************************************************************/
        struct tcd_t {
            vuint32_t SADDR;    /* source address */

            vuint16_t SMOD:5;   /* source address modulo */
            vuint16_t SSIZE:3;  /* source transfer size */
            vuint16_t DMOD:5;   /* destination address modulo */
            vuint16_t DSIZE:3;  /* destination transfer size */
            vint16_t SOFF;      /* signed source address offset */

            vuint32_t NBYTES;   /* inner (�minor�) byte count */

            vint32_t SLAST;     /* last destination address adjustment, or
                                   scatter/gather address (if e_sg = 1) */

            vuint32_t DADDR;    /* destination address */

            vuint16_t CITERE_LINK:1;
            vuint16_t CITER:15;

            vint16_t DOFF;      /* signed destination address offset */

            vint32_t DLAST_SGA;

            vuint16_t BITERE_LINK:1;    /* beginning ("major") iteration count */
            vuint16_t BITER:15;

            vuint16_t BWC:2;    /* bandwidth control */
            vuint16_t MAJORLINKCH:6;    /* enable channel-to-channel link */
            vuint16_t DONE:1;   /* channel done */
            vuint16_t ACTIVE:1; /* channel active */
            vuint16_t MAJORE_LINK:1;    /* enable channel-to-channel link */
            vuint16_t E_SG:1;   /* enable scatter/gather descriptor */
            vuint16_t D_REQ:1;  /* disable ipd_req when done */
            vuint16_t INT_HALF:1;       /* interrupt on citer = (biter >> 1) */
            vuint16_t INT_MAJ:1;        /* interrupt on major loop completion */
            vuint16_t START:1;  /* explicit channel start */
        } TCD[64];              /* transfer_control_descriptor */

    };

/* This is outside of the eDMA structure */
/* There are 2 possible ways to use the citer bit field, this structure */
/* uses the different format from the main structure.                   */
    struct tcd_alt_t {
        vuint32_t SADDR;        /* source address */

        vuint16_t SMOD:5;       /* source address modulo */
        vuint16_t SSIZE:3;      /* source transfer size */
        vuint16_t DMOD:5;       /* destination address modulo */
        vuint16_t DSIZE:3;      /* destination transfer size */
        vint16_t SOFF;          /* signed source address offset */

        vuint32_t NBYTES;       /* inner (�minor�) byte count */

        vint32_t SLAST;         /* last destination address adjustment, or
                                   scatter/gather address (if e_sg = 1) */

        vuint32_t DADDR;        /* destination address */

        vuint16_t CITERE_LINK:1;
        vuint16_t CITERLINKCH:6;
        vuint16_t CITER:9;

        vint16_t DOFF;          /* signed destination address offset */

        vint32_t DLAST_SGA;

        vuint16_t BITERE_LINK:1;        /* beginning (�major�) iteration count */
        vuint16_t BITERLINKCH:6;
        vuint16_t BITER:9;

        vuint16_t BWC:2;        /* bandwidth control */
        vuint16_t MAJORLINKCH:6;        /* enable channel-to-channel link */
        vuint16_t DONE:1;       /* channel done */
        vuint16_t ACTIVE:1;     /* channel active */
        vuint16_t MAJORE_LINK:1;        /* enable channel-to-channel link */
        vuint16_t E_SG:1;       /* enable scatter/gather descriptor */
        vuint16_t D_REQ:1;      /* disable ipd_req when done */
        vuint16_t INT_HALF:1;   /* interrupt on citer = (biter >> 1) */
        vuint16_t INT_MAJ:1;    /* interrupt on major loop completion */
        vuint16_t START:1;      /* explicit channel start */
    };                          /* transfer_control_descriptor */
/****************************************************************************/
/*                          MODULE : INTC                                   */
/****************************************************************************/
    struct INTC_tag {
        union {
            vuint32_t R;
            struct {
                vuint32_t:26;
                vuint32_t VTES:1;
                  vuint32_t:4;
                vuint32_t HVEN:1;
            } B;
        } MCR;                  /* Module Configuration Register */

        int32_t INTC_reserved00;

        union {
            vuint32_t R;
            struct {
                vuint32_t:28;
                vuint32_t PRI:4;
            } B;
        } CPR;                  /* Current Priority Register */

        uint32_t intc_reserved1;

        union {
            vuint32_t R;
            struct {
                vuint32_t VTBA:21;
                vuint32_t INTVEC:9;
                  vuint32_t:2;
            } B;
        } IACKR;                /* Interrupt Acknowledge Register */

        uint32_t intc_reserved2;

        union {
            vuint32_t R;
            struct {
                vuint32_t:32;
            } B;
        } EOIR;                 /* End of Interrupt Register */

        uint32_t intc_reserved3;

        union {
            vuint8_t R;
            struct {
                vuint8_t:6;
                vuint8_t SET:1;
                vuint8_t CLR:1;
            } B;
        } SSCIR[8];             /* Software Set/Clear Interruput Register */

        uint32_t intc_reserved4[6];

        union {
            vuint8_t R;
            struct {
                vuint8_t:4;
                vuint8_t PRI:4;
            } B;
        } PSR[307];             /* Software Set/Clear Interrupt Register */

    };
/****************************************************************************/
/*                          MODULE : EQADC                                  */
/****************************************************************************/
    struct EQADC_tag {
        union {
            vuint32_t R;
            struct {
                vuint32_t:27;
                vuint32_t ESSIE:2;
                  vuint32_t:1;
                vuint32_t DBG:2;
            } B;
        } MCR;                  /* Module Configuration Register */

        int32_t EQADC_reserved00;

        union {
            vuint32_t R;
            struct {
                vuint32_t:6;
                vuint32_t NMF:26;
            } B;
        } NMSFR;                /* Null Message Send Format Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t:28;
                vuint32_t DFL:4;
            } B;
        } ETDFR;                /* External Trigger Digital Filter Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t CFPUSH:32;
            } B;
        } CFPR[6];              /* CFIFO Push Registers */

        uint32_t eqadc_reserved1;

        uint32_t eqadc_reserved2;

        union {
            vuint32_t R;
            struct {
                vuint32_t:16;
                vuint32_t RFPOP:16;
            } B;
        } RFPR[6];              /* Result FIFO Pop Registers */

        uint32_t eqadc_reserved3;

        uint32_t eqadc_reserved4;

        union {
            vuint16_t R;
            struct {
                vuint16_t:5;
                vuint16_t SSE:1;
                vuint16_t CFINV:1;
                  vuint16_t:1;
                vuint16_t MODE:4;
                  vuint16_t:4;
            } B;
        } CFCR[6];              /* CFIFO Control Registers */

        uint32_t eqadc_reserved5;

        union {
            vuint16_t R;
            struct {
                vuint16_t NCIE:1;
                vuint16_t TORIE:1;
                vuint16_t PIE:1;
                vuint16_t EOQIE:1;
                vuint16_t CFUIE:1;
                  vuint16_t:1;
                vuint16_t CFFE:1;
                vuint16_t CFFS:1;
                  vuint16_t:4;
                vuint16_t RFOIE:1;
                  vuint16_t:1;
                vuint16_t RFDE:1;
                vuint16_t RFDS:1;
            } B;
        } IDCR[6];              /* Interrupt and DMA Control Registers */

        uint32_t eqadc_reserved6;

        union {
            vuint32_t R;
            struct {
                vuint32_t NCF:1;
                vuint32_t TORF:1;
                vuint32_t PF:1;
                vuint32_t EOQF:1;
                vuint32_t CFUF:1;
                vuint32_t SSS:1;
                vuint32_t CFFF:1;
                  vuint32_t:5;
                vuint32_t RFOF:1;
                  vuint32_t:1;
                vuint32_t RFDF:1;
                  vuint32_t:1;
                vuint32_t CFCTR:4;
                vuint32_t TNXTPTR:4;
                vuint32_t RFCTR:4;
                vuint32_t POPNXTPTR:4;
            } B;
        } FISR[6];              /* FIFO and Interrupt Status Registers */

        uint32_t eqadc_reserved7;

        uint32_t eqadc_reserved8;

        union {
            vuint16_t R;
            struct {
                vuint16_t:5;
                vuint16_t TCCF:11;
            } B;
        } CFTCR[6];             /* CFIFO Transfer Counter Registers */

        uint32_t eqadc_reserved9;

        union {
            vuint32_t R;
            struct {
                vuint32_t CFS0:2;
                vuint32_t CFS1:2;
                vuint32_t CFS2:2;
                vuint32_t CFS3:2;
                vuint32_t CFS4:2;
                vuint32_t CFS5:2;
                  vuint32_t:5;
                vuint32_t LCFTCB0:4;
                vuint32_t TC_LCFTCB0:11;
            } B;
        } CFSSR0;               /* CFIFO Status Register 0 */

        union {
            vuint32_t R;
            struct {
                vuint32_t CFS0:2;
                vuint32_t CFS1:2;
                vuint32_t CFS2:2;
                vuint32_t CFS3:2;
                vuint32_t CFS4:2;
                vuint32_t CFS5:2;
                  vuint32_t:5;
                vuint32_t LCFTCB1:4;
                vuint32_t TC_LCFTCB1:11;
            } B;
        } CFSSR1;               /* CFIFO Status Register 1 */

        union {
            vuint32_t R;
            struct {
                vuint32_t CFS0:2;
                vuint32_t CFS1:2;
                vuint32_t CFS2:2;
                vuint32_t CFS3:2;
                vuint32_t CFS4:2;
                vuint32_t CFS5:2;
                  vuint32_t:4;
                vuint32_t ECBNI:1;
                vuint32_t LCFTSSI:4;
                vuint32_t TC_LCFTSSI:11;
            } B;
        } CFSSR2;               /* CFIFO Status Register 2 */

        union {
            vuint32_t R;
            struct {
                vuint32_t CFS0:2;
                vuint32_t CFS1:2;
                vuint32_t CFS2:2;
                vuint32_t CFS3:2;
                vuint32_t CFS4:2;
                vuint32_t CFS5:2;
                  vuint32_t:20;
            } B;
        } CFSR;

        uint32_t eqadc_reserved11;

        union {
            vuint32_t R;
            struct {
                vuint32_t:21;
                vuint32_t MDT:3;
                  vuint32_t:4;
                vuint32_t BR:4;
            } B;
        } SSICR;                /* SSI Control Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t RDV:1;
                  vuint32_t:5;
                vuint32_t RDATA:26;
            } B;
        } SSIRDR;               /* SSI Recieve Data Register */

        uint32_t eqadc_reserved12[17];

        struct {
            union {
                vuint32_t R;
                struct {
                    vuint32_t:32;
                } B;
            } R[4];

            uint32_t eqadc_reserved13[12];

        } CF[6];

        uint32_t eqadc_reserved14[32];

        struct {
            union {
                vuint32_t R;
                struct {
                    vuint32_t:32;
                } B;
            } R[4];

            uint32_t eqadc_reserved15[12];

        } RF[6];

    };
/****************************************************************************/
/*                          MODULE : DSPI                                   */
/****************************************************************************/
    struct DSPI_tag {
        union {
            vuint32_t R;
            struct {
                vuint32_t MSTR:1;
                vuint32_t CONT_SCKE:1;
                vuint32_t DCONF:2;
                vuint32_t FRZ:1;
                vuint32_t MTFE:1;
                vuint32_t PCSSE:1;
                vuint32_t ROOE:1;
                  vuint32_t:2;
                vuint32_t PCSIS5:1;
                vuint32_t PCSIS4:1;
                vuint32_t PCSIS3:1;
                vuint32_t PCSIS2:1;
                vuint32_t PCSIS1:1;
                vuint32_t PCSIS0:1;
                vuint32_t DOZE:1;
                vuint32_t MDIS:1;
                vuint32_t DIS_TXF:1;
                vuint32_t DIS_RXF:1;
                vuint32_t CLR_TXF:1;
                vuint32_t CLR_RXF:1;
                vuint32_t SMPL_PT:2;
                  vuint32_t:7;
                vuint32_t HALT:1;
            } B;
        } MCR;                  /* Module Configuration Register */

        uint32_t dspi_reserved1;

        union {
            vuint32_t R;
            struct {
                vuint32_t TCNT:16;
                  vuint32_t:16;
            } B;
        } TCR;

        union {
            vuint32_t R;
            struct {
                vuint32_t DBR:1;
                vuint32_t FMSZ:4;
                vuint32_t CPOL:1;
                vuint32_t CPHA:1;
                vuint32_t LSBFE:1;
                vuint32_t PCSSCK:2;
                vuint32_t PASC:2;
                vuint32_t PDT:2;
                vuint32_t PBR:2;
                vuint32_t CSSCK:4;
                vuint32_t ASC:4;
                vuint32_t DT:4;
                vuint32_t BR:4;
            } B;
        } CTAR[8];              /* Clock and Transfer Attributes Registers */

        union {
            vuint32_t R;
            struct {
                vuint32_t TCF:1;
                vuint32_t TXRXS:1;
                  vuint32_t:1;
                vuint32_t EOQF:1;
                vuint32_t TFUF:1;
                  vuint32_t:1;
                vuint32_t TFFF:1;
                  vuint32_t:5;
                vuint32_t RFOF:1;
                  vuint32_t:1;
                vuint32_t RFDF:1;
                  vuint32_t:1;
                vuint32_t TXCTR:4;
                vuint32_t TXNXTPTR:4;
                vuint32_t RXCTR:4;
                vuint32_t POPNXTPTR:4;
            } B;
        } SR;                   /* Status Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t TCFRE:1;
                  vuint32_t:2;
                vuint32_t EOQFRE:1;
                vuint32_t TFUFRE:1;
                  vuint32_t:1;
                vuint32_t TFFFRE:1;
                vuint32_t TFFFDIRS:1;
                  vuint32_t:4;
                vuint32_t RFOFRE:1;
                  vuint32_t:1;
                vuint32_t RFDFRE:1;
                vuint32_t RFDFDIRS:1;
                  vuint32_t:16;
            } B;
        } RSER;                 /* DMA/Interrupt Request Select and Enable Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t CONT:1;
                vuint32_t CTAS:3;
                vuint32_t EOQ:1;
                vuint32_t CTCNT:1;
                  vuint32_t:4;
                vuint32_t PCS5:1;
                vuint32_t PCS4:1;
                vuint32_t PCS3:1;
                vuint32_t PCS2:1;
                vuint32_t PCS1:1;
                vuint32_t PCS0:1;
                vuint32_t TXDATA:16;
            } B;
        } PUSHR;                /* PUSH TX FIFO Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t:16;
                vuint32_t RXDATA:16;
            } B;
        } POPR;                 /* POP RX FIFO Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t TXCMD:16;
                vuint32_t TXDATA:16;
            } B;
        } TXFR[4];              /* Transmit FIFO Registers */

        vuint32_t DSPI_reserved_txf[12];

        union {
            vuint32_t R;
            struct {
                vuint32_t:16;
                vuint32_t RXDATA:16;
            } B;
        } RXFR[4];              /* Transmit FIFO Registers */

        vuint32_t DSPI_reserved_rxf[12];

        union {
            vuint32_t R;
            struct {
                vuint32_t MTOE:1;
                  vuint32_t:1;
                vuint32_t MTOCNT:6;
                  vuint32_t:4;
                vuint32_t TXSS:1;
                vuint32_t TPOL:1;
                vuint32_t TRRE:1;
                vuint32_t CID:1;
                vuint32_t DCONT:1;
                vuint32_t DSICTAS:3;
                  vuint32_t:6;
                vuint32_t DPCS5:1;
                vuint32_t DPCS4:1;
                vuint32_t DPCS3:1;
                vuint32_t DPCS2:1;
                vuint32_t DPCS1:1;
                vuint32_t DPCS0:1;
            } B;
        } DSICR;                /* DSI Configuration Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t:16;
                vuint32_t SER_DATA:16;
            } B;
        } SDR;                  /* DSI Serialization Data Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t:16;
                vuint32_t ASER_DATA:16;
            } B;
        } ASDR;                 /* DSI Alternate Serialization Data Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t:16;
                vuint32_t COMP_DATA:16;
            } B;
        } COMPR;                /* DSI Transmit Comparison Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t:16;
                vuint32_t DESER_DATA:16;
            } B;
        } DDR;                  /* DSI deserialization Data Register */

    };
/****************************************************************************/
/*                          MODULE : eSCI                                   */
/****************************************************************************/
    struct ESCI_tag {
        union {
            vuint32_t R;
            struct {
                vuint32_t:3;
                vuint32_t SBR:13;
                vuint32_t LOOPS:1;
                vuint32_t SCISDOZ:1;
                vuint32_t RSRC:1;
                vuint32_t M:1;
                vuint32_t WAKE:1;
                vuint32_t ILT:1;
                vuint32_t PE:1;
                vuint32_t PT:1;
                vuint32_t TIE:1;
                vuint32_t TCIE:1;
                vuint32_t RIE:1;
                vuint32_t ILIE:1;
                vuint32_t TE:1;
                vuint32_t RE:1;
                vuint32_t RWU:1;
                vuint32_t SBK:1;
            } B;
        } CR1;                  /* Control Register 1 */

        union {
            vuint16_t R;
            struct {
                vuint16_t MDIS:1;
                vuint16_t FBR:1;
                vuint16_t BSTP:1;
                vuint16_t IEBERR:1;
                vuint16_t RXDMA:1;
                vuint16_t TXDMA:1;
                vuint16_t BRK13:1;
                  vuint16_t:1;
                vuint16_t BESM13:1;
                vuint16_t SBSTP:1;
                  vuint16_t:2;
                vuint16_t ORIE:1;
                vuint16_t NFIE:1;
                vuint16_t FEIE:1;
                vuint16_t PFIE:1;
            } B;
        } CR2;                  /* Control Register 2 */

        union {
            vuint16_t R;
            struct {
                vuint16_t R8:1;
                vuint16_t T8:1;
                  vuint16_t:6;
                vuint8_t D;
            } B;
        } DR;                   /* Data Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t TDRE:1;
                vuint32_t TC:1;
                vuint32_t RDRF:1;
                vuint32_t IDLE:1;
                vuint32_t OR:1;
                vuint32_t NF:1;
                vuint32_t FE:1;
                vuint32_t PF:1;
                  vuint32_t:3;
                vuint32_t BERR:1;
                  vuint32_t:3;
                vuint32_t RAF:1;
                vuint32_t RXRDY:1;
                vuint32_t TXRDY:1;
                vuint32_t LWAKE:1;
                vuint32_t STO:1;
                vuint32_t PBERR:1;
                vuint32_t CERR:1;
                vuint32_t CKERR:1;
                vuint32_t FRC:1;
                  vuint32_t:7;
                vuint32_t OVFL:1;
            } B;
        } SR;                   /* Status Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t LRES:1;
                vuint32_t WU:1;
                vuint32_t WUD0:1;
                vuint32_t WUD1:1;
                vuint32_t LDBG:1;
                vuint32_t DSF:1;
                vuint32_t PRTY:1;
                vuint32_t LIN:1;
                vuint32_t RXIE:1;
                vuint32_t TXIE:1;
                vuint32_t WUIE:1;
                vuint32_t STIE:1;
                vuint32_t PBIE:1;
                vuint32_t CIE:1;
                vuint32_t CKIE:1;
                vuint32_t FCIE:1;
                  vuint32_t:7;
                vuint32_t OFIE:1;
                  vuint32_t:8;
            } B;
        } LCR;                  /* LIN Control Register */

        union {
            vuint32_t R;
        } LTR;                  /* LIN Transmit Register */

        union {
            vuint32_t R;
        } LRR;                  /* LIN Recieve Register */

        union {
            vuint32_t R;
        } LPR;                  /* LIN CRC Polynom Register  */

    };
/****************************************************************************/
/*                          MODULE : FlexCAN                                */
/****************************************************************************/
    struct FLEXCAN2_tag {
        union {
            vuint32_t R;
            struct {
                vuint32_t MDIS:1;
                vuint32_t FRZ:1;
                  vuint32_t:1;
                vuint32_t HALT:1;
                vuint32_t NOTRDY:1;
                  vuint32_t:1;
                vuint32_t SOFTRST:1;
                vuint32_t FRZACK:1;
                  vuint32_t:1;
                  vuint32_t:1;
                  vuint32_t:1;
                vuint32_t MDISACK:1;
                  vuint32_t:1;
                  vuint32_t:1;
                  vuint32_t:12;
                vuint32_t MAXMB:6;
            } B;
        } MCR;                  /* Module Configuration Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t PRESDIV:8;
                vuint32_t RJW:2;
                vuint32_t PSEG1:3;
                vuint32_t PSEG2:3;
                vuint32_t BOFFMSK:1;
                vuint32_t ERRMSK:1;
                vuint32_t CLKSRC:1;
                vuint32_t LPB:1;
                  vuint32_t:4;
                vuint32_t SMP:1;
                vuint32_t BOFFREC:1;
                vuint32_t TSYN:1;
                vuint32_t LBUF:1;
                vuint32_t LOM:1;
                vuint32_t PROPSEG:3;
            } B;
        } CR;                   /* Control Register */

        union {
            vuint32_t R;
        } TIMER;                /* Free Running Timer */
        int32_t FLEXCAN_reserved00;

        union {
            vuint32_t R;
            struct {
                vuint32_t:3;
                vuint32_t MI:29;
            } B;
        } RXGMASK;              /* RX Global Mask */

        union {
            vuint32_t R;
            struct {
                vuint32_t:3;
                vuint32_t MI:29;
            } B;
        } RX14MASK;             /* RX 14 Mask */

        union {
            vuint32_t R;
            struct {
                vuint32_t:3;
                vuint32_t MI:29;
            } B;
        } RX15MASK;             /* RX 15 Mask */

        union {
            vuint32_t R;
            struct {
                vuint32_t:16;
                vuint32_t RXECNT:8;
                vuint32_t TXECNT:8;
            } B;
        } ECR;                  /* Error Counter Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t:16;
                vuint32_t BIT1ERR:1;
                vuint32_t BIT0ERR:1;
                vuint32_t ACKERR:1;
                vuint32_t CRCERR:1;
                vuint32_t FRMERR:1;
                vuint32_t STFERR:1;
                vuint32_t TXWRN:1;
                vuint32_t RXWRN:1;
                vuint32_t IDLE:1;
                vuint32_t TXRX:1;
                vuint32_t FLTCONF:2;
                  vuint32_t:1;
                vuint32_t BOFFINT:1;
                vuint32_t ERRINT:1;
                  vuint32_t:1;
            } B;
        } ESR;                  /* Error and Status Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t BUF63M:1;
                vuint32_t BUF62M:1;
                vuint32_t BUF61M:1;
                vuint32_t BUF60M:1;
                vuint32_t BUF59M:1;
                vuint32_t BUF58M:1;
                vuint32_t BUF57M:1;
                vuint32_t BUF56M:1;
                vuint32_t BUF55M:1;
                vuint32_t BUF54M:1;
                vuint32_t BUF53M:1;
                vuint32_t BUF52M:1;
                vuint32_t BUF51M:1;
                vuint32_t BUF50M:1;
                vuint32_t BUF49M:1;
                vuint32_t BUF48M:1;
                vuint32_t BUF47M:1;
                vuint32_t BUF46M:1;
                vuint32_t BUF45M:1;
                vuint32_t BUF44M:1;
                vuint32_t BUF43M:1;
                vuint32_t BUF42M:1;
                vuint32_t BUF41M:1;
                vuint32_t BUF40M:1;
                vuint32_t BUF39M:1;
                vuint32_t BUF38M:1;
                vuint32_t BUF37M:1;
                vuint32_t BUF36M:1;
                vuint32_t BUF35M:1;
                vuint32_t BUF34M:1;
                vuint32_t BUF33M:1;
                vuint32_t BUF32M:1;
            } B;
        } IMRH;                 /* Interruput Masks Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t BUF31M:1;
                vuint32_t BUF30M:1;
                vuint32_t BUF29M:1;
                vuint32_t BUF28M:1;
                vuint32_t BUF27M:1;
                vuint32_t BUF26M:1;
                vuint32_t BUF25M:1;
                vuint32_t BUF24M:1;
                vuint32_t BUF23M:1;
                vuint32_t BUF22M:1;
                vuint32_t BUF21M:1;
                vuint32_t BUF20M:1;
                vuint32_t BUF19M:1;
                vuint32_t BUF18M:1;
                vuint32_t BUF17M:1;
                vuint32_t BUF16M:1;
                vuint32_t BUF15M:1;
                vuint32_t BUF14M:1;
                vuint32_t BUF13M:1;
                vuint32_t BUF12M:1;
                vuint32_t BUF11M:1;
                vuint32_t BUF10M:1;
                vuint32_t BUF09M:1;
                vuint32_t BUF08M:1;
                vuint32_t BUF07M:1;
                vuint32_t BUF06M:1;
                vuint32_t BUF05M:1;
                vuint32_t BUF04M:1;
                vuint32_t BUF03M:1;
                vuint32_t BUF02M:1;
                vuint32_t BUF01M:1;
                vuint32_t BUF00M:1;
            } B;
        } IMRL;                 /* Interruput Masks Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t BUF63I:1;
                vuint32_t BUF62I:1;
                vuint32_t BUF61I:1;
                vuint32_t BUF60I:1;
                vuint32_t BUF59I:1;
                vuint32_t BUF58I:1;
                vuint32_t BUF57I:1;
                vuint32_t BUF56I:1;
                vuint32_t BUF55I:1;
                vuint32_t BUF54I:1;
                vuint32_t BUF53I:1;
                vuint32_t BUF52I:1;
                vuint32_t BUF51I:1;
                vuint32_t BUF50I:1;
                vuint32_t BUF49I:1;
                vuint32_t BUF48I:1;
                vuint32_t BUF47I:1;
                vuint32_t BUF46I:1;
                vuint32_t BUF45I:1;
                vuint32_t BUF44I:1;
                vuint32_t BUF43I:1;
                vuint32_t BUF42I:1;
                vuint32_t BUF41I:1;
                vuint32_t BUF40I:1;
                vuint32_t BUF39I:1;
                vuint32_t BUF38I:1;
                vuint32_t BUF37I:1;
                vuint32_t BUF36I:1;
                vuint32_t BUF35I:1;
                vuint32_t BUF34I:1;
                vuint32_t BUF33I:1;
                vuint32_t BUF32I:1;
            } B;
        } IFRH;                 /* Interruput Flag Register */

        union {
            vuint32_t R;
            struct {
                vuint32_t BUF31I:1;
                vuint32_t BUF30I:1;
                vuint32_t BUF29I:1;
                vuint32_t BUF28I:1;
                vuint32_t BUF27I:1;
                vuint32_t BUF26I:1;
                vuint32_t BUF25I:1;
                vuint32_t BUF24I:1;
                vuint32_t BUF23I:1;
                vuint32_t BUF22I:1;
                vuint32_t BUF21I:1;
                vuint32_t BUF20I:1;
                vuint32_t BUF19I:1;
                vuint32_t BUF18I:1;
                vuint32_t BUF17I:1;
                vuint32_t BUF16I:1;
                vuint32_t BUF15I:1;
                vuint32_t BUF14I:1;
                vuint32_t BUF13I:1;
                vuint32_t BUF12I:1;
                vuint32_t BUF11I:1;
                vuint32_t BUF10I:1;
                vuint32_t BUF09I:1;
                vuint32_t BUF08I:1;
                vuint32_t BUF07I:1;
                vuint32_t BUF06I:1;
                vuint32_t BUF05I:1;
                vuint32_t BUF04I:1;
                vuint32_t BUF03I:1;
                vuint32_t BUF02I:1;
                vuint32_t BUF01I:1;
                vuint32_t BUF00I:1;
            } B;
        } IFRL;                 /* Interruput Flag Register */

        uint32_t flexcan2_reserved2[19];

        struct canbuf_t {
            union {
                vuint32_t R;
                struct {
                    vuint32_t:4;
                    vuint32_t CODE:4;
                      vuint32_t:1;
                    vuint32_t SRR:1;
                    vuint32_t IDE:1;
                    vuint32_t RTR:1;
                    vuint32_t LENGTH:4;
                    vuint32_t TIMESTAMP:16;
                } B;
            } CS;

            union {
                vuint32_t R;
                struct {
                    vuint32_t:3;
                    vuint32_t STD_ID:11;
                    vuint32_t EXT_ID:18;
                } B;
            } ID;

            union {
                vuint8_t B[8];  /* Data buffer in Bytes (8 bits) */
                vuint16_t H[4]; /* Data buffer in Half-words (16 bits) */
                vuint32_t W[2]; /* Data buffer in words (32 bits) */
                vuint32_t R[2]; /* Data buffer in words (32 bits) */
            } DATA;

        } BUF[64];

    };

/* Define memories */

#define SRAM_START  0x40000000
#define SRAM_SIZE      0x10000
#define SRAM_END    0x4000FFFF

#define FLASH_START         0x0
#define FLASH_SIZE     0x200000
#define FLASH_END      0x1FFFFF

/* Define instances of modules */
#define PBRIDGE_A (*( struct PBRIDGE_A_tag *) 0xC3F00000)
#define FMPLL     (*( struct FMPLL_tag *)     0xC3F80000)
#define EBI       (*( struct EBI_tag *)       0xC3F84000)
#define FLASH     (*( struct FLASH_tag *)     0xC3F88000)
#define SIU       (*( struct SIU_tag *)       0xC3F90000)

#define EMIOS     (*( struct EMIOS_tag *)     0xC3FA0000)
#define ETPU      (*( struct ETPU_tag *)      0xC3FC0000)
#define ETPU_DATA_RAM  (*( uint32_t *)        0xC3FC8000)
#define ETPU_DATA_RAM_EXT  (*( uint32_t *)    0xC3FCC000)
#define ETPU_DATA_RAM_END  0xC3FC8BFC
#define CODE_RAM       (*( uint32_t *)        0xC3FD0000)
#define ETPU_CODE_RAM  (*( uint32_t *)        0xC3FD0000)

#define PBRIDGE_B (*( struct PBRIDGE_B_tag *) 0xFFF00000)
#define XBAR      (*( struct XBAR_tag *)      0xFFF04000)
#define ECSM      (*( struct ECSM_tag *)      0xFFF40000)
#define EDMA      (*( struct EDMA_tag *)      0xFFF44000)
#define INTC      (*( struct INTC_tag *)      0xFFF48000)

#define EQADC     (*( struct EQADC_tag *)     0xFFF80000)

#define DSPI_A    (*( struct DSPI_tag *)      0xFFF90000)
#define DSPI_B    (*( struct DSPI_tag *)      0xFFF94000)
#define DSPI_C    (*( struct DSPI_tag *)      0xFFF98000)
#define DSPI_D    (*( struct DSPI_tag *)      0xFFF9C000)

#define ESCI_A    (*( struct ESCI_tag *)      0xFFFB0000)
#define ESCI_B    (*( struct ESCI_tag *)      0xFFFB4000)

#define CAN_A     (*( struct FLEXCAN2_tag *)  0xFFFC0000)
#define CAN_B     (*( struct FLEXCAN2_tag *)  0xFFFC4000)
#define CAN_C     (*( struct FLEXCAN2_tag *)  0xFFFC8000)

#ifdef __MWERKS__
#pragma pop
#endif

#ifdef  __cplusplus
}
#endif
#endif                          /* ifdef _MPC5554_H */
/*********************************************************************
 *
 * Copyright:
 *	Freescale Semiconductor, INC. All Rights Reserved.
 *  You are hereby granted a copyright license to use, modify, and
 *  distribute the SOFTWARE so long as this entire notice is
 *  retained without alteration in any modified and/or redistributed
 *  versions, and that such modified versions are clearly identified
 *  as such. No licenses are granted by implication, estoppel or
 *  otherwise under any patents or trademarks of Freescale
 *  Semiconductor, Inc. This software is provided on an "AS IS"
 *  basis and without warranty.
 *
 *  To the maximum extent permitted by applicable law, Freescale
 *  Semiconductor DISCLAIMS ALL WARRANTIES WHETHER EXPRESS OR IMPLIED,
 *  INCLUDING IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A
 *  PARTICULAR PURPOSE AND ANY WARRANTY AGAINST INFRINGEMENT WITH
 *  REGARD TO THE SOFTWARE (INCLUDING ANY MODIFIED VERSIONS THEREOF)
 *  AND ANY ACCOMPANYING WRITTEN MATERIALS.
 *
 *  To the maximum extent permitted by applicable law, IN NO EVENT
 *  SHALL Freescale Semiconductor BE LIABLE FOR ANY DAMAGES WHATSOEVER
 *  (INCLUDING WITHOUT LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS,
 *  BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR OTHER
 *  PECUNIARY LOSS) ARISING OF THE USE OR INABILITY TO USE THE SOFTWARE.
 *
 *  Freescale Semiconductor assumes no responsibility for the
 *  maintenance and support of this software
 *
 ********************************************************************/
