/**************************************************************************
 * Copyright (C) 2020 ASH WARE, Inc.
 *************************************************************************/
/**************************************************************************
* FILE NAME: etec_MS1553_RX.c   
* 
* DESCRIPTION: This file contains the thread and function definitions common
* across all MIL-STD-1553 receiver eTPU drivers (MT, RT, BC) - the low-level
* receive code.
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
// verify this code uses no stack or scratchpad
#pragma verify_memory_size STACK 0x00 bytes
#pragma verify_memory_size GLOBAL_SCRATCHPAD 0x00 bytes

#pragma same_channel_frame_base MS1553

#include <ETpu_Std.h>
#include "etec_MS1553_common.h"
#include "etec_MS1553.h"


/***************************************************************************/
/* RX_P Entry Table Definition
/***************************************************************************/
/* DESCRIPTION:
/* The table below configures the 32 unique entry points for the low-level
/* MIL-STD-1553 receiver (RX) eTPU code (positive digital input).
/* Note that all functions/channels that service the 1553 bus for a terminal
/* share an eTPU channel frame.
/*
/***************************************************************************/
DEFINE_ENTRY_TABLE(MS1553, MS1553_RX_P, alternate, inputpin, autocfsr)
{

	//-----------------------------------------------------
	// Valid states, ...
	//           HSR    LSR M1 M2 PIN F0 F1 vector
	ETPU_VECTOR2(6,7,   x,  x, x, x,  x, x, Init_RX),
	ETPU_VECTOR2(2,3,   x,  x, x, 0,  0, x, Shutdown_RX),
	ETPU_VECTOR2(2,3,   x,  x, x, 0,  1, x, Shutdown_RX),
	ETPU_VECTOR2(2,3,   x,  x, x, 1,  0, x, Shutdown_RX),
	ETPU_VECTOR2(2,3,   x,  x, x, 1,  1, x, Shutdown_RX),

	ETPU_VECTOR1(0,     x,  0, 1, 0,  0, 0, SeekSynchP_RX),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  0, 0, SeekSynchP_RX),

	ETPU_VECTOR1(0,     x,  0, 1, 0,  1, 0, AwaitInitIdleP),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  1, 0, AwaitInitIdleP),

	ETPU_VECTOR1(0,     x,  1, 0, 0,  1, 0, FoundInitIdle),
	ETPU_VECTOR1(0,     x,  1, 0, 1,  1, 0, FoundInitIdle),
	// When Both TDL and MRL are set, MRL must have occurred first ...
	ETPU_VECTOR1(0,     x,  1, 1, 0,  1, 0, FoundInitIdle),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  1, 0, FoundInitIdle),

	ETPU_VECTOR1(0,     x,  1, 0, 0,  0, 0, FoundIdle_RX),
	ETPU_VECTOR1(0,     x,  1, 0, 1,  0, 0, FoundIdle_RX),
	// When Both TDL and MRL are set, MRL must have occurred first ...
	ETPU_VECTOR1(0,     x,  1, 1, 0,  0, 0, FoundIdle_RX),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  0, 0, FoundIdle_RX),


	ETPU_VECTOR1(0,     x,  0, 1, 0,  1, 1, FromOneBit),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  1, 1, FromOneBit),

	ETPU_VECTOR1(0,     x,  0, 1, 0,  0, 1, FromZeroBit),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  0, 1, FromZeroBit),

	ETPU_VECTOR1(0,     x,  1, 0, 0,  0, 1, HandleWord_RX),
	ETPU_VECTOR1(0,     x,  1, 0, 1,  0, 1, HandleWord_RX),
	ETPU_VECTOR1(0,     x,  1, 0, 0,  1, 1, HandleWord_RX),
	ETPU_VECTOR1(0,     x,  1, 0, 1,  1, 1, HandleWord_RX),
	// in the cases below the HandleWord match has been pushed back into further
	// signal activity - process the HandleWord and then handle transition detection in
	// separate thread
	ETPU_VECTOR1(0,     x,  1, 1, 0,  0, 1, HandleWord_RX),
	ETPU_VECTOR1(0,     x,  1, 1, 0,  1, 1, HandleWord_RX),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  0, 1, HandleWord_RX),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  1, 1, HandleWord_RX),

	//-----------------------------------------------------
	// Unused States
	//           HSR    LSR M1 M2 PIN F0 F1 vector
	ETPU_VECTOR3(1,4,5, x,  x, x, x,  x, x, _Error_handler_entry),
	ETPU_VECTOR1(0,     1,  0, 0, 0,  x, x, _Error_handler_entry),
	ETPU_VECTOR1(0,     1,  0, 0, 1,  x, x, _Error_handler_entry),
};

