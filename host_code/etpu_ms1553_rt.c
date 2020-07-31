/**************************************************************************
 * Copyright (C) 2020 ASH WARE, Inc.
 *************************************************************************/
/**************************************************************************
* FILE NAME: etpu_ms1553_rt.c
* 
* DESCRIPTION: API for interacting with the MIL-STD-1553 RT eTPU driver
*
*
*========================================================================
* REV      AUTHOR      DATE        DESCRIPTION OF CHANGE                 
* ---   -----------  ----------    ---------------------                 
* 1.0     J Diener   27/May/20     Initial version.     
*
**************************************************************************/

#include "etpu_ms1553_rt.h"


uint32_t etpu_ms1553_set_tx_status_word(
    ms1553_instance_t *p_ms1553_instance,
    uint16_t status_word
    )
{
    if (p_ms1553_instance == 0)
        return 1;
    p_ms1553_instance->MS1553_etpu_access_24bit->_txStatusWord = status_word;
    return 0;
}

uint32_t etpu_ms1553_set_tx_mode_word(
    ms1553_instance_t *p_ms1553_instance,
    uint16_t mode_word
    )
{
    if (p_ms1553_instance == 0)
        return 1;
    p_ms1553_instance->MS1553_etpu_access_24bit->_txModeWord = mode_word;
    return 0;
}

uint32_t etpu_ms1553_set_tx_data(
    ms1553_instance_t *p_ms1553_instance,
    uint32_t data_word_cnt,
    uint16_t* p_data
    )
{
    uint32_t i;
    if (p_ms1553_instance == 0 || p_data == 0 || data_word_cnt >= 32)
        return 1;
    for (i = 0; i < data_word_cnt; i++)
        p_ms1553_instance->MS1553_etpu_access_24bit->_txBuf[i] = *p_data++;
    return 0;
}


uint32_t etpu_ms1553_set_tx_data_inhibit(
    ms1553_instance_t *p_ms1553_instance,
    uint8_t tx_data_inhibit
    )
{
    if (p_ms1553_instance == 0)
        return 1;
    p_ms1553_instance->MS1553_etpu_access_8bit->_txDataWordInhibit = tx_data_inhibit;
    return 0;
}

uint32_t etpu_ms1553_set_tx_inhibit(
    ms1553_instance_t *p_ms1553_instance,
    uint8_t tx_inhibit
    )
{
    if (p_ms1553_instance == 0)
        return 1;
    p_ms1553_instance->MS1553_etpu_access_8bit->_txInhibit = tx_inhibit;
    return 0;
}
