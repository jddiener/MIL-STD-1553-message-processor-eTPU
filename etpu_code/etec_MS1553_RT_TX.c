/**************************************************************************
 * Copyright (C) 2020 ASH WARE, Inc.
 *************************************************************************/
/**************************************************************************
* FILE NAME: etec_MS1553_RT_TX.c   
* 
* DESCRIPTION: This file contains the thread and function definitions specific
* to the Remote Terminal (RT) MIL-STD-1553 transmitter eTPU drivers
*
* 
*========================================================================
* REV      AUTHOR      DATE        DESCRIPTION OF CHANGE                 
* ---   -----------  ----------    ---------------------                 
* 1.0   John Diener  2020-May-05   Initial release version.
*
**************************************************************************/

// verify proper version of compiler toolset is used
#pragma verify_version GE, "2.62D", "use ETEC version 2.62D or newer"

#pragma same_channel_frame_base MS1553

#include <ETpu_Std.h>
#include "etec_MS1553_common.h"
#include "etec_MS1553.h"


/***************************************************************************/
/* RT_TX Entry Table Definition
/***************************************************************************/
/* DESCRIPTION:
/* The table below configures the 32 unique entry points for the Remote Terminal
/* MIL-STD-1553 transmitter (RT_TX) eTPU code.
/* Note that all functions/channels that service the 1553 bus for a terminal
/* share an eTPU channel frame.
/*
/***************************************************************************/
DEFINE_ENTRY_TABLE(MS1553, MS1553_RT_TX, alternate, outputpin, autocfsr)
{
	//           HSR    LSR M1 M2 PIN F0 F1 vector
	ETPU_VECTOR2(6,7,   x,  x, x, x,  x, x, Init_TX),
	ETPU_VECTOR2(2,3,   x,  x, x, 0,  0, x, Shutdown_TX),
	ETPU_VECTOR2(2,3,   x,  x, x, 0,  1, x, Shutdown_TX),
	ETPU_VECTOR2(2,3,   x,  x, x, 1,  0, x, Shutdown_TX),
	ETPU_VECTOR2(2,3,   x,  x, x, 1,  1, x, Shutdown_TX),

	ETPU_VECTOR1(0,     1,  0, 0, 0,  x, x, TransmitRequest_RT),
	ETPU_VECTOR1(0,     1,  0, 0, 1,  x, x, TransmitRequest_RT), // note: shouldn't happen as transmit should be quiescent at request time

	ETPU_VECTOR1(0,     x,  1, 1, 0,  0, 0, StartTransmitBit),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  0, 0, StartTransmitBit),

	ETPU_VECTOR1(0,     x,  1, 1, 0,  1, 0, TransmitBit),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  1, 0, TransmitBit),

	ETPU_VECTOR1(0,     x,  1, 1, 0,  1, 1, TransmitCleanup_RT),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  1, 1, TransmitCleanup_RT),

	ETPU_VECTOR1(0,     x,  0, 1, 0,  1, 1, TransmitComplete_RT),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  1, 1, TransmitComplete_RT),

	//-----------------------------------------------------
	// Unused States
	//           HSR    LSR M1 M2 PIN F0 F1 vector
	ETPU_VECTOR3(1,4,5, x,  x, x, x,  x, x, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 0, 0,  0, 0, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 0, 0,  1, 0, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 0, 0,  0, 1, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 0, 0,  1, 1, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 0, 1,  0, 0, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 0, 1,  1, 0, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 0, 1,  0, 1, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 0, 1,  1, 1, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  0, 1, 0,  0, 0, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  0, 1, 0,  1, 0, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  0, 1, 0,  0, 1, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  0, 0, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  1, 0, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  0, 1, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 1, 0,  0, 1, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  0, 1, _Error_handler_entry),	
};


/***************************************************************************/
/* TransmitRequest_RT eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread is activated by link from the RT master RX channel - it kicks off
/* the transmission of an RT response.
/*
/***************************************************************************/
_eTPU_thread MS1553::TransmitRequest_RT(_eTPU_matches_enabled)
{
    channel.LSR = LSR_CLEAR;

	erta = ertb = tcr1 + _txDelay; // initialize a start time...

    //_txBuffer = _txStatusWord << 8;
    _txNextWordPtr = &_txStatusWord;
    _txBufPtr = _txBuf;
   	TransmitCommandSync();
}

/***************************************************************************/
/* TransmitCleanup_RT eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread runs half way through the parity bit, and sets up to transmit the
/* next word if necessary, or end transmission.
/*
/***************************************************************************/
_eTPU_thread MS1553::TransmitCleanup_RT(_eTPU_matches_enabled)
{
	ClearMatchALatch();
	ClearMatchBLatch();

    if (--_txWordCnt >= 0 && (_txDataWordInhibit & TX_INHIBIT_BITMASK) == TX_INHIBIT_DISABLE)
    {
        // IF THERE IS ANOTHER WORD TO TRANSMIT, THE SYNC MUST BE CONTIGUOUS TO THE PARITY BIT!!
        // IMMEDIATELY SET UP NEXT SYNC
        if (_txType & TRS_STATUS_DATA)
        {
            _txNextWordPtr = _txBufPtr;
            _txBufPtr++;
        }
        else // if (_txType & TRS_STATUS_MODE)
            _txNextWordPtr = &_txModeWord;
        TransmitDataSync();
    }

	// if here, then this is the end of the transmit sequence...

	_txEndTimestamp = ertb;

	// need to get pins low...
	ertb = ertb + _0P50_bits;
	OnMatchB(PinLow);
	WriteErtBToMatchBAndEnable();

	chan += 1;
	ertb = ertb + _0P50_bits;
	OnMatchB(PinLow);
	ClearMatchALatch();
	ClearMatchBLatch();
	WriteErtBToMatchBAndEnable();
}

/***************************************************************************/
/* TransmitComplete_RT eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread runs when transmission has fully completed and the bus has gone idle.
/* The RT RX master channel is sent a link to let it know that the tranmsision
/* sequence is complete.
/*
/***************************************************************************/
_eTPU_thread MS1553::TransmitComplete_RT(_eTPU_matches_enabled)
{
	ClearMatchALatch();
	ClearMatchBLatch();
	// notify RT-RX that transmit is done
	link = _rxBaseChan;
}
