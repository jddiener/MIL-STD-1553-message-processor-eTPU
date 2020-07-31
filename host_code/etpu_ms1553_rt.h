/**************************************************************************
 * Copyright (C) 2020 ASH WARE, Inc.
 *************************************************************************/
/**************************************************************************
* FILE NAME: etpu_ms1553_rt.c
* 
* DESCRIPTION: API declarations for interacting with the MIL-STD-1553 RT eTPU driver
*
*
*========================================================================
* REV      AUTHOR      DATE        DESCRIPTION OF CHANGE                 
* ---   -----------  ----------    ---------------------                 
* 1.0     J Diener   27/May/20     Initial version.     
*
**************************************************************************/


#ifndef __ETPU_MS1553_RT_H
#define __ETPU_MS1553_RT_H

#include "etpu_ms1553.h"

#ifdef __cplusplus
extern "C" {
#endif

uint32_t etpu_ms1553_set_tx_status_word(
    ms1553_instance_t *p_ms1553_instance,
    uint16_t status_word
    );

uint32_t etpu_ms1553_set_tx_mode_word(
    ms1553_instance_t *p_ms1553_instance,
    uint16_t mode_word
    );

uint32_t etpu_ms1553_set_tx_data(
    ms1553_instance_t *p_ms1553_instance,
    uint32_t data_word_cnt,
    uint16_t* p_data
    );

uint32_t etpu_ms1553_set_tx_data_inhibit(
    ms1553_instance_t *p_ms1553_instance,
    uint8_t tx_data_inhibit
    );

uint32_t etpu_ms1553_set_tx_inhibit(
    ms1553_instance_t *p_ms1553_instance,
    uint8_t tx_inhibit
    );

#ifdef __cplusplus
}
#endif

#endif // __ETPU_MS1553_RT_H
