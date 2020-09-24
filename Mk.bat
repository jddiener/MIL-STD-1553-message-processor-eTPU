echo off
setlocal
rem Copyright ASH WARE, Inc, 2020.  All rights Reserved

echo ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
echo RUNNING:  %CD%\%0  AT  %TIME%
echo ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

rem --------- AshWare-Headquarters
set DEVTOOL=%TEST_BED_BIN_DIR%\DevTool.exe
if exist %DEVTOOL% goto FoundToolset
set DEVTOOL=..\..\..\Builds\DevTool.exe
if exist %DEVTOOL% goto FoundToolset

rem --------- Customer
set DEVTOOL=%DEV_TOOL_ETPU_BIN%\ETpuDevTool.exe
if exist %DEVTOOL% goto FoundToolSet

echo .
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
echo !!!  IN ONE OF THE ABOVE LINES (as appropriate)                                                          !!!
echo !!!  Modify the environment variable, DEVTOOL, to ASH WARE's tool location (or perform missing install)  !!!
echo !!!  Such as:                                                                                            !!!
echo !!!      SET DEVTOOL="\Program Files (x86)\ASH WARE\eTPU2p DevTool IDE V2_72C\ETpuDevTool.exe"           !!!
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
echo .
exit /b -1

:FoundToolset


goto skip_make
:skip_make


del Sim.log
pushd etpu_code
del *.elf *_defines.h *_idata.* *_scm.* *_struct.* *_ana.html *.map
popd

set BUILD_OPTIONS=-AutoBuild -IAcceptLicense -NoEnvFile -Minimize -lf5=Sim.Log -q

echo *************************
echo Building the code for module eTPU-AB
%DEVTOOL% -p=Proj.ETpuIdeProj %BUILD_OPTIONS% "-tn=BUILD ETPU CODE for eTPU-AB"
if  %ERRORLEVEL% NEQ 0 ( goto errors )
echo Building the code for module eTPU-C
%DEVTOOL% -p=Proj_C.ETpuIdeProj %BUILD_OPTIONS% "-tn=BUILD ETPU CODE for eTPU-C"
if  %ERRORLEVEL% NEQ 0 ( goto errors )

echo .
echo BUILD COMPLETED SUCCESSFULLY

goto end
:errors
echo *************************************************
echo        YIKES, WE GOT ERRORS!!
echo *************************************************
exit /b -1
:end
