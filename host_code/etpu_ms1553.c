/**************************************************************************
* Copyright (C) 2020 ASH WARE, Inc.
*************************************************************************/
/**************************************************************************
* FILE NAME: etpu_ms1553.c
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

#include "etpu_ms1553.h"
#include "etpu_ms1553_isr.h"


uint32_t etpu_ms1553_init(
    ms1553_instance_t *p_ms1553_instance
    )
{
    uint32_t *cpba;
    uint32_t tcr_freq;
    volatile struct eTPU_struct* p_eTPU;
    
    /* test key config parameters for validity */
    if (p_ms1553_instance->terminal_type != MS1553_TT_MONITOR_TERMINAL && 
        p_ms1553_instance->terminal_type != MS1553_TT_REMOTE_TERMINAL && 
        p_ms1553_instance->terminal_type != MS1553_TT_BUS_CONTROLLER)
        return FS_ETPU_ERROR_VALUE;
    /* must have valid RX channel */
    if ((p_ms1553_instance->rx_chan_base_num >= 32 && p_ms1553_instance->rx_chan_base_num < 64) ||
        (p_ms1553_instance->rx_chan_base_num >= 96))
        return FS_ETPU_ERROR_VALUE;
    /* RT/BC terminals must have valid TX channel */
    if ((p_ms1553_instance->terminal_type == MS1553_TT_REMOTE_TERMINAL || p_ms1553_instance->terminal_type == MS1553_TT_BUS_CONTROLLER) &&
        ((p_ms1553_instance->rx_chan_base_num >= 32 && p_ms1553_instance->rx_chan_base_num < 64) ||
         (p_ms1553_instance->rx_chan_base_num >= 96)))
        return FS_ETPU_ERROR_VALUE;
    /* MT must have invalid TX channel */
    if ((p_ms1553_instance->terminal_type == MS1553_TT_MONITOR_TERMINAL) && (p_ms1553_instance->tx_chan_base_num != 0xff))
        return FS_ETPU_ERROR_VALUE;

    /* disable all eTPU channels associated with this MS1553 data bus message processor instance */
    fs_etpu_disable_ext(p_ms1553_instance->module, p_ms1553_instance->rx_chan_base_num);
    fs_etpu_disable_ext(p_ms1553_instance->module, p_ms1553_instance->rx_chan_base_num+1);
    if (p_ms1553_instance->tx_chan_base_num != 0xff)
    {
        fs_etpu_disable_ext(p_ms1553_instance->module, p_ms1553_instance->tx_chan_base_num);
        fs_etpu_disable_ext(p_ms1553_instance->module, p_ms1553_instance->tx_chan_base_num+1);
    }
    
    /* allocate eTPU data memory for the istance if not previously allocated */
    cpba = (uint32_t*)p_ms1553_instance->cpba;
    if (cpba == 0)
    {
        cpba = (uint32_t*)fs_etpu_malloc2_ext(p_ms1553_instance->module, p_ms1553_instance->rx_chan_base_num, _FRAME_SIZE_MS1553_);
        if (cpba == 0)
            return FS_ETPU_ERROR_MALLOC;
        else
            p_ms1553_instance->cpba = (uint32_t)cpba;
    }
    p_ms1553_instance->MS1553_etpu_access_8bit = (etpu_if_MS1553_CHANNEL_FRAME*)cpba;
    p_ms1553_instance->MS1553_etpu_access_24bit = 
      (etpu_if_MS1553_CHANNEL_FRAME_PSE*)(((uint32_t)cpba - fs_etpu_data_ram_start) + fs_etpu_data_ram_ext);

    /* clear entire channel frame */
    fs_memset32_ext((uint32_t*)cpba, 0, _FRAME_SIZE_MS1553_);
    
    /* set timing parameters common to all MS1553 eTPU drivers */
    /* NOTE: if the terminal straddles two eTPU engines (RX on one, TX on other), they MUST have the same timing configuration! */
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
    p_ms1553_instance->MS1553_etpu_access_24bit->_0P50_bits  = tcr_freq / (2 * 1000000);
    p_ms1553_instance->MS1553_etpu_access_24bit->_1P25_bits  = tcr_freq / (uint32_t)(1000000 / 1.25f);
    p_ms1553_instance->MS1553_etpu_access_24bit->_1P50_bits  = tcr_freq / (uint32_t)(1000000 / 1.50f);
    p_ms1553_instance->MS1553_etpu_access_24bit->_1P75_bits  = tcr_freq / (uint32_t)(1000000 / 1.75f);
    p_ms1553_instance->MS1553_etpu_access_24bit->_2P25_bits  = tcr_freq / (uint32_t)(1000000 / 2.25f);
    p_ms1553_instance->MS1553_etpu_access_24bit->_2P50_bits  = tcr_freq / (uint32_t)(1000000 / 2.50f);
    p_ms1553_instance->MS1553_etpu_access_24bit->_18P75_bits = tcr_freq / (uint32_t)(1000000 / 18.75f);
    p_ms1553_instance->MS1553_etpu_access_24bit->_initIdleTimeout = tcr_freq / (uint32_t)(1000000 / p_ms1553_instance->initial_idle_timeout);
    p_ms1553_instance->MS1553_etpu_access_24bit->_rtStatusTimeout = tcr_freq / (uint32_t)(1000000 / p_ms1553_instance->rt_status_timeout);
    p_ms1553_instance->MS1553_etpu_access_24bit->_txDelay         = tcr_freq / (uint32_t)(1000000 / p_ms1553_instance->transmit_delay);

    /* additional terminal configuration */
    p_ms1553_instance->MS1553_etpu_access_24bit->_terminalAddress = p_ms1553_instance->terminal_address << 11;
    p_ms1553_instance->MS1553_etpu_access_8bit->_messageStatusInterruptMask = p_ms1553_instance->interrupt_mask;
    
    /* configure channel params for potential cross-engine linking */
    if (p_ms1553_instance->rx_chan_base_num < 32)
        p_ms1553_instance->MS1553_etpu_access_8bit->_rxBaseChan = FS_ETPU_LINK_ETPU_A(p_ms1553_instance->rx_chan_base_num);
    else
        p_ms1553_instance->MS1553_etpu_access_8bit->_rxBaseChan = FS_ETPU_LINK_ETPU_B(p_ms1553_instance->rx_chan_base_num);

    if (p_ms1553_instance->tx_chan_base_num < 32)
        p_ms1553_instance->MS1553_etpu_access_8bit->_txBaseChan = FS_ETPU_LINK_ETPU_A(p_ms1553_instance->tx_chan_base_num);
    else
        p_ms1553_instance->MS1553_etpu_access_8bit->_txBaseChan = FS_ETPU_LINK_ETPU_B(p_ms1553_instance->tx_chan_base_num);

    /* register this terminal with the interrupt handler */
    if (etpu_ms1553_register_instance(p_ms1553_instance, p_ms1553_instance->rx_chan_base_num))
        return FS_ETPU_ERROR_VALUE;
    if (p_ms1553_instance->terminal_type == MS1553_TT_BUS_CONTROLLER)
    {
        /* the bus controller needs its TX portion registered also, as it can generate an interrupt */
        if (etpu_ms1553_register_instance(p_ms1553_instance, p_ms1553_instance->tx_chan_base_num))
            return FS_ETPU_ERROR_VALUE;
    }
    
    /* terminal type specific code will complete initialization, enable channels, etc. */
    if (p_ms1553_instance->terminal_type == MS1553_TT_MONITOR_TERMINAL)
    {
	    /* positive RX chan */
    	p_eTPU->CHAN[p_ms1553_instance->rx_chan_base_num].CR.R =
    		(_ENTRY_TABLE_PIN_DIR_MS1553_MS1553_MT_RX_P_ << 25) +
    		(_ENTRY_TABLE_TYPE_MS1553_MS1553_MT_RX_P_ << 24) +
    		(_FUNCTION_NUM_MS1553_MS1553_MT_RX_P_ << 16) +
    		((p_ms1553_instance->cpba - fs_etpu_data_ram_start) >> 3);
    	p_eTPU->CHAN[p_ms1553_instance->rx_chan_base_num].SCR.R = 0; /* FM bits not used */
	    /* negative RX chan */
    	p_eTPU->CHAN[p_ms1553_instance->rx_chan_base_num + 1].CR.R =
    		(_ENTRY_TABLE_PIN_DIR_MS1553_MS1553_MT_RX_N_ << 25) +
    		(_ENTRY_TABLE_TYPE_MS1553_MS1553_MT_RX_N_ << 24) +
    		(_FUNCTION_NUM_MS1553_MS1553_MT_RX_N_ << 16) +
    		((p_ms1553_instance->cpba - fs_etpu_data_ram_start) >> 3);
    	p_eTPU->CHAN[p_ms1553_instance->rx_chan_base_num + 1].SCR.R = 0; /* FM bits not used */
    }
    else if (p_ms1553_instance->terminal_type == MS1553_TT_REMOTE_TERMINAL)
    {
	    /* positive RX chan */
    	p_eTPU->CHAN[p_ms1553_instance->rx_chan_base_num].CR.R =
    		(_ENTRY_TABLE_PIN_DIR_MS1553_MS1553_RT_RX_P_ << 25) +
    		(_ENTRY_TABLE_TYPE_MS1553_MS1553_RT_RX_P_ << 24) +
    		(_FUNCTION_NUM_MS1553_MS1553_RT_RX_P_ << 16) +
    		((p_ms1553_instance->cpba - fs_etpu_data_ram_start) >> 3);
    	p_eTPU->CHAN[p_ms1553_instance->rx_chan_base_num].SCR.R = 0; /* FM bits not used */
	    /* negative RX chan */
    	p_eTPU->CHAN[p_ms1553_instance->rx_chan_base_num + 1].CR.R =
    		(_ENTRY_TABLE_PIN_DIR_MS1553_MS1553_RT_RX_N_ << 25) +
    		(_ENTRY_TABLE_TYPE_MS1553_MS1553_RT_RX_N_ << 24) +
    		(_FUNCTION_NUM_MS1553_MS1553_RT_RX_N_ << 16) +
    		((p_ms1553_instance->cpba - fs_etpu_data_ram_start) >> 3);
    	p_eTPU->CHAN[p_ms1553_instance->rx_chan_base_num + 1].SCR.R = 0; /* FM bits not used */
	    /* positive TX chan */
    	p_eTPU->CHAN[p_ms1553_instance->tx_chan_base_num].CR.R =
    		(_ENTRY_TABLE_PIN_DIR_MS1553_MS1553_RT_TX_ << 25) +
    		(_ENTRY_TABLE_TYPE_MS1553_MS1553_RT_TX_ << 24) +
    		(_FUNCTION_NUM_MS1553_MS1553_RT_TX_ << 16) +
    		((p_ms1553_instance->cpba - fs_etpu_data_ram_start) >> 3);
    	p_eTPU->CHAN[p_ms1553_instance->tx_chan_base_num].SCR.R = 0; /* FM bits not used */
	    /* negative TX chan */
    	p_eTPU->CHAN[p_ms1553_instance->tx_chan_base_num + 1].CR.R =
    		(_ENTRY_TABLE_PIN_DIR_MS1553_MS1553_RT_TX_ << 25) +
    		(_ENTRY_TABLE_TYPE_MS1553_MS1553_RT_TX_ << 24) +
    		(_FUNCTION_NUM_MS1553_MS1553_RT_TX_ << 16) +
    		((p_ms1553_instance->cpba - fs_etpu_data_ram_start) >> 3);
    	p_eTPU->CHAN[p_ms1553_instance->tx_chan_base_num + 1].SCR.R = 0; /* FM bits not used */
    }
    else if (p_ms1553_instance->terminal_type == MS1553_TT_BUS_CONTROLLER)
    {
	    /* positive RX chan */
    	p_eTPU->CHAN[p_ms1553_instance->rx_chan_base_num].CR.R =
    		(_ENTRY_TABLE_PIN_DIR_MS1553_MS1553_BC_RX_P_ << 25) +
    		(_ENTRY_TABLE_TYPE_MS1553_MS1553_BC_RX_P_ << 24) +
    		(_FUNCTION_NUM_MS1553_MS1553_BC_RX_P_ << 16) +
    		((p_ms1553_instance->cpba - fs_etpu_data_ram_start) >> 3);
    	p_eTPU->CHAN[p_ms1553_instance->rx_chan_base_num].SCR.R = 0; /* FM bits not used */
	    /* negative RX chan */
    	p_eTPU->CHAN[p_ms1553_instance->rx_chan_base_num + 1].CR.R =
    		(_ENTRY_TABLE_PIN_DIR_MS1553_MS1553_BC_RX_N_ << 25) +
    		(_ENTRY_TABLE_TYPE_MS1553_MS1553_BC_RX_N_ << 24) +
    		(_FUNCTION_NUM_MS1553_MS1553_BC_RX_N_ << 16) +
    		((p_ms1553_instance->cpba - fs_etpu_data_ram_start) >> 3);
    	p_eTPU->CHAN[p_ms1553_instance->rx_chan_base_num + 1].SCR.R = 0; /* FM bits not used */
	    /* positive TX chan */
    	p_eTPU->CHAN[p_ms1553_instance->tx_chan_base_num].CR.R =
    		(_ENTRY_TABLE_PIN_DIR_MS1553_MS1553_BC_TX_ << 25) +
    		(_ENTRY_TABLE_TYPE_MS1553_MS1553_BC_TX_ << 24) +
    		(_FUNCTION_NUM_MS1553_MS1553_BC_TX_ << 16) +
    		((p_ms1553_instance->cpba - fs_etpu_data_ram_start) >> 3);
    	p_eTPU->CHAN[p_ms1553_instance->tx_chan_base_num].SCR.R = 0; /* FM bits not used */
	    /* negative TX chan */
    	p_eTPU->CHAN[p_ms1553_instance->tx_chan_base_num + 1].CR.R =
    		(_ENTRY_TABLE_PIN_DIR_MS1553_MS1553_BC_TX_ << 25) +
    		(_ENTRY_TABLE_TYPE_MS1553_MS1553_BC_TX_ << 24) +
    		(_FUNCTION_NUM_MS1553_MS1553_BC_TX_ << 16) +
    		((p_ms1553_instance->cpba - fs_etpu_data_ram_start) >> 3);
    	p_eTPU->CHAN[p_ms1553_instance->tx_chan_base_num + 1].SCR.R = 0; /* FM bits not used */
    }

    /* enable interrupts */
    fs_etpu_interrupt_enable_ext(p_ms1553_instance->module, p_ms1553_instance->rx_chan_base_num);
    fs_etpu_interrupt_enable_ext(p_ms1553_instance->module, p_ms1553_instance->rx_chan_base_num+1);
    /* bus controller receives bus busy interrupt from base TX chan */
    if (p_ms1553_instance->terminal_type == MS1553_TT_BUS_CONTROLLER)
        fs_etpu_interrupt_enable_ext(p_ms1553_instance->module, p_ms1553_instance->tx_chan_base_num);
    
    /* Write initialization HSRs */
    p_eTPU->CHAN[p_ms1553_instance->rx_chan_base_num].HSRR.R = MS1553_RX_INIT_HSR;
    if (p_ms1553_instance->terminal_type == MS1553_TT_REMOTE_TERMINAL || p_ms1553_instance->terminal_type == MS1553_TT_BUS_CONTROLLER)
        p_eTPU->CHAN[p_ms1553_instance->tx_chan_base_num].HSRR.R = MS1553_TX_INIT_HSR;

	/* Set channel priority */
    fs_etpu_enable_ext(p_ms1553_instance->module, p_ms1553_instance->rx_chan_base_num, p_ms1553_instance->priority);
    fs_etpu_enable_ext(p_ms1553_instance->module, p_ms1553_instance->rx_chan_base_num+1, p_ms1553_instance->priority);
    if (p_ms1553_instance->tx_chan_base_num != 0xff)
        fs_etpu_enable_ext(p_ms1553_instance->module, p_ms1553_instance->tx_chan_base_num, p_ms1553_instance->priority);

    return 0;
}

