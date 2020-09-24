/**************************************************************************
 * Copyright (C) 2020 ASH WARE, Inc.
 *************************************************************************/
/**************************************************************************
* FILE NAME: etpu_ms1553_isr.h
* 
* DESCRIPTION: API declaration handling MIL-STD-1553 interrupts from the eTPU
*
*
*========================================================================
* REV      AUTHOR      DATE        DESCRIPTION OF CHANGE                 
* ---   -----------  ----------    ---------------------                 
* 1.0     J Diener   27/May/20     Initial version.     
*
**************************************************************************/

#ifndef __ETPU_MS1553_ISR_H
#define __ETPU_MS1553_ISR_H

#include "typedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

uint32_t etpu_ms1553_register_instance(
    ms1553_instance_t *p_ms1553_instance,
    ETPU_MODULE em,
    uint32_t chan_base_num
    );

uint32_t etpu_ms1553_ISR(
    ETPU_MODULE em,
    uint32_t etpu_channel
    );

#ifdef __cplusplus
}
#endif

#endif // __ETPU_MS1553_ISR_H
