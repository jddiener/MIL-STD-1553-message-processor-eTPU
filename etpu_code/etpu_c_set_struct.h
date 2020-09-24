/* This file is auto-generated by the ASH WARE ETEC Linker. */
/* It contains useful information for host-CPU side driver code */
/*    !!!   DO NOT EDIT THIS FILE   !!! */
/* Copyright (C) 2015 ASH WARE, Inc. */

#ifndef __etpu_c_set_struct_H
#define __etpu_c_set_struct_H


/* data structure (map) of all non-24-bit GLOBAL data */
/* unnamed bit-fields are used to fill any gaps in the data map */
/* bitfield access generates read-modify-write code (non-coherent), */
/* so if this is an issue, access bitfields via their unit instead. */
typedef struct
{
	/* 0x0000 */
	etpu_if_sint32				_Global_error_data;
} etpu_if_C_GLOBAL_DATA;
#define etpu_if_C_GLOBAL_DATA_EXPECTED_SIZE 4


/* data structure of all 24-bit Tester CHANNEL FRAME data (meant to be accessed via PSE mirror)*/
/* unnamed bit-fields are used to fill any gaps in the data map */
/* bitfield access generates read-modify-write code (non-coherent), */
/* so if this is an issue, access bitfields via their unit instead. */
/* NOTE: it is recommended that 24-bit data be accessed via the separate */
/* signed and unsigned PSE data structures.  Unsigned 24-bit reads must have */
/* the upper 8 bits of the resulting 32-bit word ANDed to 0. */
typedef struct
{
	/* 0x0000 */
	etpu_if_sint32				linkToChanNum;
	/* 0x0004 */
	etpu_if_sint32				LatencyStart;
	/* 0x0008 */
	etpu_if_sint32				LatencyDuration;
	/* 0x000c */
	etpu_if_sint32				LatencyPeriod;
	/* 0x0010 */
	etpu_if_sint32				EncodedForcedState;
	/* 0x0014 */
	etpu_if_sint32				latencyTimeStamp;
} etpu_if_C_Tester_CHANNEL_FRAME_PSE;
#define etpu_if_C_Tester_CHANNEL_FRAME_PSE_EXPECTED_SIZE 24


/* data structure of all signed 24-bit Tester CHANNEL FRAME data (meant to be accessed via PSE mirror)*/
/* unnamed bit-fields are used to fill any gaps in the data map */
/* bitfield access generates read-modify-write code (non-coherent), */
/* so if this is an issue, access bitfields via their unit instead. */
typedef struct
{
	/* 0x0000 */
	etpu_if_sint32				linkToChanNum;
	/* 0x0004 */
	etpu_if_sint32				LatencyStart;
	/* 0x0008 */
	etpu_if_sint32				LatencyDuration;
	/* 0x000c */
	etpu_if_sint32				LatencyPeriod;
	/* 0x0010 */
	etpu_if_sint32				EncodedForcedState;
	/* 0x0014 */
	etpu_if_sint32				latencyTimeStamp;
} etpu_if_C_Tester_CHANNEL_FRAME_signedPSE;
#define etpu_if_C_Tester_CHANNEL_FRAME_signedPSE_EXPECTED_SIZE 24


