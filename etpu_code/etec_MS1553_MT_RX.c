/**************************************************************************
 * Copyright (C) 2020 ASH WARE, Inc.
 *************************************************************************/
/**************************************************************************
* FILE NAME: etec_MS1553_MT_RX.c   
* 
* DESCRIPTION: This file contains the thread and function definitions specific
* to the Monitor Terminal (MT) MIL-STD-1553 receiver eTPU driver
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
/* MT_RX_P Entry Table Definition
/***************************************************************************/
/* DESCRIPTION:
/* The table below configures the 32 unique entry points for the Monitor Terminal
/* MIL-STD-1553 receiver (MT_RX) eTPU code (positive digital input).
/* Note that all functions/channels that service the 1553 bus for a terminal
/* share an eTPU channel frame.
/*
/***************************************************************************/
DEFINE_ENTRY_TABLE(MS1553, MS1553_MT_RX_P, alternate, inputpin, autocfsr)
{

	//-----------------------------------------------------
	// Valid states, ...
	//           HSR    LSR M1 M2 PIN F0 F1 vector
	ETPU_VECTOR2(6,7,   x,  x, x, x,  x, x, Init_MT_RX),
	ETPU_VECTOR2(2,3,   x,  x, x, 0,  0, x, Shutdown_RX),
	ETPU_VECTOR2(2,3,   x,  x, x, 0,  1, x, Shutdown_RX),
	ETPU_VECTOR2(2,3,   x,  x, x, 1,  0, x, Shutdown_RX),
	ETPU_VECTOR2(2,3,   x,  x, x, 1,  1, x, Shutdown_RX),
	
	ETPU_VECTOR1(0,     x,  0, 1, 0,  1, 0, AwaitInitIdleP),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  1, 0, AwaitInitIdleP),

	ETPU_VECTOR1(0,     x,  1, 0, 0,  1, 0, FoundInitIdle),
	ETPU_VECTOR1(0,     x,  1, 0, 1,  1, 0, FoundInitIdle),
	// When Both TDL and MRL are set, MRL must have occurred first ...
	ETPU_VECTOR1(0,     x,  1, 1, 0,  1, 0, FoundInitIdle),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  1, 0, FoundInitIdle),

	ETPU_VECTOR1(0,     x,  0, 1, 0,  0, 0, SeekSynchP_MT_RT),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  0, 0, SeekSynchP_MT_RT),

	ETPU_VECTOR1(0,     x,  1, 0, 0,  0, 0, FoundIdle_MT),
	ETPU_VECTOR1(0,     x,  1, 0, 1,  0, 0, FoundIdle_MT),
	// When Both TDL and MRL are set, MRL must have occurred first ...
	ETPU_VECTOR1(0,     x,  1, 1, 0,  0, 0, FoundIdle_MT),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  0, 0, FoundIdle_MT),


	ETPU_VECTOR1(0,     x,  0, 1, 0,  1, 1, FromOneBit),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  1, 1, FromOneBit),

	ETPU_VECTOR1(0,     x,  0, 1, 0,  0, 1, FromZeroBit),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  0, 1, FromZeroBit),

	ETPU_VECTOR1(0,     x,  1, 0, 0,  0, 1, HandleWord_MT),
	ETPU_VECTOR1(0,     x,  1, 0, 1,  0, 1, HandleWord_MT),
	ETPU_VECTOR1(0,     x,  1, 0, 0,  1, 1, HandleWord_MT),
	ETPU_VECTOR1(0,     x,  1, 0, 1,  1, 1, HandleWord_MT),

	//-----------------------------------------------------
	// Unused States
	//           HSR    LSR M1 M2 PIN F0 F1 vector
	ETPU_VECTOR3(1,4,5, x,  x, x, x,  x, x, _Error_handler_entry),
	ETPU_VECTOR1(0,     1,  0, 0, 0,  x, x, _Error_handler_entry),
	ETPU_VECTOR1(0,     1,  0, 0, 1,  x, x, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 1, 0,  0, 1, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 1, 0,  1, 1, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  0, 1, _Error_handler_entry),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  1, 1, _Error_handler_entry),

};

