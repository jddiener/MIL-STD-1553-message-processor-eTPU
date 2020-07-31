/**************************************************************************
* FILE NAME: etec_MS1553.h   
* 
* DESCRIPTION: This file contains the ETEC class declaration for the MIL-STD-1553
* eTPU drivers (RX for MT/RT/BC, and TX for RT/BC).
* 
* 
*========================================================================
* REV      AUTHOR      DATE         DESCRIPTION OF CHANGE
* ---   -----------  -----------    ---------------------
* 1.0   John Diener  2020-May-05    Initial release version.
*
**************************************************************************/

#ifndef __ETEC_MS1553_H
#define __ETEC_MS1553_H

//---------------------------------------------------------
// Synch States
enum SYNCH_STATES
{
    SYNCH_STATE_UNSYNCHED,
    SYNCH_STATE_CMD_STATUS_WORD,
    SYNCH_STATE_DATA_WORD,
};
//---------------------------------------------------------

//---------------------------------------------------------
// Protocol States
enum MS1553_STATES
{
    MS1553_STATE_AWAIT_MESSAGE,
//---------------------------------------------------------
// RT To Controller States, ...
    MS1553_STATE_TBD_TO_RT_AWAITING_DATA,
// Controller To RT States, ...
    MS1553_STATE_BC_TO_RT_AWAITING_DATA,
    MS1553_STATE_BC_TO_RT_AWAITING_STATUS,
// RT to Controller States, ...
    MS1553_STATE_RT_TO_BC_AWAITING_STATUS,
    MS1553_STATE_RT_TO_BC_AWAITING_DATA,
// RT To RT States, ...
    MS1553_STATE_RT_TO_RT_AWAITING_STATUS_A,
    MS1553_STATE_RT_TO_RT_AWAITING_DATA,
    MS1553_STATE_RT_TO_RT_AWAITING_STATUS_B,
// Mode Command States, ...
    MS1553_STATE_MC_XD_AWAITING_STATUS,
    MS1553_STATE_MC_XD_AWAITING_DATA,
    MS1553_STATE_MC_RBD_AWAITING_DATA,
    MS1553_STATE_MC_RD_AWAITING_DATA,
    MS1553_STATE_MC_RD_AWAITING_STATUS,
    MS1553_STATE_MC_X_AWAITING_STATUS,

// Awaiting Idle States (make consecutive for optimization purposes)  AND MUST BE LAST
    MS1553_STATE_AWAIT_IDLE,        // await initial idle or after error (must be first of idle states)
    MS1553_STATE_BC_TO_RT_AWAITING_IDLE_A,
    MS1553_STATE_BC_TO_RT_AWAITING_IDLE_B,
    MS1553_STATE_RT_TO_BC_AWAITING_IDLE_A,
    MS1553_STATE_RT_TO_BC_AWAITING_IDLE_B,
    MS1553_STATE_RT_TO_RT_AWAITING_IDLE_A,
    MS1553_STATE_RT_TO_RT_AWAITING_IDLE_B,
    MS1553_STATE_RT_TO_RT_AWAITING_IDLE_C,
    // mode command await idle states
    MS1553_STATE_MC_XD_AWAITING_IDLE_A,
    MS1553_STATE_MC_XD_AWAITING_IDLE_B,
    MS1553_STATE_MC_RBD_AWAITING_IDLE,
    MS1553_STATE_MC_RD_AWAITING_IDLE_A,
    MS1553_STATE_MC_RD_AWAITING_IDLE_B,
    MS1553_STATE_MC_XB_AWAITING_IDLE,
    MS1553_STATE_MC_X_AWAITING_IDLE_A,
    MS1553_STATE_MC_X_AWAITING_IDLE_B,
};
//---------------------------------------------------------


enum TX_TYPE
{
    TT_CMD_STATUS,
    TT_DATA,
};

enum TX_RT_STATE
{
    TRS_STATUS      = 0x1,
    TRS_STATUS_DATA = 0x2,
    TRS_STATUS_MODE = 0x4,
};

enum TX_BC_STATE
{
    TBS_CMD         = 0x1,  // transmit commands
    TBS_CMD_DATA    = 0x2,  // receive commands
    TBS_CMD_CMD     = 0x4,  // rt-rt commands
};

#define MS1553_TX_DATA_WORD_READY           0x800000U


// Command Word bitmask defines

#define MS1553_WORD_COUNT_BITMASK           0x001F

#define MS1553_SUBADDRESS_MODE_BITMASK      0x03E0
#define MS1553_MODE_1_BITMASK               0x03E0
#define MS1553_MODE_2_BITMASK               0x0000
#define MS1553_MODE_DATA_BITMASK            0x0010

#define MS1553_RX_TX_BITMASK                0x0400

#define MS1553_TERMINAL_ADDRESS_BITMASK     0xF800


