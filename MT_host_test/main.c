/* main.c
 *
 * This is the entry point for the system.  System init
 * is performed, then the main app is kicked off.
 */

#include "isrLib.h"
#include "scriptLib.h"

#include "etpu_init.h"
#include "etpu_util_ext.h"

#include "etpu_ms1553_mt.h"
#include "etpu_ms1553_isr.h"

// eTPU configuration 

#define MT_RX_CHAN (8 + 64)


// test facilitation variables/data

#define INVALID_WORD 0xBAD

uint32_t g_test_number;
uint32_t g_mt_interrupt_active;

uint32_t g_command_isr_cnt;
uint32_t g_mode_data_isr_cnt;
uint32_t g_data_isr_cnt;
uint32_t g_status_isr_cnt;
uint32_t g_message_isr_cnt;
uint32_t g_tx_inhibited_isr_cnt;
uint32_t g_error_isr_cnt;

uint16_t                            g_mt_data[32];

struct mt_test_result
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
};
struct mt_test_result g_mt_test_results[32] =
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
      { 0x7B5F, 0x25AF, 0x39A5, 0x25AF, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 4
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
    { 1, 0, 1, 0, 0, 0, 1,
      { MESSAGE_ERROR,                             BC_TO_RT_XFR,                PARITY_ERROR, },
      { 0x2224, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { 0x815F, 0x5663, 0x64F9, 0x64F9, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 15
    { 0, 0, 0, 0, 0, 0, 1,
      { MESSAGE_ERROR,                        0,                           TOO_FEW_DATA_WORDS_ERROR, },
      { 0x2225, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 16
};

void mt_command_handler(ms1553_instance_t* p_mt_instance);
void mt_mode_data_handler(ms1553_instance_t* p_mt_instance);
void mt_data_handler(ms1553_instance_t* p_mt_instance);
void mt_status_handler(ms1553_instance_t* p_mt_instance);
void mt_message_handler(ms1553_instance_t* p_mt_instance);
void mt_tx_inhibited_handler(ms1553_instance_t* p_mt_instance);
void mt_error_handler(ms1553_instance_t* p_mt_instance);



/* main application entry point */
/* w/ GNU, if we name this main, it requires linking with the libgcc.a
   run-time support.  This may be useful with C++ because this extra
   code initializes static C++ objects.  However, this C demo will
   skip it */
int user_main()
{
    volatile struct eTPU_struct* p_eTPU = eTPU_AB;
    ms1553_instance_t mt;
    uint32_t mt_chan_mask;
    uint32_t last_test_number = g_test_number;

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
    mt_chan_mask = (1 << (MT_RX_CHAN & 0x1f));

    while (1)
    {
        int i;
        uint32_t cisr, cier;
        uint32_t mt_cisr;

        cier = p_eTPU->CIER_B.R;
        cisr = p_eTPU->CISR_B.R;
        mt_cisr = cisr & cier & mt_chan_mask;

        if (mt_cisr)
        {
            /* clear the to-be-handled interrupts immediately */
            p_eTPU->CISR_B.R = mt_cisr;

            for (i = 0; i < 32; i++)
            {
                if ((mt_cisr & (1<<i)) != 0)
                {
                    /* call handler */
                    g_mt_interrupt_active = 1;
                    /* note: if this was eTPU-B, we would need to add 64 to channel number */
                    etpu_ms1553_ISR(i + 64);
                    g_mt_interrupt_active = 0;
                }
            }
        }
        
        if (g_test_number != last_test_number)
        {
            if (g_command_isr_cnt           != g_mt_test_results[g_test_number].command_isr_cnt ||
                g_mode_data_isr_cnt         != g_mt_test_results[g_test_number].mode_data_isr_cnt ||
                g_data_isr_cnt              != g_mt_test_results[g_test_number].data_isr_cnt ||
                g_status_isr_cnt            != g_mt_test_results[g_test_number].status_isr_cnt ||
                g_message_isr_cnt           != g_mt_test_results[g_test_number].message_isr_cnt ||
                g_tx_inhibited_isr_cnt      != g_mt_test_results[g_test_number].tx_inhibited_isr_cnt ||
                g_error_isr_cnt             != g_mt_test_results[g_test_number].error_isr_cnt )
                print("error: unexpected ISR count");
            
            if (mt.state.message_state      != g_mt_test_results[g_test_number].state.message_state)
                print("error: unexpected message interrupt status");

            if (mt.state.message_type       != g_mt_test_results[g_test_number].state.message_type )
                print("error: unexpected message type");

            if (mt.state.error_status       != g_mt_test_results[g_test_number].state.error_status )
                print("error: unexpected error status");

            if (mt.status.cmdWord1          != g_mt_test_results[g_test_number].status.cmdWord1 ||
                mt.status.cmdWord2          != g_mt_test_results[g_test_number].status.cmdWord2 ||
                mt.status.statusWord1       != g_mt_test_results[g_test_number].status.statusWord1 ||
                mt.status.statusWord2       != g_mt_test_results[g_test_number].status.statusWord2 ||
                mt.status.modeWord          != g_mt_test_results[g_test_number].status.modeWord )
                print("error: unexpected message status");

            if (g_mt_data[0]                != g_mt_test_results[g_test_number].rx_data[0] ||
                g_mt_data[1]                != g_mt_test_results[g_test_number].rx_data[1] ||
                g_mt_data[2]                != g_mt_test_results[g_test_number].rx_data[2] ||
                g_mt_data[3]                != g_mt_test_results[g_test_number].rx_data[3] ||
                g_mt_data[4]                != g_mt_test_results[g_test_number].rx_data[4] ||
                g_mt_data[5]                != g_mt_test_results[g_test_number].rx_data[5] ||
                g_mt_data[6]                != g_mt_test_results[g_test_number].rx_data[6] ||
                g_mt_data[7]                != g_mt_test_results[g_test_number].rx_data[7] )
                print("error: unexpected data values");

            // reset isr cnts
            g_command_isr_cnt = 0;
            g_mode_data_isr_cnt = 0;
            g_data_isr_cnt = 0;
            g_status_isr_cnt = 0;
            g_message_isr_cnt = 0;
            g_tx_inhibited_isr_cnt = 0;
            g_error_isr_cnt = 0;

            last_test_number = g_test_number;            
        }

    }

	return 0;
}


void mt_message_handler(ms1553_instance_t* p_mt_instance)
{
    /* real code would store off or process the message in some way */
    /* this code will just test that the message was processed as expected */
    etpu_ms1553_get_message_status(p_mt_instance);
    // always read 8 words for now, for testing purposes
    etpu_ms1553_get_message_data(p_mt_instance, 8/*g_mt_status.cmdWord1&0x1f*/, g_mt_data);
    
    g_message_isr_cnt++;
}

/* these handlers just increment isr counters */
void mt_command_handler(ms1553_instance_t* p_mt_instance)
{
    g_command_isr_cnt++;
}
void mt_mode_data_handler(ms1553_instance_t* p_mt_instance)
{
    g_mode_data_isr_cnt++;
}
void mt_data_handler(ms1553_instance_t* p_mt_instance)
{
    g_data_isr_cnt++;
}
void mt_status_handler(ms1553_instance_t* p_mt_instance)
{
    g_status_isr_cnt++;
}
void mt_tx_inhibited_handler(ms1553_instance_t* p_mt_instance)
{
    g_tx_inhibited_isr_cnt++;
}
void mt_error_handler(ms1553_instance_t* p_mt_instance)
{
    /* get all the data for test purposes; actual error handler may just want to get the state, which contains the error code */
    etpu_ms1553_get_message_status(p_mt_instance);
    // always read 8 words for now, for testing purposes
    etpu_ms1553_get_message_data(p_mt_instance, 8/*g_mt_status.cmdWord1&0x1f*/, g_mt_data);

    g_error_isr_cnt++;
}