uint32_t etpu_ms1553_shutdown(
    ms1553_instance_t *p_ms1553_instance
    )
{
    uint32_t hsrr;
    volatile struct eTPU_struct* p_eTPU;

    if (p_ms1553_instance == 0)
        return 1;
    
    if (p_ms1553_instance->module == EM_AB)
        p_eTPU = eTPU_AB;
    else
        p_eTPU = eTPU_C;
    if (p_ms1553_instance->rx_chan_base_num != 0xff)
    {
        while ((hsrr = p_eTPU->CHAN[p_ms1553_instance->rx_chan_base_num].HSRR.R) != 0)
            ;
        p_eTPU->CHAN[p_ms1553_instance->rx_chan_base_num].HSRR.R = MS1553_RX_SHUTDOWN_HSR;
        while ((hsrr = p_eTPU->CHAN[p_ms1553_instance->rx_chan_base_num].HSRR.R) != 0)
            ;
        fs_etpu_disable_ext(p_ms1553_instance->module, p_ms1553_instance->rx_chan_base_num);
        fs_etpu_disable_ext(p_ms1553_instance->module, p_ms1553_instance->rx_chan_base_num+1);
    }
    if (p_ms1553_instance->tx_chan_base_num != 0xff)
    {
        while ((hsrr = p_eTPU->CHAN[p_ms1553_instance->tx_chan_base_num].HSRR.R) != 0)
            ;
        p_eTPU->CHAN[p_ms1553_instance->tx_chan_base_num].HSRR.R = MS1553_TX_SHUTDOWN_HSR;
        while ((hsrr = p_eTPU->CHAN[p_ms1553_instance->tx_chan_base_num].HSRR.R) != 0)
            ;
        fs_etpu_disable_ext(p_ms1553_instance->module, p_ms1553_instance->tx_chan_base_num);
    }
    
    return 0;
}


