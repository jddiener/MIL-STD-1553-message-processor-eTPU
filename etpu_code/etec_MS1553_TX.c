/**************************************************************************
 * Copyright (C) 2020 ASH WARE, Inc.
 *************************************************************************/
/**************************************************************************
* FILE NAME: etec_MS1553_TX.c   
* 
* DESCRIPTION: This file contains the thread and function definitions common
* across all MIL-STD-1553 transmitter eTPU drivers (RT)
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
/* TX Entry Table Definition
/***************************************************************************/
/* DESCRIPTION:
/* The table below configures the 32 unique entry points for the low-level
/* MIL-STD-1553 transmitter (TX) eTPU code.
/* Note that all functions/channels that service the 1553 bus for a terminal
/* share an eTPU channel frame.
/*
/***************************************************************************/
DEFINE_ENTRY_TABLE(MS1553, MS1553_TX, alternate, outputpin, autocfsr)
{
	//           HSR    LSR M1 M2 PIN F0 F1 vector
	ETPU_VECTOR3(1,4,5, x,  x, x, x,  x, x, Transmit),
	ETPU_VECTOR2(6,7,   x,  x, x, x,  x, x, Init_TX),
	ETPU_VECTOR2(2,3,   x,  x, x, 0,  0, x, Shutdown_TX),
	ETPU_VECTOR2(2,3,   x,  x, x, 0,  1, x, Shutdown_TX),
	ETPU_VECTOR2(2,3,   x,  x, x, 1,  0, x, Shutdown_TX),
	ETPU_VECTOR2(2,3,   x,  x, x, 1,  1, x, Shutdown_TX),

	ETPU_VECTOR1(0,     x,  1, 1, 0,  0, 0, StartTransmitBit),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  0, 0, StartTransmitBit),

	ETPU_VECTOR1(0,     x,  1, 1, 0,  1, 0, TransmitBit),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  1, 0, TransmitBit),

	ETPU_VECTOR1(0,     x,  1, 1, 0,  1, 1, TransmitCleanup),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  1, 1, TransmitCleanup),

	ETPU_VECTOR1(0,     x,  0, 1, 0,  1, 1, TransmitComplete),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  1, 1, TransmitComplete),

	//-----------------------------------------------------
	// Unused States
	//           HSR    LSR M1 M2 PIN F0 F1 vector
	ETPU_VECTOR1(0,     1,  0, 0, 0,  x, x, _Error_handler_entry),
	ETPU_VECTOR1(0,     1,  0, 0, 1,  x, x, _Error_handler_entry),
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
/* Init_TX eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread configures the TX channel pair for 1553 output processing. 
/*
/***************************************************************************/
_eTPU_thread MS1553::Init_TX(_eTPU_matches_disabled)
{
	// configure the master channel
	SetPinLow();
	OnTransA( NoDetect );
	OnTransB( NoDetect );
	MatchBSingleTransition();
	ActionUnitA( MatchTCR1, CaptureTCR1, GreaterEqual);
	ActionUnitB( MatchTCR1, CaptureTCR1, GreaterEqual);
	EnableEventHandling();
	ClearAllLatches();
	EnableOutputBuffer();

	chan += 1;
	SetPinLow();
	OnTransA( NoDetect );
	OnTransB( NoDetect );
	MatchBSingleTransition();
	ActionUnitA( MatchTCR1, CaptureTCR1, GreaterEqual);
	ActionUnitB( MatchTCR1, CaptureTCR1, GreaterEqual);
	DisableEventHandling();
	ClearAllLatches();
	EnableOutputBuffer();
}

/***************************************************************************/
/* Shutdown_TX eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread disables any transmission in progress and outputs idle.  Channel pair
/* needs to be re-initialized before resuming transmission.
/*
/***************************************************************************/
_eTPU_thread MS1553::Shutdown_TX(_eTPU_matches_disabled)
{
    DisableMatch();
    SetPinLow();
    DisableEventHandling();
	ClearAllLatches();
    
    chan += 1;
    DisableMatch();
    SetPinLow();
	ClearAllLatches();
}

