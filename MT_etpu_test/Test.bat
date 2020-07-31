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
echo MT protocol tests
echo ============================================================

set TEST_NAME=MT : MODE COMMAND FAULTS
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS% -s=eTPU_A@@MT_etpu_test\MT_ModeCommandFaults.ETpuCommand  -v=eTPU_A@@common_test\NoWaveform.Vector  "-tn=%TEST_NAME%"
popd
if  %ERRORLEVEL% NEQ 0 ( goto errors )

set TEST_NAME=MT : BC TO RT FAULTS
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS%  -s=eTPU_A@@MT_etpu_test\MT_BcToRtFaults.ETpuCommand  -v=eTPU_A@@common_test\NoWaveform.Vector  "-tn=%TEST_NAME%"
popd
if  %ERRORLEVEL% NEQ 0 ( goto errors )

set TEST_NAME=MT : RT TO BC FAULTS
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS%  -s=eTPU_A@@MT_etpu_test\MT_RtToBcFaults.ETpuCommand  -v=eTPU_A@@common_test\NoWaveform.Vector  "-tn=%TEST_NAME%"
popd
if  %ERRORLEVEL% NEQ 0 ( goto errors )

set TEST_NAME=MT : RT TO RT FAULTS
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS%  -s=eTPU_A@@MT_etpu_test\MT_RtToRtFaults.ETpuCommand  -v=eTPU_A@@common_test\NoWaveform.Vector  "-tn=%TEST_NAME%"
popd
if  %ERRORLEVEL% NEQ 0 ( goto errors )

set TEST_NAME=MT : FUNCTIONAL
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS%  -s=eTPU_A@@MT_etpu_test\MT_FunctionalTest.ETpuCommand  -v=eTPU_A@@common_test\NoWaveform.Vector  "-tn=%TEST_NAME%"
popd
if  %ERRORLEVEL% NEQ 0 ( goto errors )

set TEST_NAME=MT : FILTER FUNCTIONAL
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS%  -s=eTPU_A@@MT_etpu_test\MT_FilterTest.ETpuCommand  -v=eTPU_A@@common_test\NoWaveform.Vector  "-tn=%TEST_NAME%"
popd
if  %ERRORLEVEL% NEQ 0 ( goto errors )

echo ============================================================
echo MT Coverage test
echo ============================================================

set TEST_NAME=MT Coverage
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS%  -s=eTPU_A@@MT_etpu_test\MT_CoverageTest.ETpuCommand  -v=eTPU_A@@common_test\NoWaveform.Vector  "-tn=%TEST_NAME%"
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
