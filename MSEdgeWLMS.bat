@echo off
goto check_Permissions

:check_Permissions
cls
echo So.. You wanna keep using that MSEdgeVM ? ;-)
echo Script made by jSacco juan.sacco@avast.com
echo #############################################
echo.
echo Detecting permissions... Please wait

net session >nul 2>&1
if %errorLevel% == 0 (
    echo Administrative permissions confirmed!
) else (
    echo Failure: Current permissions inadequate :-(
)
echo Press a key to continue execution !
pause >nul
sc delete WLMS
REG DELETE "HKLM\SYSTEM\CurrentControlSet\Services\WLMS" /f
echo Restart for the changes to take effect!
