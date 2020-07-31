/**************************************************************************
 * Copyright (C) 2020 ASH WARE, Inc.
 *************************************************************************/
/**************************************************************************
* FILE NAME: etpu_ms1553_isr.c
* 
* DESCRIPTION: routines for handling MIL-STD-1553 interrupts from the eTPU
*
*
*========================================================================
* REV      AUTHOR      DATE        DESCRIPTION OF CHANGE                 
* ---   -----------  ----------    ---------------------                 
* 1.0     J Diener   27/May/20     Initial version.     
*
**************************************************************************/

#include "etpu_ms1553.h"
#include "etpu_ms1553_mt.h"
#include "etpu_ms1553_isr.h"

typedef struct
{
    uint32_t chan_base_num;
    ms1553_instance_t* instance;
} ms1553_etpu_channel_instance_map_t;

#define MAX_MS1553_INSTANCE 8
uint32_t g_ms1553_instance_count = 0;
ms1553_etpu_channel_instance_map_t g_ms1553_etpu_channel_instance_map[MAX_MS1553_INSTANCE];


ms1553_instance_t* etpu_ms1553_get_instance_from_channel(uint32_t etpu_channel)
{
    uint32_t i;
    
    for (i = 0; i < g_ms1553_instance_count; i++)
    {
        if (g_ms1553_etpu_channel_instance_map[i].chan_base_num == etpu_channel ||
            g_ms1553_etpu_channel_instance_map[i].chan_base_num + 1 == etpu_channel)
            return g_ms1553_etpu_channel_instance_map[i].instance;
    }
    return 0;
}


uint32_t etpu_ms1553_register_instance(
    ms1553_instance_t *p_ms1553_instance,
    uint32_t chan_base_num
    )
{
    uint32_t i;
    
    /* check if previously registered */
    for (i = 0; i < g_ms1553_instance_count; i++)
    {
        if (g_ms1553_etpu_channel_instance_map[i].chan_base_num == chan_base_num)
        {
            /* chan registered previously, but update instance */
            g_ms1553_etpu_channel_instance_map[i].instance = p_ms1553_instance;
            return 0;
        }
    }
    
    if (g_ms1553_instance_count >= MAX_MS1553_INSTANCE)
        return 1;
        
    g_ms1553_etpu_channel_instance_map[g_ms1553_instance_count].chan_base_num = chan_base_num;
    g_ms1553_etpu_channel_instance_map[g_ms1553_instance_count].instance = p_ms1553_instance;
    g_ms1553_instance_count++;
    return 0;
}


uint32_t etpu_ms1553_ISR(
    uint32_t etpu_channel
    )
{
    ms1553_instance_t* instance;
    
    instance = etpu_ms1553_get_instance_from_channel(etpu_channel);
    if (!instance)
        return 1; 

    /* read message state first */
    if (etpu_ms1553_get_state(instance))
        return 1;
        
    if (etpu_channel == instance->tx_chan_base_num && instance->p_bus_busy_handler != 0)
        instance->p_bus_busy_handler(instance);    

    /* call the appropriate handlers given state */
    if (instance->state.message_state & MESSAGE_COMPLETE)
    {
        /* message complete is special in that it may come in conjunction with status interrupts: */
        /* - COMMAND_WORD_VALID
           - MODE_DATA_VALID
           - MESSAGE_DATA_VALID
           - MESSAGE_STATUS_VALID
           The message complete handler should deal with these extra interrupt flags as needed.
           */
        if (instance->p_message_handler != 0)
            instance->p_message_handler(instance);
    }
    else
    {
        if ((instance->state.message_state & COMMAND_WORD_VALID) && (instance->p_cmd_word_handler != 0))
            instance->p_cmd_word_handler(instance);
        if ((instance->state.message_state & MODE_DATA_VALID) && (instance->p_mode_data_handler != 0))
            instance->p_mode_data_handler(instance);
        if ((instance->state.message_state & MESSAGE_DATA_VALID) && (instance->p_message_data_handler != 0))
            instance->p_message_data_handler(instance);
        if ((instance->state.message_state & MESSAGE_STATUS_VALID) && (instance->p_status_word_handler != 0))
            instance->p_status_word_handler(instance);
        if ((instance->state.message_state & MESSAGE_TRANSMIT_INHIBITED) && (instance->p_transmit_inhibited_handler != 0))
            instance->p_transmit_inhibited_handler(instance);
        if ((instance->state.message_state & BUS_IDLE_DETECTED) && (instance->p_idle_detected_handler != 0))
            instance->p_idle_detected_handler(instance);
        if ((instance->state.message_state & MESSAGE_ERROR) && (instance->p_error_handler != 0))
            instance->p_error_handler(instance);
    }
    
    return 0;
}