/***************************************************************************/
/* MT_RX_N Entry Table Definition
/***************************************************************************/
/* DESCRIPTION:
/* The table below configures the 32 unique entry points for the Monitor Terminal
/* MIL-STD-1553 receiver (MT_RX) eTPU code (negative digital input).
/* Note that all functions/channels that service the 1553 bus for a terminal
/* share an eTPU channel frame.
/*
/***************************************************************************/
DEFINE_ENTRY_TABLE(MS1553, MS1553_MT_RX_N, alternate, inputpin, autocfsr)
{

	// Valid states, ...

	//           HSR    LSR M1 M2 PIN F0 F1 vector
	ETPU_VECTOR1(0,     x,  0, 1, 0,  1, 0, AwaitInitIdleN),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  1, 0, AwaitInitIdleN),

	ETPU_VECTOR1(0,     x,  0, 1, 0,  0, 0, SeekSynchN_MT_RT),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  0, 0, SeekSynchN_MT_RT),

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
/* Init_MT_RX eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread configures the RX channel pair for 1553 MT input processing. 
/*
/***************************************************************************/
_eTPU_thread MS1553::Init_MT_RX(_eTPU_matches_disabled)
{
    _state = MS1553_STATE_AWAIT_MESSAGE;
    _rxBufPtr =  _rxBuf;
    InitCommon_RX();
}

/***************************************************************************/
/* SeekSynchP_MT_RT eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread activates when a rising edge is detected on the positive MT_RX input
/* while seeking a sync.
/*
/***************************************************************************/
_eTPU_thread MS1553::SeekSynchP_MT_RT(_eTPU_matches_enabled)
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
        
        if (_state != MS1553_STATE_AWAIT_IDLE)
    		Error_InWord(EXPECTED_IDLE_MISSING_ERROR);
	}
	else
    	SeekSynchCommonP();
}

/***************************************************************************/
/* SeekSynchN_MT_RT eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread activates when a rising edge is detected on the negative MT_RX input
/* while seeking a sync.
/*
/***************************************************************************/
_eTPU_thread MS1553::SeekSynchN_MT_RT(_eTPU_matches_enabled)
{
	ClearTransLatch();
	if ( _state >= MS1553_STATE_AWAIT_IDLE )
	{
		// Expected an idle but got an edge instead.
		// Report this as an error

        // configure to find next idle
        int temp = ertA + _2P50_bits;
		chan = chan - 1;
        ertA = temp;
        ClearMatchALatch();
        WriteErtAToMatchAAndEnable();

        if (_state != MS1553_STATE_AWAIT_IDLE)
            Error_InWord(EXPECTED_IDLE_MISSING_ERROR);
	}
	else
    	SeekSynchCommonN();
}

