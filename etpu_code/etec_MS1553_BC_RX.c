/**************************************************************************
 * Copyright (C) 2020 ASH WARE, Inc.
 *************************************************************************/
/**************************************************************************
* FILE NAME: etec_MS1553_BC_RX.c   
* 
* DESCRIPTION: This file contains the thread and function definitions specific
* to the Bus Controller (BC) MIL-STD-1553 receiver eTPU driver
*
* 
*========================================================================
* REV      AUTHOR      DATE        DESCRIPTION OF CHANGE                 
* ---   -----------  ----------    ---------------------                 
* 1.0   John Diener  2020-May-27   Initial release version.
*
**************************************************************************/

// verify proper version of compiler toolset is used
#pragma verify_version GE, "2.62D", "use ETEC version 2.62D or newer"

#pragma same_channel_frame_base MS1553

#include <ETpu_Std.h>
#include "etec_MS1553_common.h"
#include "etec_MS1553.h"


/***************************************************************************/
/* BC_RX_P Entry Table Definition
/***************************************************************************/
/* DESCRIPTION:
/* The table below configures the 32 unique entry points for the Bus Controller
/* MIL-STD-1553 receiver (BC_RX) eTPU code (positive digital input).
/* Note that all functions/channels that service the 1553 bus for a terminal
/* share an eTPU channel frame.
/*
/***************************************************************************/
DEFINE_ENTRY_TABLE(MS1553, MS1553_BC_RX_P, alternate, inputpin, autocfsr)
{

	//-----------------------------------------------------
	// Valid states, ...
	//           HSR    LSR M1 M2 PIN F0 F1 vector
	ETPU_VECTOR2(6,7,   x,  x, x, x,  x, x, Init_BC_RX),
	ETPU_VECTOR2(2,3,   x,  x, x, 0,  0, x, Shutdown_RX),
	ETPU_VECTOR2(2,3,   x,  x, x, 0,  1, x, Shutdown_RX),
	ETPU_VECTOR2(2,3,   x,  x, x, 1,  0, x, Shutdown_RX),
	ETPU_VECTOR2(2,3,   x,  x, x, 1,  1, x, Shutdown_RX),

	ETPU_VECTOR3(1,4,5, x,  x, x, x,  x, x, SeekBusIdleRequest),

	ETPU_VECTOR1(0,     x,  0, 1, 0,  1, 0, SeekBusIdleP),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  1, 0, SeekBusIdleP),
	// When Both TDL and MRL are set, MRL must have occurred first ...
	// BUT, give TDL priority because it means the bus is not truly idle
	ETPU_VECTOR1(0,     x,  1, 1, 0,  1, 0, SeekBusIdleP),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  1, 0, SeekBusIdleP),

	ETPU_VECTOR1(0,     x,  1, 0, 0,  1, 0, SeekBusIdleSuccess),
	ETPU_VECTOR1(0,     x,  1, 0, 1,  1, 0, SeekBusIdleSuccess),
	
	ETPU_VECTOR1(0,     x,  0, 1, 0,  0, 0, SeekSynchP_BC),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  0, 0, SeekSynchP_BC),

	ETPU_VECTOR1(0,     x,  1, 0, 0,  0, 0, FoundIdle_BC),
	ETPU_VECTOR1(0,     x,  1, 0, 1,  0, 0, FoundIdle_BC),
	// When Both TDL and MRL are set, MRL must have occurred first ...
	ETPU_VECTOR1(0,     x,  1, 1, 0,  0, 0, FoundIdle_BC),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  0, 0, FoundIdle_BC),


	ETPU_VECTOR1(0,     x,  0, 1, 0,  1, 1, FromOneBit),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  1, 1, FromOneBit),

	ETPU_VECTOR1(0,     x,  0, 1, 0,  0, 1, FromZeroBit),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  0, 1, FromZeroBit),

	ETPU_VECTOR1(0,     x,  1, 0, 0,  0, 1, HandleWord_BC),
	ETPU_VECTOR1(0,     x,  1, 0, 1,  0, 1, HandleWord_BC),
	ETPU_VECTOR1(0,     x,  1, 0, 0,  1, 1, HandleWord_BC),
	ETPU_VECTOR1(0,     x,  1, 0, 1,  1, 1, HandleWord_BC),
	// in the cases below the HandleWord match has been pushed back into further
	// signal activity - process the HandleWord and then handle transition detection in
	// separate thread
	ETPU_VECTOR1(0,     x,  1, 1, 0,  0, 1, HandleWord_BC),
	ETPU_VECTOR1(0,     x,  1, 1, 0,  1, 1, HandleWord_BC),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  0, 1, HandleWord_BC),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  1, 1, HandleWord_BC),

    // expect message response (BC has already transmitted its part)
	ETPU_VECTOR1(0,     1,  0, 0, 0,  x, x, ExpectMessageResponse_BC),
	ETPU_VECTOR1(0,     1,  0, 0, 1,  x, x, ExpectMessageResponse_BC),

	//-----------------------------------------------------
	// Unused States
	//           HSR    LSR M1 M2 PIN F0 F1 vector
	// <none>
};

