/**************************************************************************
 * Copyright (C) 2020 ASH WARE, Inc.
 *************************************************************************/
/**************************************************************************
* FILE NAME: etpu_config.h
* 
* DESCRIPTION: Defines eTPU module configuration.
* Note: only to be included in etpu_init.c.
*
*
*========================================================================
* REV      AUTHOR      DATE        DESCRIPTION OF CHANGE                 
* ---   -----------  ----------    ---------------------                 
* 1.0     J Diener   01/Jun/20     Initial version.     
*
**************************************************************************/

/* include appropriate target var definition file */
#include "mpc5554_vars.h"
//#include "mpc5777c_vars.h"
//#include "mpc5777c_vars_c.h"

/**************************************************************************
 * general macros
 **************************************************************************/
#define FS_ETPU_TCR1_PRESCALER(x)    (((x)-1) & 0xFF)
#define FS_ETPU_TCR2_PRESCALER(x)    ((((x)-1) & 0x3F)<<16)
#define FS_ETPU_TCR1_STAC_SRVSLOT(x) (((x) & 0xF)<<16)
#define FS_ETPU_TCR2_STAC_SRVSLOT(x) ((x) & 0xF)
#define FS_ETPU_CHANNEL_FUNCTION(x)  ((x) & 0x1F)
#define FS_ETPU_CHANNEL_PARAMS(x)    ((x) & 0x7F)
#define FS_ETPU_FUNCTION_MODE(x)     ((x) & 0x3)

#define FS_ETPU_ENTRY_TABLE_ADDR     (((FS_ETPU_ENTRY_TABLE)>>11) & 0x1F)

#define FS_ETPU_FUNCTION_MODE_00     FS_ETPU_FUNCTION_MODE(0)
#define FS_ETPU_FUNCTION_MODE_01     FS_ETPU_FUNCTION_MODE(1)
#define FS_ETPU_FUNCTION_MODE_10     FS_ETPU_FUNCTION_MODE(2)
#define FS_ETPU_FUNCTION_MODE_11     FS_ETPU_FUNCTION_MODE(3)

#define FS_ETPU_HSR_0                (0)
#define FS_ETPU_HSR_1                (1)
#define FS_ETPU_HSR_2                (2)
#define FS_ETPU_HSR_3                (3)
#define FS_ETPU_HSR_4                (4)
#define FS_ETPU_HSR_5                (5)
#define FS_ETPU_HSR_6                (6)
#define FS_ETPU_HSR_7                (7)

#define ETPU_ENGINE_A_CHANNEL(x)  (x)
#define ETPU_ENGINE_B_CHANNEL(x)  ((x)+64)
#define ETPU_CHAN_NOT_USED        (-1)

struct etpu_config_t my_etpu_config =
{
  /* etpu_config.mcr */
  FS_ETPU_VIS_OFF	/* SCM not visible (VIS=0) */
  | FS_ETPU_MISC_ENABLE	/* SCM operation enabled (SCMMISEN=1) */,

  /* etpu_config.misc */
  _MISC_VALUE_,

  /* etpu_config.scmoff */
  _SCM_OFF_OPCODE_,

  /* etpu_config.ecr_a */
  _ENTRY_TABLE_BASE_ADDR_	/* entry table base address = shifted FS_ETPU_ENTRY_TABLE */
  | FS_ETPU_CHAN_FILTER_3SAMPLE	/* channel filter mode = three-sample mode (CDFC=2) */
  | FS_ETPU_ENGINE_ENABLE	/* engine is enabled (MDIS=0) */
  | FS_ETPU_FILTER_CLOCK_DIV2	/* channel filter clock = etpuclk div 16 (FPSCK=3) */,

  /* etpu_config.tbcr_a */
  FS_ETPU_ANGLE_MODE_DISABLE	/* TCR2 angle mode is disabled (AM=0) */
  | FS_ETPU_TCR2_PRESCALER(16)	/* TCR2 prescaler = 16 (TCR2P='16-1') */
  | FS_ETPU_TCR1_PRESCALER(1)	/* TCR1 prescaler = 1 (TCR1P='1-1') */
  | FS_ETPU_TCRCLK_MODE_INTEGRATION	/* TCRCLK signal is filtered using integration mode (TCRCF=1x) */
  | FS_ETPU_TCRCLK_INPUT_CHANCLOCK	/* TCRCLK signal is filtered with filter clock = channel filter clock (TCRCF=x1) */
  | FS_ETPU_TCR2CTL_DIV8	/* TCR2 source = etpuclk div 8 (TCR2CTL=4) */
  | FS_ETPU_TCR1CTL_DIV2	/* TCR1 source = etpuclk div 2 (TCR1CTL=2) */,

  /* etpu_config.stacr_a */
  FS_ETPU_TCR1_STAC_SERVER	/* TCR1 resource operates as server (RSC1=1) */
  | FS_ETPU_TCR2_STAC_SERVER	/* TCR2 resource operates as server (RSC2=1) */
  | FS_ETPU_TCR1_STAC_DISABLE	/* TCR1 operation on STAC bus disabled (REN1=0) */
  | FS_ETPU_TCR2_STAC_DISABLE	/* TCR2 operation on STAC bus disabled (REN2=0) */
  | FS_ETPU_TCR1_STAC_SRVSLOT(0)	/* TCR1 resource server slot = 0 (SRV1=0) */
  | FS_ETPU_TCR2_STAC_SRVSLOT(0)	/* TCR2 resource server slot = 0 (SRV2=0) */,