/***************************************************************************/
/* RX_N Entry Table Definition
/***************************************************************************/
/* DESCRIPTION:
/* The table below configures the 32 unique entry points for the low-level
/* MIL-STD-1553 receiver (RX) eTPU code (negative digital input).
/* Note that all functions/channels that service the 1553 bus for a terminal
/* share an eTPU channel frame.
/*
/***************************************************************************/
DEFINE_ENTRY_TABLE(MS1553, MS1553_RX_N, alternate, inputpin, autocfsr)
{

	// Valid states, ...

	//           HSR    LSR M1 M2 PIN F0 F1 vector
	ETPU_VECTOR1(0,     x,  0, 1, 0,  1, 0, AwaitInitIdleN),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  1, 0, AwaitInitIdleN),

	ETPU_VECTOR1(0,     x,  0, 1, 0,  0, 0, SeekSynchN_RX),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  0, 0, SeekSynchN_RX),

	// Unused States
	//           HSR    LSR M1 M2 PIN F0 F1 vector
	ETPU_VECTOR2(2,3,   x,  x, x, 0,  0, x, _Error_handler_entry),
	ETPU_VECTOR2(2,3,   x,  x, x, 0,  1, x, _Error_handler_entry),
	ETPU_VECTOR2(2,3,   x,  x, x, 1,  0, x, _Error_handler_entry),
	ETPU_VECTOR2(2,3,   x,  x, x, 1,  1, x, _Error_handler_entry),
	ETPU_VECTOR3(1,4,5, x,  x, x, x,  x, x, _Error_handler_entry),
	ETPU_VECTOR2(6,7,   x,  x, x, x,  x, x, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 0, 0,  0, 0, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 0, 1,  0, 0, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 0, 0,  1, 0, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 0, 0,  0, 1, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 0, 0,  1, 1, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 0, 1,  1, 0, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 0, 1,  0, 1, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 0, 1,  1, 1, _Error_handler_entry),
	ETPU_VECTOR1(0,     1,  0, 0, 0,  x, x, _Error_handler_entry),
	ETPU_VECTOR1(0,     1,  0, 0, 1,  x, x, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  0, 1, 0,  0, 1, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  0, 1, 0,  1, 1, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  0, 1, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  1, 1, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 1, 0,  0, 0, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 1, 0,  1, 0, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 1, 0,  0, 1, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 1, 0,  1, 1, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  0, 0, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  1, 0, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  0, 1, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  1, 1, _Error_handler_entry),
};


/***************************************************************************/
/* Init_RX eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread configures the RX channel pair for 1553 input processing. 
/*
/***************************************************************************/
_eTPU_thread MS1553::Init_RX(_eTPU_matches_disabled)
{
    _rxBufPtr = _rxBuf;
    InitCommon_RX();
}

/***************************************************************************/
/* Shutdown_RX eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread disables the RX channel pair such that they will not react to
/* input signals nor interrupt the host.
/*
/***************************************************************************/
_eTPU_thread MS1553::Shutdown_RX(_eTPU_matches_disabled)
{
    DisableMatch();
    DisableEventHandling();
	ClearAllLatches();
    
    chan += 1;
    DisableMatch();
    DisableEventHandling();
	ClearAllLatches();
}