/***************************************************************************/
/* BC_RX_N Entry Table Definition
/***************************************************************************/
/* DESCRIPTION:
/* The table below configures the 32 unique entry points for the Bus Controller
/* MIL-STD-1553 receiver (BC_RX) eTPU code (negative digital input).
/* Note that all functions/channels that service the 1553 bus for a terminal
/* share an eTPU channel frame.
/*
/***************************************************************************/
DEFINE_ENTRY_TABLE(MS1553, MS1553_BC_RX_N, alternate, inputpin, autocfsr)
{

	// Valid states, ...

	//           HSR    LSR M1 M2 PIN F0 F1 vector

	ETPU_VECTOR1(0,     x,  0, 1, 0,  1, 0, SeekBusIdleN),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  1, 0, SeekBusIdleN),

	ETPU_VECTOR1(0,     x,  0, 1, 0,  0, 0, SeekSynchN_BC),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  0, 0, SeekSynchN_BC),

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
/* Init_BC_RX eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread configures the RX channel pair for 1553 BC input processing. 
/* RX is disabled at startup and only enabled during portions of messages
/* when RTs are transmitting.
/*
/***************************************************************************/
_eTPU_thread MS1553::Init_BC_RX(_eTPU_matches_disabled)
{
	// initialize P channel
	DisableOutputBuffer();
	DetectADisable(); // start with RX disabled
	DetectBDisable();
	DisableMatch();
	SingleMatchSingleTransition();
	ActionUnitA( MatchTCR1, CaptureTCR1, GreaterEqual);
	ActionUnitB( MatchTCR1, CaptureTCR1, GreaterEqual);
	EnableEventHandling();
	ClearAllLatches();
	ClrFlag0();
	ClrFlag1();

	_synchState = SYNCH_STATE_UNSYNCHED;
	_isLastEdgeAValid=0;
	_isLastEdgeBValid=0;
	
	// initialize N channel
	chan = chan + 1;
	DisableOutputBuffer();
	DetectADisable(); // start with RX disabled
	DetectBDisable();
	DisableMatch();
	SingleMatchSingleTransition();
	ActionUnitA( MatchTCR1, CaptureTCR1, GreaterEqual);
	ActionUnitB( MatchTCR1, CaptureTCR1, GreaterEqual);
	EnableEventHandling();
	ClearAllLatches();
	ClrFlag0();
	ClrFlag1();
}

/***************************************************************************/
/* SeekBusIdleRequest eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread activates upon a host service request to seek a bus idle condition.
/* It kicks off a bus idle seek.
/*
/***************************************************************************/
_eTPU_thread MS1553::SeekBusIdleRequest(_eTPU_matches_disabled)
{
	DetectARisingEdge();
	ClearAllLatches();
	SetFlag0();
	ClrFlag1();
	
	// seek for requested idle period
	erta = tcr1 + _seekIdleTimeout;
	WriteErtAToMatchAAndEnable();
	
	chan = chan + 1;
	DetectARisingEdge();
	ClearAllLatches();
	SetFlag0();
	ClrFlag1();
}