/***************************************************************************/
/* HandleWord_MT eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread activates 0.25us after the expected end of a word - it verifies
/* the word is valid and then performs message protocol processing.
/*
/***************************************************************************/
_eTPU_thread MS1553::HandleWord_MT(_eTPU_matches_enabled)
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
		Error_InWord( MISSING_BIT_ERROR );
	}
	
	// Check parity
	// Set parity error if invalid
	if( !(finalParity&1) )
	{
		Error_InWord( PARITY_ERROR );
	}

	//----------------------------------
	switch (_state)
	{
    	// Seeking a message
    	case MS1553_STATE_AWAIT_MESSAGE:
    	{
    		// Is it a 'Command' synch?
    		if( _synchState==SYNCH_STATE_CMD_STATUS_WORD )
    		{
    		    _cmdWordBuffer = receivedWord;
    		    _rxBufPtr = _rxBuf;
    		    _isBroadcastMsg = FALSE;

    		    // check for a mode command
    			if(((receivedWord&MS1553_SUBADDRESS_MODE_BITMASK)==MS1553_MODE_1_BITMASK) || 
    			   ((receivedWord&MS1553_SUBADDRESS_MODE_BITMASK)==MS1553_MODE_2_BITMASK))
    			{
   				if ((receivedWord & MS1553_TERMINAL_ADDRESS_BITMASK) == MS1553_TERMINAL_ADDRESS_BITMASK)
    				{
					    _cmdWord1 = receivedWord;
					    _validMessage = 1;
    				    _isBroadcastMsg = TRUE;
    				}
					else if ((receivedWord & MS1553_TERMINAL_ADDRESS_BITMASK) == _terminalAddress || 
					         _terminalAddress == MS1553_TERMINAL_ADDRESS_BITMASK)
					{
					    _cmdWord1 = receivedWord;
					    _validMessage = 1;
					}

					if (receivedWord & MS1553_MODE_DATA_BITMASK)
					{
                        if ( receivedWord & MS1553_RX_TX_BITMASK )
                        {
                            if (_isBroadcastMsg)
                                Error_InWord(INVALID_MODE_COMMAND);
                            else
                            {
                                _messageType = MODE_XMT_WITH_DATA;
                                _state = MS1553_STATE_MC_XD_AWAITING_IDLE_A;
                            }
                        }
                        else
                        {
                            if (_isBroadcastMsg)
                            {
                                _messageType = MODE_BROADCAST_WITH_DATA;
                                _state = MS1553_STATE_MC_RBD_AWAITING_DATA;
                            }
                            else
                            {
                                _messageType = MODE_RCV_WITH_DATA;
                                _state = MS1553_STATE_MC_RD_AWAITING_DATA;
                            }
                        }
                    }
                    else
                    {
                        if ( receivedWord & MS1553_RX_TX_BITMASK )
                        {
                            if (_isBroadcastMsg)
                            {
                                _messageType = MODE_BROADCAST_WITHOUT_DATA;
                                _state = MS1553_STATE_MC_XB_AWAITING_IDLE;
                            }
                            else
                            {
                                _messageType = MODE_XMT_WITHOUT_DATA;
                                _state = MS1553_STATE_MC_X_AWAITING_IDLE_A;
                            }
                        }
                        else
                        {
                            // no data word + receive bit set is an error
                            Error_InWord(INVALID_MODE_COMMAND);
                        }
                    }
                    if (_validMessage & 1)
                    {
                        _messageStatus = COMMAND_WORD_VALID;
                        if ((_messageType != MODE_BROADCAST_WITHOUT_DATA) && (_messageStatusInterruptMask & COMMAND_WORD_VALID))
                            channel.CIRC = CIRC_INT_FROM_SERVICED;
                    }
    			}
    			else
    			{
    				_rxDataWordCnt = ((receivedWord - 1) & MS1553_WORD_COUNT_BITMASK) + 1;

    				// Is it a transmit message?
    				// (Transmit if bit.10 is a '1')
    				if( receivedWord & MS1553_RX_TX_BITMASK )
    				{
    					// Set the state to
    					// 'RT To Controller Transfer ... Seeking RT Status'
    					_state=MS1553_STATE_RT_TO_BC_AWAITING_IDLE_A;

    					// There should be an idle next,
    					// If not, by clearing the edge valid, an error will be detected. 
    					_isLastEdgeAValid = 0;
    					_isLastEdgeBValid = 0;

    					// Set message type to 'RT To Controller Transfer'
    					_messageType = RT_TO_BC_XFR;

					    if ((receivedWord & MS1553_TERMINAL_ADDRESS_BITMASK) == _terminalAddress || 
					         _terminalAddress == MS1553_TERMINAL_ADDRESS_BITMASK)
					    {
    					    _cmdWord1 = receivedWord;
    					    _dataWordCnt = _rxDataWordCnt;
    					    _validMessage = 1;
                            _messageStatus = COMMAND_WORD_VALID;
                            if (_messageStatusInterruptMask & COMMAND_WORD_VALID)
                                channel.CIRC = CIRC_INT_FROM_SERVICED;
					    }
    				}

    				// If not a Transmit,
    				// then it is a receive
    				else
    				{
        				if ((receivedWord & MS1553_TERMINAL_ADDRESS_BITMASK) == MS1553_TERMINAL_ADDRESS_BITMASK)
        				    _isBroadcastMsg = TRUE;

    					// Set the state to
    					// 'TBD to RT Transfer ... Seeking RT-TXD or DATA'
    					// Note: Next word will be a 'DATA' (for 'Controller to RT')
    					//       OR next word will be a 'XMT CMD'  (for RT to RT xfer)
    					_state=MS1553_STATE_TBD_TO_RT_AWAITING_DATA;

    					if (_terminalAddress == MS1553_TERMINAL_ADDRESS_BITMASK || 
					        (receivedWord & MS1553_TERMINAL_ADDRESS_BITMASK) == _terminalAddress ||
					        _isBroadcastMsg == TRUE)
					    {
    					    _cmdWord1 = receivedWord;
    					    _dataWordCnt = _rxDataWordCnt;
    					    _validMessage = 1;
					    }
    				}
    			}
    		}
    		else
    		{
  				Error_InWord(MESSAGE_STARTS_WITH_DATA_ERROR);
    		}
    		break;
    	}

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
    			Error_InWord(RT_DATA_WHEN_EXPECTED_STATUS_ERROR);
    		}
    		else
    		{
    			if (_validMessage & 1)
    			{
                    _rxStatusWord1 = receivedWord;
                    _messageStatus = MESSAGE_STATUS_VALID;
                    if (_messageStatusInterruptMask & MESSAGE_STATUS_VALID)
                        channel.CIRC = CIRC_INT_FROM_SERVICED;
                }

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
    			Error_InWord(RT_STATUS_WHEN_EXPECTED_DATA_ERROR);
    		}
    		else
    		{
    			if (_validMessage & 1)
    			{
    			    *_rxBufPtr++ = receivedWord;
    			}

    			// Decrement the data word count
    			// If all data words have been received,
    			// Set to seeking IDLE
    			_rxDataWordCnt--;
    			if(_rxDataWordCnt == 0)
    			{
    			    if (_validMessage & 1)
    			    {
                        _messageStatus = MESSAGE_DATA_VALID;
                        // the data valid interrupt will piggy-back with the message complete 
                        //if (_messageStatusInterruptMask & MESSAGE_DATA_VALID)
                        //    channel.CIRC = CIRC_INT_FROM_SERVICED;
                    }

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
    		//   INDETERMINATE CONTROLLER STATE
    		//=====================================

    	case MS1553_STATE_TBD_TO_RT_AWAITING_DATA:
    	{
    		// Is it another command synch?
    		if( _synchState==SYNCH_STATE_CMD_STATUS_WORD)
    		{
    			// It is a RT to RT transfer
    			_state = MS1553_STATE_RT_TO_RT_AWAITING_IDLE_A;
    			_messageType = _isBroadcastMsg ? RT_TO_RT_BROADCAST_XFR : RT_TO_RT_XFR;
    			
    			if ((receivedWord & MS1553_TERMINAL_ADDRESS_BITMASK) == _terminalAddress)
                    _validMessage = 1;

    			// There should be an idle next,
    			// If not, by clearing the edge valid, an error will be detected. 
    			_isLastEdgeAValid = 0;
    			_isLastEdgeBValid = 0;
    			
    			if (_validMessage & 1)
    			{
                    _cmdWord1 = _cmdWordBuffer;
                    _cmdWord2 = receivedWord;
                    _messageStatus = COMMAND_WORD_VALID;
                    if (_messageStatusInterruptMask & COMMAND_WORD_VALID)
                        channel.CIRC = CIRC_INT_FROM_SERVICED;
                }
    		}
    		else
    		{
    			// It is a Controller to RT transfer
    			// And the first data was just received
    			_state = MS1553_STATE_BC_TO_RT_AWAITING_DATA;
    			_messageType = _isBroadcastMsg ? BC_TO_RT_BROADCAST_XFR : BC_TO_RT_XFR;

    			if (_validMessage & 1)
    			{
        			// first data word, put in start of buffer directly
        			_rxBuf[0] = receivedWord;
        			_rxBufPtr = &(_rxBuf[1]);
        		}

    			// Decrement the data word count
    			// If all data words have been received,
    			// Set to seeking IDLE
    			_rxDataWordCnt--;
    			if(_rxDataWordCnt == 0)
    			{
    			    if (_validMessage & 1)
    			    {
                        _messageStatus = COMMAND_WORD_VALID | MESSAGE_DATA_VALID;
                        if (!_isBroadcastMsg && (_messageStatusInterruptMask & (COMMAND_WORD_VALID | MESSAGE_DATA_VALID)))
                            channel.CIRC = CIRC_INT_FROM_SERVICED;
                    }

    				_state = MS1553_STATE_BC_TO_RT_AWAITING_IDLE_A;

    				// There should be an idle next,
    				// If not, by clearing the edge valid, an error will be detected. 
    				_isLastEdgeAValid = 0;
    				_isLastEdgeBValid = 0;
    			}
    			else if (_validMessage & 1)
    			{
                    _messageStatus = COMMAND_WORD_VALID;
                    if (_messageStatusInterruptMask & COMMAND_WORD_VALID)
                        channel.CIRC = CIRC_INT_FROM_SERVICED;
    			}
    		}
    		break;
    	}

    		//=====================================
    		//   CONTROLLER TO RT STATES
    		//=====================================

    	case MS1553_STATE_BC_TO_RT_AWAITING_DATA:
    	{
    		if( _synchState==SYNCH_STATE_CMD_STATUS_WORD)
    		{
    			Error_InWord(RT_STATUS_WHEN_EXPECTED_DATA_ERROR);
    		}

			if (_validMessage & 1)
			{
			    *_rxBufPtr++ = receivedWord;
			}

    		// Decrement the data word count
    		// If all data words have been received,
    		// Set to seeking IDLE
    		_rxDataWordCnt--;
    		if( _rxDataWordCnt == 0 )
    		{
    		    if (_validMessage & 1)
    		    {
                    _messageStatus = MESSAGE_DATA_VALID;
                    if (!_isBroadcastMsg && (_messageStatusInterruptMask & MESSAGE_DATA_VALID))
                        channel.CIRC = CIRC_INT_FROM_SERVICED;
                }

    			_state = MS1553_STATE_BC_TO_RT_AWAITING_IDLE_A;

    			// There should be an idle next,
    			// If not, by clearing the edge valid, an error will be detected. 
    			_isLastEdgeAValid = 0;
    			_isLastEdgeBValid = 0;
    		}
    		break;
    	}
    	case MS1553_STATE_BC_TO_RT_AWAITING_STATUS:
    	{
    		if( _synchState==SYNCH_STATE_DATA_WORD)
    		{
    			Error_InWord(RT_DATA_WHEN_EXPECTED_STATUS_ERROR);
    		}

			if (_validMessage & 1)
			{
                _rxStatusWord1 = receivedWord;
                _messageStatus = MESSAGE_STATUS_VALID;
                // the status valid interrupt will piggy-back with the message complete 
                //if (_messageStatusInterruptMask & MESSAGE_STATUS_VALID)
                //    channel.CIRC = CIRC_INT_FROM_SERVICED;
            }

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
    			Error_InWord(RT_DATA_WHEN_EXPECTED_STATUS_ERROR);
    		}

			if (_validMessage & 1)
			{
                _rxStatusWord1 = receivedWord;
                _messageStatus = MESSAGE_STATUS_VALID;
                if (_messageStatusInterruptMask & MESSAGE_STATUS_VALID)
                    channel.CIRC = CIRC_INT_FROM_SERVICED;
            }

    		_state = MS1553_STATE_RT_TO_RT_AWAITING_DATA;
    		break;
    	}
    	case MS1553_STATE_RT_TO_RT_AWAITING_DATA:
    	{
    		if( _synchState!=SYNCH_STATE_DATA_WORD)
    		{
    			Error_InWord(RT_STATUS_WHEN_EXPECTED_DATA_ERROR);
    		}

    		if (_validMessage & 1)
			    *_rxBufPtr++ = receivedWord;
    		
    		// Decrement the data word count
    		// If all data words have been received,
    		// Set to seeking IDLE
    		_rxDataWordCnt--;
    		if( _rxDataWordCnt == 0)
    		{
    		    if (_validMessage & 1)
    		    {
                    _messageStatus = MESSAGE_DATA_VALID;
                    if (!_isBroadcastMsg && (_messageStatusInterruptMask & MESSAGE_DATA_VALID))
                        channel.CIRC = CIRC_INT_FROM_SERVICED;
                }

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
    			Error_InWord(RT_DATA_WHEN_EXPECTED_STATUS_ERROR);
    		}

			if (_validMessage & 1)
			{
                _rxStatusWord2 = receivedWord;
                _messageStatus = MESSAGE_STATUS_VALID;
                // the status valid interrupt will piggy-back with the message complete 
                //if (_messageStatusInterruptMask & MESSAGE_STATUS_VALID)
                //    channel.CIRC = CIRC_INT_FROM_SERVICED;
            }

    		_state = MS1553_STATE_RT_TO_RT_AWAITING_IDLE_C;

    		// There should be an idle next,
    		// If not, by clearing the edge valid, an error will be detected. 
    		_isLastEdgeAValid = 0;
    		_isLastEdgeBValid = 0;
    		break;
    	}

        //=====================================
        //   MODE COMMAND STATES
        //=====================================

        case MS1553_STATE_MC_XD_AWAITING_STATUS:
        {
    		if( _synchState!=SYNCH_STATE_CMD_STATUS_WORD)
    		{
    			Error_InWord(RT_DATA_WHEN_EXPECTED_STATUS_ERROR);
    		}
    		if (_validMessage & 1)
    		{
    		    _rxStatusWord1 = receivedWord;
                _messageStatus = MESSAGE_STATUS_VALID;
                if (_messageStatusInterruptMask & MESSAGE_STATUS_VALID)
                    channel.CIRC = CIRC_INT_FROM_SERVICED;
    		}
    		_state = MS1553_STATE_MC_XD_AWAITING_DATA;
    		break;
        }
        
        case MS1553_STATE_MC_XD_AWAITING_DATA:
        {
    		if( _synchState!=SYNCH_STATE_DATA_WORD)
    		{
    			Error_InWord(RT_STATUS_WHEN_EXPECTED_DATA_ERROR);
    		}
    		if (_validMessage & 1)
    		{
    		    _rxModeWord = receivedWord;
                _messageStatus = MODE_DATA_VALID;
                // the mode data valid interrupt will piggy-back with the message complete 
                //if (_messageStatusInterruptMask & MODE_DATA_VALID)
                //    channel.CIRC = CIRC_INT_FROM_SERVICED;
    		}
    		_state = MS1553_STATE_MC_XD_AWAITING_IDLE_B;
    		break;
        }
        
        case MS1553_STATE_MC_RBD_AWAITING_DATA:
        {
    		if( _synchState!=SYNCH_STATE_DATA_WORD)
    		{
    			Error_InWord(RT_STATUS_WHEN_EXPECTED_DATA_ERROR);
    		}
    		// since this is a broadcast, data is always received
   		    _rxModeWord = receivedWord;
            _messageStatus = MODE_DATA_VALID;
            // the mode data valid interrupt will piggy-back with the message complete 
            //if (_messageStatusInterruptMask & MODE_DATA_VALID)
            //    channel.CIRC = CIRC_INT_FROM_SERVICED;
    		_state = MS1553_STATE_MC_RBD_AWAITING_IDLE;
    		break;
        }
        
        case MS1553_STATE_MC_RD_AWAITING_DATA:
        {
    		if( _synchState!=SYNCH_STATE_DATA_WORD)
    		{
    			Error_InWord(RT_STATUS_WHEN_EXPECTED_DATA_ERROR);
    		}
    		if (_validMessage & 1)
    		{
    		    _rxModeWord = receivedWord;
                _messageStatus = MODE_DATA_VALID;
                if (_messageStatusInterruptMask & MODE_DATA_VALID)
                    channel.CIRC = CIRC_INT_FROM_SERVICED;
    		}
    		_state = MS1553_STATE_MC_RD_AWAITING_IDLE_A;
            break;
        }
        
        case MS1553_STATE_MC_RD_AWAITING_STATUS:
        {
    		if( _synchState!=SYNCH_STATE_CMD_STATUS_WORD)
    		{
    			Error_InWord(RT_DATA_WHEN_EXPECTED_STATUS_ERROR);
    		}
    		if (_validMessage & 1)
    		{
    		    _rxStatusWord1 = receivedWord;
                _messageStatus = MESSAGE_STATUS_VALID;
                // the status valid interrupt will piggy-back with the message complete 
                //if (_messageStatusInterruptMask & MESSAGE_STATUS_VALID)
                //    channel.CIRC = CIRC_INT_FROM_SERVICED;
    		}
    		_state = MS1553_STATE_MC_RD_AWAITING_IDLE_B;
            break;
        }
        
        case MS1553_STATE_MC_X_AWAITING_STATUS:
        {
    		if( _synchState!=SYNCH_STATE_CMD_STATUS_WORD)
    		{
    			Error_InWord(RT_DATA_WHEN_EXPECTED_STATUS_ERROR);
    		}
    		if (_validMessage & 1)
    		{
    		    _rxStatusWord1 = receivedWord;
                _messageStatus = MESSAGE_STATUS_VALID;
                // the status valid interrupt will piggy-back with the message complete 
                //if (_messageStatusInterruptMask & MESSAGE_STATUS_VALID)
                //    channel.CIRC = CIRC_INT_FROM_SERVICED;
    		}
    		_state = MS1553_STATE_MC_X_AWAITING_IDLE_B;
            break;
        }

    	default:
    	{
    	    // this case could only happen due to memory corruption or similar
    	    // recover by re-starting with an idle
    	    _state = MS1553_STATE_AWAIT_IDLE;
    	    break;
    	}
    }
	_synchState = SYNCH_STATE_UNSYNCHED;
}