/* data structure (map) of all non-24-bit MS1553 CHANNEL FRAME data */
/* unnamed bit-fields are used to fill any gaps in the data map */
/* bitfield access generates read-modify-write code (non-coherent), */
/* so if this is an issue, access bitfields via their unit instead. */
typedef struct
{
	/* 0x0000 */
	etpu_if_uint8				_rxBaseChan;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	/* 0x0004 */
	etpu_if_uint8				_txBaseChan;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	/* 0x0008 */
	etpu_if_uint8				_parityError;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	/* 0x000c */
	etpu_if_uint8				_missingBitError;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	/* 0x0010 */
	etpu_if_uint8				_state;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	/* 0x0014 */
	etpu_if_uint8				_validMessage;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	/* 0x0018 */
	union {
		etpu_if_uint8			_UNIT;
		struct {
#if defined(MSB_BITFIELD_ORDER)
			etpu_if_uint8 : 5;
			etpu_if_uint8		_bcMessageInProgress : 1;
			etpu_if_uint8		_isRtRtTransmitter : 1;
			etpu_if_uint8		_isBroadcastMsg : 1;
#elif defined(LSB_BITFIELD_ORDER)
			etpu_if_uint8		_isBroadcastMsg : 1;
			etpu_if_uint8		_isRtRtTransmitter : 1;
			etpu_if_uint8		_bcMessageInProgress : 1;
			etpu_if_uint8 : 5;
#else
#error Users of auto-struct must define either MSB_BITFIELD_ORDER or LSB_BITFIELD_ORDER
#endif
		} _BF;
	} _BF_UNIT_0018;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	/* 0x001c */
	etpu_if_uint8				_messageType;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	/* 0x0020 */
	etpu_if_uint8				_messageStatus;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	/* 0x0024 */
	etpu_if_uint8				_messageStatusInterruptMask;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	/* 0x0028 */
	etpu_if_uint8				_errorStatus;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	/* 0x002c */
	etpu_if_sint8				_txParityCheck;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	/* 0x0030 */
	etpu_if_uint8				_synchType;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	/* 0x0034 */
	etpu_if_uint8				_txType;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	/* 0x0038 */
	etpu_if_uint8				_txInhibit;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	/* 0x003c */
	etpu_if_uint8				_txDataWordInhibit;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	/* 0x0040 */
	etpu_if_uint8				_bcTxType;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	etpu_if_uint8 : 8;
	/* 0x0044 */
	etpu_if_uint32 : 32;
	/* 0x0048 */
	etpu_if_uint32 : 32;
	/* 0x004c */
	etpu_if_uint32 : 32;
	/* 0x0050 */
	etpu_if_uint32 : 32;
	/* 0x0054 */
	etpu_if_uint32 : 32;
	/* 0x0058 */
	etpu_if_uint32 : 32;
	/* 0x005c */
	etpu_if_uint32 : 32;
	/* 0x0060 */
	etpu_if_uint32 : 32;
	/* 0x0064 */
	etpu_if_uint32 : 32;
	/* 0x0068 */
	etpu_if_uint32 : 32;
	/* 0x006c */
	etpu_if_uint32 : 32;
	/* 0x0070 */
	etpu_if_uint32 : 32;
	/* 0x0074 */
	etpu_if_uint32 : 32;
	/* 0x0078 */
	etpu_if_uint32 : 32;
	/* 0x007c */
	etpu_if_uint32 : 32;
	/* 0x0080 */
	etpu_if_uint32 : 32;
	/* 0x0084 */
	etpu_if_uint32 : 32;
	/* 0x0088 */
	etpu_if_uint32 : 32;
	/* 0x008c */
	etpu_if_uint32 : 32;
	/* 0x0090 */
	etpu_if_uint32 : 32;
	/* 0x0094 */
	etpu_if_uint32 : 32;
	/* 0x0098 */
	etpu_if_uint32 : 32;
	/* 0x009c */
	etpu_if_uint32 : 32;
	/* 0x00a0 */
	etpu_if_uint32 : 32;
	/* 0x00a4 */
	etpu_if_uint32 : 32;
	/* 0x00a8 */
	etpu_if_uint32 : 32;
	/* 0x00ac */
	etpu_if_uint32 : 32;
	/* 0x00b0 */
	etpu_if_uint32 : 32;
	/* 0x00b4 */
	etpu_if_uint32 : 32;
	/* 0x00b8 */
	etpu_if_uint32 : 32;
	/* 0x00bc */
	etpu_if_uint32 : 32;
	/* 0x00c0 */
	etpu_if_uint32 : 32;
	/* 0x00c4 */
	etpu_if_uint32 : 32;
	/* 0x00c8 */
	etpu_if_uint32 : 32;
	/* 0x00cc */
	etpu_if_uint32 : 32;
	/* 0x00d0 */
	etpu_if_uint32 : 32;
	/* 0x00d4 */
	etpu_if_uint32 : 32;
	/* 0x00d8 */
	etpu_if_uint32 : 32;
	/* 0x00dc */
	etpu_if_uint32 : 32;
	/* 0x00e0 */
	etpu_if_uint32 : 32;
	/* 0x00e4 */
	etpu_if_uint32 : 32;
	/* 0x00e8 */
	etpu_if_uint32 : 32;
	/* 0x00ec */
	etpu_if_uint32 : 32;
	/* 0x00f0 */
	etpu_if_uint32 : 32;
	/* 0x00f4 */
	etpu_if_uint32 : 32;
	/* 0x00f8 */
	etpu_if_uint32 : 32;
	/* 0x00fc */
	etpu_if_uint32 : 32;
	/* 0x0100 */
	etpu_if_uint32 : 32;
	/* 0x0104 */
	etpu_if_uint32 : 32;
	/* 0x0108 */
	etpu_if_uint32 : 32;
	/* 0x010c */
	etpu_if_uint32 : 32;
	/* 0x0110 */
	etpu_if_uint32 : 32;
	/* 0x0114 */
	etpu_if_uint32 : 32;
	/* 0x0118 */
	etpu_if_uint32 : 32;
	/* 0x011c */
	etpu_if_uint32 : 32;
	/* 0x0120 */
	etpu_if_uint32 : 32;
	/* 0x0124 */
	etpu_if_uint32 : 32;
	/* 0x0128 */
	etpu_if_uint32 : 32;
	/* 0x012c */
	etpu_if_uint32 : 32;
	/* 0x0130 */
	etpu_if_uint32 : 32;
	/* 0x0134 */
	etpu_if_uint32 : 32;
	/* 0x0138 */
	etpu_if_uint32 : 32;
	/* 0x013c */
	etpu_if_uint32 : 32;
	/* 0x0140 */
	etpu_if_uint32 : 32;
	/* 0x0144 */
	etpu_if_uint32 : 32;
	/* 0x0148 */
	etpu_if_uint32 : 32;
	/* 0x014c */
	etpu_if_uint32 : 32;
	/* 0x0150 */
	etpu_if_uint32 : 32;
	/* 0x0154 */
	etpu_if_uint32 : 32;
	/* 0x0158 */
	etpu_if_uint32 : 32;
	/* 0x015c */
	etpu_if_uint32 : 32;
	/* 0x0160 */
	etpu_if_uint32 : 32;
	/* 0x0164 */
	etpu_if_uint32 : 32;
	/* 0x0168 */
	etpu_if_uint32 : 32;
	/* 0x016c */
	etpu_if_uint32 : 32;
	/* 0x0170 */
	etpu_if_uint32 : 32;
	/* 0x0174 */
	etpu_if_uint32 : 32;
	/* 0x0178 */
	etpu_if_uint32 : 32;
	/* 0x017c */
	etpu_if_uint32 : 32;
	/* 0x0180 */
	etpu_if_uint32 : 32;
	/* 0x0184 */
	etpu_if_uint32 : 32;
	/* 0x0188 */
	etpu_if_uint32 : 32;
	/* 0x018c */
	etpu_if_uint32 : 32;
	/* 0x0190 */
	etpu_if_uint32 : 32;
	/* 0x0194 */
	etpu_if_uint32 : 32;
	/* 0x0198 */
	etpu_if_uint32 : 32;
	/* 0x019c */
	etpu_if_uint32 : 32;
} etpu_if_C_MS1553_CHANNEL_FRAME;
#define etpu_if_C_MS1553_CHANNEL_FRAME_EXPECTED_SIZE 416