/***************************************************************************/
/* SeekBusIdleP eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread activates when a rising edge is detected on the positive BC_RX input
/* when the idle bus detection feature is activated.
/*
/***************************************************************************/
_eTPU_thread MS1553::SeekBusIdleP(_eTPU_matches_enabled)
{
    ClearTransLatch();
    // idle not found yet, restart search
	erta = erta + _seekIdleTimeout;
	WriteErtAToMatchAAndEnable();
}

/***************************************************************************/
/* SeekBusIdleN eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread activates when a rising edge is detected on the negative BC_RX input
/* when the idle bus detection feature is activated.
/*
/***************************************************************************/
_eTPU_thread MS1553::SeekBusIdleN(_eTPU_matches_enabled)
{
    int tmp = erta;
    ClearTransLatch();
    // idle not found yet, restart search (A chan)
    chan = chan - 1;
    DisableMatch();
	erta = tmp + _seekIdleTimeout;
	WriteErtAToMatchAAndEnable();
}

/***************************************************************************/
/* SeekBusIdleSuccess eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread activates when a bus idle seek is successful.  It generates an interrupt
/* if enabled, and turns off RX (the default state).
/*
/***************************************************************************/
_eTPU_thread MS1553::SeekBusIdleSuccess(_eTPU_matches_enabled)
{
    // alert host that seek idle has succeeded
	_messageStatus = BUS_IDLE_DETECTED;
    if (_messageStatusInterruptMask & BUS_IDLE_DETECTED)
        channel.CIRC = CIRC_INT_FROM_SERVICED;
    
    DetectADisable();
    ClearAllLatches();
    ClrFlag0();
    chan = chan + 1;
    DetectADisable();
    ClearAllLatches();
    ClrFlag0();
}

/***************************************************************************/
/* SeekSynchP_BC eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread activates when a rising edge is detected on the positive BC_RX input
/* while seeking a sync.
/*
/***************************************************************************/
_eTPU_thread MS1553::SeekSynchP_BC(_eTPU_matches_enabled)
{
	ClearTransLatch();
	if ( _state >= MS1553_STATE_AWAIT_IDLE )
	{
		// Expected an idle but got an edge instead.
		// Report this as an error

        // configure to find next idle
        ertA = ertA + _2P50_bits;
        ClearMatchALatch();
        WriteErtAToMatchAAndEnable();
        
   	    Error_InWord_BC(EXPECTED_IDLE_MISSING_ERROR);
	}
	else
    	SeekSynchCommonP();
}

/***************************************************************************/
/* SeekSynchN_BC eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread activates when a rising edge is detected on the negative BC_RX input
/* while seeking a sync.
/*
/***************************************************************************/
_eTPU_thread MS1553::SeekSynchN_BC(_eTPU_matches_enabled)
{
	ClearTransLatch();
	if ( _state >= MS1553_STATE_AWAIT_IDLE )
	{
		// Expected and idle but got an edge instead.
		// Report this as an error

        // configure to find next idle
        int temp = ertA + _2P50_bits;
		chan = chan - 1;
        ertA = temp;
        ClearMatchALatch();
        WriteErtAToMatchAAndEnable();

   	    Error_InWord_BC(EXPECTED_IDLE_MISSING_ERROR);
	}
	else
    	SeekSynchCommonN();
}

