echo off
setlocal
rem Copyright ASH WARE, Inc, 2011.  All rights Reserved

echo ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
echo RUNNING:  %CD%\%0  AT  %TIME%
echo ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

rem --------- AshWare-Headquarters
set DEVTOOL=..\ASHWARE\Builds\DevTool.exe
if exist ..\%DEVTOOL% goto FoundToolset

rem --------- Other users
set DEVTOOL=%DEV_TOOL_ETPU_BIN%\ETpuDevTool.exe
if exist %DEVTOOL% goto FoundToolset

echo .
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
echo !!!  IN ONE OF THE ABOVE LINES (as appropriate)                                                  !!!
echo !!!  Modify the environment variable, DEVTOOL, to ASH WARE's Simulator location                  !!!
echo !!!  Such as:                                                                                    !!!
echo !!!      SET DEVTOOL="\Program Files (x86)\ASH WARE\eTPU2p DevTool IDE V2_71A\ETpuDevTool.exe"   !!!
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
echo .
set errorlevel 1
goto :end

:FoundToolset

del *.report *.Coverage *.CoverageData *.TotalCoverageData

echo *************************
echo Testing, ...

set OPTIONS=-p=Proj.ETpuIdeProj -AutoRun -IAcceptLicense -NoBuild -NoEnvFile -Minimize -lf5=Sim.Log -q


goto StartHere
:StartHere

echo .
echo DEVTOOL: %DEVTOOL% 
echo .

echo ============================================================
echo Low-level RX tests
echo ============================================================

set TEST_NAME=RX : CORNER CASES
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS%  "-s=eTPU_A@@RX_TX_etpu_test\RX_CornerCasesTest.ETpuCommand"  "-v=eTPU_A@@common_test\NoWaveform.Vector"  "-tn=%TEST_NAME%"
popd
if  %ERRORLEVEL% NEQ 0 ( goto errors )

set TEST_NAME=RX : SEEK SYNCH
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS%  -s=eTPU_A@@RX_TX_etpu_test\RX_SeekSynchTest.ETpuCommand  -v=eTPU_A@@common_test\NoWaveform.Vector  "-tn=%TEST_NAME%"
popd
if  %ERRORLEVEL% NEQ 0 ( goto errors )

set TEST_NAME=RX : FAULTS
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS%  -s=eTPU_A@@RX_TX_etpu_test\RX_FaultTest.ETpuCommand  -v=eTPU_A@@common_test\NoWaveform.Vector  "-tn=%TEST_NAME%"
popd
if  %ERRORLEVEL% NEQ 0 ( goto errors )

set TEST_NAME=RX : DATA to DATA
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS%  -s=eTPU_A@@RX_TX_etpu_test\RX_DataToDataTest.ETpuCommand  -v=eTPU_A@@RX_TX_etpu_test\RX_DataToData.Vector  "-tn=%TEST_NAME%"
popd
if  %ERRORLEVEL% NEQ 0 ( goto errors )

set TEST_NAME=RX : SYNCH to DATA
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS%  -s=eTPU_A@@RX_TX_etpu_test\RX_SynchToDataTest.ETpuCommand  -v=eTPU_A@@RX_TX_etpu_test\RX_SynchToData.Vector  "-tn=%TEST_NAME%"
popd
if  %ERRORLEVEL% NEQ 0 ( goto errors )

set TEST_NAME=RX : PARITY to SYNCH
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS%  -s=eTPU_A@@RX_TX_etpu_test\RX_ParityToSynchTest.ETpuCommand  -v=eTPU_A@@RX_TX_etpu_test\RX_ParityToSynch.Vector  "-tn=%TEST_NAME%"
popd
if  %ERRORLEVEL% NEQ 0 ( goto errors )

set TEST_NAME=RX : PARITY to IDLE
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS%  -s=eTPU_A@@RX_TX_etpu_test\RX_ParityToIdleTest.ETpuCommand  -v=eTPU_A@@RX_TX_etpu_test\RX_ParityToIdle.Vector  "-tn=%TEST_NAME%"
popd
if  %ERRORLEVEL% NEQ 0 ( goto errors )

set TEST_NAME=RX : IDLE to SYNCH
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS%  -s=eTPU_A@@RX_TX_etpu_test\RX_IdleToSynchTest.ETpuCommand  -v=eTPU_A@@RX_TX_etpu_test\RX_IdleToSynch.Vector  "-tn=%TEST_NAME%"
popd
if  %ERRORLEVEL% NEQ 0 ( goto errors )

echo ============================================================
echo Low-level TX tests
echo ============================================================

set TEST_NAME=TX : ALL FUNCTIONALITY
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS% -s=eTPU_A@@RX_TX_etpu_test\TX_Test.ETpuCommand  -v=eTPU_A@@common_test\NoWaveform.Vector  "-tn=%TEST_NAME%"
popd
if  %ERRORLEVEL% NEQ 0 ( goto errors )

echo ============================================================
echo Low-level Coverage test
echo ============================================================

set TEST_NAME=RX TX Coverage
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS%  -s=eTPU_A@@RX_TX_etpu_test\RX_TX_CoverageTest.ETpuCommand  -v=eTPU_A@@common_test\NoWaveform.Vector  "-tn=%TEST_NAME%"
popd
if  %ERRORLEVEL% NEQ 0 ( goto errors )

rem goto skip_test_report
echo ============================================================
echo Generate Test Report
echo ============================================================
echo Building the test report
..\TestReportGenerator *.ETpuCommand
if  %ERRORLEVEL% NEQ 0 ( goto errors )
:skip_test_report

echo .
echo ALL  TESTS PASS

goto end
:errors
echo *************************************************
echo        YIKES, WE GOT ERRORS!!
echo *************************************************
exit /b -1
:end