/***************************************************************************/
/* SeekSynchP_RX eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread activates when a rising edge is detected on the positive RX input
/* while seeking a sync.
/*
/***************************************************************************/
_eTPU_thread MS1553::SeekSynchP_RX(_eTPU_matches_enabled)
{
	ClearTransLatch();
	SeekSynchCommonP();
}

/***************************************************************************/
/* SeekSynchN_RX eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread activates when a rising edge is detected on the negative RX input
/* while seeking a sync.
/*
/***************************************************************************/
_eTPU_thread MS1553::SeekSynchN_RX(_eTPU_matches_enabled)
{
	ClearTransLatch();
    SeekSynchCommonN();
}

/***************************************************************************/
/* HandleWord_RX eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread activates 0.25us after the expected end of a word - it verifies
/* the word is valid and if so stores it in the receive buffer.
/*
/***************************************************************************/
_eTPU_thread MS1553::HandleWord_RX(_eTPU_matches_enabled)
{
	int receivedWord = (int) _rxBuffer;

	// - This thread is scheduled 0.25 bits past the parity.
	//
	// - An idle lasts at least 2 bits. (4 bits mid-parity to mid-sync)
	// 
	// Schedule a thread 1.75 bits from this thread
	// that detects an idle.
    read_mer();
    ertA = ertA + _1P75_bits;
    ClearMatchALatch();
    WriteErtAToMatchAAndEnable();

	//----------------------------------
	// Go back to the 'searching for synch' state
	ClrFlag0();
	ClrFlag1();

	//----------------------------------
	// Change channels and enable transition detection
	chan = chan + 1;
	DetectARisingEdge();

	//----------------------------------
	if( _rxBitCount==16)
	{
		// Only way to get here is if last two bits are '0', '1'
		// Add parity for the '1'
		_rxParityCheck++;
	}
	else if( _rxBitCount==17)
	{
		// Removing the parity bit
		receivedWord = receivedWord>>1;
	}
	else if( _rxBitCount==18)
	{
		// Only way to get here is if last two bits are '0' --> '1' --> CmdSynch
		// Remove parity bit and CmdSynch
		receivedWord = receivedWord>>2;

		// Add the parity bit
		_rxParityCheck++;
	}
	else
	{
		_missingBitError=1;
	}

	//----------------------------------
	// Save the just-received word,
	// but only if no error
	if( !(_missingBitError & 1) )
	{
		// Check parity
		// Set parity error if invalid
		if( !(_rxParityCheck&1) )
		{
			_parityError=1;
		}
		else
		{
			// Word is VALID, so SAVE IT!
			// (No errors)
			*_rxBufPtr++ = receivedWord; // no wrap support (but this code only for test support)
		}
	}

	_synchState = SYNCH_STATE_UNSYNCHED;
}

/***************************************************************************/
/* FoundIdle_RX eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread activates if there has been no bus activity for the 2us following
/* the end of a word.
/*
/***************************************************************************/
_eTPU_thread MS1553::FoundIdle_RX(_eTPU_matches_enabled)
{
	_isLastEdgeAValid = 0;
	_isLastEdgeBValid = 0;

	ClearMatchALatch();
}

/***************************************************************************/
/* AwaitInitIdleP eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread activates when a rising edge is detected on the positive RX input
/* while seeking bus idle after initialization.  The seek is restarted from scratch.
/*
/***************************************************************************/
_eTPU_thread MS1553::AwaitInitIdleP(_eTPU_matches_enabled)
{
    ClearTransLatch();
    // initial idle not found yet, restart search
	erta = erta + _initIdleTimeout;
	WriteErtAToMatchAAndEnable();
}

/***************************************************************************/
/* AwaitInitIdleN eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread activates when a rising edge is detected on the negative RX input
/* while seeking bus idle after initialization.  The seek is restarted from scratch.
/*
/***************************************************************************/
_eTPU_thread MS1553::AwaitInitIdleN(_eTPU_matches_enabled)
{
    int tmp = erta;
    ClearTransLatch();
    // initial idle not found yet, restart search (A chan)
    chan = chan - 1;
    DisableMatch();
	erta = tmp + _initIdleTimeout;
	WriteErtAToMatchAAndEnable();
}

