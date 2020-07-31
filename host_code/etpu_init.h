/**************************************************************************
 * Copyright (C) 2020 ASH WARE, Inc.
 *************************************************************************/
/**************************************************************************
* FILE NAME: etpu_init.h
* 
* DESCRIPTION: API for initializing the eTPU module
*
**************************************************************************/

#ifndef __ETPU_INIT_H
#define __ETPU_INIT_H

#include "typedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************
 * eTPU module initialization
 *
 * Returns failure code, or pass (0).
 ****************************************************************/
uint32_t etpu_init();

#ifdef __cplusplus
}
#endif

#endif /* __ETPU_INIT_H */
