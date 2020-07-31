/**************************************************************************
 * Copyright (C) 2020 ASH WARE, Inc.
 *************************************************************************/
/**************************************************************************
* FILE NAME: etec_MS1553_RT_RX.c   
* 
* DESCRIPTION: This file contains the thread and function definitions specific
* to the Remote Terminal (RT) MIL-STD-1553 receiver eTPU driver
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
/* RT_RX_P Entry Table Definition
/***************************************************************************/
/* DESCRIPTION:
/* The table below configures the 32 unique entry points for the Remote Terminal
/* MIL-STD-1553 receiver (RT_RX) eTPU code (positive digital input).
/* Note that all functions/channels that service the 1553 bus for a terminal
/* share an eTPU channel frame.
/*
/***************************************************************************/
DEFINE_ENTRY_TABLE(MS1553, MS1553_RT_RX_P, alternate, inputpin, autocfsr)
{

	//-----------------------------------------------------
	// Valid states, ...
	//           HSR    LSR M1 M2 PIN F0 F1 vector
	ETPU_VECTOR2(6,7,   x,  x, x, x,  x, x, Init_RT_RX),
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

	ETPU_VECTOR1(0,     x,  1, 0, 0,  0, 0, FoundIdle_RT),
	ETPU_VECTOR1(0,     x,  1, 0, 1,  0, 0, FoundIdle_RT),
	// When Both TDL and MRL are set, MRL must have occurred first ...
	ETPU_VECTOR1(0,     x,  1, 1, 0,  0, 0, FoundIdle_RT),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  0, 0, FoundIdle_RT),


	ETPU_VECTOR1(0,     x,  0, 1, 0,  1, 1, FromOneBit),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  1, 1, FromOneBit),

	ETPU_VECTOR1(0,     x,  0, 1, 0,  0, 1, FromZeroBit),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  0, 1, FromZeroBit),

	ETPU_VECTOR1(0,     x,  1, 0, 0,  0, 1, HandleWord_RT),
	ETPU_VECTOR1(0,     x,  1, 0, 1,  0, 1, HandleWord_RT),
	ETPU_VECTOR1(0,     x,  1, 0, 0,  1, 1, HandleWord_RT),
	ETPU_VECTOR1(0,     x,  1, 0, 1,  1, 1, HandleWord_RT),
	// in the cases below the HandleWord match has been pushed back into further
	// signal activity - process the HandleWord and then handle transition detection in
	// separate thread
	ETPU_VECTOR1(0,     x,  1, 1, 0,  0, 1, HandleWord_RT),
	ETPU_VECTOR1(0,     x,  1, 1, 0,  1, 1, HandleWord_RT),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  0, 1, HandleWord_RT),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  1, 1, HandleWord_RT),

    // transmit complete link from the TX chan set
	ETPU_VECTOR1(0,     1,  0, 0, 0,  x, x, TransmitDone_RT),
	ETPU_VECTOR1(0,     1,  0, 0, 1,  x, x, TransmitDone_RT),

	//-----------------------------------------------------
	// Unused States
	//           HSR    LSR M1 M2 PIN F0 F1 vector
	ETPU_VECTOR3(1,4,5, x,  x, x, x,  x, x, _Error_handler_entry),

};

/***************************************************************************/
/* RT_RX_N Entry Table Definition
/***************************************************************************/
/* DESCRIPTION:
/* The table below configures the 32 unique entry points for the Remote Terminal
/* MIL-STD-1553 receiver (RT_RX) eTPU code (negative digital input).
/* Note that all functions/channels that service the 1553 bus for a terminal
/* share an eTPU channel frame.
/*
/***************************************************************************/
DEFINE_ENTRY_TABLE(MS1553, MS1553_RT_RX_N, alternate, inputpin, autocfsr)
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
/* Init_RT_RX eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread configures the RX channel pair for 1553 RT input processing. 
/*
/***************************************************************************/
_eTPU_thread MS1553::Init_RT_RX(_eTPU_matches_disabled)
{
    _state = MS1553_STATE_AWAIT_MESSAGE;
    _rxBufPtr = _rxBuf;
    InitCommon_RX();
}

