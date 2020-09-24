/* main.c
 *
 * This is the entry point for the system.  System init
 * is performed, then the main app is kicked off.
 */

#include "isrLib.h"
#include "scriptLib.h"

#include "etpu_init.h"
#include "etpu_util_ext.h"

#include "etpu_ms1553.h"
#include "etpu_ms1553_rt.h"
#include "etpu_ms1553_bc.h"
#include "etpu_ms1553_isr.h"

// eTPU configuration 

#define MT_RX_CHAN (8 + 64)

#define RT_RX_CHAN (10 + 64)
#define RT_TX_CHAN (12 + 64)

#define BC_RX_CHAN 10
#define BC_TX_CHAN 12


// test facilitation variables/data

#define INVALID_WORD 0xBAD

uint32_t g_test_complete = 0;

uint32_t g_test_number;
uint32_t g_message_complete;
uint32_t g_mt_interrupt_active;
uint32_t g_rt_interrupt_active;
uint32_t g_bc_interrupt_active;

uint32_t g_mt_command_isr_cnt;
uint32_t g_mt_mode_data_isr_cnt;
uint32_t g_mt_data_isr_cnt;
uint32_t g_mt_status_isr_cnt;
uint32_t g_mt_message_isr_cnt;
uint32_t g_mt_tx_inhibited_isr_cnt;
uint32_t g_mt_error_isr_cnt;
uint32_t g_rt_command_isr_cnt;
uint32_t g_rt_mode_data_isr_cnt;
uint32_t g_rt_data_isr_cnt;
uint32_t g_rt_status_isr_cnt;
uint32_t g_rt_message_isr_cnt;
uint32_t g_rt_tx_inhibited_isr_cnt;
uint32_t g_rt_error_isr_cnt;
uint32_t g_bc_command_isr_cnt;
uint32_t g_bc_mode_data_isr_cnt;
uint32_t g_bc_data_isr_cnt;
uint32_t g_bc_status_isr_cnt;
uint32_t g_bc_message_isr_cnt;
uint32_t g_bc_tx_inhibited_isr_cnt;
volatile uint32_t g_bc_idle_detected_isr_cnt;
uint32_t g_bc_bus_busy_isr_cnt;
uint32_t g_bc_error_isr_cnt;

uint16_t g_mt_data[32];
uint16_t g_rt_data[32];
uint16_t g_bc_data[32];