/***************************************************************************/
/* HandleWord_BC eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread activates 0.25us after the expected end of a word - it verifies
/* the word is valid and then performs message protocol processing.
/*
/***************************************************************************/
_eTPU_thread MS1553::HandleWord_BC(_eTPU_matches_enabled)
{
	int receivedWord = (int) _rxBuffer;
	int finalParity = _rxParityCheck;

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
		finalParity++;
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
		finalParity++;
	}
	else
	{
	    _missingBitError = 1;
	}

	//----------------------------------
	// Save the just-received word,
	// but only if no error
	
	// check for missing bit error
	if ( _missingBitError & 1 )
	{
	    _missingBitError = 0;
		Error_InWord_BC( MISSING_BIT_ERROR );
	}
	
	// Check parity
	// Set parity error if invalid
	if( !(finalParity&1) )
	{
		Error_InWord_BC( PARITY_ERROR );
	}

	//----------------------------------
	switch (_state)
	{

    		//=====================================
    		//   RT TO CONTROLLER STATES
    		//=====================================

    	case MS1553_STATE_RT_TO_BC_AWAITING_STATUS:
    	{
    		// In an 'RT To Controller Transfer'
    		// Verify next incoming word is an 'RT Status Word'
    		if( _synchState!=SYNCH_STATE_CMD_STATUS_WORD )
    		{
    			// An RT Status was expected
    			// but an RT DATA SYNCH was received instead.
    			Error_InWord_BC(RT_DATA_WHEN_EXPECTED_STATUS_ERROR);
    		}
    		else
    		{
                _rxStatusWord1 = receivedWord;
                _messageStatus = MESSAGE_STATUS_VALID;
                if (_messageStatusInterruptMask & MESSAGE_STATUS_VALID)
                    channel.CIRC = CIRC_INT_FROM_SERVICED;

    			// Set the state to
    			// 'RT To Controller Transfer ... Seeking RT DATA'
    			_state = MS1553_STATE_RT_TO_BC_AWAITING_DATA;
    		}
    		break;
    	}
    	case MS1553_STATE_RT_TO_BC_AWAITING_DATA:
    	{
    		// In an 'RT To Controller Transfer'
    		// Verify next incoming word is an 'RT Data Word'
    		if( _synchState!=SYNCH_STATE_DATA_WORD )
    		{
    			// An RT Status was expected
    			// but an RT DATA SYNCH was received instead.
    			Error_InWord_BC(RT_STATUS_WHEN_EXPECTED_DATA_ERROR);
    		}
    		else
    		{
   			    *_rxBufPtr++ = receivedWord;

    			// Decrement the data word count
    			// If all data words have been received,
    			// Set to seeking IDLE
    			_rxDataWordCnt--;
    			if( _rxDataWordCnt == 0)
    			{
                    _messageStatus = MESSAGE_DATA_VALID;
                    // the data valid interrupt will piggy-back with the message complete 
                    //if (_messageStatusInterruptMask & MESSAGE_DATA_VALID)
                    //    channel.CIRC = CIRC_INT_FROM_SERVICED;
    				_state = MS1553_STATE_RT_TO_BC_AWAITING_IDLE_B;

    				// There should be an idle next,
    				// If not, by clearing the edge valid, an error will be detected. 
    				_isLastEdgeAValid = 0;
    				_isLastEdgeBValid = 0;
    			}
    		}
    		break;
    	}

    		//=====================================
    		//   CONTROLLER TO RT STATES
    		//=====================================

    	case MS1553_STATE_BC_TO_RT_AWAITING_STATUS:
    	{
    		if( _synchState==SYNCH_STATE_DATA_WORD)
    		{
    			Error_InWord_BC(RT_DATA_WHEN_EXPECTED_STATUS_ERROR);
    		}

            _rxStatusWord1 = receivedWord;
            _messageStatus = MESSAGE_STATUS_VALID;
            // the status valid interrupt will piggy-back with the message complete 
            //if (_messageStatusInterruptMask & MESSAGE_STATUS_VALID)
            //    channel.CIRC = CIRC_INT_FROM_SERVICED;

    		_state = MS1553_STATE_BC_TO_RT_AWAITING_IDLE_B;

    		// There should be an idle next,
    		// If not, by clearing the edge valid, an error will be detected. 
    		_isLastEdgeAValid = 0;
    		_isLastEdgeBValid = 0;
    		break;
    	}

    		//=====================================
    		//   RT TO RT STATES
    		//=====================================

    	case MS1553_STATE_RT_TO_RT_AWAITING_STATUS_A:
    	{
    		if( _synchState!=SYNCH_STATE_CMD_STATUS_WORD)
    		{
    			Error_InWord_BC(RT_DATA_WHEN_EXPECTED_STATUS_ERROR);
    		}

    		_rxStatusWord1 = receivedWord;
            _messageStatus = MESSAGE_STATUS_VALID;
            if (_messageStatusInterruptMask & MESSAGE_STATUS_VALID)
                channel.CIRC = CIRC_INT_FROM_SERVICED;
    		
    		_state = MS1553_STATE_RT_TO_RT_AWAITING_DATA;
    		
    		break;
    	}
    	case MS1553_STATE_RT_TO_RT_AWAITING_DATA:
    	{
    		if( _synchState!=SYNCH_STATE_DATA_WORD)
    		{
    			Error_InWord_BC(RT_STATUS_WHEN_EXPECTED_DATA_ERROR);
    		}

		    *_rxBufPtr++ = receivedWord;

    		// Decrement the data word count
    		// If all data words have been received,
    		// Set to seeking IDLE
    		_rxDataWordCnt--;
    		if( _rxDataWordCnt == 0)
    		{
               _messageStatus = MESSAGE_DATA_VALID;
               if (!_isBroadcastMsg && (_messageStatusInterruptMask & MESSAGE_DATA_VALID))
                   channel.CIRC = CIRC_INT_FROM_SERVICED;

    			_state = MS1553_STATE_RT_TO_RT_AWAITING_IDLE_B;

    			// There should be an idle next,
    			// If not, by clearing the edge valid, an error will be detected. 
    			_isLastEdgeAValid = 0;
    			_isLastEdgeBValid = 0;
    		}
    		
    		break;
    	}
    	case MS1553_STATE_RT_TO_RT_AWAITING_STATUS_B:
    	{
    		if( _synchState!=SYNCH_STATE_CMD_STATUS_WORD)
    		{
    			Error_InWord_BC(RT_DATA_WHEN_EXPECTED_STATUS_ERROR);
    		}

    		_state = MS1553_STATE_RT_TO_RT_AWAITING_IDLE_C;

    		// There should be an idle next,
    		// If not, by clearing the edge valid, an error will be detected. 
    		_isLastEdgeAValid = 0;
    		_isLastEdgeBValid = 0;
    		
            _rxStatusWord2 = receivedWord;
            _messageStatus = MESSAGE_STATUS_VALID;
            // the status valid interrupt will piggy-back with the message complete 
            //if (_messageStatusInterruptMask & MESSAGE_STATUS_VALID)
            //    channel.CIRC = CIRC_INT_FROM_SERVICED;
    		
    		break;
    	}

    	//=====================================
    	//   MODE COMMAND STATES
    	//=====================================

        case MS1553_STATE_MC_XD_AWAITING_STATUS:
        {
    		if( _synchState!=SYNCH_STATE_CMD_STATUS_WORD)
    		{
    			Error_InWord_BC(RT_DATA_WHEN_EXPECTED_STATUS_ERROR);
    		}
            _rxStatusWord1 = receivedWord;
            _messageStatus = MESSAGE_STATUS_VALID;
            if (_messageStatusInterruptMask & MESSAGE_STATUS_VALID)
                channel.CIRC = CIRC_INT_FROM_SERVICED;
    		_state = MS1553_STATE_MC_XD_AWAITING_DATA;
    		break;
        }
        
        case MS1553_STATE_MC_XD_AWAITING_DATA:
        {
    		if( _synchState!=SYNCH_STATE_DATA_WORD)
    		{
    			Error_InWord_BC(RT_STATUS_WHEN_EXPECTED_DATA_ERROR);
    		}
		    _rxModeWord = receivedWord;
            _messageStatus = MODE_DATA_VALID;
            // the mode data valid interrupt will piggy-back with the message complete 
            //if (_messageStatusInterruptMask & MODE_DATA_VALID)
            //    channel.CIRC = CIRC_INT_FROM_SERVICED;
    		_state = MS1553_STATE_MC_XD_AWAITING_IDLE_B;
    		break;
        }
        
        case MS1553_STATE_MC_RD_AWAITING_STATUS:
        {
    		if( _synchState!=SYNCH_STATE_CMD_STATUS_WORD)
    		{
    			Error_InWord_BC(RT_DATA_WHEN_EXPECTED_STATUS_ERROR);
    		}
            _rxStatusWord1 = receivedWord;
            _messageStatus = MESSAGE_STATUS_VALID;
            // the mode data valid interrupt will piggy-back with the message complete 
            //if (_messageStatusInterruptMask & MODE_DATA_VALID)
            //    channel.CIRC = CIRC_INT_FROM_SERVICED;
    		_state = MS1553_STATE_MC_RD_AWAITING_IDLE_B;
            break;
        }
        
        case MS1553_STATE_MC_X_AWAITING_STATUS:
        {
    		if( _synchState!=SYNCH_STATE_CMD_STATUS_WORD)
    		{
    			Error_InWord_BC(RT_DATA_WHEN_EXPECTED_STATUS_ERROR);
    		}
            _rxStatusWord1 = receivedWord;
            _messageStatus = MESSAGE_STATUS_VALID;
            // the mode data valid interrupt will piggy-back with the message complete 
            //if (_messageStatusInterruptMask & MODE_DATA_VALID)
            //    channel.CIRC = CIRC_INT_FROM_SERVICED;
    		_state = MS1553_STATE_MC_X_AWAITING_IDLE_B;
            break;
        }

    	default:
    	{
    	    // this case could only happen due to memory corruption or similar
    	    Error_InWord_BC(INTERNAL_ERROR);
    	    break;
    	}
    }
	_synchState = SYNCH_STATE_UNSYNCHED;
}