/***************************************************************************/
/* HandleWord_RT eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread activates 0.25us after the expected end of a word - it verifies
/* the word is valid and then performs message protocol processing.
/*
/***************************************************************************/
_eTPU_thread MS1553::HandleWord_RT(_eTPU_matches_enabled)
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
					else if ((receivedWord & MS1553_TERMINAL_ADDRESS_BITMASK) == _terminalAddress)
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
    					
    					// note: cannot be a broadcast
    					if ((receivedWord & MS1553_TERMINAL_ADDRESS_BITMASK) == _terminalAddress)
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
    					// Set the state to
    					// 'TBD to RT Transfer ... Seeking RT TX Command or DATA'
    					// Note: Next word will be a 'DATA' (for 'Controller to RT')
    					//       OR next word will be a 'XMT CMD'  (for RT to RT xfer)
    					_state=MS1553_STATE_TBD_TO_RT_AWAITING_DATA;
    					
    					if ((receivedWord & MS1553_TERMINAL_ADDRESS_BITMASK) == _terminalAddress)
    					{
    					    _cmdWord1 = receivedWord;
    					    _dataWordCnt = _rxDataWordCnt;
    					    _validMessage = 1;
    					}
    					else if ((receivedWord & MS1553_TERMINAL_ADDRESS_BITMASK) == MS1553_TERMINAL_ADDRESS_BITMASK)
    					{
    					    // broadcast..., all RTs read data
    					    _cmdWord1 = receivedWord;
    					    _dataWordCnt = _rxDataWordCnt;
    					    _validMessage = 1;
    					    _isBroadcastMsg = TRUE;
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
    			// Decrement the data word count
    			// If all data words have been received,
    			// Set to seeking IDLE
    			_rxDataWordCnt--;
    			if( _rxDataWordCnt == 0)
    			{
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
    			{
                    _validMessage = 1;
                    _isRtRtTransmitter = TRUE;
                }
                else
                    _isRtRtTransmitter = FALSE;

    			// There should be an idle next,
    			// If not, by clearing the edge valid, an error will be detected. 
    			_isLastEdgeAValid = 0;
    			_isLastEdgeBValid = 0;
    			
    			if (_validMessage & 1)
    			{
                    _cmdWord1 = _cmdWordBuffer;
                    _cmdWord2 = receivedWord;
				    _dataWordCnt = _rxDataWordCnt;
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
    			if( _rxDataWordCnt == 0)
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
    		if( _rxDataWordCnt == 0)
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

    		_state = MS1553_STATE_RT_TO_RT_AWAITING_DATA;
    		
    		// do not save this status word
    		// for an RT-RT transfer, an RT only saves the final status from receiving RT if it was transmitting RT
    		// thus no status interrupt here
    		
    		break;
    	}
    	case MS1553_STATE_RT_TO_RT_AWAITING_DATA:
    	{
    		if( _synchState!=SYNCH_STATE_DATA_WORD)
    		{
    			Error_InWord(RT_STATUS_WHEN_EXPECTED_DATA_ERROR);
    		}

    		// save data if we are a receiving RT
    		if (_validMessage & 1) // && !_isRtRtTransmitter) // transmitting RT skips this state, check not needed
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

    		_state = MS1553_STATE_RT_TO_RT_AWAITING_IDLE_C;

    		// There should be an idle next,
    		// If not, by clearing the edge valid, an error will be detected. 
    		_isLastEdgeAValid = 0;
    		_isLastEdgeBValid = 0;
    		
            // store the status if this was transmitting RT
            if (_isRtRtTransmitter)
            {
                _rxStatusWord1 = receivedWord;
                _messageStatus = MESSAGE_STATUS_VALID;
                // the status valid interrupt will piggy-back with the message complete 
                //if (_messageStatusInterruptMask & MESSAGE_STATUS_VALID)
                //    channel.CIRC = CIRC_INT_FROM_SERVICED;
            }
    		
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
    		_state = MS1553_STATE_MC_XD_AWAITING_DATA;
    		break;
        }
        
        case MS1553_STATE_MC_XD_AWAITING_DATA:
        {
    		if( _synchState!=SYNCH_STATE_DATA_WORD)
    		{
    			Error_InWord(RT_STATUS_WHEN_EXPECTED_DATA_ERROR);
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
    		_state = MS1553_STATE_MC_RD_AWAITING_IDLE_B;
            break;
        }
        
        case MS1553_STATE_MC_X_AWAITING_STATUS:
        {
    		if( _synchState!=SYNCH_STATE_CMD_STATUS_WORD)
    		{
    			Error_InWord(RT_DATA_WHEN_EXPECTED_STATUS_ERROR);
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
/* FoundIdle_RT eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread activates if there has been no bus activity for the 2us following
/* the end of a word.
/*
/***************************************************************************/
_eTPU_thread MS1553::FoundIdle_RT(_eTPU_matches_enabled)
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
    		if (_validMessage & 1)
    		{
        	    _state = MS1553_STATE_RT_TO_BC_AWAITING_IDLE_B;
        	    DataResponse_RT();
    		}
    		else
    		{
                // only do timeout check if this not the responding RT 
        		ertA = ertA + _rtStatusTimeout;
        		WriteErtAToMatchAAndEnable();
            }
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
    			break;
    		}
			if (_validMessage & 1)
			{
        	    _state = MS1553_STATE_BC_TO_RT_AWAITING_IDLE_B;
        	    StatusResponse_RT();
			}
    		else
    		{
                _state = MS1553_STATE_BC_TO_RT_AWAITING_STATUS;
        		// only do timeout check if this not the responding RT 
        		ertA = ertA + _rtStatusTimeout;
        		WriteErtAToMatchAAndEnable();
            }
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
    		if ((_validMessage & 1) && _isRtRtTransmitter)
    		{
        	    _state = MS1553_STATE_RT_TO_RT_AWAITING_IDLE_B;
        	    DataResponse_RT();
    		}
    		else
    		{
       	        _state = MS1553_STATE_RT_TO_RT_AWAITING_STATUS_A;
        		// only do timeout check if this not the responding RT 
        		ertA = ertA + _rtStatusTimeout;
        		WriteErtAToMatchAAndEnable();
        	}
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
    			break;
    		}

			if ((_validMessage & 1) && !_isRtRtTransmitter)
			{
        	    _state = MS1553_STATE_RT_TO_RT_AWAITING_IDLE_C;
        	    StatusResponse_RT();
			}
    		else
    		{
                _state = MS1553_STATE_RT_TO_RT_AWAITING_STATUS_B;
                // only do timeout check if this not the responding RT 
        		ertA = ertA + _rtStatusTimeout;
        		WriteErtAToMatchAAndEnable();
        	}
    		break;
    	}

    	//-----------------------------
    	// This is a message complete idle
    	case MS1553_STATE_BC_TO_RT_AWAITING_IDLE_B:
    	case MS1553_STATE_RT_TO_BC_AWAITING_IDLE_B:
    	case MS1553_STATE_RT_TO_RT_AWAITING_IDLE_C:
    	{
    	    MessageComplete();
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
    		if (!(_validMessage & 1))
    		{
                _state = MS1553_STATE_MC_XD_AWAITING_STATUS;
        		ertA = ertA + _rtStatusTimeout;
        		WriteErtAToMatchAAndEnable();
        	}
        	else
        	{
                _state = MS1553_STATE_MC_XD_AWAITING_IDLE_B;
                ModeResponse_RT();
        	}
    		break;
    	}
    	
    	//---------------------------------------------------------------------
    	// next RT to transmit status
    	case MS1553_STATE_MC_RD_AWAITING_IDLE_A:
    	{
    		if (!(_validMessage & 1))
    		{
                _state = MS1553_STATE_MC_RD_AWAITING_STATUS;
        		ertA = ertA + _rtStatusTimeout;
        		WriteErtAToMatchAAndEnable();
        	}
        	else
        	{
                _state = MS1553_STATE_MC_RD_AWAITING_IDLE_B;
                StatusResponse_RT();
        	}
    		break;
    	}
    	
    	//---------------------------------------------------------------------
    	// next RT to transmit status
    	case MS1553_STATE_MC_X_AWAITING_IDLE_A:
    	{
    		if (!(_validMessage & 1))
    		{
                _state = MS1553_STATE_MC_X_AWAITING_STATUS;
        		ertA = ertA + _rtStatusTimeout;
        		WriteErtAToMatchAAndEnable();
        	}
        	else
        	{
                _state = MS1553_STATE_MC_X_AWAITING_IDLE_B;
                StatusResponse_RT();
        	}
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
/* TransmitDone_RT eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread activates from a link sent by the TX channel pair, indicating the RT
/* response has completed.  A bus idle is expected next.
/*
/***************************************************************************/
_eTPU_thread MS1553::TransmitDone_RT(_eTPU_matches_enabled)
{
    channel.LSR = LSR_CLEAR;

    // any message status should now be cleared
    _messageStatus = 0;
   
    // idle minimum is 2.5 bits from mid-parity to start of next synch
    ertA = _txEndTimestamp + _2P50_bits;
    channel.ERWA = ERW_WRITE_ERT_TO_MATCH;
    // clear any old trans detect state and re-enable servicing
    channel.TDL = TDL_CLEAR;
    channel.IPACA = IPAC_RISING;
    chan += 1;
    channel.TDL = TDL_CLEAR;
    channel.IPACA = IPAC_RISING;
}


/***************************************************************************/
/* StatusResponse_RT eTPU fragment
/***************************************************************************/
/* DESCRIPTION:
/* This fragment is called when the RT needs to transmit a status response.  It
/* configures the transmission and links to the master TX channel to 
/* initiate the process.
/*
/***************************************************************************/
_eTPU_fragment MS1553::StatusResponse_RT()
{
    if ((_txInhibit & TX_INHIBIT_BITMASK) == TX_INHIBIT_ENABLED)
    {
    	_state = MS1553_STATE_AWAIT_MESSAGE;
    	_validMessage = 0;
    	_messageStatus = MESSAGE_TRANSMIT_INHIBITED;
        if (_messageStatusInterruptMask & MESSAGE_TRANSMIT_INHIBITED)
            channel.CIRC = CIRC_INT_FROM_SERVICED;
    }
    else
    {
        // send request to TX
        _txType = TRS_STATUS;
        _txWordCnt = 0;
        link = _txBaseChan;
        // turn off RX until TX completes
        channel.IPACA = IPAC_NO_DETECT;
        channel.TDL = TDL_CLEAR;
        chan += 1;
        channel.IPACA = IPAC_NO_DETECT;
        channel.TDL = TDL_CLEAR;
    }
}

/***************************************************************************/
/* DataResponse_RT eTPU fragment
/***************************************************************************/
/* DESCRIPTION:
/* This fragment is called when the RT needs to transmit a status and data response.  It
/* configures the transmission and links to the master TX channel to 
/* initiate the process.
/*
/***************************************************************************/
_eTPU_fragment MS1553::DataResponse_RT()
{
    if ((_txInhibit & TX_INHIBIT_BITMASK) == TX_INHIBIT_ENABLED)
    {
    	_state = MS1553_STATE_AWAIT_MESSAGE;
    	_validMessage = 0;
    	_messageStatus = MESSAGE_TRANSMIT_INHIBITED;
        if (_messageStatusInterruptMask & MESSAGE_TRANSMIT_INHIBITED)
            channel.CIRC = CIRC_INT_FROM_SERVICED;
    }
    else
    {
        // send request to TX
        _txType = TRS_STATUS_DATA;
        _txWordCnt = _dataWordCnt;
        link = _txBaseChan;
        // turn off RX until TX completes
        channel.IPACA = IPAC_NO_DETECT;
        channel.TDL = TDL_CLEAR;
        chan += 1;
        channel.IPACA = IPAC_NO_DETECT;
        channel.TDL = TDL_CLEAR;
    }
}

/***************************************************************************/
/* ModeResponse_RT eTPU fragment
/***************************************************************************/
/* DESCRIPTION:
/* This fragment is called when the RT needs to transmit a status and mode data
/* response.  It configures the transmission and links to the master TX channel to 
/* initiate the process.
/*
/***************************************************************************/
_eTPU_fragment MS1553::ModeResponse_RT()
{
    if ((_txInhibit & TX_INHIBIT_BITMASK) == TX_INHIBIT_ENABLED)
    {
    	_state = MS1553_STATE_AWAIT_MESSAGE;
    	_validMessage = 0;
    	_messageStatus = MESSAGE_TRANSMIT_INHIBITED;
        if (_messageStatusInterruptMask & MESSAGE_TRANSMIT_INHIBITED)
            channel.CIRC = CIRC_INT_FROM_SERVICED;
    }
    else
    {
        // send request to TX
        _txType = TRS_STATUS_MODE;
        _txWordCnt = 1;
        link = _txBaseChan;
        // turn off RX until TX completes
        channel.IPACA = IPAC_NO_DETECT;
        channel.TDL = TDL_CLEAR;
        chan += 1;
        channel.IPACA = IPAC_NO_DETECT;
        channel.TDL = TDL_CLEAR;
    }
}