  /* etpu_config.ecr_b */
  _ENTRY_TABLE_BASE_ADDR_	/* entry table base address = shifted FS_ETPU_ENTRY_TABLE */
  | FS_ETPU_CHAN_FILTER_2SAMPLE	/* channel filter mode = two-sample mode (CDFC=0) */
  | FS_ETPU_ENGINE_ENABLE	/* engine is enabled (MDIS=0) */
  | FS_ETPU_FILTER_CLOCK_DIV2	/* channel filter clock = etpuclk div 2 (FPSCK=0) */,

  /* etpu_config.tbcr_b */
  FS_ETPU_ANGLE_MODE_DISABLE	/* TCR2 angle mode is disabled (AM=0) */
  | FS_ETPU_TCR2_PRESCALER(16)	/* TCR2 prescaler = 16 (TCR2P='16-1') */
  | FS_ETPU_TCR1_PRESCALER(1)	/* TCR1 prescaler = 1 (TCR1P='1-1') */
  | FS_ETPU_TCRCLK_MODE_INTEGRATION	/* TCRCLK signal is filtered using integration mode (TCRCF=1x) */
  | FS_ETPU_TCRCLK_INPUT_CHANCLOCK	/* TCRCLK signal is filtered with filter clock = channel filter clock (TCRCF=x1) */
  | FS_ETPU_TCR2CTL_DIV8	/* TCR2 source = etpuclk div 8 (TCR2CTL=4) */
  | FS_ETPU_TCR1CTL_DIV2	/* TCR1 source = etpuclk div 2 (TCR1CTL=2) */,

  /* etpu_config.stacr_b */
  FS_ETPU_TCR1_STAC_SERVER	/* TCR1 resource operates as server (RSC1=1) */
  | FS_ETPU_TCR2_STAC_SERVER	/* TCR2 resource operates as server (RSC2=1) */
  | FS_ETPU_TCR1_STAC_DISABLE	/* TCR1 operation on STAC bus disabled (REN1=0) */
  | FS_ETPU_TCR2_STAC_DISABLE	/* TCR2 operation on STAC bus disabled (REN2=0) */
  | FS_ETPU_TCR1_STAC_SRVSLOT(0)	/* TCR1 resource server slot = 0 (SRV1=0) */
  | FS_ETPU_TCR2_STAC_SRVSLOT(0)	/* TCR2 resource server slot = 0 (SRV2=0) */
};

#if defined(MPC5777C)
struct etpu_config_t my_etpu_c_config =
{
	/* etpu_config.mcr */
	FS_ETPU_VIS_OFF	/* SCM not visible (VIS=0) */
	| FS_ETPU_MISC_ENABLE	/* SCM operation enabled (SCMMISEN=1) */,

	/* etpu_config.misc */
	C_MISC_VALUE_,

	/* etpu_config.scmoff */
	C_SCM_OFF_OPCODE_,

	/* etpu_config.ecr_a */
	C_ENTRY_TABLE_BASE_ADDR_	/* entry table base address = shifted FS_ETPU_ENTRY_TABLE */
	| FS_ETPU_CHAN_FILTER_3SAMPLE	/* channel filter mode = three-sample mode (CDFC=2) */
	| FS_ETPU_ENGINE_ENABLE	/* engine is enabled (MDIS=0) */
	| FS_ETPU_FILTER_CLOCK_DIV16	/* channel filter clock = etpuclk div 16 (FPSCK=3) */,

	/* etpu_config.tbcr_a */
	FS_ETPU_ANGLE_MODE_DISABLE	/* TCR2 angle mode is disabled (AM=0) */
	| FS_ETPU_TCR2_PRESCALER(16)/* TCR2 prescaler = 16 (TCR2P='16-1') */
	| FS_ETPU_TCR1_PRESCALER(1)	/* TCR1 prescaler = 1 (TCR1P='1-1') */
	| FS_ETPU_TCRCLK_MODE_INTEGRATION	/* TCRCLK signal is filtered using integration mode (TCRCF=1x) */
	| FS_ETPU_TCR2CTL_DIV8	/* TCR2 source = etpuclk div 8 (TCR2CTL=4) */
	| FS_ETPU_TCRCLK_INPUT_CHANCLOCK	/* TCRCLK signal is filtered with filter clock = channel filter clock (TCRCF=x1) */
	| FS_ETPU_TCR1CTL_DIV2	/* TCR1 source = etpuclk div 2 (TCR1CTL=1, TCR1CS=0) */,

	/* etpu_config.stacr_a */
	FS_ETPU_TCR1_STAC_SERVER	/* TCR1 resource operates as server (RSC1=1) */
	| FS_ETPU_TCR2_STAC_SERVER	/* TCR2 resource operates as server (RSC2=1) */
	| FS_ETPU_TCR1_STAC_DISABLE	/* TCR1 operation on STAC bus disabled (REN1=0) */
	| FS_ETPU_TCR2_STAC_DISABLE	/* TCR2 operation on STAC bus disabled (REN2=0) */
	| FS_ETPU_TCR1_STAC_SRVSLOT(0)	/* TCR1 resource server slot = 0 (SRV1=0) */
	| FS_ETPU_TCR2_STAC_SRVSLOT(0)	/* TCR2 resource server slot = 0 (SRV2=0) */,
};
#endif

uint32_t *fs_etpu_free_param;
uint32_t *fs_etpu_c_free_param;

/* initialize the eTPU counter frequency variables */
uint32_t etpu_a_tcr1_freq = 132000000/2;
uint32_t etpu_a_tcr2_freq = 132000000/8/16;
uint32_t etpu_b_tcr1_freq = 132000000/2;
uint32_t etpu_b_tcr2_freq = 132000000/8/16;
uint32_t etpu_c_tcr1_freq = 132000000/2;
uint32_t etpu_c_tcr2_freq = 132000000/8/16;