/***************************************************************************/
/* FoundIdle_MT eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread activates if there has been no bus activity for the 2us following
/* the end of a word.
/*
/***************************************************************************/
_eTPU_thread MS1553::FoundIdle_MT(_eTPU_matches_enabled)
{
	_isLastEdgeAValid = 0;
	_isLastEdgeBValid = 0;

    read_mer();
	ClearMatchALatch();

    switch (_state)
    {
        case MS1553_STATE_AWAIT_IDLE:
        {
            // back to potentially good state, await message
            _state = MS1553_STATE_AWAIT_MESSAGE;
            break;
        }
        
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

    	//-----------------------------
    	// This IDLE detecion completes a message
    	case MS1553_STATE_RT_TO_BC_AWAITING_IDLE_B:
    	case MS1553_STATE_BC_TO_RT_AWAITING_IDLE_B:
    	case MS1553_STATE_RT_TO_RT_AWAITING_IDLE_C:
    	{
    		MessageComplete();
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
    			MessageComplete();
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
    			MessageComplete();
    		}
    		_state = MS1553_STATE_RT_TO_RT_AWAITING_STATUS_B;
    		ertA = ertA + _rtStatusTimeout;
    		WriteErtAToMatchAAndEnable();
    		break;
    	}

    	//---------------------------------------------------------------------
    	// FAULT:  Expecting data word, found IDLE
    	case MS1553_STATE_RT_TO_BC_AWAITING_DATA:
    	case MS1553_STATE_BC_TO_RT_AWAITING_DATA:
    	case MS1553_STATE_TBD_TO_RT_AWAITING_DATA:
    	case MS1553_STATE_RT_TO_RT_AWAITING_DATA:
    	{
    		// An error has been encountered at an 'IDLE'.
    		// The following form of 'Error' is called
    		// which does not require another 'IDLE' to begin receiving the next message.
    		Error_InIdle(TOO_FEW_DATA_WORDS_ERROR);
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
    		Error_InIdle(RT_STATUS_TIMEOUT_ERROR);
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
    	// mode command message completing idle detected
    	case MS1553_STATE_MC_XD_AWAITING_IDLE_B:
    	case MS1553_STATE_MC_RBD_AWAITING_IDLE:
    	case MS1553_STATE_MC_RD_AWAITING_IDLE_B:
    	case MS1553_STATE_MC_XB_AWAITING_IDLE:
    	case MS1553_STATE_MC_X_AWAITING_IDLE_B:
    	{
    	    MessageComplete();
      		break;
    	}
    	
    	//---------------------------------------------------------------------
    	// mode data expected, but idle found instead
    	case MS1553_STATE_MC_XD_AWAITING_DATA:
    	case MS1553_STATE_MC_RBD_AWAITING_DATA:
    	case MS1553_STATE_MC_RD_AWAITING_DATA:
    	{
    		Error_InIdle(EXPECTED_MODE_DATA_MISSING_ERROR);
    		break;
    	}

    	default:
    	{
    	    // this case could only happen due to memory corruption or similar
    	    // recover by moving to the await message state (since we just completed an idle wait)
    	    _state = MS1553_STATE_AWAIT_MESSAGE;
    	    break;
    	}
    }
}