/***************************************************************************/
/* FoundIdle_BC eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread activates if there has been no bus activity for the 2us following
/* the end of a word.
/*
/***************************************************************************/
_eTPU_thread MS1553::FoundIdle_BC(_eTPU_matches_enabled)
{
    _isLastEdgeAValid = 0;
    _isLastEdgeBValid = 0;

    read_mer();
    ClearMatchALatch();

    switch (_state)
    {
    	//---------------------------------------------------------------------
    	// RT TO CONTROLLER TRANSFER
    	//
    	// Found the expected IDLE
    	// A 'Status' response is expected from the RT
    	// generate a new match that will detect a lack of that match
    	case MS1553_STATE_RT_TO_BC_AWAITING_IDLE_A:
    	{
    		_state = MS1553_STATE_RT_TO_BC_AWAITING_STATUS;
       		ertA = ertA + _rtStatusTimeout;
       		WriteErtAToMatchAAndEnable();
    		break;
    	}

    	//---------------------------------------------------------------------
    	// CONTROLLER TO RT TRANSFER
    	//
    	// This is the idle
    	// between the controller's data sourcing
    	// and the RT's status (acknowledge)
    	case MS1553_STATE_BC_TO_RT_AWAITING_IDLE_A:
    	{
    		// If the synch address is 0x1F 
    		// then it is a 'broadcast' (to all RT receivers)
    		// and there will therefore be no receiver providing a 'status'
    		// So the message ends on receipt of this 'Idle'
    		if( _isBroadcastMsg )
    		{
    		    MessageComplete_BC();
    			break;
    		}
    		_state = MS1553_STATE_BC_TO_RT_AWAITING_STATUS;
       		ertA = ertA + _rtStatusTimeout;
       		WriteErtAToMatchAAndEnable();
    		break;
    	}

    	//---------------------------------------------------------------------
    	// RT TO RT TRANSFER
    	//
    	// This is the first idle
    	// between the controller's command words
    	// and the RT Transmitter's status (acknowledge)
    	case MS1553_STATE_RT_TO_RT_AWAITING_IDLE_A:
    	{
    		_state = MS1553_STATE_RT_TO_RT_AWAITING_STATUS_A;
       		ertA = ertA + _rtStatusTimeout;
       		WriteErtAToMatchAAndEnable();
    		break;
    	}

    	//-----------------------------
    	// This is the second idle
    	// between the Transmitter RT's last data word
    	// and the Receiver RT's status (acknowledge)
    	case MS1553_STATE_RT_TO_RT_AWAITING_IDLE_B:
    	{
    		// If the synch address is 0x1F 
    		// then it is a 'broadcast' (to all RT receivers)
    		// and there will therefore be no Receiver RT providing a 'status'
    		// So the message ends on receipt of this 'Idle'
    		if( _isBroadcastMsg )
    		{
    		    MessageComplete_BC();
    			break;
    		}
    		_state = MS1553_STATE_RT_TO_RT_AWAITING_STATUS_B;
       		ertA = ertA + _rtStatusTimeout;
       		WriteErtAToMatchAAndEnable();
    		break;
    	}

    	//-----------------------------
    	// This is a message complete idle
    	case MS1553_STATE_BC_TO_RT_AWAITING_IDLE_B:
    	case MS1553_STATE_RT_TO_BC_AWAITING_IDLE_B:
    	case MS1553_STATE_RT_TO_RT_AWAITING_IDLE_C:
    	{
    	    MessageComplete_BC();
    		break;
    	}

    	//---------------------------------------------------------------------
    	// FAULT:  Expecting data word, found IDLE
    	case MS1553_STATE_RT_TO_BC_AWAITING_DATA:
    	case MS1553_STATE_RT_TO_RT_AWAITING_DATA:
    	{
    		// An error has been encountered at an 'IDLE'.
    		// The following form of 'Error' is called
    		// which does not require another 'IDLE' to begin receiving the next message.
    		Error_InIdle_BC(TOO_FEW_DATA_WORDS_ERROR);
    		break;
    	}
    	//---------------------------------------------------------------------
    	// FAULT:  Expecting 'RT STATUS' found (instead) a too long idle period
    	case MS1553_STATE_RT_TO_BC_AWAITING_STATUS:
    	case MS1553_STATE_BC_TO_RT_AWAITING_STATUS:
    	case MS1553_STATE_RT_TO_RT_AWAITING_STATUS_A:
    	case MS1553_STATE_RT_TO_RT_AWAITING_STATUS_B:
        case MS1553_STATE_MC_XD_AWAITING_STATUS:
        case MS1553_STATE_MC_RD_AWAITING_STATUS:
        case MS1553_STATE_MC_X_AWAITING_STATUS:
    	{
    		Error_InIdle_BC(RT_STATUS_TIMEOUT_ERROR);
    		break;
    	}

        //=====================================
        //   MODE COMMAND STATES
        //=====================================
    	
    	//---------------------------------------------------------------------
    	// next RT to transmit status and mode data
    	case MS1553_STATE_MC_XD_AWAITING_IDLE_A:
    	{
    	    _state = MS1553_STATE_MC_XD_AWAITING_STATUS;
       		ertA = ertA + _rtStatusTimeout;
       		WriteErtAToMatchAAndEnable();
    		break;
    	}
    	
    	//---------------------------------------------------------------------
    	// next RT to transmit status
    	case MS1553_STATE_MC_RD_AWAITING_IDLE_A:
    	{
    	    _state = MS1553_STATE_MC_RD_AWAITING_STATUS;
       		ertA = ertA + _rtStatusTimeout;
       		WriteErtAToMatchAAndEnable();
    		break;
    	}
    	
    	//---------------------------------------------------------------------
    	// next RT to transmit status
    	case MS1553_STATE_MC_X_AWAITING_IDLE_A:
    	{
    	    _state = MS1553_STATE_MC_X_AWAITING_STATUS;
       		ertA = ertA + _rtStatusTimeout;
       		WriteErtAToMatchAAndEnable();
    		break;
    	}
    	
    	//---------------------------------------------------------------------
    	// message completing idle detection
    	case MS1553_STATE_MC_XD_AWAITING_IDLE_B:
    	case MS1553_STATE_MC_RBD_AWAITING_IDLE:
    	case MS1553_STATE_MC_RD_AWAITING_IDLE_B:
    	case MS1553_STATE_MC_XB_AWAITING_IDLE:
    	case MS1553_STATE_MC_X_AWAITING_IDLE_B:
    	{
    	    MessageComplete_BC();
      		break;
    	}
    	
    	//---------------------------------------------------------------------
    	// mode data expected, but idle found instead
    	case MS1553_STATE_MC_XD_AWAITING_DATA:
    	{
    		Error_InIdle_BC(EXPECTED_MODE_DATA_MISSING_ERROR);
    		break;
    	}
    	
    	default:
    	{
    	    // this case could only happen due to memory corruption or similar
    	    Error_InIdle_BC(INTERNAL_ERROR);
    	    break;
    	}
    }
}