/* data structure of all 24-bit MS1553 CHANNEL FRAME data (meant to be accessed via PSE mirror)*/
/* unnamed bit-fields are used to fill any gaps in the data map */
/* bitfield access generates read-modify-write code (non-coherent), */
/* so if this is an issue, access bitfields via their unit instead. */
/* NOTE: it is recommended that 24-bit data be accessed via the separate */
/* signed and unsigned PSE data structures.  Unsigned 24-bit reads must have */
/* the upper 8 bits of the resulting 32-bit word ANDed to 0. */
typedef struct
{
	/* 0x0000 */
	etpu_if_sint32				_firstBitDelineator;
	/* 0x0004 */
	etpu_if_sint32				_0P50_bits;
	/* 0x0008 */
	etpu_if_uint32				_txBuffer;
	/* 0x000c */
	etpu_if_sint32				_txBitCount;
	/* 0x0010 */
	etpu_if_sint32				_terminalAddress;
	/* 0x0014 */
	etpu_if_sint32				_1P25_bits;
	/* 0x0018 */
	etpu_if_sint32				_1P50_bits;
	/* 0x001c */
	etpu_if_sint32				_1P75_bits;
	/* 0x0020 */
	etpu_if_sint32				_2P25_bits;
	/* 0x0024 */
	etpu_if_sint32				_2P50_bits;
	/* 0x0028 */
	etpu_if_sint32				_18P75_bits;
	/* 0x002c */
	etpu_if_sint32				_LastEdgeOnA;
	/* 0x0030 */
	etpu_if_sint32				_LastEdgeOnB;
	/* 0x0034 */
	etpu_if_sint32				_synchState;
	/* 0x0038 */
	etpu_if_sint32				_isLastEdgeAValid;
	/* 0x003c */
	etpu_if_sint32				_isLastEdgeBValid;
	/* 0x0040 */
	etpu_if_sint32				_rxBuffer;
	/* 0x0044 */
	etpu_if_sint32				_rxBitCount;
	/* 0x0048 */
	etpu_if_sint32				_rxParityCheck;
	/* 0x004c */
	etpu_if_uint32				_rxBuf[32];
	/* 0x00cc */
	etpu_if_uint32				_rxBufPtr;
	/* 0x00d0 */
	etpu_if_uint32				_cmdWordBuffer;
	/* 0x00d4 */
	etpu_if_sint32				_rxDataWordCnt;
	/* 0x00d8 */
	etpu_if_sint32				_initIdleTimeout;
	/* 0x00dc */
	etpu_if_sint32				_rtStatusTimeout;
	/* 0x00e0 */
	etpu_if_sint32				_seekIdleTimeout;
	/* 0x00e4 */
	etpu_if_uint32				_cmdWord1;
	/* 0x00e8 */
	etpu_if_uint32				_cmdWord2;
	/* 0x00ec */
	etpu_if_uint32				_rxModeWord;
	/* 0x00f0 */
	etpu_if_uint32				_rxStatusWord1;
	/* 0x00f4 */
	etpu_if_uint32				_rxStatusWord2;
	/* 0x00f8 */
	etpu_if_uint32				_dataWordCnt;
	/* 0x00fc */
	etpu_if_uint32				_transmitWord;
	/* 0x0100 */
	etpu_if_uint32				_transmitNextWord;
	/* 0x0104 */
	etpu_if_uint32				_txNextWordPtr;
	/* 0x0108 */
	etpu_if_uint32				_txEndTimestamp;
	/* 0x010c */
	etpu_if_uint32				_txDelay;
	/* 0x0110 */
	etpu_if_uint32				_txModeWord;
	/* 0x0114 */
	etpu_if_uint32				_txStatusWord;
	/* 0x0118 */
	etpu_if_sint32				_txWordCnt;
	/* 0x011c */
	etpu_if_uint32				_txBuf[32];
	/* 0x019c */
	etpu_if_uint32				_txBufPtr;
} etpu_if_C_MS1553_CHANNEL_FRAME_PSE;
#define etpu_if_C_MS1553_CHANNEL_FRAME_PSE_EXPECTED_SIZE 416


