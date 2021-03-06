// This file is auto-generated by the ASH WARE ETEC Linker.
//    !!!   DO NOT EDIT THIS FILE   !!!
// Copyright (C) 2015 ASH WARE, Inc. 

// It contains data structures with initialization information.
// The data structures are created using the data initialization macros.
// The host side code uses this initialization information
// to initialize global data and also the private channel frames.

// Global Memory Initialization Data Array
unsigned int _global_mem_init[] =
{
#undef __GLOBAL_MEM_INIT32
#define __GLOBAL_MEM_INIT32( addr , val ) val,
#include "etpu_ab_set_idata.h"
#undef __GLOBAL_MEM_INIT32
};

// Tester Channel Frame Initialization Data Array
unsigned int _Tester_frame_init[] =
{
#undef __Tester_CHAN_FRAME_INIT32
#define __Tester_CHAN_FRAME_INIT32( addr , val ) val,
#include "etpu_ab_set_idata.h"
#undef __Tester_CHAN_FRAME_INIT32
};

// MS1553 Channel Frame Initialization Data Array
unsigned int _MS1553_frame_init[] =
{
#undef __MS1553_CHAN_FRAME_INIT32
#define __MS1553_CHAN_FRAME_INIT32( addr , val ) val,
#include "etpu_ab_set_idata.h"
#undef __MS1553_CHAN_FRAME_INIT32
};