struct test_result
{
    uint32_t command_isr_cnt;
    uint32_t mode_data_isr_cnt;
    uint32_t data_isr_cnt;
    uint32_t status_isr_cnt;
    uint32_t message_isr_cnt;
    uint32_t tx_inhibited_isr_cnt;
    uint32_t error_isr_cnt;
    ms1553_instance_state_t state;
    ms1553_instance_message_status_t status;
    uint16_t rx_data[8];
    // tx
    uint16_t tx_status_word;
    uint16_t tx_mode_data_word;
    uint16_t tx_data[8];
};
struct test_result g_mt_test_results[32] =
{
    { 0, 0, 0, 0, 0, 0, 0,
      { COMMAND_WORD_VALID,                        BC_TO_RT_XFR,                NO_ERROR, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // note : 0 element is not used
      
    { 1, 0, 1, 0, 1, 0, 0,
      { MESSAGE_STATUS_VALID | MESSAGE_COMPLETE,   BC_TO_RT_XFR,                NO_ERROR, },
      { 0x2223, INVALID_WORD, 0x2000, INVALID_WORD, INVALID_WORD, },
      { 0x815f, 0x5663, 0x64f9, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 1
      
    { 1, 0, 0, 1, 1, 0, 0,
      { MESSAGE_DATA_VALID | MESSAGE_COMPLETE,     RT_TO_BC_XFR,                NO_ERROR, },
      { 0x2623, INVALID_WORD, 0x2000, INVALID_WORD, INVALID_WORD, },
      { 0x7B5F, 0x25AF, 0x39A5, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 2
      
    { 1, 0, 0, 1, 1, 0, 0,
      { MESSAGE_DATA_VALID | MESSAGE_COMPLETE,     RT_TO_BC_XFR,                NO_ERROR, },
      { 0x2624, INVALID_WORD, 0x2000, INVALID_WORD, INVALID_WORD, },
      { 0x7B5F, 0x25AF, 0x39A5, 0x25AF, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 3
      
    { 1, 0, 0, 1, 1, 0, 0,
      { MESSAGE_DATA_VALID | MESSAGE_COMPLETE,     RT_TO_BC_XFR,                NO_ERROR, },
      { 0x2621, INVALID_WORD, 0x2000, INVALID_WORD, INVALID_WORD, },
      { 0x3333, 0x25AF, 0x39A5, 0x25AF, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 4
      
    { 1, 0, 1, 1, 1, 0, 0,
      { MESSAGE_STATUS_VALID | MESSAGE_COMPLETE,   RT_TO_RT_XFR,                NO_ERROR, },
      { 0x2221, 0x3621, 0x3000, 0x2000, INVALID_WORD, },
      { 0x1111, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 5
      
    { 1, 0, 0, 0, 1, 0, 0,
      { MESSAGE_DATA_VALID | MESSAGE_COMPLETE,     BC_TO_RT_BROADCAST_XFR,      NO_ERROR, },
      { 0xFA24, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { 0x815f, 0x5663, 0x64f9, 0x9CAF, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 6
      
    { 1, 0, 0, 1, 1, 0, 0,
      { MESSAGE_DATA_VALID | MESSAGE_COMPLETE,     RT_TO_RT_BROADCAST_XFR,      NO_ERROR, },
      { 0xFA21, 0x3621, 0x3000, INVALID_WORD, INVALID_WORD, },
      { 0x1111, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 7
      
    { 1, 0, 0, 0, 1, 0, 0,
      { MESSAGE_STATUS_VALID | MESSAGE_COMPLETE,   MODE_XMT_WITHOUT_DATA,       NO_ERROR, },
      { 0x27E2, INVALID_WORD, 0x2000, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 8
      
    { 1, 0, 0, 1, 1, 0, 0,
      { MODE_DATA_VALID | MESSAGE_COMPLETE,        MODE_XMT_WITH_DATA,          NO_ERROR, },
      { 0x27F2, INVALID_WORD, 0x2000, INVALID_WORD, 0x815F, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 9
      
    { 1, 1, 0, 0, 1, 0, 0,
      { MESSAGE_STATUS_VALID | MESSAGE_COMPLETE,   MODE_RCV_WITH_DATA,          NO_ERROR, },
      { 0x23F2, INVALID_WORD, 0x2000, INVALID_WORD, 0x815F, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 10
      
    { 0, 0, 0, 0, 1, 0, 0,
      { COMMAND_WORD_VALID | MESSAGE_COMPLETE,     MODE_BROADCAST_WITHOUT_DATA, NO_ERROR, },
      { 0xFFE2, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 11
      
    { 1, 0, 0, 0, 1, 0, 0,
      { MODE_DATA_VALID | MESSAGE_COMPLETE,        MODE_BROADCAST_WITH_DATA,    NO_ERROR, },
      { 0xFBF2, INVALID_WORD, INVALID_WORD, INVALID_WORD, 0x22E0, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 12
      
    { 1, 0, 0, 0, 1, 0, 0,
      { MESSAGE_STATUS_VALID | MESSAGE_COMPLETE,   MODE_XMT_WITHOUT_DATA,       NO_ERROR, },
      { 0xC409, INVALID_WORD, 0xC000, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 13
      
    { 1, 0, 0, 0, 1, 0, 0,
      { MESSAGE_STATUS_VALID | MESSAGE_COMPLETE,   MODE_XMT_WITHOUT_DATA,       NO_ERROR, },
      { 0x27E2, INVALID_WORD, 0x2000, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 14
      
    { 1, 0, 0, 1, 0, 0, 1,
      { MESSAGE_ERROR,                             RT_TO_BC_XFR,                PARITY_ERROR, },
      { 0x3621, INVALID_WORD, 0x3000, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 15
      
    { 1, 0, 0, 1, 0, 0, 1,
      { MESSAGE_ERROR,                             RT_TO_BC_XFR,                TOO_FEW_DATA_WORDS_ERROR, },
      { 0x3621, INVALID_WORD, 0x3000, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 16
      
    { 0, 0, 0, 0, 0, 0, 0,
      { MESSAGE_ERROR,                             0,                           NO_ERROR, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 17
};
struct test_result g_rt_test_results[32] =
{
    { 0, 0, 0, 0, 0, 0, 0,
      { COMMAND_WORD_VALID,                        BC_TO_RT_XFR,                NO_ERROR, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      INVALID_WORD,
      INVALID_WORD,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // note : 0 element is not used
      
    { 1, 0, 1, 0, 1, 0, 0,
      { MESSAGE_COMPLETE,                          BC_TO_RT_XFR,                NO_ERROR, },
      { 0x2223, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { 0x815f, 0x5663, 0x64f9, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      0x2000,
      INVALID_WORD,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 1
      
    { 1, 0, 0, 0, 1, 0, 0,
      { MESSAGE_COMPLETE,                          RT_TO_BC_XFR,                NO_ERROR, },
      { 0x2623, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      0x2000,
      INVALID_WORD,
      { 0x7B5F, 0x25AF, 0x39A5, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 2
      
    { 1, 0, 0, 0, 1, 0, 0,
      { MESSAGE_COMPLETE,                          RT_TO_BC_XFR,                NO_ERROR, },
      { 0x2624, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      0x2000,
      INVALID_WORD,
      { 0x7B5F, 0x25AF, 0x39A5, 0x25AF, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 3
      
    { 1, 0, 0, 0, 1, 0, 0,
      { MESSAGE_COMPLETE,                          RT_TO_BC_XFR,                NO_ERROR, },
      { 0x2621, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      0x2000,
      INVALID_WORD,
      { 0x3333, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 4
      
    { 1, 0, 1, 0, 1, 0, 0,
      { MESSAGE_COMPLETE,                          RT_TO_RT_XFR,                NO_ERROR, },
      { 0x2221, 0x3621, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { 0x1111, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      0x2000,
      INVALID_WORD,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 5
      
    { 1, 0, 0, 0, 1, 0, 0,
      { MESSAGE_DATA_VALID | MESSAGE_COMPLETE,     BC_TO_RT_BROADCAST_XFR,      NO_ERROR, },
      { 0xFA24, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { 0x815f, 0x5663, 0x64f9, 0x9CAF, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      INVALID_WORD,
      INVALID_WORD,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 6
      
    { 1, 0, 0, 0, 1, 0, 0,
      { MESSAGE_DATA_VALID | MESSAGE_COMPLETE,     RT_TO_RT_BROADCAST_XFR,      NO_ERROR, },
      { 0xFA21, 0x3621, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { 0x1111, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      INVALID_WORD,
      INVALID_WORD,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 7
      
    { 1, 0, 0, 0, 1, 0, 0,
      { MESSAGE_COMPLETE,                          MODE_XMT_WITHOUT_DATA,       NO_ERROR, },
      { 0x27E2, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      0x2000,
      INVALID_WORD,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 8
      
    { 1, 0, 0, 0, 1, 0, 0,
      { MESSAGE_COMPLETE,                          MODE_XMT_WITH_DATA,          NO_ERROR, },
      { 0x27F2, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      0x2000,
      0x815F,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 9
      
    { 1, 1, 0, 0, 1, 0, 0,
      { MESSAGE_COMPLETE,                          MODE_RCV_WITH_DATA,          NO_ERROR, },
      { 0x23F2, INVALID_WORD, INVALID_WORD, INVALID_WORD, 0x815F, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      0x2000,
      INVALID_WORD,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 10
      
    { 0, 0, 0, 0, 1, 0, 0,
      {  COMMAND_WORD_VALID | MESSAGE_COMPLETE,    MODE_BROADCAST_WITHOUT_DATA, NO_ERROR, },
      { 0xFFE2, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      INVALID_WORD,
      INVALID_WORD,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 11
      
    { 1, 0, 0, 0, 1, 0, 0,
      { MODE_DATA_VALID | MESSAGE_COMPLETE,        MODE_BROADCAST_WITH_DATA,    NO_ERROR, },
      { 0xFBF2, INVALID_WORD, INVALID_WORD, INVALID_WORD, 0x22E0, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      INVALID_WORD,
      INVALID_WORD,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 12
      
    { 0, 0, 0, 0, 0, 0, 0,
      { MODE_DATA_VALID | MESSAGE_COMPLETE,        MODE_BROADCAST_WITH_DATA,    NO_ERROR, },
      { 0xFBF2, INVALID_WORD, INVALID_WORD, INVALID_WORD, 0x22E0, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      INVALID_WORD,
      INVALID_WORD,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 13
      
    { 1, 0, 0, 0, 1, 0, 0,
      { MESSAGE_COMPLETE,                          MODE_XMT_WITHOUT_DATA,       NO_ERROR, },
      { 0x27E2, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      0x2000,
      INVALID_WORD,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 14
      
    { 0, 0, 0, 0, 0, 0, 1,
      { MESSAGE_ERROR,                             RT_TO_BC_XFR,                PARITY_ERROR, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      INVALID_WORD,
      INVALID_WORD,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 15
      
    { 0, 0, 0, 0, 0, 0, 1,
      { MESSAGE_ERROR,                             RT_TO_BC_XFR,                TOO_FEW_DATA_WORDS_ERROR, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      INVALID_WORD,
      INVALID_WORD,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 16
      
    { 0, 0, 0, 0, 0, 0, 0,
      { MESSAGE_ERROR,                             0,                           NO_ERROR, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      INVALID_WORD,
      INVALID_WORD,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 17
};
struct test_result g_bc_test_results[32] =
{
    { 0, 0, 0, 0, 0, 0, 0,
      { COMMAND_WORD_VALID,                        BC_TO_RT_XFR,                NO_ERROR, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // note : 0 element is not used
      
    { 0, 0, 0, 0, 1, 0, 0,
      { MESSAGE_STATUS_VALID | MESSAGE_COMPLETE,   BC_TO_RT_XFR,                NO_ERROR, },
      { 0x2223, INVALID_WORD, 0x2000, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 1
      
    { 0, 0, 0, 1, 1, 0, 0,
      { MESSAGE_DATA_VALID | MESSAGE_COMPLETE,     RT_TO_BC_XFR,                NO_ERROR, },
      { 0x2623, INVALID_WORD, 0x2000, INVALID_WORD, INVALID_WORD, },
      { 0x7B5F, 0x25AF, 0x39A5, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 2
      
    { 0, 0, 0, 1, 1, 0, 0,
      { MESSAGE_DATA_VALID | MESSAGE_COMPLETE,     RT_TO_BC_XFR,                NO_ERROR, },
      { 0x2624, INVALID_WORD, 0x2000, INVALID_WORD, INVALID_WORD, },
      { 0x7B5F, 0x25AF, 0x39A5, 0x25AF, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 3
      
    { 0, 0, 0, 1, 1, 0, 0,
      { MESSAGE_DATA_VALID | MESSAGE_COMPLETE,     RT_TO_BC_XFR,                NO_ERROR, },
      { 0x2621, INVALID_WORD, 0x2000, INVALID_WORD, INVALID_WORD, },
      { 0x3333, 0x25AF, 0x39A5, 0x25AF, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 4
      
    { 0, 0, 1, 1, 1, 0, 0,
      { MESSAGE_STATUS_VALID | MESSAGE_COMPLETE,   RT_TO_RT_XFR,                NO_ERROR, },
      { 0x2221, 0x3621, 0x3000, 0x2000, INVALID_WORD, },
      { 0x1111, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 5
      
    { 0, 0, 0, 0, 1, 0, 0,
      { MESSAGE_COMPLETE,                          BC_TO_RT_BROADCAST_XFR,      NO_ERROR, },
      { 0xFA24, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 6
      
    { 0, 0, 0, 1, 1, 0, 0,
      { MESSAGE_DATA_VALID | MESSAGE_COMPLETE,     RT_TO_RT_BROADCAST_XFR,      NO_ERROR, },
      { 0xFA21, 0x3621, 0x3000, INVALID_WORD, INVALID_WORD, },
      { 0x1111, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 7  
          
    { 0, 0, 0, 0, 1, 0, 0,
      { MESSAGE_STATUS_VALID | MESSAGE_COMPLETE,   MODE_XMT_WITHOUT_DATA,       NO_ERROR, },
      { 0x27E2, INVALID_WORD, 0x2000, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 8
      
    { 0, 0, 0, 1, 1, 0, 0,
      { MODE_DATA_VALID | MESSAGE_COMPLETE,        MODE_XMT_WITH_DATA,          NO_ERROR, },
      { 0x27F2, INVALID_WORD, 0x2000, INVALID_WORD, 0x815F, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 9
      
    { 0, 0, 0, 0, 1, 0, 0,
      { MESSAGE_STATUS_VALID | MESSAGE_COMPLETE,   MODE_RCV_WITH_DATA,          NO_ERROR, },
      { 0x23F2, INVALID_WORD, 0x2000, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 10
      
    { 0, 0, 0, 0, 1, 0, 0,
      { MESSAGE_COMPLETE,                          MODE_BROADCAST_WITHOUT_DATA, NO_ERROR, },
      { 0xFFE2, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 11
      
    { 0, 0, 0, 0, 1, 0, 0,
      { MESSAGE_COMPLETE,                          MODE_BROADCAST_WITH_DATA,    NO_ERROR, },
      { 0xFBF2, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 12   
        
    { 0, 0, 0, 0, 1, 0, 0,
      { MESSAGE_STATUS_VALID | MESSAGE_COMPLETE,   MODE_XMT_WITHOUT_DATA,       NO_ERROR, },
      { 0xC409, INVALID_WORD, 0xC000, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 13
      
    { 0, 0, 0, 0, 1, 0, 0,
      { MESSAGE_STATUS_VALID | MESSAGE_COMPLETE,   MODE_XMT_WITHOUT_DATA,       NO_ERROR, },
      { 0x27E2, INVALID_WORD, 0x2000, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 14
      
    { 0, 0, 0, 1, 0, 0, 1,
      { MESSAGE_ERROR,                             RT_TO_BC_XFR,                PARITY_ERROR, },
      { 0x3621, INVALID_WORD, 0x3000, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 15
      
    { 0, 0, 0, 1, 0, 0, 1,
      { MESSAGE_ERROR,                             RT_TO_BC_XFR,                TOO_FEW_DATA_WORDS_ERROR, },
      { 0x3621, INVALID_WORD, 0x3000, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 16
      
    { 0, 0, 0, 0, 0, 0, 0,
      { MESSAGE_ERROR,                             BC_TO_RT_XFR,                NO_ERROR, },
      { 0x2223, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 17
};

struct test_message
{
    uint8_t  message_type;
    uint16_t tx_cmdWord1;
    uint16_t tx_cmdWord2;
    uint8_t  word_count;
    uint16_t tx_data[8];
};
struct test_message g_bc_test_message[32] = 
{
    { BC_TO_RT_XFR,                 0x2223, INVALID_WORD,       3,
      { 0x815f, 0x5663, 0x64f9, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 1
    { RT_TO_BC_XFR,                 0x2623, INVALID_WORD,       0,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 2
    { RT_TO_BC_XFR,                 0x2624, INVALID_WORD,       0,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 3
    { RT_TO_BC_XFR,                 0x2621, INVALID_WORD,       0,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 4
    { RT_TO_RT_XFR,                 0x2221, 0x3621,             0,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 5
    { BC_TO_RT_BROADCAST_XFR,       0xfa24, INVALID_WORD,     4,
      { 0x815f, 0x5663, 0x64f9, 0x9caf, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 6
    { RT_TO_RT_BROADCAST_XFR,       0xfa21, 0x3621,           0,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 7
    { MODE_XMT_WITHOUT_DATA,        0x27e2, INVALID_WORD,       0,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 8
    { MODE_XMT_WITH_DATA,           0x27f2, INVALID_WORD,       0,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 9
    { MODE_RCV_WITH_DATA,           0x23f2, INVALID_WORD,       1,
      { 0x815f, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 10
    { MODE_BROADCAST_WITHOUT_DATA,  0xffe2, INVALID_WORD, 0,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 11
    { MODE_BROADCAST_WITH_DATA,     0xfbf2, INVALID_WORD,    1,
      { 0x22e0, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 12

    { MODE_XMT_WITHOUT_DATA,        0xc409, INVALID_WORD,       0,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 13
    { MODE_XMT_WITHOUT_DATA,        0x27e2, INVALID_WORD,       0,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 14
      
    { RT_TO_BC_XFR,                 0x3621, INVALID_WORD,       0,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 15
      
    { RT_TO_BC_XFR,                 0x3621, INVALID_WORD,       0,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 16
      
    { BC_TO_RT_XFR,                 0x2223, INVALID_WORD,       3,
      { 0x815f, 0x5663, 0x64f9, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 17 (shutdown, should be ignored)
};


void mt_command_handler(ms1553_instance_t* p_mt_instance);
void mt_mode_data_handler(ms1553_instance_t* p_mt_instance);
void mt_data_handler(ms1553_instance_t* p_mt_instance);
void mt_status_handler(ms1553_instance_t* p_mt_instance);
void mt_message_handler(ms1553_instance_t* p_mt_instance);
void mt_tx_inhibited_handler(ms1553_instance_t* p_mt_instance);
void mt_error_handler(ms1553_instance_t* p_mt_instance);

void rt_command_handler(ms1553_instance_t* p_rt_instance);
void rt_mode_data_handler(ms1553_instance_t* p_rt_instance);
void rt_data_handler(ms1553_instance_t* p_rt_instance);
void rt_status_handler(ms1553_instance_t* p_rt_instance);
void rt_message_handler(ms1553_instance_t* p_rt_instance);
void rt_tx_inhibited_handler(ms1553_instance_t* p_rt_instance);
void rt_error_handler(ms1553_instance_t* p_rt_instance);

void bc_command_handler(ms1553_instance_t* p_bc_instance);
void bc_mode_data_handler(ms1553_instance_t* p_bc_instance);
void bc_data_handler(ms1553_instance_t* p_bc_instance);
void bc_status_handler(ms1553_instance_t* p_bc_instance);
void bc_message_handler(ms1553_instance_t* p_bc_instance);
void bc_tx_inhibited_handler(ms1553_instance_t* p_bc_instance);
void bc_idle_detected_handler(ms1553_instance_t* p_bc_instance);
void bc_bus_busy_handler(ms1553_instance_t* p_bc_instance);
void bc_error_handler(ms1553_instance_t* p_bc_instance);



/* main application entry point */
/* w/ GNU, if we name this main, it requires linking with the libgcc.a
   run-time support.  This may be useful with C++ because this extra
   code initializes static C++ objects.  However, this C demo will
   skip it */
int user_main()
{
    volatile struct eTPU_struct* p_eTPU = eTPU_AB;
    ms1553_instance_t mt;
    ms1553_instance_t rt;
    ms1553_instance_t bc;
    uint32_t mt_chan_mask, rt_chan_mask, bc_chan_mask;
    uint32_t post_message_loop_counter;
    
    /* double speed of eTPU_B to support test config */
    etpu_b_tcr1_freq *= 2;
    etpu_b_tcr2_freq *= 2;

	/* initialize interrupt support */
	isrLibInit();

	/* eTPU init */
	if (etpu_init())
		return 1; // init failed

	/* start the eTPU timers */
	fs_timer_start_ext(EM_AB);

    /* initialize MT */
    mt.terminal_type = MS1553_TT_MONITOR_TERMINAL;
    mt.module = EM_AB;
    mt.rx_chan_base_num = MT_RX_CHAN;
    mt.tx_chan_base_num = 0xFF;
    mt.priority = FS_ETPU_PRIORITY_HIGH;
    mt.cpba = 0;
    mt.terminal_address = 0x1f; // accept all messages
    mt.interrupt_mask = 0xff;
    mt.p_cmd_word_handler = mt_command_handler;
    mt.p_mode_data_handler = mt_mode_data_handler;
    mt.p_message_data_handler = mt_data_handler;
    mt.p_status_word_handler = mt_status_handler;
    mt.p_message_handler = mt_message_handler;
    mt.p_transmit_inhibited_handler = mt_tx_inhibited_handler;
    mt.p_error_handler = mt_error_handler;
    mt.initial_idle_timeout = 4.5f;
    mt.rt_status_timeout = 9.0f;
    mt.transmit_delay = 4.0f;

    if (etpu_ms1553_init(&mt))
        return 1;
    mt_chan_mask = (3 << (MT_RX_CHAN & 0x1f));

    /* initialize RT */
    rt.terminal_type = MS1553_TT_REMOTE_TERMINAL;
    rt.module = EM_AB;
    rt.rx_chan_base_num = RT_RX_CHAN;
    rt.tx_chan_base_num = RT_TX_CHAN;
    rt.priority = FS_ETPU_PRIORITY_HIGH;
    rt.cpba = 0;
    rt.terminal_address = 4;
    rt.interrupt_mask = 0xff;
    rt.p_cmd_word_handler = rt_command_handler;
    rt.p_mode_data_handler = rt_mode_data_handler;
    rt.p_message_data_handler = rt_data_handler;
    rt.p_status_word_handler = rt_status_handler;
    rt.p_message_handler = rt_message_handler;
    rt.p_transmit_inhibited_handler = rt_tx_inhibited_handler;
    rt.p_error_handler = rt_error_handler;
    rt.initial_idle_timeout = 4.5f;
    rt.rt_status_timeout = 9.0f;
    rt.transmit_delay = 4.0f;
    
    if (etpu_ms1553_init(&rt))
        return 1;
    rt_chan_mask = (3 << (RT_RX_CHAN & 0x1f));

    /* initialize BC */
    bc.terminal_type = MS1553_TT_BUS_CONTROLLER;
    bc.module = EM_AB;
    bc.rx_chan_base_num = BC_RX_CHAN;
    bc.tx_chan_base_num = BC_TX_CHAN;
    bc.priority = FS_ETPU_PRIORITY_HIGH;
    bc.cpba = 0;
    bc.terminal_address = 0; // does not apply to BC
    bc.interrupt_mask = 0xff;
    bc.p_cmd_word_handler = bc_command_handler;
    bc.p_mode_data_handler = bc_mode_data_handler;
    bc.p_message_data_handler = bc_data_handler;
    bc.p_status_word_handler = bc_status_handler;
    bc.p_message_handler = bc_message_handler;
    bc.p_transmit_inhibited_handler = bc_tx_inhibited_handler;
    bc.p_idle_detected_handler = bc_idle_detected_handler;
    bc.p_bus_busy_handler = bc_bus_busy_handler;
    bc.p_error_handler = bc_error_handler;
    bc.initial_idle_timeout = 4.5f;
    bc.rt_status_timeout = 9.0f;
    bc.transmit_delay = 4.0f;
    
    if (etpu_ms1553_init(&bc))
        return 1;
    bc_chan_mask = (3 << (BC_RX_CHAN & 0x1f)) | (3 << (BC_TX_CHAN & 0x1f));
    
    wait_time(1000); // sync up with script
    
    // execute seek idle
    g_bc_idle_detected_isr_cnt = 0;
    etpu_ms1553_seek_idle(&bc, 10.0f);
    while (!g_bc_idle_detected_isr_cnt)
    {
        int i;
        uint32_t cisr_a, cier_a;
        uint32_t bc_cisr;
        uint32_t isr_test_mask;

        cier_a = p_eTPU->CIER_A.R;
        cisr_a = p_eTPU->CISR_A.R;
        bc_cisr = cisr_a & cier_a & bc_chan_mask;
        if (bc_cisr)
        {
            /* clear the to-be-handled interrupts immediately */
            p_eTPU->CISR_A.R = bc_cisr;
            isr_test_mask = 1;

            for (i = 0; i < 32; i++)
            {
                if ((bc_cisr & isr_test_mask) != 0)
                {
                    /* call handler */
                    g_bc_interrupt_active = 1;
                    /* note: if this was eTPU-B, we would need to add 64 to channel number */
                    etpu_ms1553_ISR(EM_AB, i);
                    g_bc_interrupt_active = 0;
                    bc_cisr &= (~isr_test_mask);
                    if (bc_cisr == 0) break;
                }
                isr_test_mask <<= 1;
            }
        }
    }
    

    while (g_test_number < 17)
    {
        wait_time(200); // each test take less than 200us
        etpu_ms1553_start_message(&bc, 
            g_bc_test_message[g_test_number].message_type, 
            g_bc_test_message[g_test_number].tx_cmdWord1, 
            g_bc_test_message[g_test_number].tx_cmdWord2, 
            g_bc_test_message[g_test_number].tx_data, 
            g_bc_test_message[g_test_number].word_count); 

        if (g_test_number == 0)
        {
            // test bus busy error
            g_bc_bus_busy_isr_cnt = 0;
            etpu_ms1553_start_message(&bc, 
                g_bc_test_message[g_test_number].message_type, 
                g_bc_test_message[g_test_number].tx_cmdWord1, 
                g_bc_test_message[g_test_number].tx_cmdWord2, 
                g_bc_test_message[g_test_number].tx_data, 
                g_bc_test_message[g_test_number].word_count); 
        }

        // inner test loop
        g_message_complete = 0;
        post_message_loop_counter = 5;
        if (g_test_number == 16)
        {
            // override values since no message should actually occur
            g_message_complete = 1;
            post_message_loop_counter = 100;
        }
        while (!g_message_complete || post_message_loop_counter-- != 0)
        {
            int i;
            uint32_t cisr_a, cisr_b, cier_a, cier_b;
            uint32_t mt_cisr, rt_cisr, bc_cisr;
            uint32_t isr_test_mask;

            cier_a = p_eTPU->CIER_A.R;
            cisr_a = p_eTPU->CISR_A.R;
            bc_cisr = cisr_a & cier_a & bc_chan_mask;
            if (bc_cisr)
            {
                /* clear the to-be-handled interrupts immediately */
                p_eTPU->CISR_A.R = bc_cisr;
                isr_test_mask = 1;

                for (i = 0; i < 32; i++)
                {
                    if ((bc_cisr & isr_test_mask) != 0)
                    {
                        /* call handler */
                        g_bc_interrupt_active = 1;
                        /* note: if this was eTPU-B, we would need to add 64 to channel number */
                        etpu_ms1553_ISR(EM_AB, i);
                        g_bc_interrupt_active = 0;
                        bc_cisr &= (~isr_test_mask);
                        if (bc_cisr == 0) break;
                    }
                    isr_test_mask <<= 1;
                }
            }

            cier_b = p_eTPU->CIER_B.R;
            cisr_b = p_eTPU->CISR_B.R;
            rt_cisr = cisr_b & cier_b & rt_chan_mask;
            if (rt_cisr)
            {
                /* clear the to-be-handled interrupts immediately */
                p_eTPU->CISR_B.R = rt_cisr;
                isr_test_mask = 1;

                for (i = 0; i < 32; i++)
                {
                    if ((rt_cisr & isr_test_mask) != 0)
                    {
                        /* call handler */
                        g_rt_interrupt_active = 1;
                        /* note: if this was eTPU-B, we would need to add 64 to channel number */
                        etpu_ms1553_ISR(EM_AB, i + 64);
                        g_rt_interrupt_active = 0;
                        rt_cisr &= (~isr_test_mask);
                        if (rt_cisr == 0) break;
                    }
                    isr_test_mask <<= 1;
                }
            }

            cier_b = p_eTPU->CIER_B.R;
            cisr_b = p_eTPU->CISR_B.R;
            mt_cisr = cisr_b & cier_b & mt_chan_mask;
            if (mt_cisr)
            {
                /* clear the to-be-handled interrupts immediately */
                p_eTPU->CISR_B.R = mt_cisr;
                isr_test_mask = 1;

                for (i = 0; i < 32; i++)
                {
                    if ((mt_cisr & isr_test_mask) != 0)
                    {
                        /* call handler */
                        g_mt_interrupt_active = 1;
                        /* note: if this was eTPU-B, we would need to add 64 to channel number */
                        etpu_ms1553_ISR(EM_AB, i + 64);
                        g_mt_interrupt_active = 0;
                        mt_cisr &= (~isr_test_mask);
                        if (mt_cisr == 0) break;
                    }
                    isr_test_mask <<= 1;
                }
            }
        }
        if (g_test_number == 0)
        {
            if (g_bc_bus_busy_isr_cnt != 1)
                print("error: bus busy interrupt did not occur");
        }
        g_test_number++;
        if (g_test_number == 17)
        {
            // since no interrupts expected, need to read state/status here
            etpu_ms1553_get_state(&mt);
            etpu_ms1553_get_message_status(&mt);
            etpu_ms1553_get_message_data(&mt, 8/*g_mt_status.cmdWord1&0x1f*/, g_mt_data);
            
            etpu_ms1553_get_state(&rt);
            etpu_ms1553_get_message_status(&rt);
            etpu_ms1553_get_message_data(&rt, 8/*g_mt_status.cmdWord1&0x1f*/, g_rt_data);

            etpu_ms1553_get_state(&bc);
            etpu_ms1553_get_message_status(&bc);
            etpu_ms1553_get_message_data(&bc, 8/*g_mt_status.cmdWord1&0x1f*/, g_bc_data);
        }
        
        // check listening MT
        if (g_mt_command_isr_cnt        != g_mt_test_results[g_test_number].command_isr_cnt ||
            g_mt_mode_data_isr_cnt      != g_mt_test_results[g_test_number].mode_data_isr_cnt ||
            g_mt_data_isr_cnt           != g_mt_test_results[g_test_number].data_isr_cnt ||
            g_mt_status_isr_cnt         != g_mt_test_results[g_test_number].status_isr_cnt ||
            g_mt_message_isr_cnt        != g_mt_test_results[g_test_number].message_isr_cnt ||
            g_mt_tx_inhibited_isr_cnt   != g_mt_test_results[g_test_number].tx_inhibited_isr_cnt ||
            g_mt_error_isr_cnt          != g_mt_test_results[g_test_number].error_isr_cnt )
            print("error: MT: unexpected ISR count");
        
        if (mt.state.message_state      != g_mt_test_results[g_test_number].state.message_state)
            print("error: MT: unexpected message interrupt status");

        if (mt.state.message_type       != g_mt_test_results[g_test_number].state.message_type )
            print("error: MT: unexpected message type");

        if (mt.state.error_status       != g_mt_test_results[g_test_number].state.error_status )
            print("error: MT: unexpected error status");

        if (mt.status.cmdWord1          != g_mt_test_results[g_test_number].status.cmdWord1 ||
            mt.status.cmdWord2          != g_mt_test_results[g_test_number].status.cmdWord2 ||
            mt.status.statusWord1       != g_mt_test_results[g_test_number].status.statusWord1 ||
            mt.status.statusWord2       != g_mt_test_results[g_test_number].status.statusWord2 ||
            mt.status.modeWord          != g_mt_test_results[g_test_number].status.modeWord )
            print("error: MT: unexpected message status");

        if (g_mt_data[0]                != g_mt_test_results[g_test_number].rx_data[0] ||
            g_mt_data[1]                != g_mt_test_results[g_test_number].rx_data[1] ||
            g_mt_data[2]                != g_mt_test_results[g_test_number].rx_data[2] ||
            g_mt_data[3]                != g_mt_test_results[g_test_number].rx_data[3] ||
            g_mt_data[4]                != g_mt_test_results[g_test_number].rx_data[4] ||
            g_mt_data[5]                != g_mt_test_results[g_test_number].rx_data[5] ||
            g_mt_data[6]                != g_mt_test_results[g_test_number].rx_data[6] ||
            g_mt_data[7]                != g_mt_test_results[g_test_number].rx_data[7] )
            print("error: MT: unexpected data values");

        // check RT
        if (g_rt_command_isr_cnt        != g_rt_test_results[g_test_number].command_isr_cnt ||
            g_rt_mode_data_isr_cnt      != g_rt_test_results[g_test_number].mode_data_isr_cnt ||
            g_rt_data_isr_cnt           != g_rt_test_results[g_test_number].data_isr_cnt ||
            g_rt_status_isr_cnt         != g_rt_test_results[g_test_number].status_isr_cnt ||
            g_rt_message_isr_cnt        != g_rt_test_results[g_test_number].message_isr_cnt ||
            g_rt_tx_inhibited_isr_cnt   != g_rt_test_results[g_test_number].tx_inhibited_isr_cnt ||
            g_rt_error_isr_cnt          != g_rt_test_results[g_test_number].error_isr_cnt )
            print("error: RT: unexpected ISR count");
        
        if (rt.state.message_state      != g_rt_test_results[g_test_number].state.message_state)
            print("error: RT: unexpected message interrupt status");

        if (rt.state.message_type       != g_rt_test_results[g_test_number].state.message_type )
            print("error: RT: unexpected message type");

        if (rt.state.error_status       != g_rt_test_results[g_test_number].state.error_status )
            print("error: RT: unexpected error status");

        if (rt.status.cmdWord1          != g_rt_test_results[g_test_number].status.cmdWord1 ||
            rt.status.cmdWord2          != g_rt_test_results[g_test_number].status.cmdWord2 ||
            rt.status.statusWord1       != g_rt_test_results[g_test_number].status.statusWord1 ||
            rt.status.statusWord2       != g_rt_test_results[g_test_number].status.statusWord2 ||
            rt.status.modeWord          != g_rt_test_results[g_test_number].status.modeWord )
            print("error: RT: unexpected message status");

        if (g_rt_data[0]                != g_rt_test_results[g_test_number].rx_data[0] ||
            g_rt_data[1]                != g_rt_test_results[g_test_number].rx_data[1] ||
            g_rt_data[2]                != g_rt_test_results[g_test_number].rx_data[2] ||
            g_rt_data[3]                != g_rt_test_results[g_test_number].rx_data[3] ||
            g_rt_data[4]                != g_rt_test_results[g_test_number].rx_data[4] ||
            g_rt_data[5]                != g_rt_test_results[g_test_number].rx_data[5] ||
            g_rt_data[6]                != g_rt_test_results[g_test_number].rx_data[6] ||
            g_rt_data[7]                != g_rt_test_results[g_test_number].rx_data[7] )
            print("error: RT: unexpected data values");

        // check BC
        if (g_bc_command_isr_cnt        != g_bc_test_results[g_test_number].command_isr_cnt ||
            g_bc_mode_data_isr_cnt      != g_bc_test_results[g_test_number].mode_data_isr_cnt ||
            g_bc_data_isr_cnt           != g_bc_test_results[g_test_number].data_isr_cnt ||
            g_bc_status_isr_cnt         != g_bc_test_results[g_test_number].status_isr_cnt ||
            g_bc_message_isr_cnt        != g_bc_test_results[g_test_number].message_isr_cnt ||
            g_bc_tx_inhibited_isr_cnt   != g_bc_test_results[g_test_number].tx_inhibited_isr_cnt ||
            g_bc_error_isr_cnt          != g_bc_test_results[g_test_number].error_isr_cnt )
            print("error: BC: unexpected ISR count");
        
        if (bc.state.message_state      != g_bc_test_results[g_test_number].state.message_state)
            print("error: BC: unexpected message interrupt status");

        if (bc.state.message_type       != g_bc_test_results[g_test_number].state.message_type )
            print("error: BC: unexpected message type");

        if (bc.state.error_status       != g_bc_test_results[g_test_number].state.error_status )
            print("error: BC: unexpected error status");

        if (bc.status.cmdWord1          != g_bc_test_results[g_test_number].status.cmdWord1 ||
            bc.status.cmdWord2          != g_bc_test_results[g_test_number].status.cmdWord2 ||
            bc.status.statusWord1       != g_bc_test_results[g_test_number].status.statusWord1 ||
            bc.status.statusWord2       != g_bc_test_results[g_test_number].status.statusWord2 ||
            bc.status.modeWord          != g_bc_test_results[g_test_number].status.modeWord )
            print("error: BC: unexpected message status");

        if (g_bc_data[0]                != g_bc_test_results[g_test_number].rx_data[0] ||
            g_bc_data[1]                != g_bc_test_results[g_test_number].rx_data[1] ||
            g_bc_data[2]                != g_bc_test_results[g_test_number].rx_data[2] ||
            g_bc_data[3]                != g_bc_test_results[g_test_number].rx_data[3] ||
            g_bc_data[4]                != g_bc_test_results[g_test_number].rx_data[4] ||
            g_bc_data[5]                != g_bc_test_results[g_test_number].rx_data[5] ||
            g_bc_data[6]                != g_bc_test_results[g_test_number].rx_data[6] ||
            g_bc_data[7]                != g_bc_test_results[g_test_number].rx_data[7] )
            print("error: BC: unexpected data values");
        
        // reset isr cnts
        g_mt_command_isr_cnt = 0;
        g_mt_mode_data_isr_cnt = 0;
        g_mt_data_isr_cnt = 0;
        g_mt_status_isr_cnt = 0;
        g_mt_message_isr_cnt = 0;
        g_mt_tx_inhibited_isr_cnt = 0;
        g_mt_error_isr_cnt = 0;
        g_rt_command_isr_cnt = 0;
        g_rt_mode_data_isr_cnt = 0;
        g_rt_data_isr_cnt = 0;
        g_rt_status_isr_cnt = 0;
        g_rt_message_isr_cnt = 0;
        g_rt_tx_inhibited_isr_cnt = 0;
        g_rt_error_isr_cnt = 0;
        g_bc_command_isr_cnt = 0;
        g_bc_mode_data_isr_cnt = 0;
        g_bc_data_isr_cnt = 0;
        g_bc_status_isr_cnt = 0;
        g_bc_message_isr_cnt = 0;
        g_bc_tx_inhibited_isr_cnt = 0;
        g_bc_idle_detected_isr_cnt = 0;
        g_bc_error_isr_cnt = 0;

        if (g_test_number == 16)
        {
            // shutdown the terminals
            etpu_ms1553_shutdown(&mt);
            etpu_ms1553_shutdown(&rt);
            etpu_ms1553_shutdown(&bc);
        }
    }
    
    g_test_complete = 1;
    while (1) ;

	return 0;
}

/* MT handlers */

void mt_message_handler(ms1553_instance_t* p_mt_instance)
{
    /* real code would store off or process the message in some way */
    /* this code will just test that the message was processed as expected */
    etpu_ms1553_get_message_status(p_mt_instance);
    // always read 8 words for now, for testing purposes
    etpu_ms1553_get_message_data(p_mt_instance, 8/*g_mt_status.cmdWord1&0x1f*/, g_mt_data);
    
    g_mt_message_isr_cnt++;
}
void mt_error_handler(ms1553_instance_t* p_mt_instance)
{
    /* get all the data for test purposes; actual error handler may just want to get the state, which contains the error code */
    etpu_ms1553_get_message_status(p_mt_instance);
    // always read 8 words for now, for testing purposes
    etpu_ms1553_get_message_data(p_mt_instance, 8/*g_mt_status.cmdWord1&0x1f*/, g_mt_data);

    g_mt_error_isr_cnt++;
}

/* these handlers just increment isr counters */
void mt_command_handler(ms1553_instance_t* p_mt_instance)
{
    g_mt_command_isr_cnt++;
}
void mt_mode_data_handler(ms1553_instance_t* p_mt_instance)
{
    g_mt_mode_data_isr_cnt++;
}
void mt_data_handler(ms1553_instance_t* p_mt_instance)
{
    g_mt_data_isr_cnt++;
}
void mt_status_handler(ms1553_instance_t* p_mt_instance)
{
    g_mt_status_isr_cnt++;
}
void mt_tx_inhibited_handler(ms1553_instance_t* p_mt_instance)
{
    g_mt_tx_inhibited_isr_cnt++;
}


/* RT handlers */

void rt_message_handler(ms1553_instance_t* p_rt_instance)
{
    /* real code would store off or process the message in some way */
    /* this code will just test that the message was processed as expected */
    etpu_ms1553_get_message_status(p_rt_instance);
    // always read 8 words for now, for testing purposes
    etpu_ms1553_get_message_data(p_rt_instance, 8/*g_mt_status.cmdWord1&0x1f*/, g_rt_data);
    
    g_rt_message_isr_cnt++;
}
void rt_error_handler(ms1553_instance_t* p_rt_instance)
{
    /* get all the data for test purposes; actual error handler may just want to look at the state, which contains the error code */
    etpu_ms1553_get_message_status(p_rt_instance);
    // always read 8 words for now, for testing purposes
    etpu_ms1553_get_message_data(p_rt_instance, 8/*g_mt_status.cmdWord1&0x1f*/, g_rt_data);

    g_rt_error_isr_cnt++;
}

void rt_command_handler(ms1553_instance_t* p_rt_instance)
{
    /* retrieve the status, just to get command words */
    etpu_ms1553_get_message_status(p_rt_instance);
    /* we now have message state which provides the info necessary to properly respond */
    /* this interrupt only happens if this RT is targeted (or message is broadcast */
    /* message types:
         BC_TO_RT_XFR                   - provide STATUS after MESSAGE_DATA interrupt
         RT_TO_BC_XFR                   - provide STATUS/DATA now
         RT_TO_RT_XFR                   - if transmitter, provide STATUS/DATA now
                                        - if receiver, provide STATUS after MESSAGE_DATA interrupt
         MODE_XMT_WITHOUT_DATA          - provide STATUS now
         MODE_XMT_WITH_DATA             - provide STATUS/MODE WORD now
         MODE_RCV_WITH_DATA             - can provide STATUS now, or after MODE_DATA interrupt (latter recommended)
         BC_TO_RT_BROADCAST_XFR         - no response
         RT_TO_RT_BROADCAST_XFR         - if transmitter, provide STATUS/DATA now
         MODE_BROADCAST_WITHOUT_DATA    - no response
         MODE_BROADCAST_WITH_DATA       - no response
    */
    if (p_rt_instance->state.message_type == RT_TO_BC_XFR ||
        ((p_rt_instance->state.message_type == RT_TO_RT_XFR || p_rt_instance->state.message_type == RT_TO_RT_BROADCAST_XFR) && 
         (p_rt_instance->status.cmdWord1 & 0xF800) == (p_rt_instance->terminal_address << 11)))
    {
        /* status and data response required now */
        etpu_ms1553_set_tx_status_word(p_rt_instance, g_rt_test_results[g_test_number+1].tx_status_word);
        etpu_ms1553_set_tx_data(p_rt_instance, p_rt_instance->status.cmdWord1 & 0x1F, g_rt_test_results[g_test_number+1].tx_data);
    }
    else if (p_rt_instance->state.message_type == MODE_XMT_WITHOUT_DATA )
    {
        /* status response required now */
        etpu_ms1553_set_tx_status_word(p_rt_instance, g_rt_test_results[g_test_number+1].tx_status_word);
    }
    else if (p_rt_instance->state.message_type == MODE_XMT_WITH_DATA )
    {
        /* status & mode data response required now */
        etpu_ms1553_set_tx_status_word(p_rt_instance, g_rt_test_results[g_test_number+1].tx_status_word);
        etpu_ms1553_set_tx_mode_word(p_rt_instance, g_rt_test_results[g_test_number+1].tx_mode_data_word);
    }

    g_rt_command_isr_cnt++;
}

void rt_mode_data_handler(ms1553_instance_t* p_rt_instance)
{
    if (p_rt_instance->state.message_type == MODE_RCV_WITH_DATA)
    {
        /* status response required now */
        etpu_ms1553_set_tx_status_word(p_rt_instance, g_rt_test_results[g_test_number+1].tx_status_word);
    }

    g_rt_mode_data_isr_cnt++;
}

void rt_data_handler(ms1553_instance_t* p_rt_instance)
{
    if (p_rt_instance->state.message_type == BC_TO_RT_XFR ||
        (p_rt_instance->state.message_type == RT_TO_RT_XFR && 
         (p_rt_instance->status.cmdWord2 & 0xF800) == (p_rt_instance->terminal_address << 11)))
    {
        /* status response required now */
        etpu_ms1553_set_tx_status_word(p_rt_instance, g_rt_test_results[g_test_number+1].tx_status_word);
    }

    g_rt_data_isr_cnt++;
}


/* these handlers just increment isr counters */
void rt_status_handler(ms1553_instance_t* p_rt_instance)
{
    g_rt_status_isr_cnt++;
}
void rt_tx_inhibited_handler(ms1553_instance_t* p_rt_instance)
{
    g_rt_tx_inhibited_isr_cnt++;
}


/* BC handlers */

void bc_message_handler(ms1553_instance_t* p_bc_instance)
{
    /* real code might prepare to send the next message */
    /* this code will just test that the message was processed as expected */
    etpu_ms1553_get_message_status(p_bc_instance);
    // always read 8 words for now, for testing purposes
    etpu_ms1553_get_message_data(p_bc_instance, 8, g_bc_data);
    
    g_message_complete = 1;
    
    g_bc_message_isr_cnt++;
}
void bc_error_handler(ms1553_instance_t* p_bc_instance)
{
    /* get all the data for test purposes; actual error handler may just want to get the state, which contains the error code */
    etpu_ms1553_get_message_status(p_bc_instance);
    // always read 8 words for now, for testing purposes
    etpu_ms1553_get_message_data(p_bc_instance, 8, g_bc_data);

    g_message_complete = 1;

    g_bc_error_isr_cnt++;
}

/* these handlers just increment isr counters */
void bc_command_handler(ms1553_instance_t* p_bc_instance)
{
    g_bc_command_isr_cnt++;
}
void bc_mode_data_handler(ms1553_instance_t* p_bc_instance)
{
    g_bc_mode_data_isr_cnt++;
}
void bc_data_handler(ms1553_instance_t* p_bc_instance)
{
    g_bc_data_isr_cnt++;
}
void bc_status_handler(ms1553_instance_t* p_bc_instance)
{
    g_bc_status_isr_cnt++;
}
void bc_idle_detected_handler(ms1553_instance_t* p_bc_instance)
{
    g_bc_idle_detected_isr_cnt++;
}
void bc_bus_busy_handler(ms1553_instance_t* p_bc_instance)
{
    g_bc_bus_busy_isr_cnt++;
}
void bc_tx_inhibited_handler(ms1553_instance_t* p_bc_instance)
{
    g_bc_tx_inhibited_isr_cnt++;
}


