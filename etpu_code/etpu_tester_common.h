/*************************************************************************
 * FILE NAME: etpu_test_common.h  Copyright (C) 2008 ASH WARE, Inc.*
 *                                      All Rights Reserved              *
 *                                                                       *
 * This file provides definitions common to the eTPU-side code, and to   *
 * the host CPU interface to the eTPU.                                   *
 ************************************************************************/
#ifndef  __TESTER_COMMON_H__
#define  __TESTER_COMMON_H__

// Host Service Request Definitions -
#define AW_TESTER_LINK_HSR        7  
#define AW_TESTER_LATENCY_HSR     6  
#define AW_TESTER_WR_FLAGS_HSR    5  
#define AW_TESTER_FORCE_STATE_HSR 4  

// Forced States
#define AW_TESTER_FORCE_MATCH_A    12 
#define AW_TESTER_FORCE_MATCH_B    8 
#define AW_TESTER_FORCE_SET_FLAG1  4 
#define AW_TESTER_FORCE_SET_FLAG0  0 

#endif // __TESTER_COMMON_H__
