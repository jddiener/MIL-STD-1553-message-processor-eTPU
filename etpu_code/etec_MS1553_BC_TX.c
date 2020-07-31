/**************************************************************************
 * Copyright (C) 2020 ASH WARE, Inc.
 *************************************************************************/
/**************************************************************************
* FILE NAME: etec_MS1553_BC_TX.c   
* 
* DESCRIPTION: This file contains the thread and function definitions specific
* to the Bus Controller (BC) MIL-STD-1553 transmitter eTPU drivers
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
/* BC_TX Entry Table Definition
/***************************************************************************/
/* DESCRIPTION:
/* The table below configures the 32 unique entry points for the Bus Controller
/* MIL-STD-1553 transmitter (BC_TX) eTPU code.
/* Note that all functions/channels that service the 1553 bus for a terminal
/* share an eTPU channel frame.
/*
/***************************************************************************/
DEFINE_ENTRY_TABLE(MS1553, MS1553_BC_TX, alternate, outputpin, autocfsr)
{
	//           HSR    LSR M1 M2 PIN F0 F1 vector
	ETPU_VECTOR2(6,7,   x,  x, x, x,  x, x, Init_TX),
	ETPU_VECTOR2(2,3,   x,  x, x, 0,  0, x, Shutdown_TX),
	ETPU_VECTOR2(2,3,   x,  x, x, 0,  1, x, Shutdown_TX),
	ETPU_VECTOR2(2,3,   x,  x, x, 1,  0, x, Shutdown_TX),
	ETPU_VECTOR2(2,3,   x,  x, x, 1,  1, x, Shutdown_TX),

	ETPU_VECTOR3(1,4,5, x,  x, x, x,  x, x, TransmitMessage_BC),

	ETPU_VECTOR1(0,     x,  1, 1, 0,  0, 0, StartTransmitBit),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  0, 0, StartTransmitBit),

	ETPU_VECTOR1(0,     x,  1, 1, 0,  1, 0, TransmitBit),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  1, 0, TransmitBit),

	ETPU_VECTOR1(0,     x,  1, 1, 0,  1, 1, TransmitCleanup_BC),
	ETPU_VECTOR1(0,     x,  1, 1, 1,  1, 1, TransmitCleanup_BC),

	ETPU_VECTOR1(0,     x,  0, 1, 0,  1, 1, TransmitComplete_BC),
	ETPU_VECTOR1(0,     x,  0, 1, 1,  1, 1, TransmitComplete_BC),

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
/* TransmitMessage_BC eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread is activated by a host service request.  It sets up to transmit
/* the command word(s) and data, depending upon the requested message type.  The
/* request is ignored and an error set if a message is already in progress.
/*
/***************************************************************************/
_eTPU_thread MS1553::TransmitMessage_BC(_eTPU_matches_enabled)
{
    // check if message currently in process
    // if busy, ignore request, set error status and generate interrupt
    if (_bcMessageInProgress == TRUE)
    {
    	_errorStatus = BC_BUS_BUSY_ERROR;
        channel.CIRC = CIRC_INT_FROM_SERVICED;
        _ExitThread();
    }
    
    // configure protocol processing based upon message type
    switch (_messageType)
    {
        // single command word message types
        case RT_TO_BC_XFR:
            _bcTxType = TBS_CMD;
            _txWordCnt = 0;
            _rxDataWordCnt = _cmdWord1 & 0x1f;
            _state = MS1553_STATE_RT_TO_BC_AWAITING_IDLE_A;
            _isBroadcastMsg = FALSE;
            break;
        case MODE_XMT_WITHOUT_DATA:
            _bcTxType = TBS_CMD;
            _txWordCnt = 0;
            _rxDataWordCnt = 0;
            _state = MS1553_STATE_MC_X_AWAITING_IDLE_A;
            _isBroadcastMsg = FALSE;
            break;
        case MODE_XMT_WITH_DATA:
            _bcTxType = TBS_CMD;
            _txWordCnt = 0;
            _rxDataWordCnt = 0;
            _state = MS1553_STATE_MC_XD_AWAITING_IDLE_A;
            _isBroadcastMsg = FALSE;
            break;
        case MODE_BROADCAST_WITHOUT_DATA:
            _bcTxType = TBS_CMD;
            _txWordCnt = 0;
            _rxDataWordCnt = 0;
            _state = MS1553_STATE_MC_XB_AWAITING_IDLE;
            _isBroadcastMsg = TRUE;
            break;

        // command word + data message types
        case BC_TO_RT_XFR:
            _bcTxType = TBS_CMD_DATA;
            _txWordCnt = _cmdWord1 & 0x1f;
            _rxDataWordCnt = 0;
            _state = MS1553_STATE_BC_TO_RT_AWAITING_IDLE_A;
            _isBroadcastMsg = FALSE;
            break;
        case BC_TO_RT_BROADCAST_XFR:
            _bcTxType = TBS_CMD_DATA;
            _txWordCnt = _cmdWord1 & 0x1f;
            _rxDataWordCnt = 0;
            _state = MS1553_STATE_BC_TO_RT_AWAITING_IDLE_A;
            _isBroadcastMsg = TRUE;
            break;
        case MODE_RCV_WITH_DATA:
            _bcTxType = TBS_CMD_DATA;
            _txWordCnt = 1;
            _rxDataWordCnt = 0;
            _state = MS1553_STATE_MC_RD_AWAITING_IDLE_A;
            _isBroadcastMsg = FALSE;
            break;
        case MODE_BROADCAST_WITH_DATA:
            _bcTxType = TBS_CMD_DATA;
            _txWordCnt = 1;
            _rxDataWordCnt = 0;
            _state = MS1553_STATE_MC_RBD_AWAITING_IDLE;
            _isBroadcastMsg = TRUE;
            break;

        // two command word message types
        case RT_TO_RT_XFR:
            _bcTxType = TBS_CMD_CMD;
            _txWordCnt = 1;
            _rxDataWordCnt = _cmdWord2 & 0x1f;
            _state = MS1553_STATE_RT_TO_RT_AWAITING_IDLE_A;
            _isBroadcastMsg = FALSE;
            break;
        case RT_TO_RT_BROADCAST_XFR:
            _bcTxType = TBS_CMD_CMD;
            _txWordCnt = 1;
            _rxDataWordCnt = _cmdWord2 & 0x1f;
            _state = MS1553_STATE_RT_TO_RT_AWAITING_IDLE_A;
            _isBroadcastMsg = TRUE;
            break;
            
        default:
            _errorStatus = BC_INVALID_MESSAGE_TYPE_ERROR;
            channel.CIRC = CIRC_INT_FROM_SERVICED;
            _ExitThread();
            break;
    }

    _bcMessageInProgress = TRUE;
    _messageStatus = 0;

    // begin the message in half a bit time
	erta = ertb = tcr1 + _0P50_bits; // initialize a start time...

    _txNextWordPtr = &_cmdWord1;
    _txBufPtr = _txBuf;
   	TransmitCommandSync();
}