/***************************************************************************/
/* Transmit eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread is activated by the user to start a transmission of word(s).
/*
/***************************************************************************/
_eTPU_thread MS1553::Transmit(_eTPU_matches_disabled)
{
	erta = ertb = tcr1 + _0P50_bits; // initialize a start time...
	TransmitCommon();
}

/***************************************************************************/
/* TransmitCommon eTPU fragment
/***************************************************************************/
/* DESCRIPTION:
/* This fragment performs transmit setup common to either the intial word or later
/* words in a sequence.
/*
/***************************************************************************/
_eTPU_fragment MS1553::TransmitCommon()
{
    _txNextWordPtr = &_transmitNextWord;
    _transmitNextWord = _transmitWord;    
    _transmitWord &= ~MS1553_TX_DATA_WORD_READY;
	if (_synchType == TT_CMD_STATUS)
    	TransmitCommandSync();
    else
        TransmitDataSync();
}


/***************************************************************************/
/* StartTransmitBit eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread generates the first data bit after the sync, runs at mid-sync.
/* The data to be sent must be written by the user by this point.
/*
/***************************************************************************/
_eTPU_thread MS1553::StartTransmitBit(_eTPU_matches_enabled, _eTPU_preload_high)
{
	_txBuffer = *_txNextWordPtr << 9;
	ClearMatchALatch();
	ClearMatchBLatch();
	SetFlag0();
	if (CC.C)
	{
		// output a 1
		_txParityCheck = 1;
		erta = ertb + _1P50_bits;
		ertb = erta + _0P50_bits;
		OnMatchA(PinHigh);
		OnMatchB(PinLow);
		WriteErtAToMatchAAndEnable();
		WriteErtBToMatchBAndEnable();


		chan += 1;
		erta = ertb + _1P50_bits;
		ertb = erta + _0P50_bits;
		OnMatchA(PinLow);
		OnMatchB(PinHigh);
		ConfigMatch_AB();
	}
	else
	{
		// output a 0
		_txParityCheck = 0;
		erta = ertb + _1P50_bits;
		ertb = erta + _0P50_bits;
		OnMatchA(PinLow);
		OnMatchB(PinHigh);
		WriteErtAToMatchAAndEnable();
		WriteErtBToMatchBAndEnable();


		chan += 1;
		erta = ertb + _1P50_bits;
		ertb = erta + _0P50_bits;
		OnMatchA(PinHigh);
		OnMatchB(PinLow);
		ConfigMatch_AB();
	}
}


