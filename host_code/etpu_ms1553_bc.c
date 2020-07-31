/**************************************************************************
 * Copyright (C) 2020 ASH WARE, Inc.
 *************************************************************************/
/**************************************************************************
* FILE NAME: etpu_ms1553_bc.c
* 
* DESCRIPTION: API for interacting with the MIL-STD-1553 BC eTPU driver
*
*
*========================================================================
* REV      AUTHOR      DATE        DESCRIPTION OF CHANGE                 
* ---   -----------  ----------    ---------------------                 
* 1.0     J Diener   27/May/20     Initial version.     
*
**************************************************************************/

#include "etpu_ms1553_bc.h"


uint32_t etpu_ms1553_start_message(
    ms1553_instance_t *p_ms1553_instance,
    uint8_t message_type,
    uint16_t cmd_word_1,
    uint16_t cmd_word_2,
    uint16_t* p_data,
    uint8_t tx_word_count
    )
{
    uint8_t i;
    uint32_t hsrr;
    volatile struct eTPU_struct* p_eTPU;
    
    if (p_ms1553_instance == 0)
        return 1;

    if (p_ms1553_instance->module == EM_AB)
        p_eTPU = eTPU_AB;
    else
        p_eTPU = eTPU_C;

    p_ms1553_instance->MS1553_etpu_access_8bit->_messageType = message_type;    
    p_ms1553_instance->MS1553_etpu_access_24bit->_cmdWord1 = cmd_word_1;
    p_ms1553_instance->MS1553_etpu_access_24bit->_cmdWord2 = cmd_word_2;
    for (i = 0; i < tx_word_count; i++)
        p_ms1553_instance->MS1553_etpu_access_24bit->_txBuf[i] = (uint32_t)p_data[i];

    while ((hsrr = p_eTPU->CHAN[p_ms1553_instance->tx_chan_base_num].HSRR.R) != 0)
        ;
    p_eTPU->CHAN[p_ms1553_instance->tx_chan_base_num].HSRR.R = MS1553_BC_START_MESSAGE;
    
    return 0;
}

uint32_t etpu_ms1553_seek_idle(
    ms1553_instance_t *p_ms1553_instance,
    float seek_idle_timeout_us
    )
{
    uint32_t hsrr;
    uint32_t tcr_freq;
    volatile struct eTPU_struct* p_eTPU;

    if (p_ms1553_instance == 0)
        return 1;

    if (p_ms1553_instance->module == EM_AB)
    {
        if (p_ms1553_instance->rx_chan_base_num < 32)
            tcr_freq = etpu_a_tcr1_freq;
        else
            tcr_freq = etpu_b_tcr1_freq;
        p_eTPU = eTPU_AB;
    }
    else
    {
        tcr_freq = etpu_c_tcr1_freq;
        p_eTPU = eTPU_C;
    }
    p_ms1553_instance->MS1553_etpu_access_24bit->_seekIdleTimeout = tcr_freq / (uint32_t)(1000000 / seek_idle_timeout_us);

    while ((hsrr = p_eTPU->CHAN[p_ms1553_instance->rx_chan_base_num].HSRR.R) != 0)
        ;
    p_eTPU->CHAN[p_ms1553_instance->rx_chan_base_num].HSRR.R = MS1553_BC_SEEK_IDLE;

    return 0;
}