/***************************************************************************/
/* ExpectMessageResponse_BC eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread activates when a link is received from the master TX channel of
/* the BC eTPU driver.  It awakens the RX capability to process the rest of the message -
/* RT status and data response(s).
/*
/***************************************************************************/
_eTPU_thread MS1553::ExpectMessageResponse_BC(_eTPU_matches_enabled)
{
    channel.LSR = LSR_CLEAR;

    // first step is to find the expected idle (or error)
   
    // idle minimum is 2.5 bits from mid-parity to start of next synch
    ertA = _txEndTimestamp + _2P50_bits;
    channel.ERWA = ERW_WRITE_ERT_TO_MATCH;
    // clear any old trans detect state and re-enable servicing
    channel.TDL = TDL_CLEAR;
    channel.IPACA = IPAC_RISING;
    chan += 1;
    channel.TDL = TDL_CLEAR;
    channel.IPACA = IPAC_RISING;
    
    // reset receive buffer
    _rxBufPtr = _rxBuf;
}


/***************************************************************************/
/* Error_InWord_BC eTPU fragment
/***************************************************************************/
/* DESCRIPTION:
/* This fragment is called if an error has been detected in a word or in the protocol
/* processing following a word. The message processing is terminated.  The BC driver 
/* should seek for bus idle before continuing with the next message.
/*
/***************************************************************************/
_eTPU_fragment MS1553::Error_InWord_BC(int8 errorNum)
{
    _errorStatus = errorNum;
	_messageStatus = MESSAGE_ERROR;
    if (_messageStatusInterruptMask & MESSAGE_ERROR)
        channel.CIRC = CIRC_INT_FROM_SERVICED;

	_state = MS1553_STATE_AWAIT_MESSAGE;

    // turn off RX until next message issued by BC
    chan = _rxBaseChan;
    channel.MRLE = MRLE_DISABLE;
    channel.IPACA = IPAC_NO_DETECT;
    channel.TDL = TDL_CLEAR;
    chan += 1;
    channel.IPACA = IPAC_NO_DETECT;
    channel.TDL = TDL_CLEAR;

    _bcMessageInProgress = FALSE;
}

