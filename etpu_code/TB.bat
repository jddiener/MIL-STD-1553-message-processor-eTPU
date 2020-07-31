echo off
setlocal
Title Test Bed

echo FAIL > TestBed.result

set TEST_BED_BIN_DIR=c:\Temp\Mtdt_0\

set IS_SKIP_BRAZIL_TESTS=YES

call  Test.Bat
if  %ERRORLEVEL% NEQ 0 ( goto errors )

echo PASS > TestBed.result
goto end
:errors
echo *************************************************
echo        YIKES, WE GOT ERRORS!!
echo *************************************************
exit /b -1
:end