/***************************************************************************/
/* FoundInitIdle eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread activates when the bus has been idle the specified amount of time,
/* post-initialization.  After this, the receiver is in active mode awaiting words.
/*
/***************************************************************************/
_eTPU_thread MS1553::FoundInitIdle(_eTPU_matches_enabled)
{
    ClearMatchALatch();
    ClrFlag0();
    chan = chan + 1;
    ClrFlag0();
}

/***************************************************************************/
/* FromOneBit eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread activates when a rising edge is detected on the positive input, if
/* the previous received bit was a one.
/*
/***************************************************************************/
_eTPU_thread MS1553::FromOneBit(_eTPU_matches_enabled, _eTPU_preload_low)
{
	ClearTransLatch();
	int t = ertA - _firstBitDelineator;
	_rxBitCount++;
	_firstBitDelineator = ertA + _1P25_bits;
	if( t < 0 )
	{
		// Detected a '1'
		_rxBuffer = (_rxBuffer << 1) + 1;
		_rxParityCheck++;
	}
	else if ( t < _0P50_bits )
	{
		// Detected a '0'
		ClrFlag0();
		_rxBuffer = (_rxBuffer << 1) + 0;
	}
	else
	{
		_missingBitError=1;
	}
}

/***************************************************************************/
/* FromZeroBit eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread activates when a rising edge is detected on the positive input, if
/* the previous received bit was a zero.
/*
/***************************************************************************/
_eTPU_thread MS1553::FromZeroBit(_eTPU_matches_enabled, _eTPU_preload_low)
{
    int24 TWO = 2;

	ClearTransLatch();

    int24 t = ertA - _firstBitDelineator;
    int24 tmpRxBuffer = _rxBuffer << 2;
    _firstBitDelineator = ertA + _1P25_bits;
	if( t < 0)
	{
		// Detected a '0'
		_rxBuffer = tmpRxBuffer >> 1 + 0; // only 1 bit detected, correct overshift
		_rxBitCount++;
	}
	else if( (t = t - _0P50_bits) < 0)
	{
		// Detected two bits: '1', '1', detected
		SetFlag0();
		_rxBuffer = tmpRxBuffer + TWO + 1;
		_rxBitCount += TWO;

		// Two one's cancel.
		//_rxParityCheck += 2;
	}
	else if( t - _0P50_bits < 0)
	{
		// Two bits: '1', '0', detected
		_rxBuffer = tmpRxBuffer + TWO;
		_rxBitCount += TWO;
		_rxParityCheck++;
	}
	else
	{
		_missingBitError=1;		
	}
}


/***************************************************************************/
/* InitCommon_RX eTPU fragment
/***************************************************************************/
/* DESCRIPTION:
/* This fragment performs intialization common to multiple terminal types.  The
/* function seeks an intial bus idle after completion of the fragment.
/*
/***************************************************************************/
_eTPU_fragment MS1553::InitCommon_RX()
{
    // initialize P channel
	DisableOutputBuffer();
	DetectARisingEdge();
	DetectBDisable();
	DisableMatch();
	SingleMatchSingleTransition();
	ActionUnitA( MatchTCR1, CaptureTCR1, GreaterEqual);
	ActionUnitB( MatchTCR1, CaptureTCR1, GreaterEqual);
	EnableEventHandling();
	ClearAllLatches();
	SetFlag0();
	ClrFlag1();

	_synchState = SYNCH_STATE_UNSYNCHED;
	_isLastEdgeAValid=0;
	_isLastEdgeBValid=0;
	
	// must find initial idle coming out of initialization
	erta = tcr1 + _initIdleTimeout;
	WriteErtAToMatchAAndEnable();
	
	// initialize N channel
	chan = chan + 1;
	DisableOutputBuffer();
	DetectARisingEdge();
	DetectBDisable();
	DisableMatch();
	SingleMatchSingleTransition();
	ActionUnitA( MatchTCR1, CaptureTCR1, GreaterEqual);
	ActionUnitB( MatchTCR1, CaptureTCR1, GreaterEqual);
	EnableEventHandling();
	ClearAllLatches();
	SetFlag0();
	ClrFlag1();
}