/***************************************************************************/
/* Error_InIdle_BC eTPU fragment
/***************************************************************************/
/* DESCRIPTION:
/* This fragment is called if a protocol error has been detected after idle detection.
/*
/***************************************************************************/
_eTPU_fragment MS1553::Error_InIdle_BC(int8 errorNum)
{
    _errorStatus = errorNum;
	_messageStatus = MESSAGE_ERROR;
    if (_messageStatusInterruptMask & MESSAGE_ERROR)
        channel.CIRC = CIRC_INT_FROM_SERVICED;

	_state = MS1553_STATE_AWAIT_MESSAGE;

    // turn off RX until next message issued by BC
	chan = _rxBaseChan;
    channel.IPACA = IPAC_NO_DETECT;
    channel.TDL = TDL_CLEAR;
    chan += 1;
    channel.IPACA = IPAC_NO_DETECT;
    channel.TDL = TDL_CLEAR;

    _bcMessageInProgress = FALSE;
}

/***************************************************************************/
/* MessageComplete_BC eTPU fragment
/***************************************************************************/
/* DESCRIPTION:
/* This fragment is called when a valid message completes.  It clears the error
/* status and interrupts the host if so enabled.  Upon exit the RX is disabled until
/* the next BC message processing re-enables it.
/*
/***************************************************************************/
_eTPU_fragment MS1553::MessageComplete_BC()
{
    _errorStatus = NO_ERROR;
	_messageStatus |= MESSAGE_COMPLETE;
    if (_messageStatusInterruptMask & _messageStatus)
        channel.CIRC = CIRC_INT_FROM_SERVICED;

	_state = MS1553_STATE_AWAIT_MESSAGE;

    // turn off RX until next message issued by BC
    channel.IPACA = IPAC_NO_DETECT;
    channel.TDL = TDL_CLEAR;
    chan += 1;
    channel.IPACA = IPAC_NO_DETECT;
    channel.TDL = TDL_CLEAR;

    _bcMessageInProgress = FALSE;
}