/* data structure of all signed 24-bit MS1553 CHANNEL FRAME data (meant to be accessed via PSE mirror)*/
/* unnamed bit-fields are used to fill any gaps in the data map */
/* bitfield access generates read-modify-write code (non-coherent), */
/* so if this is an issue, access bitfields via their unit instead. */
typedef struct
{
	/* 0x0000 */
	etpu_if_sint32				_firstBitDelineator;
	/* 0x0004 */
	etpu_if_sint32				_0P50_bits;
	/* 0x0008 */
	etpu_if_uint32 : 32;
	/* 0x000c */
	etpu_if_sint32				_txBitCount;
	/* 0x0010 */
	etpu_if_sint32				_terminalAddress;
	/* 0x0014 */
	etpu_if_sint32				_1P25_bits;
	/* 0x0018 */
	etpu_if_sint32				_1P50_bits;
	/* 0x001c */
	etpu_if_sint32				_1P75_bits;
	/* 0x0020 */
	etpu_if_sint32				_2P25_bits;
	/* 0x0024 */
	etpu_if_sint32				_2P50_bits;
	/* 0x0028 */
	etpu_if_sint32				_18P75_bits;
	/* 0x002c */
	etpu_if_sint32				_LastEdgeOnA;
	/* 0x0030 */
	etpu_if_sint32				_LastEdgeOnB;
	/* 0x0034 */
	etpu_if_sint32				_synchState;
	/* 0x0038 */
	etpu_if_sint32				_isLastEdgeAValid;
	/* 0x003c */
	etpu_if_sint32				_isLastEdgeBValid;
	/* 0x0040 */
	etpu_if_sint32				_rxBuffer;
	/* 0x0044 */
	etpu_if_sint32				_rxBitCount;
	/* 0x0048 */
	etpu_if_sint32				_rxParityCheck;
	/* 0x004c */
	etpu_if_uint32 : 32;
	/* 0x0050 */
	etpu_if_uint32 : 32;
	/* 0x0054 */
	etpu_if_uint32 : 32;
	/* 0x0058 */
	etpu_if_uint32 : 32;
	/* 0x005c */
	etpu_if_uint32 : 32;
	/* 0x0060 */
	etpu_if_uint32 : 32;
	/* 0x0064 */
	etpu_if_uint32 : 32;
	/* 0x0068 */
	etpu_if_uint32 : 32;
	/* 0x006c */
	etpu_if_uint32 : 32;
	/* 0x0070 */
	etpu_if_uint32 : 32;
	/* 0x0074 */
	etpu_if_uint32 : 32;
	/* 0x0078 */
	etpu_if_uint32 : 32;
	/* 0x007c */
	etpu_if_uint32 : 32;
	/* 0x0080 */
	etpu_if_uint32 : 32;
	/* 0x0084 */
	etpu_if_uint32 : 32;
	/* 0x0088 */
	etpu_if_uint32 : 32;
	/* 0x008c */
	etpu_if_uint32 : 32;
	/* 0x0090 */
	etpu_if_uint32 : 32;
	/* 0x0094 */
	etpu_if_uint32 : 32;
	/* 0x0098 */
	etpu_if_uint32 : 32;
	/* 0x009c */
	etpu_if_uint32 : 32;
	/* 0x00a0 */
	etpu_if_uint32 : 32;
	/* 0x00a4 */
	etpu_if_uint32 : 32;
	/* 0x00a8 */
	etpu_if_uint32 : 32;
	/* 0x00ac */
	etpu_if_uint32 : 32;
	/* 0x00b0 */
	etpu_if_uint32 : 32;
	/* 0x00b4 */
	etpu_if_uint32 : 32;
	/* 0x00b8 */
	etpu_if_uint32 : 32;
	/* 0x00bc */
	etpu_if_uint32 : 32;
	/* 0x00c0 */
	etpu_if_uint32 : 32;
	/* 0x00c4 */
	etpu_if_uint32 : 32;
	/* 0x00c8 */
	etpu_if_uint32 : 32;
	/* 0x00cc */
	etpu_if_uint32 : 32;
	/* 0x00d0 */
	etpu_if_uint32 : 32;
	/* 0x00d4 */
	etpu_if_sint32				_rxDataWordCnt;
	/* 0x00d8 */
	etpu_if_sint32				_initIdleTimeout;
	/* 0x00dc */
	etpu_if_sint32				_rtStatusTimeout;
	/* 0x00e0 */
	etpu_if_sint32				_seekIdleTimeout;
	/* 0x00e4 */
	etpu_if_uint32 : 32;
	/* 0x00e8 */
	etpu_if_uint32 : 32;
	/* 0x00ec */
	etpu_if_uint32 : 32;
	/* 0x00f0 */
	etpu_if_uint32 : 32;
	/* 0x00f4 */
	etpu_if_uint32 : 32;
	/* 0x00f8 */
	etpu_if_uint32 : 32;
	/* 0x00fc */
	etpu_if_uint32 : 32;
	/* 0x0100 */
	etpu_if_uint32 : 32;
	/* 0x0104 */
	etpu_if_uint32 : 32;
	/* 0x0108 */
	etpu_if_uint32 : 32;
	/* 0x010c */
	etpu_if_uint32 : 32;
	/* 0x0110 */
	etpu_if_uint32 : 32;
	/* 0x0114 */
	etpu_if_uint32 : 32;
	/* 0x0118 */
	etpu_if_sint32				_txWordCnt;
	/* 0x011c */
	etpu_if_uint32 : 32;
	/* 0x0120 */
	etpu_if_uint32 : 32;
	/* 0x0124 */
	etpu_if_uint32 : 32;
	/* 0x0128 */
	etpu_if_uint32 : 32;
	/* 0x012c */
	etpu_if_uint32 : 32;
	/* 0x0130 */
	etpu_if_uint32 : 32;
	/* 0x0134 */
	etpu_if_uint32 : 32;
	/* 0x0138 */
	etpu_if_uint32 : 32;
	/* 0x013c */
	etpu_if_uint32 : 32;
	/* 0x0140 */
	etpu_if_uint32 : 32;
	/* 0x0144 */
	etpu_if_uint32 : 32;
	/* 0x0148 */
	etpu_if_uint32 : 32;
	/* 0x014c */
	etpu_if_uint32 : 32;
	/* 0x0150 */
	etpu_if_uint32 : 32;
	/* 0x0154 */
	etpu_if_uint32 : 32;
	/* 0x0158 */
	etpu_if_uint32 : 32;
	/* 0x015c */
	etpu_if_uint32 : 32;
	/* 0x0160 */
	etpu_if_uint32 : 32;
	/* 0x0164 */
	etpu_if_uint32 : 32;
	/* 0x0168 */
	etpu_if_uint32 : 32;
	/* 0x016c */
	etpu_if_uint32 : 32;
	/* 0x0170 */
	etpu_if_uint32 : 32;
	/* 0x0174 */
	etpu_if_uint32 : 32;
	/* 0x0178 */
	etpu_if_uint32 : 32;
	/* 0x017c */
	etpu_if_uint32 : 32;
	/* 0x0180 */
	etpu_if_uint32 : 32;
	/* 0x0184 */
	etpu_if_uint32 : 32;
	/* 0x0188 */
	etpu_if_uint32 : 32;
	/* 0x018c */
	etpu_if_uint32 : 32;
	/* 0x0190 */
	etpu_if_uint32 : 32;
	/* 0x0194 */
	etpu_if_uint32 : 32;
	/* 0x0198 */
	etpu_if_uint32 : 32;
	/* 0x019c */
	etpu_if_uint32 : 32;
} etpu_if_C_MS1553_CHANNEL_FRAME_signedPSE;
#define etpu_if_C_MS1553_CHANNEL_FRAME_signedPSE_EXPECTED_SIZE 416


