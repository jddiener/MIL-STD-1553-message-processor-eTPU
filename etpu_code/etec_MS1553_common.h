/**************************************************************************
* FILE NAME: etec_MS1553_common.h   
* 
* DESCRIPTION: This header file contains definitions common to both eTPU code
* and host-side interface code.
* 
* 
*========================================================================
* REV      AUTHOR      DATE         DESCRIPTION OF CHANGE
* ---   -----------  -----------    ---------------------
* 1.0   Johnn Diener 2020-May-05    Initial release
*
**************************************************************************/

#ifndef __ETEC_MS1553_COMMON_H
#define __ETEC_MS1553_COMMON_H

// Host Service Requests
#define MS1553_RX_INIT_HSR      7
#define MS1553_TX_INIT_HSR      7
#define MS1553_RX_SHUTDOWN_HSR  2
#define MS1553_TX_SHUTDOWN_HSR  2
#define MS1553_BC_START_MESSAGE 1
#define MS1553_BC_SEEK_IDLE     1

// RX/TX buffer size
#define MS1553_BUFFER_DEPTH     32

// TX (data) inhibit flag
#define TX_INHIBIT_BITMASK      1
#define TX_INHIBIT_DISABLE      0
#define TX_INHIBIT_ENABLED      1

// Message Status (stage) (interrupt)
#define COMMAND_WORD_VALID                  0x01
#define MODE_DATA_VALID                     0x02
#define MESSAGE_DATA_VALID                  0x04
#define MESSAGE_STATUS_VALID                0x08
#define MESSAGE_COMPLETE                    0x10
#define MESSAGE_TRANSMIT_INHIBITED          0x20
#define BUS_IDLE_DETECTED                   0x40
#define MESSAGE_ERROR                       0x80

// Message Type
#define MESSAGE_TYPE_UNDETERMINED           0
#define BC_TO_RT_XFR                        1
#define RT_TO_BC_XFR                        2
#define RT_TO_RT_XFR                        3
#define MODE_XMT_WITHOUT_DATA               4
#define MODE_XMT_WITH_DATA                  5
#define MODE_RCV_WITH_DATA                  6
#define BC_TO_RT_BROADCAST_XFR              7
#define RT_TO_RT_BROADCAST_XFR              8
#define MODE_BROADCAST_WITHOUT_DATA         9
#define MODE_BROADCAST_WITH_DATA            10

// Message Fault Codes
#define NO_ERROR                            0x00
#define MISSING_BIT_ERROR                   0x80
#define PARITY_ERROR                        0x81
#define TOO_FEW_DATA_WORDS_ERROR            0x82
#define EXPECTED_IDLE_MISSING_ERROR         0x83
#define RT_DATA_WHEN_EXPECTED_STATUS_ERROR  0x84
#define RT_STATUS_WHEN_EXPECTED_DATA_ERROR  0x85
#define RT_STATUS_TIMEOUT_ERROR             0x86
#define MESSAGE_STARTS_WITH_DATA_ERROR      0x87
#define INVALID_MODE_COMMAND                0x88
#define EXPECTED_MODE_DATA_MISSING_ERROR    0x89
#define BC_INVALID_MESSAGE_TYPE_ERROR       0x8A
#define BC_BUS_BUSY_ERROR                   0x8B
// This message indicates that the software has gotten into
// an unexpected state (will never happen under normal operation)
#define INTERNAL_ERROR                      0x90

#endif  // __ETEC_MS1553_COMMON_H
