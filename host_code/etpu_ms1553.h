/**************************************************************************
* Copyright (C) 2020 ASH WARE, Inc.
*************************************************************************/
/**************************************************************************
* FILE NAME: etpu_ms1553.h
* 
* DESCRIPTION: common APIs for initialzing and interacting with all the
* MIL-STD-1553 eTPU drivers
*
*
*========================================================================
* REV      AUTHOR      DATE        DESCRIPTION OF CHANGE                 
* ---   -----------  ----------    ---------------------                 
* 1.0     J Diener   27/May/20     Initial version.     
*
**************************************************************************/


#ifndef __ETPU_MS1553_H
#define __ETPU_MS1553_H

#include "typedefs.h"
#include "etpu_util_ext.h"
#include "etpu_auto_api.h"
#include "etec_ms1553_common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    MS1553_TT_MONITOR_TERMINAL,
    MS1553_TT_REMOTE_TERMINAL,
    MS1553_TT_BUS_CONTROLLER,
} ms1553_terminal_type_t;

typedef struct
{
    uint8_t     message_state;
    uint8_t     message_type;
    uint8_t     error_status;
} ms1553_instance_state_t;

typedef struct
{
    uint16_t    cmdWord1;
    uint16_t    cmdWord2;
    uint16_t    statusWord1;
    uint16_t    statusWord2;
    uint16_t    modeWord;
} ms1553_instance_message_status_t;

typedef struct ms1553_instance_struct
{
    ms1553_terminal_type_t              terminal_type;

    /* eTPU configuration */
    ETPU_MODULE                         module;
    uint8_t                             rx_chan_base_num;
    uint8_t                             tx_chan_base_num;
    uint8_t                             priority;

    uint32_t                            cpba;
    etpu_if_MS1553_CHANNEL_FRAME*       MS1553_etpu_access_8bit;
    etpu_if_MS1553_CHANNEL_FRAME_PSE*   MS1553_etpu_access_24bit;

    /* common terminal configuration */
    uint32_t                            terminal_address;
    uint8_t                             interrupt_mask;
    /* interrupt handlers */
    void                                (*p_cmd_word_handler)(struct ms1553_instance_struct *);
    void                                (*p_mode_data_handler)(struct ms1553_instance_struct *);
    void                                (*p_message_data_handler)(struct ms1553_instance_struct *);
    void                                (*p_status_word_handler)(struct ms1553_instance_struct *);
    void                                (*p_message_handler)(struct ms1553_instance_struct *);
    void                                (*p_transmit_inhibited_handler)(struct ms1553_instance_struct *);
    void                                (*p_idle_detected_handler)(struct ms1553_instance_struct *);
    void                                (*p_bus_busy_handler)(struct ms1553_instance_struct *);
    void                                (*p_error_handler)(struct ms1553_instance_struct *);

    /* message state/status retrieved from eTPU drivers */
    ms1553_instance_state_t             state;
    ms1553_instance_message_status_t    status;
    
    /* configurable timing parameters */
    float                               initial_idle_timeout;
    float                               rt_status_timeout;

    /* MT-specific configuration */
    /* none currently */
    
    /* RT-specific configuration */
    float                               transmit_delay;

    /* BC-specific configuration */
    /* none currently */

} ms1553_instance_t;


uint32_t etpu_ms1553_init(
    ms1553_instance_t *p_ms1553_instance
    );

uint32_t etpu_ms1553_shutdown(
    ms1553_instance_t *p_ms1553_instance
    );

uint32_t etpu_ms1553_get_state(
    ms1553_instance_t *p_ms1553_instance
    );

uint32_t etpu_ms1553_get_message_status(
    ms1553_instance_t *p_ms1553_instance
    );

uint32_t etpu_ms1553_get_message_data(
    ms1553_instance_t *p_ms1553_instance,
    uint32_t word_count,
    uint16_t* p_data_buf);

uint32_t etpu_ms1553_reset_error_status(
    ms1553_instance_t *p_ms1553_instance
    );

#ifdef __cplusplus
}
#endif

#endif // __ETPU_MS1553_H