_eTPU_class MS1553
{
	// For execution speed considerations, keep these parameter first!
	// low preload, RX
	int24 _firstBitDelineator;
	int24 _0P50_bits;

    // high preload, TX
    unsigned int24 _txBuffer;
	int24 _txBitCount;

    ///////////////////////////////////////////////////////////////////

    // Common data members

	// this terminal's address
	// -1 allowed for an MT - will capture all bus transmissions
	// note: TA is shifted to match bit position in command/status words (bits 15-11)
	int _terminalAddress;

	// Various Bit Time Constants
	int24 _1P25_bits;
	int24 _1P50_bits;
	int24 _1P75_bits;
	int24 _2P25_bits;
	int24 _2P50_bits;
	int24 _18P75_bits;

    // channel numbers in low 5 bits; upper bit(s) may contain eTPU-A, eTPU-B link flag bits
    unsigned int8 _rxBaseChan;
    unsigned int8 _txBaseChan;
    
    ///////////////////////////////////////////////////////////////////
    
    // RX data members
    
	//-----------------------------
    // low-level RX support
    
	// channel frame
	int24 _LastEdgeOnA;
	int24 _LastEdgeOnB;

	// '0' is not synched
	// '1' is a 'COMMAND/STATUS'
	// '2' is a 'DATA' synch
	int24 _synchState;

	int _isLastEdgeAValid;
	int _isLastEdgeBValid;

	int _rxBuffer;
	int _rxBitCount;
	int _rxParityCheck;

	unsigned int8 _parityError;
	unsigned int8 _missingBitError;

    unsigned int24 _rxBuf[MS1553_BUFFER_DEPTH];
    // Pointer for the next incoming word
    unsigned int24 *_rxBufPtr;

	//-----------------------------
	// MT/RT/BC Protocol support

    enum MS1553_STATES _state;

    unsigned int8 _validMessage; // when 1, this is an active message involving this MT/RT
    _Bool _isBroadcastMsg;
    _Bool _isRtRtTransmitter;

    unsigned int _cmdWordBuffer; // temp buffer for possible valid RT-RT transfer
	int _rxDataWordCnt;

    // timing configuration settings (user configurable)
	int24 _initIdleTimeout;
	int24 _rtStatusTimeout;
	int24 _seekIdleTimeout;

    // message status/settings/information
    unsigned int8 _messageType;   
    unsigned int8 _messageStatus;
    unsigned int8 _messageStatusInterruptMask;

    // command words (received by MT/RT, transmitted by BC)
    unsigned int24 _cmdWord1;
    unsigned int24 _cmdWord2;
    
    // received mode data and status words
    unsigned int24 _rxModeWord;
    unsigned int24 _rxStatusWord1;
    unsigned int24 _rxStatusWord2;
    
    unsigned int24 _dataWordCnt;
    
    // error status (0 if no error)
    // gets cleared on valid message completion
    unsigned int8 _errorStatus;
    

    ///////////////////////////////////////////////////////////////////

    // TX data members

	unsigned int24 _transmitWord; // word being transmitted (data in bits 15-0, bit 23 is ready flag)
	unsigned int24 _transmitNextWord;
    unsigned int24* _txNextWordPtr;
	int8 _txParityCheck;
	enum TX_TYPE _synchType;
	unsigned int24 _txEndTimestamp;

	//-----------------------------
	// RT transmit support
	
	enum TX_RT_STATE _txType;
	unsigned int24 _txDelay; // response time, user configurable (> 4us, < 12us)

	unsigned int8 _txInhibit;
	unsigned int8 _txDataWordInhibit;
	
	unsigned int24 _txModeWord;
	unsigned int24 _txStatusWord;
	
	//-----------------------------
	// RT/BC transmit support (data / mode data)

	int24 _txWordCnt;
    unsigned int24 _txBuf[MS1553_BUFFER_DEPTH];
    unsigned int24* _txBufPtr;

	//-----------------------------
	// BC message support
	_Bool _bcMessageInProgress;
	enum TX_BC_STATE _bcTxType;


    ///////////////////////////////////////////////////////////////////

	//-----------------------------
	// RX fragments

	_eTPU_fragment InitCommon_RX();
	_eTPU_fragment SeekSynchCommonP();
	_eTPU_fragment SeekSynchCommonN();
	
	_eTPU_fragment Error_InWord(int8 errorNum);
	_eTPU_fragment Error_InIdle(int8 errorNum);
	_eTPU_fragment MessageComplete();

	_eTPU_fragment Error_InWord_BC(int8 errorNum);
	_eTPU_fragment Error_InIdle_BC(int8 errorNum);
	_eTPU_fragment MessageComplete_BC();

    _eTPU_fragment StatusResponse_RT();
    _eTPU_fragment DataResponse_RT();
    _eTPU_fragment ModeResponse_RT();

	//-----------------------------
	// RX methods
	
	// none currently

	//-----------------------------
	// RX threads

	// common threads
	_eTPU_thread AwaitInitIdleP(_eTPU_matches_enabled);
	_eTPU_thread AwaitInitIdleN(_eTPU_matches_enabled);
	_eTPU_thread FoundInitIdle(_eTPU_matches_enabled);
	_eTPU_thread FromOneBit(_eTPU_matches_enabled, _eTPU_preload_low);
	_eTPU_thread FromZeroBit(_eTPU_matches_enabled, _eTPU_preload_low);
	_eTPU_thread Shutdown_RX(_eTPU_matches_disabled);

    // basic-only RX threads
	_eTPU_thread Init_RX(_eTPU_matches_disabled);
	_eTPU_thread SeekSynchP_RX(_eTPU_matches_enabled);
	_eTPU_thread SeekSynchN_RX(_eTPU_matches_enabled);
	_eTPU_thread HandleWord_RX(_eTPU_matches_enabled);
	_eTPU_thread FoundIdle_RX(_eTPU_matches_enabled);

	// MT-only threads
	_eTPU_thread Init_MT_RX(_eTPU_matches_disabled);
	_eTPU_thread HandleWord_MT(_eTPU_matches_enabled);
	_eTPU_thread FoundIdle_MT(_eTPU_matches_enabled);
	
	// MT/RT threads
	_eTPU_thread SeekSynchP_MT_RT(_eTPU_matches_enabled);
	_eTPU_thread SeekSynchN_MT_RT(_eTPU_matches_enabled);

	// RT-only threads
	_eTPU_thread Init_RT_RX(_eTPU_matches_disabled);
	_eTPU_thread HandleWord_RT(_eTPU_matches_enabled);
	_eTPU_thread FoundIdle_RT(_eTPU_matches_enabled);
	_eTPU_thread TransmitDone_RT(_eTPU_matches_enabled);
	
	// BC-only threads
	_eTPU_thread Init_BC_RX(_eTPU_matches_disabled);
	_eTPU_thread SeekBusIdleRequest(_eTPU_matches_disabled);
	_eTPU_thread SeekBusIdleP(_eTPU_matches_enabled);
	_eTPU_thread SeekBusIdleN(_eTPU_matches_enabled);
	_eTPU_thread SeekBusIdleSuccess(_eTPU_matches_enabled);
	_eTPU_thread SeekSynchP_BC(_eTPU_matches_enabled);
	_eTPU_thread SeekSynchN_BC(_eTPU_matches_enabled);
	_eTPU_thread HandleWord_BC(_eTPU_matches_enabled);
	_eTPU_thread FoundIdle_BC(_eTPU_matches_enabled);
    _eTPU_thread ExpectMessageResponse_BC(_eTPU_matches_enabled);

	//-----------------------------
	// RX entry tables

	_eTPU_entry_table MS1553_RX_P;
	_eTPU_entry_table MS1553_RX_N;
	_eTPU_entry_table MS1553_MT_RX_P;
	_eTPU_entry_table MS1553_MT_RX_N;
	_eTPU_entry_table MS1553_RT_RX_P;
	_eTPU_entry_table MS1553_RT_RX_N;
	_eTPU_entry_table MS1553_BC_RX_P;
	_eTPU_entry_table MS1553_BC_RX_N;


    ///////////////////////////////////////////////////////////////////
    
    ///////////////////////////////////////////////////////////////////

    //-----------------------------
    // TX fragments
	
    _eTPU_fragment TransmitCommon();
    _eTPU_fragment TransmitCommandSync();
    _eTPU_fragment TransmitDataSync();

    //-----------------------------
    // TX methods
	
    // none currently

    //-----------------------------
    // TX threads

    // common threads
    _eTPU_thread Init_TX(_eTPU_matches_disabled);
    _eTPU_thread Transmit(_eTPU_matches_disabled);
    _eTPU_thread StartTransmitBit(_eTPU_matches_enabled, _eTPU_preload_high);
    _eTPU_thread TransmitBit(_eTPU_matches_enabled, _eTPU_preload_high);
    _eTPU_thread Shutdown_TX(_eTPU_matches_disabled);

    // basic-only TX threads
    _eTPU_thread TransmitCleanup(_eTPU_matches_enabled);
    _eTPU_thread TransmitComplete(_eTPU_matches_enabled);
	
    // RT-only threads
    _eTPU_thread TransmitRequest_RT(_eTPU_matches_enabled);
    _eTPU_thread TransmitCleanup_RT(_eTPU_matches_enabled);
    _eTPU_thread TransmitComplete_RT(_eTPU_matches_enabled);
	
    // BC-only threads
    _eTPU_thread TransmitMessage_BC(_eTPU_matches_enabled);
    _eTPU_thread TransmitCleanup_BC(_eTPU_matches_enabled);
    _eTPU_thread TransmitComplete_BC(_eTPU_matches_enabled);

	//-----------------------------
	// TX entry tables

	_eTPU_entry_table MS1553_TX;
	_eTPU_entry_table MS1553_RT_TX;
	_eTPU_entry_table MS1553_BC_TX;

};

#endif // __ETEC_MS1553_H