/***************************************************************************/
/* TransmitBit eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread runs each bit time to output a bit.  It also generates the final
/* bit, parity.
/*
/***************************************************************************/
_eTPU_thread MS1553::TransmitBit(_eTPU_matches_enabled, _eTPU_preload_high)
{
	ClearMatchALatch();
	ClearMatchBLatch();
	if (--_txBitCount)
	{
		// still have bits to transfer
		_txBuffer = _txBuffer << 1;
		if (CC.C)
		{
			// output a 1
			_txParityCheck++;
			erta = ertb + _0P50_bits;
			ertb = erta + _0P50_bits;
			OnMatchA(PinHigh);
			OnMatchB(PinLow);
			WriteErtAToMatchAAndEnable();
			WriteErtBToMatchBAndEnable();


			chan += 1;
			erta = ertb + _0P50_bits;
			ertb = erta + _0P50_bits;
			OnMatchA(PinLow);
			OnMatchB(PinHigh);
			ConfigMatch_AB();
		}
		else
		{
			// output a 0
			erta = ertb + _0P50_bits;
			ertb = erta + _0P50_bits;
			OnMatchA(PinLow);
			OnMatchB(PinHigh);
			WriteErtAToMatchAAndEnable();
			WriteErtBToMatchBAndEnable();


			chan += 1;
			erta = ertb + _0P50_bits;
			ertb = erta + _0P50_bits;
			OnMatchA(PinHigh);
			OnMatchB(PinLow);
			ConfigMatch_AB();
		}
	}
	else
	{
		// transmit parity...
		SetFlag1();
		if (_txParityCheck & 1)
		{
			// odd parity - output a 0
			erta = ertb + _0P50_bits;
			ertb = erta + _0P50_bits;
			OnMatchA(PinLow);
			OnMatchB(PinHigh);
			WriteErtAToMatchAAndEnable();
			WriteErtBToMatchBAndEnable();


			chan += 1;
			erta = ertb + _0P50_bits;
			ertb = erta + _0P50_bits;
			OnMatchA(PinHigh);
			OnMatchB(PinLow);
			ConfigMatch_AB();
		}
		else
		{
			// odd parity - output a 1
			erta = ertb + _0P50_bits;
			ertb = erta + _0P50_bits;
			OnMatchA(PinHigh);
			OnMatchB(PinLow);
			WriteErtAToMatchAAndEnable();
			WriteErtBToMatchBAndEnable();


			chan += 1;
			erta = ertb + _0P50_bits;
			ertb = erta + _0P50_bits;
			OnMatchA(PinLow);
			OnMatchB(PinHigh);
			ConfigMatch_AB();
		}
	}
}

/***************************************************************************/
/* TransmitCleanup eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread runs half way through the parity bit, and sets up to transmit the
/* next word if one is ready, or end transmission.
/*
/***************************************************************************/
_eTPU_thread MS1553::TransmitCleanup(_eTPU_matches_enabled)
{
	ClearMatchALatch();
	ClearMatchBLatch();

    if (_transmitWord & MS1553_TX_DATA_WORD_READY)
    {
        // immediately tack on next word
        TransmitCommon();
    }

	// if here, then this is the end of a transmit sequence...

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
/* TransmitComplete eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread runs when transmission has fully completed and the bus has gone idle.
/*
/***************************************************************************/
_eTPU_thread MS1553::TransmitComplete(_eTPU_matches_enabled)
{
	ClearMatchALatch();
	ClearMatchBLatch();
}

/***************************************************************************/
/* TransmitCommandSync eTPU fragment
/***************************************************************************/
/* DESCRIPTION:
/* This fragment starts the generation of a command sync.
/*
/***************************************************************************/
_eTPU_fragment MS1553::TransmitCommandSync()
{
	unsigned int24 start;

	_txBitCount = 16;

	ClrFlag0();
	ClrFlag1();

	// command sync
	OnMatchA(PinHigh);
	OnMatchB(PinLow);

	erta = start = ertb + _0P50_bits; // set start of sync
	ertb = start + _1P50_bits;
	ConfigMatch_AB();


	chan += 1;

	// command sync
	OnMatchA(PinLow);
	OnMatchB(PinHigh);

	erta = start; // set start of sync
	ertb = start + _1P50_bits;
	ConfigMatch_AB();
}

/***************************************************************************/
/* TransmitDataSync eTPU fragment
/***************************************************************************/
/* DESCRIPTION:
/* This fragment starts the generation of a data sync.
/*
/***************************************************************************/
_eTPU_fragment MS1553::TransmitDataSync()
{
	unsigned int24 start;

	_txBitCount = 16;

	ClrFlag0();
	ClrFlag1();

	// data sync
	OnMatchA(PinLow);
	OnMatchB(PinHigh);

	erta = start = ertb + _0P50_bits; // set start of sync
	ertb = start + _1P50_bits;
	ConfigMatch_AB();


	chan += 1;

	// data sync
	OnMatchA(PinHigh);
	OnMatchB(PinLow);

	erta = start; // set start of sync
	ertb = start + _1P50_bits;
	ConfigMatch_AB();
}

