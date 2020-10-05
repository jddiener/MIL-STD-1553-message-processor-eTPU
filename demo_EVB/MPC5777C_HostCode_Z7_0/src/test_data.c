// File: test_data.c

#include "test_data.h"

struct test_result g_mt_test_results[] =
{
    { 0, 0, 0, 0, 0, 0, 0,
      { COMMAND_WORD_VALID,                        BC_TO_RT_XFR,                NO_ERROR, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // note : 0 element is not used
      
    { 1, 0, 1, 0, 1, 0, 0,
      { MESSAGE_STATUS_VALID | MESSAGE_COMPLETE,   BC_TO_RT_XFR,                NO_ERROR, },
      { 0x2223, INVALID_WORD, 0x2000, INVALID_WORD, INVALID_WORD, },
      { 0x815f, 0x5663, 0x64f9, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 1
      
    { 1, 0, 0, 1, 1, 0, 0,
      { MESSAGE_DATA_VALID | MESSAGE_COMPLETE,     RT_TO_BC_XFR,                NO_ERROR, },
      { 0x2623, INVALID_WORD, 0x2000, INVALID_WORD, INVALID_WORD, },
      { 0x7B5F, 0x25AF, 0x39A5, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 2
      
    { 1, 0, 0, 0, 1, 0, 0,
      { MESSAGE_DATA_VALID | MESSAGE_COMPLETE,     BC_TO_RT_BROADCAST_XFR,      NO_ERROR, },
      { 0xFA24, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { 0x815f, 0x5663, 0x64f9, 0x9CAF, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 3
      
    { 1, 0, 0, 0, 1, 0, 0,
      { MESSAGE_STATUS_VALID | MESSAGE_COMPLETE,   MODE_XMT_WITHOUT_DATA,       NO_ERROR, },
      { 0x27E2, INVALID_WORD, 0x2000, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 4
      
    { 1, 0, 0, 1, 1, 0, 0,
      { MODE_DATA_VALID | MESSAGE_COMPLETE,        MODE_XMT_WITH_DATA,          NO_ERROR, },
      { 0x27F2, INVALID_WORD, 0x2000, INVALID_WORD, 0x815F, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 5
      
    { 1, 1, 0, 0, 1, 0, 0,
      { MESSAGE_STATUS_VALID | MESSAGE_COMPLETE,   MODE_RCV_WITH_DATA,          NO_ERROR, },
      { 0x23F2, INVALID_WORD, 0x2000, INVALID_WORD, 0x815F, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 6
      
    { 0, 0, 0, 0, 1, 0, 0,
      { COMMAND_WORD_VALID | MESSAGE_COMPLETE,     MODE_BROADCAST_WITHOUT_DATA, NO_ERROR, },
      { 0xFFE2, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 7
      
    { 1, 0, 0, 0, 1, 0, 0,
      { MODE_DATA_VALID | MESSAGE_COMPLETE,        MODE_BROADCAST_WITH_DATA,    NO_ERROR, },
      { 0xFBF2, INVALID_WORD, INVALID_WORD, INVALID_WORD, 0x22E0, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 8
      
    { 1, 0, 0, 0, 1, 0, 0,
      { MESSAGE_STATUS_VALID | MESSAGE_COMPLETE,   MODE_XMT_WITHOUT_DATA,       NO_ERROR, },
      { 0x27E2, INVALID_WORD, 0x2000, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 9
};
struct test_result g_rt_test_results[] =
{
    { 0, 0, 0, 0, 0, 0, 0,
      { COMMAND_WORD_VALID,                        BC_TO_RT_XFR,                NO_ERROR, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      INVALID_WORD,
      INVALID_WORD,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // note : 0 element is not used
      
    { 1, 0, 1, 0, 1, 0, 0,
      { MESSAGE_COMPLETE,                          BC_TO_RT_XFR,                NO_ERROR, },
      { 0x2223, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { 0x815f, 0x5663, 0x64f9, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      0x2000,
      INVALID_WORD,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 1
      
    { 1, 0, 0, 0, 1, 0, 0,
      { MESSAGE_COMPLETE,                          RT_TO_BC_XFR,                NO_ERROR, },
      { 0x2623, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      0x2000,
      INVALID_WORD,
      { 0x7B5F, 0x25AF, 0x39A5, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 2
      
    { 1, 0, 0, 0, 1, 0, 0,
      { MESSAGE_DATA_VALID | MESSAGE_COMPLETE,     BC_TO_RT_BROADCAST_XFR,      NO_ERROR, },
      { 0xFA24, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { 0x815f, 0x5663, 0x64f9, 0x9CAF, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      INVALID_WORD,
      INVALID_WORD,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 3
      
    { 1, 0, 0, 0, 1, 0, 0,
      { MESSAGE_COMPLETE,                          MODE_XMT_WITHOUT_DATA,       NO_ERROR, },
      { 0x27E2, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      0x2000,
      INVALID_WORD,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 4
      
    { 1, 0, 0, 0, 1, 0, 0,
      { MESSAGE_COMPLETE,                          MODE_XMT_WITH_DATA,          NO_ERROR, },
      { 0x27F2, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      0x2000,
      0x815F,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 5
      
    { 1, 1, 0, 0, 1, 0, 0,
      { MESSAGE_COMPLETE,                          MODE_RCV_WITH_DATA,          NO_ERROR, },
      { 0x23F2, INVALID_WORD, INVALID_WORD, INVALID_WORD, 0x815F, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      0x2000,
      INVALID_WORD,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 6
      
    { 0, 0, 0, 0, 1, 0, 0,
      {  COMMAND_WORD_VALID | MESSAGE_COMPLETE,    MODE_BROADCAST_WITHOUT_DATA, NO_ERROR, },
      { 0xFFE2, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      INVALID_WORD,
      INVALID_WORD,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 7
      
    { 1, 0, 0, 0, 1, 0, 0,
      { MODE_DATA_VALID | MESSAGE_COMPLETE,        MODE_BROADCAST_WITH_DATA,    NO_ERROR, },
      { 0xFBF2, INVALID_WORD, INVALID_WORD, INVALID_WORD, 0x22E0, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      INVALID_WORD,
      INVALID_WORD,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 8
      
    { 1, 0, 0, 0, 1, 0, 0,
      { MESSAGE_COMPLETE,                          MODE_XMT_WITHOUT_DATA,       NO_ERROR, },
      { 0x27E2, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, 
      0x2000,
      INVALID_WORD,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 9
};
struct test_result g_bc_test_results[] =
{
    { 0, 0, 0, 0, 0, 0, 0,
      { COMMAND_WORD_VALID,                        BC_TO_RT_XFR,                NO_ERROR, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // note : 0 element is not used
      
    { 0, 0, 0, 0, 1, 0, 0,
      { MESSAGE_STATUS_VALID | MESSAGE_COMPLETE,   BC_TO_RT_XFR,                NO_ERROR, },
      { 0x2223, INVALID_WORD, 0x2000, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 1
      
    { 0, 0, 0, 1, 1, 0, 0,
      { MESSAGE_DATA_VALID | MESSAGE_COMPLETE,     RT_TO_BC_XFR,                NO_ERROR, },
      { 0x2623, INVALID_WORD, 0x2000, INVALID_WORD, INVALID_WORD, },
      { 0x7B5F, 0x25AF, 0x39A5, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 2
      
    { 0, 0, 0, 0, 1, 0, 0,
      { MESSAGE_COMPLETE,                          BC_TO_RT_BROADCAST_XFR,      NO_ERROR, },
      { 0xFA24, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 3
      
    { 0, 0, 0, 0, 1, 0, 0,
      { MESSAGE_STATUS_VALID | MESSAGE_COMPLETE,   MODE_XMT_WITHOUT_DATA,       NO_ERROR, },
      { 0x27E2, INVALID_WORD, 0x2000, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 4
      
    { 0, 0, 0, 1, 1, 0, 0,
      { MODE_DATA_VALID | MESSAGE_COMPLETE,        MODE_XMT_WITH_DATA,          NO_ERROR, },
      { 0x27F2, INVALID_WORD, 0x2000, INVALID_WORD, 0x815F, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 5
      
    { 0, 0, 0, 0, 1, 0, 0,
      { MESSAGE_STATUS_VALID | MESSAGE_COMPLETE,   MODE_RCV_WITH_DATA,          NO_ERROR, },
      { 0x23F2, INVALID_WORD, 0x2000, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 6
      
    { 0, 0, 0, 0, 1, 0, 0,
      { MESSAGE_COMPLETE,                          MODE_BROADCAST_WITHOUT_DATA, NO_ERROR, },
      { 0xFFE2, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 7
      
    { 0, 0, 0, 0, 1, 0, 0,
      { MESSAGE_COMPLETE,                          MODE_BROADCAST_WITH_DATA,    NO_ERROR, },
      { 0xFBF2, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 8
        
    { 0, 0, 0, 0, 1, 0, 0,
      { MESSAGE_STATUS_VALID | MESSAGE_COMPLETE,   MODE_XMT_WITHOUT_DATA,       NO_ERROR, },
      { 0x27E2, INVALID_WORD, 0x2000, INVALID_WORD, INVALID_WORD, },
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 9
};

struct test_message g_bc_test_message[] = 
{
    { BC_TO_RT_XFR,                 0x2223, INVALID_WORD,       3,
      { 0x815f, 0x5663, 0x64f9, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 1
    { RT_TO_BC_XFR,                 0x2623, INVALID_WORD,       0,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 2
    { BC_TO_RT_BROADCAST_XFR,       0xfa24, INVALID_WORD,     4,
      { 0x815f, 0x5663, 0x64f9, 0x9caf, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 3
    { MODE_XMT_WITHOUT_DATA,        0x27e2, INVALID_WORD,       0,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 4
    { MODE_XMT_WITH_DATA,           0x27f2, INVALID_WORD,       0,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 5
    { MODE_RCV_WITH_DATA,           0x23f2, INVALID_WORD,       1,
      { 0x815f, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 6
    { MODE_BROADCAST_WITHOUT_DATA,  0xffe2, INVALID_WORD, 0,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 7
    { MODE_BROADCAST_WITH_DATA,     0xfbf2, INVALID_WORD,    1,
      { 0x22e0, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 8
    { MODE_XMT_WITHOUT_DATA,        0x27e2, INVALID_WORD,       0,
      { INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, INVALID_WORD, }, }, // test 9
};
uint32_t g_total_test_count = sizeof(g_bc_test_message) / sizeof(struct test_message);
