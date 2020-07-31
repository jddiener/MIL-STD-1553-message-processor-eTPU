/*******************************************************************************
 * FILE NAME: Tester.c                Copyright (C) 2020 ASH WARE, Inc.        *
 *                                                                             *
 * DESCRIPTION:  eTPU C Tester code for testing timing corner cases            *
 *                                                                             *
 ******************************************************************************/
 
#include <ETpu_Std.h>
#include "etpu_tester_common.h"

#pragma ETPU_function Tester;

void Tester ( int linkToChanNum,
			  int24 LatencyStart, int24 LatencyDuration, int24 LatencyPeriod,
			  int EncodedForcedState )
{
	static int24 latencyTimeStamp;
	int tempEncodedForcedState;
	
	if ( IsHostServiceRequestEvent(AW_TESTER_LINK_HSR) )
	{
		LinkTo( (unsigned int8) linkToChanNum );
	}
	else if ( IsHostServiceRequestEvent(AW_TESTER_LATENCY_HSR) )
	{
		ActionUnitA( MatchTCR1, CaptureTCR1, GreaterEqual );
		ActionUnitB( MatchTCR1, CaptureTCR1, GreaterEqual );
		EitherMatchNonBlockingSingleTransition();
		EnableMatchAndTransitionEventHandling();

		ClrFlag0();

		latencyTimeStamp = tcr1 + LatencyStart;
		ertA = latencyTimeStamp;
		ertB = ertA + LatencyDuration;
		WriteErtAToMatchAAndEnable();
		WriteErtBToMatchBAndEnable();
		latencyTimeStamp = ertA;
	}
	else if ( IsHostServiceRequestEvent(AW_TESTER_WR_FLAGS_HSR) )
	{
		chan = (unsigned int8) linkToChanNum;
		Set( flag0 );
	}

	else if ( IsHostServiceRequestEvent(AW_TESTER_FORCE_STATE_HSR) )
	{
		tempEncodedForcedState = EncodedForcedState;
		chan = (unsigned int8) linkToChanNum;

		EnableMatchAndTransitionEventHandling();
		DisableMatchDetection();
		ClearMatchALatch();
		ClearMatchBLatch();

		// Match A ...
		if( (tempEncodedForcedState & (1<<AW_TESTER_FORCE_MATCH_A))
								   == (1<<AW_TESTER_FORCE_MATCH_A) )
		{
			ertA = tcr1;
			WriteErtAToMatchAAndEnable();
			ertA = tcr2;
			WriteErtAToMatchAAndEnable();
		}

		// Match B ...
		if( (tempEncodedForcedState & (1<<AW_TESTER_FORCE_MATCH_B))
								   == (1<<AW_TESTER_FORCE_MATCH_B) )
		{
			ertB = tcr1;
			WriteErtBToMatchBAndEnable();
			ertB = tcr2;
			WriteErtBToMatchBAndEnable();
		}

		// Flag 1
		ClrFlag1();
		if( (tempEncodedForcedState & (1<<AW_TESTER_FORCE_SET_FLAG1))
								   == (1<<AW_TESTER_FORCE_SET_FLAG1) )
		{
			SetFlag1();
		}

		// Flag 0
		ClrFlag0();
		if( (tempEncodedForcedState & (1<<AW_TESTER_FORCE_SET_FLAG0))
								   == (1<<AW_TESTER_FORCE_SET_FLAG0) )
		{
			SetFlag0();
		}
	}

	else if ( IsMatchAEvent() && (flag0==0) )
	{
		int tempChan;

		latencyTimeStamp = latencyTimeStamp + LatencyPeriod;

		while( channel.MRLB==0 )
		{
			tempChan = chan;
			chan = (unsigned int8) tempChan;
		}
		ClearMatchALatch();
		ClearMatchBLatch();
		if( LatencyPeriod > 0)
		{
			ertA = latencyTimeStamp;
			ertB = ertA + LatencyDuration;
			WriteErtAToMatchAAndEnable();
			WriteErtBToMatchBAndEnable();
		}

	}

	else
	{
		NOP();
	}
}


#pragma write h, (::ETPUfilename (etpu_tester_auto.h));
#pragma write h, (#ifndef  __TESTER_CPU_H__ );
#pragma write h, (#define  __TESTER_CPU_H__ );
#pragma write h, ( );
#pragma write h, (::ETPUliteral(#define _FUNCTION_NUM_Tester_)          ::ETPUfunctionnumber(Tester));
#pragma write h, (::ETPUliteral(#define _ENTRY_TABLE_TYPE_Tester_)             ::ETPUentrytype(Tester) );
#pragma write h, (::ETPUliteral(#define _FRAME_SIZE_Tester_)               ::ETPUram(Tester) );
#pragma write h, (::ETPUliteral(//) Function Variable Offsetts );
#pragma write h, (::ETPUliteral(#define _CPBA24_Tester_linkToChanNum_)  ::ETPUlocation(Tester,linkToChanNum));
#pragma write h, (::ETPUliteral(#define _CPBA24_Tester_LatencyStart_)     ::ETPUlocation(Tester,LatencyStart));
#pragma write h, (::ETPUliteral(#define _CPBA24_Tester_LatencyDuration_)  ::ETPUlocation(Tester,LatencyDuration));
#pragma write h, (::ETPUliteral(#define _CPBA24_Tester_LatencyPeriod_)    ::ETPUlocation(Tester,LatencyPeriod));
#pragma write h, (::ETPUliteral(#define _CPBA24_Tester_EncodedForcedState_)      ::ETPUlocation(Tester,EncodedForcedState));
#pragma write h, ( );
#pragma write h, (#endif // __TESTER_CPU_H__ );

