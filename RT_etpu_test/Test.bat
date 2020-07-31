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
echo RT protocol tests
echo ============================================================

set TEST_NAME=RT : BC TO RT FUNCTIONAL
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS% -s=eTPU_A@@RT_etpu_test\RT_BcToRt_Test.ETpuCommand  -v=eTPU_A@@common_test\NoWaveform.Vector  "-tn=%TEST_NAME%"
popd
if  %ERRORLEVEL% NEQ 0 ( goto errors )

set TEST_NAME=RT : RT TO BC FUNCTIONAL
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS% -s=eTPU_A@@RT_etpu_test\RT_RtToBc_Test.ETpuCommand  -v=eTPU_A@@common_test\NoWaveform.Vector  "-tn=%TEST_NAME%"
popd
if  %ERRORLEVEL% NEQ 0 ( goto errors )

set TEST_NAME=RT : RT TO RT FUNCTIONAL
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS% -s=eTPU_A@@RT_etpu_test\RT_RtToRt_Test.ETpuCommand  -v=eTPU_A@@common_test\NoWaveform.Vector  "-tn=%TEST_NAME%"
popd
if  %ERRORLEVEL% NEQ 0 ( goto errors )

set TEST_NAME=RT : MODE COMMAND FUNCTIONAL
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS% -s=eTPU_A@@RT_etpu_test\RT_ModeCommand_Test.ETpuCommand  -v=eTPU_A@@common_test\NoWaveform.Vector  "-tn=%TEST_NAME%"
popd
if  %ERRORLEVEL% NEQ 0 ( goto errors )

set TEST_NAME=RT : BC TO RT FAULTS
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS% -s=eTPU_A@@RT_etpu_test\RT_BcToRtFaults_Test.ETpuCommand  -v=eTPU_A@@common_test\NoWaveform.Vector  "-tn=%TEST_NAME%"
popd
if  %ERRORLEVEL% NEQ 0 ( goto errors )

set TEST_NAME=RT : RT TO BC FAULTS
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS% -s=eTPU_A@@RT_etpu_test\RT_RtToBcFaults_Test.ETpuCommand  -v=eTPU_A@@common_test\NoWaveform.Vector  "-tn=%TEST_NAME%"
popd
if  %ERRORLEVEL% NEQ 0 ( goto errors )

set TEST_NAME=RT : RT TO RT FAULTS
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS% -s=eTPU_A@@RT_etpu_test\RT_RtToRtFaults_Test.ETpuCommand  -v=eTPU_A@@common_test\NoWaveform.Vector  "-tn=%TEST_NAME%"
popd
if  %ERRORLEVEL% NEQ 0 ( goto errors )

set TEST_NAME=RT : MODE COMMAND FAULTS
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS% -s=eTPU_A@@RT_etpu_test\RT_ModeCommandFaults_Test.ETpuCommand  -v=eTPU_A@@common_test\NoWaveform.Vector  "-tn=%TEST_NAME%"
popd
if  %ERRORLEVEL% NEQ 0 ( goto errors )

set TEST_NAME=RT : DATA TRANSMIT INHIBIT
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS% -s=eTPU_A@@RT_etpu_test\RT_TxDataWordInhibit_Test.ETpuCommand  -v=eTPU_A@@common_test\NoWaveform.Vector  "-tn=%TEST_NAME%"
popd
if  %ERRORLEVEL% NEQ 0 ( goto errors )

set TEST_NAME=RT : TRANSMIT INHIBIT
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS% -s=eTPU_A@@RT_etpu_test\RT_TxInhibit_Test.ETpuCommand  -v=eTPU_A@@common_test\NoWaveform.Vector  "-tn=%TEST_NAME%"
popd
if  %ERRORLEVEL% NEQ 0 ( goto errors )

echo ============================================================
echo RX Coverage test
echo ============================================================

set TEST_NAME=RT Coverage
echo Running  "%TEST_NAME%"  test
pushd ..
%DEVTOOL% %OPTIONS%  -s=eTPU_A@@RT_etpu_test\RT_CoverageTest.ETpuCommand  -v=eTPU_A@@common_test\NoWaveform.Vector  "-tn=%TEST_NAME%"
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