/***************************************************************************/
/* SeekSynchCommonP eTPU fragment
/***************************************************************************/
/* DESCRIPTION:
/* This fragment performs sync seek actions common to multiple terminal types.
/* It executes after a rising edge is found on the positive signal channel.
/*
/***************************************************************************/
_eTPU_fragment MS1553::SeekSynchCommonP()
{
    // Logic:
    //
    // - A valid 'Synch' is received
    //   when the time from RxA to RxB is 1.5 bits (data)
    //   OR when the time from RxB to RxA is 1.5 bits (cmd)

	_LastEdgeOnA = ertA;
	if( _isLastEdgeBValid && (ertA - _LastEdgeOnB) > _1P25_bits )
	{
		// Setup the bit delineator
		_firstBitDelineator = ertA + _2P25_bits;

		// At this point it is a lot like a '0' bit
		// Set the channel flags on 'A' suchly.
		ClrFlag0();
		SetFlag1();

		// Create a 'MATCH' right after the parity bit
		// in 18.75 bits.
		ertA = ertA + _18P75_bits;
		channel.MRLA = MRL_CLEAR; // the idle detect could have fired on A due to latency, after edge detected on B - clear this MRL
		WriteErtAToMatchAAndEnable();

		// Disable Channel 'B' from detecting edges.
		chan = chan + 1;
		DetectADisable();
		channel.TDL = TDL_CLEAR;

		// Initialize the word
		_rxBuffer = 0;
		_rxBitCount = 0;
		_rxParityCheck = 0;

		// Set synch statue
		_synchState = SYNCH_STATE_DATA_WORD;
	}
	else
	{
		// Schedule a thread 2.5 bits from the this thread
		// that detects an idle.
		ertA = ertA + _2P50_bits;
		ClearMatchALatch();
		WriteErtAToMatchAAndEnable();
	}
	_isLastEdgeAValid=1;
}

/***************************************************************************/
/* SeekSynchCommonN eTPU fragment
/***************************************************************************/
/* DESCRIPTION:
/* This fragment performs sync seek actions common to multiple terminal types.
/* It executes after a rising edge is found on the negative signal channel.
/*
/***************************************************************************/
_eTPU_fragment MS1553::SeekSynchCommonN()
{
    // Logic:
    //
    // - A valid 'Synch' is received
    //   when the time from RxA to RxB is 1.5 bits (data)
    //   OR when the time from RxB to RxA is 1.5 bits (cmd)

	_LastEdgeOnB = ertA;
	if( _isLastEdgeAValid && (ertA - _LastEdgeOnA) > _1P25_bits  )
	{
		int24 temp = ertA + _18P75_bits;

		// Disable Channel 'B' from detecting edges.
		DetectADisable();

		// Set the bit delineator
		_firstBitDelineator = ertA + _1P75_bits;

		// Switch to channel 'A'
		chan = chan - 1;

		// Create a 'MATCH' right after the parity bit
		// in 18.75 bits.
		ertA = temp;
		channel.MRLA = MRL_CLEAR; // the idle detect could have fired on A due to latency, after edge detected on B - clear this MRL
		WriteErtAToMatchAAndEnable();

		// At this point it is a lot like a '1' bit
		// Set the channel flags on 'A' suchly.
		SetFlag0();
		SetFlag1();

		// Initialize the word
		_rxBuffer = 0;
		_rxBitCount = 0;
		_rxParityCheck = 0;

		// Set synch to '1' (COMMAND/STATUS synch)
		_synchState = SYNCH_STATE_CMD_STATUS_WORD;
	}
	else
	{
		int24 temp = ertA;

		// Switch to channel 'A'
		chan = chan - 1;

		// Schedule a thread 2.5 bits from the this thread
		// that detects an idle.
		ertA = temp + _2P50_bits;
		ClearMatchALatch();
		WriteErtAToMatchAAndEnable();
	}
	_isLastEdgeBValid=1;
}
