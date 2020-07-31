/**************************************************************************
 * Copyright (C) 2020 ASH WARE, Inc.
 *************************************************************************/
/**************************************************************************
* FILE NAME: etpu_ms1553_bc.c
* 
* DESCRIPTION: API declarations for interacting with the MIL-STD-1553 BC eTPU driver
*
*
*========================================================================
* REV      AUTHOR      DATE        DESCRIPTION OF CHANGE                 
* ---   -----------  ----------    ---------------------                 
* 1.0     J Diener   27/May/20     Initial version.     
*
**************************************************************************/


#ifndef __ETPU_MS1553_BC_H
#define __ETPU_MS1553_BC_H

#include "etpu_ms1553.h"

#ifdef __cplusplus
extern "C" {
#endif

uint32_t etpu_ms1553_start_message(
    ms1553_instance_t *p_ms1553_instance,
    uint8_t message_type,
    uint16_t cmd_word_1,
    uint16_t cmd_word_2,
    uint16_t* p_data,
    uint8_t word_count
    );

uint32_t etpu_ms1553_seek_idle(
    ms1553_instance_t *p_ms1553_instance,
    float seek_idle_timeout_us
    );

#ifdef __cplusplus
}
#endif

#endif // __ETPU_MS1553_BC_H