/***************************************************************************/
/* TransmitCleanup_BC eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread runs half way through the parity bit, and sets up to transmit the
/* next word if necessary, or end transmission.
/*
/***************************************************************************/
_eTPU_thread MS1553::TransmitCleanup_BC(_eTPU_matches_enabled)
{
	ClearMatchALatch();
	ClearMatchBLatch();

    if (--_txWordCnt >= 0)
    {
        // IF THERE IS ANOTHER WORD TO TRANSMIT, THE SYNC MUST BE CONTIGUOUS TO THE PARITY BIT!!
        // IMMEDIATELY SET UP NEXT SYNC
        if (_bcTxType & TBS_CMD_DATA)
        {
            _txNextWordPtr = _txBufPtr;
            _txBufPtr++;
            TransmitDataSync();
        }
        else
        {
            _txNextWordPtr = &_cmdWord2;
   	        TransmitCommandSync();
        }
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
/* TransmitComplete_BC eTPU thread
/***************************************************************************/
/* DESCRIPTION:
/* This thread runs when transmission has fully completed and the bus has gone idle.
/* The BC RX master channel is sent a link to let it know that it needs to perform
/* the next stages of protocol processing.
/*
/***************************************************************************/
_eTPU_thread MS1553::TransmitComplete_BC(_eTPU_matches_enabled)
{
	ClearMatchALatch();
	ClearMatchBLatch();

	// handoff to RX side of BC to complete message processing
	link = _rxBaseChan;
}