uint32_t etpu_ms1553_get_state(
    ms1553_instance_t *p_ms1553_instance
    )
{
    if (p_ms1553_instance == 0)
        return 1;
    p_ms1553_instance->state.message_state = p_ms1553_instance->MS1553_etpu_access_8bit->_messageStatus;
    p_ms1553_instance->state.message_type =  p_ms1553_instance->MS1553_etpu_access_8bit->_messageType;
    p_ms1553_instance->state.error_status =  p_ms1553_instance->MS1553_etpu_access_8bit->_errorStatus;
    return 0;
}

uint32_t etpu_ms1553_get_message_status(
    ms1553_instance_t *p_ms1553_instance
    )
{
    if (p_ms1553_instance == 0)
        return 1;

    p_ms1553_instance->status.cmdWord1 =    p_ms1553_instance->MS1553_etpu_access_24bit->_cmdWord1;
    p_ms1553_instance->status.cmdWord2 =    p_ms1553_instance->MS1553_etpu_access_24bit->_cmdWord2;
    p_ms1553_instance->status.statusWord1 = p_ms1553_instance->MS1553_etpu_access_24bit->_rxStatusWord1;
    p_ms1553_instance->status.statusWord2 = p_ms1553_instance->MS1553_etpu_access_24bit->_rxStatusWord2;
    p_ms1553_instance->status.modeWord =    p_ms1553_instance->MS1553_etpu_access_24bit->_rxModeWord;
    return 0;
}

uint32_t etpu_ms1553_get_message_data(
    ms1553_instance_t *p_ms1553_instance,
    uint32_t word_count,
    uint16_t* p_data_buf)
{
    uint32_t i;
    
    if (p_ms1553_instance == 0 || p_data_buf == 0)
        return 1;

    for (i = 0; i < word_count; i++)
    {
        *p_data_buf++ =  (uint16_t)p_ms1553_instance->MS1553_etpu_access_24bit->_rxBuf[i];
    }
    return 0;
}

uint32_t etpu_ms1553_reset_error_status(
    ms1553_instance_t *p_ms1553_instance
    )
{
    if (p_ms1553_instance == 0)
        return 1;

    p_ms1553_instance->MS1553_etpu_access_8bit->_errorStatus = NO_ERROR;
    return 0;
}