/***************************************************************************/
/* Error_InWord eTPU fragment
/***************************************************************************/
/* DESCRIPTION:
/* This fragment is called if an error has been detected in a word or in the protocol
/* processing following a word. The message is terminated and subsequent incoming words
/* are ignored until a valid bus idle is detected.
/*
/***************************************************************************/
_eTPU_fragment MS1553::Error_InWord(int8 errorNum)
{
    _errorStatus = errorNum;
	_state = MS1553_STATE_AWAIT_IDLE;
	_validMessage = 0;
    _messageStatus = MESSAGE_ERROR;
    if (_messageStatusInterruptMask & MESSAGE_ERROR)
        channel.CIRC = CIRC_INT_FROM_SERVICED;
}

/***************************************************************************/
/* Error_InIdle eTPU fragment
/***************************************************************************/
/* DESCRIPTION:
/* This fragment is called if a protocol error has been detected after idle detection.
/* Since the bus is in an idle state, any next word is treated as the potential start
/* of a new message. 
/*
/***************************************************************************/
_eTPU_fragment MS1553::Error_InIdle(int8 errorNum)
{
    _errorStatus = errorNum;
	_state = MS1553_STATE_AWAIT_MESSAGE;
	_validMessage = 0;
    _messageStatus = MESSAGE_ERROR;
    if (_messageStatusInterruptMask & MESSAGE_ERROR)
        channel.CIRC = CIRC_INT_FROM_SERVICED;
}

/***************************************************************************/
/* MessageComplete eTPU fragment
/***************************************************************************/
/* DESCRIPTION:
/* This fragment is called when a valid message completes.  It clears the error
/* status and interrupts the host if not masked.  Upon exit the function/channels
/* will resume seeking for the next word/message.
/*
/***************************************************************************/
_eTPU_fragment MS1553::MessageComplete()
{
    _errorStatus = NO_ERROR;
    _state = MS1553_STATE_AWAIT_MESSAGE;
    if (_validMessage & 1)
    {
    	_messageStatus |= MESSAGE_COMPLETE;
        if (_messageStatusInterruptMask & _messageStatus)
            channel.CIRC = CIRC_INT_FROM_SERVICED;
    }
    _validMessage = 0;
}
