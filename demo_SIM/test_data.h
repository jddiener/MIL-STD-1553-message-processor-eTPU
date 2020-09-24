// File 'test_data.h'

#ifndef __TEST_DATA_H
#define __TEST_DATA_H

#include "etpu_ms1553.h"

#define INVALID_WORD 0xBAD

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

extern struct test_result g_mt_test_results[];
extern struct test_result g_rt_test_results[];
extern struct test_result g_bc_test_results[];

struct test_message
{
    uint8_t  message_type;
    uint16_t tx_cmdWord1;
    uint16_t tx_cmdWord2;
    uint8_t  word_count;
    uint16_t tx_data[8];
};

extern struct test_message g_bc_test_message[];
extern uint32_t g_total_test_count;

#endif /* __TEST_DATA_H */
