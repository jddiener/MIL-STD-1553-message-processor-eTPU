/**************************************************************************
 * Copyright (C) 2020 ASH WARE, Inc.
 *************************************************************************/
/*
 * etpu_auto_api.h
 *
 *  Created on: Nov 6, 2018
 *      Author: John
 */

#ifndef ETPU_AUTO_API_H_
#define ETPU_AUTO_API_H_

#include "etpu_ab_set_defines.h"
#if defined(MPC5777C)
#include "etpu_c_set_defines.h"
#endif

/* add defines and types needed by ETEC autostruct auto-generated file */
#define MSB_BITFIELD_ORDER
typedef unsigned char   etpu_if_uint8;
typedef signed char     etpu_if_sint8;
typedef unsigned short  etpu_if_uint16;
typedef signed short    etpu_if_sint16;
typedef unsigned int    etpu_if_uint32;
typedef signed int      etpu_if_sint32;

#include "etpu_ab_set_struct.h"
#if defined(MPC5777C)
#include "etpu_c_set_struct.h"
#endif

#endif /* ETPU_AUTO_API_H_ */