/* data structure of all unsigned 24-bit MS1553 CHANNEL FRAME data (meant to be accessed via PSE mirror)*/
/* unnamed bit-fields are used to fill any gaps in the data map */
/* bitfield access generates read-modify-write code (non-coherent), */
/* so if this is an issue, access bitfields via their unit instead. */
/* NOTE: when an unsigned 24-bit parameter is read via the PSE (as an */
/* unsigned 32-bit integer), the upper 8 bits must be ANDed off to undo */
/* any potential sign extension. */
typedef struct
{
	/* 0x0000 */
	etpu_if_uint32 : 32;
	/* 0x0004 */
	etpu_if_uint32 : 32;
	/* 0x0008 */
	etpu_if_uint32				_txBuffer;
	/* 0x000c */
	etpu_if_uint32 : 32;
	/* 0x0010 */
	etpu_if_uint32 : 32;
	/* 0x0014 */
	etpu_if_uint32 : 32;
	/* 0x0018 */
	etpu_if_uint32 : 32;
	/* 0x001c */
	etpu_if_uint32 : 32;
	/* 0x0020 */
	etpu_if_uint32 : 32;
	/* 0x0024 */
	etpu_if_uint32 : 32;
	/* 0x0028 */
	etpu_if_uint32 : 32;
	/* 0x002c */
	etpu_if_uint32 : 32;
	/* 0x0030 */
	etpu_if_uint32 : 32;
	/* 0x0034 */
	etpu_if_uint32 : 32;
	/* 0x0038 */
	etpu_if_uint32 : 32;
	/* 0x003c */
	etpu_if_uint32 : 32;
	/* 0x0040 */
	etpu_if_uint32 : 32;
	/* 0x0044 */
	etpu_if_uint32 : 32;
	/* 0x0048 */
	etpu_if_uint32 : 32;
	/* 0x004c */
	etpu_if_uint32				_rxBuf[32];
	/* 0x00cc */
	etpu_if_uint32				_rxBufPtr;
	/* 0x00d0 */
	etpu_if_uint32				_cmdWordBuffer;
	/* 0x00d4 */
	etpu_if_uint32 : 32;
	/* 0x00d8 */
	etpu_if_uint32 : 32;
	/* 0x00dc */
	etpu_if_uint32 : 32;
	/* 0x00e0 */
	etpu_if_uint32 : 32;
	/* 0x00e4 */
	etpu_if_uint32				_cmdWord1;
	/* 0x00e8 */
	etpu_if_uint32				_cmdWord2;
	/* 0x00ec */
	etpu_if_uint32				_rxModeWord;
	/* 0x00f0 */
	etpu_if_uint32				_rxStatusWord1;
	/* 0x00f4 */
	etpu_if_uint32				_rxStatusWord2;
	/* 0x00f8 */
	etpu_if_uint32				_dataWordCnt;
	/* 0x00fc */
	etpu_if_uint32				_transmitWord;
	/* 0x0100 */
	etpu_if_uint32				_transmitNextWord;
	/* 0x0104 */
	etpu_if_uint32				_txNextWordPtr;
	/* 0x0108 */
	etpu_if_uint32				_txEndTimestamp;
	/* 0x010c */
	etpu_if_uint32				_txDelay;
	/* 0x0110 */
	etpu_if_uint32				_txModeWord;
	/* 0x0114 */
	etpu_if_uint32				_txStatusWord;
	/* 0x0118 */
	etpu_if_uint32 : 32;
	/* 0x011c */
	etpu_if_uint32				_txBuf[32];
	/* 0x019c */
	etpu_if_uint32				_txBufPtr;
} etpu_if_C_MS1553_CHANNEL_FRAME_unsignedPSE;
#define etpu_if_C_MS1553_CHANNEL_FRAME_unsignedPSE_EXPECTED_SIZE 416


#endif /* __etpu_c_set_struct_H */
