/* 
Antidebugging Breakpoints IDC script for IDA PRO by JSacco v0.2
How to use? Open IDA Pro, press shift+F2 paste the code and run.
Last modification date: 2021216
*/
#include <idc.idc>

static main() 
{
    // Trace everything in the cosmos? ( Not recommended )
    auto trace_kernel32 = 1; // (1) Enabled
    auto trace_ntdll = 0;    // (0) Disabled
    auto trace_user32 = 0;   // (0) Disabled
    
    // Autorun ?
    // RunTo(BeginEA());
    // GetDebuggerEvent(WFNE_SUSP, -1);
    
    if (get_process_state() == 0){
        warning("Ooops! Antidebugging breakpoints cannot be configured\n\nNo process is currently debugged..");
        return;
    }
    if (get_process_state() != -1){
        warning("Ooops! Antidebugging breakpoints cannot be configured\n\nPlease suspend the debugger first..");
        return;
    }
    
    Message("[?] API - Antidebugging Breakpoints for IDA PRO by jSacco <jsacco@exploitpack.com>\n");
    Message("[?] Based on the \"Ultimate\" Antidebugging-Reference by Peter Ferrie\n");
    Message("[?] Breakpoints properties: Trace on - enabled [ No-Break ]\n\n");
    
    if (trace_kernel32){
        kernel32_brk();
    }
    
    if (trace_ntdll){
        ntdll_brk();
    }

    if (trace_user32){
        user32_brk();
    }  
}

static kernel32_brk()
{
    // KERNEL32
    auto addr1 = LocByName("kernel32_CheckRemoteDebuggerPresent");
    auto addr2 = LocByName("kernel32_CreateToolhelp32Snapshot");
    auto addr3 = LocByName("kernel32_IsDebuggerPresent");
    auto addr4 = LocByName("kernel32_SuspendThread");
    auto addr5 = LocByName("kernel32_QueueUserAPC");
    auto addr6 = LocByName("kernel32_CreateProcessA");
    auto addr7 = LocByName("kernel32_CreateThread");
    auto addr8 = LocByName("kernel32_DebugActiveProcess");
    auto addr9 = LocByName("kernel32_RaiseException");
    auto addr10 = LocByName("kernel32_WriteProcessMemory");
    auto addr11 = LocByName("kernel32_CloseHandle");
    auto addr12 = LocByName("kernel32_LoadLibraryA");
    auto addr13 = LocByName("kernel32_LoadLibraryExA");
    auto addr14 = LocByName("kernel32_ReadFile");
    auto addr15 = LocByName("kernel32_GetLocalTime");
    auto addr16 = LocByName("kernel32_GetSystemTime");
    auto addr17 = LocByName("kernel32_GetTickCount");
    auto addr18 = LocByName("kernel32_timeGetTime");
    auto addr19 = LocByName("kernel32_QueryPerformanceCounter");
    auto addr20 = LocByName("kernel32_SwitchToThread");
    auto addr21 = LocByName("kernel32_Toolhelp32ReadProcessMemory");
    auto addr22 = LocByName("kernel32_UnhandledExceptionFilter");
    auto addr23 = LocByName("kernel32_VirtualProtect");
    auto addr24 = LocByName("kernel32_VirtualProtectEx");

	if (addr1 != BADADDR){
		Message("[*] Kernel32 CheckRemoteDebuggerPresent at address, breakpoint set %x\n", addr1);
		AddBpt(addr1);
		SetBptAttr(addr1, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr1, "Message(\"[!] ANTI-DBG TRIGGERED - kernel32_CheckRemoteDebuggerPresent: The kernel32 CheckRemoteDebuggerPresent function was introduced in Windows XP SP1 to query a value that has existed since Windows NT. Remote in this sense refers to a separate process on the same machine.\\n\")");

		// Add runtime patching here if necessary
		// PatchDword(addr1, 0x8B55FF8B);
		// PatchDword(addr1 + 4, 0x0C458BEC);
		// PatchDword(addr1 + 8, 0x008F006A);
		// PatchDword(addr1 + 12, 0xC25DC033);
		// PatchWord(addr1 + 16, 0x0008); 
	}
	
    if (addr2 != BADADDR){
		Message("[*] Kernel32 CreateToolhelp32Snapshot at address, breakpoint set %x\n", addr2);
		AddBpt(addr2);
		SetBptAttr(addr2, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr2, "Message(\"[!] ANTI-DBG TRIGGERED - kernel32_CreateToolhelp32Snapshot: The process ID of both Explorer.exe and the parent process of the current process, and the name of that parent process, can be obtained by the kernel32 CreateToolhelp32Snapshot() function and a kernel32 Process32Next() function enumeration.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr3 != BADADDR){
		Message("[*] Kernel32 IsDebuggerPresent at address, breakpoint set %x\n", addr3);
		AddBpt(addr3);
		SetBptAttr(addr3, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr3, "Message(\"[!] ANTI-DBG TRIGGERED - kernel32_IsDebuggerPresent: The kernel32 IsDebuggerPresent() function was introduced in Windows 95. It returns a non-zero value if a debugger is present.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr4 != BADADDR){
		Message("[*] Kernel32 SuspendThread at address, breakpoint set %x\n", addr4);
		AddBpt(addr4);
		SetBptAttr(addr4, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr4, "Message(\"[!] ANTI-DBG TRIGGERED - kernel32_SuspendThread: The kernel32 SuspendThread() function can be another very effective way to disable user-mode debuggers. This can be achieved by enumerating the threads of a given process, or searching for a named window and opening its owner thread, and then suspending that thread.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr5 != BADADDR){
		Message("[*] Kernel32 QueueUserAPC at address, breakpoint set %x\n", addr5);
		AddBpt(addr5);
		SetBptAttr(addr5, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr5, "Message(\"[!] ANTI-DBG TRIGGERED - kernel32_QueueUserAPC: The kernel32 QueueUserAPC() function can be used to register Asynchronous Procedure Calls (APCs). Asynchronous Procedure Calls are functions that are called when the associated thread enters an alertable state, such as by calling the kernel32 Sleep() function. \\n\")");

		// Add runtime patching here if necessary
	}

	if (addr6 != BADADDR){
		Message("[*] Kernel32 CreateProcessA at address, breakpoint set %x\n", addr6);
		AddBpt(addr6);
		SetBptAttr(addr6, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr6, "Message(\"[!] ANTI-DBG TRIGGERED - kernel32_CreateProcessA: Creates a new process and its primary thread. The new process runs in the security context of the calling process.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr7 != BADADDR){
		Message("[*] Kernel32 CreateThread at address, breakpoint set %x\n", addr7);
		AddBpt(addr7);
		SetBptAttr(addr7, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr7, "Message(\"[!] ANTI-DBG TRIGGERED - kernel32_CreateThread: Threads are a simple way for the debuggee to transfer control to a memory location where execution can resume freely, unless a breakpoint is placed at the appropriate location. They can also be used to interfere with the execution of the other threads (including the main thread), and thus interfere with debugging. \\n\")");

		// Add runtime patching here if necessary
	}

	if (addr8 != BADADDR){
		Message("[*] Kernel32 DebugActiveProcess at address, breakpoint set %x\n", addr8);
		AddBpt(addr8);
		SetBptAttr(addr8, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr8, "Message(\"[!] ANTI-DBG TRIGGERED - kernel32_DebugActiveProcess: The kernel32 DebugActiveProcess() function can be used to attach as a debugger to an already running process. Since only one debugger can be attached to a process at a time, a failure to attach to the process might indicate the presence of anotherdebugger. \\n\")");

		// Add runtime patching here if necessary
	}

	if (addr9 != BADADDR){
		Message("[*] Kernel32 RaiseException at address, breakpoint set %x\n", addr9);
		AddBpt(addr9);
		SetBptAttr(addr9, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr9, "Message(\"[!] ANTI-DBG TRIGGERED - kernel32_RaiseException: The kernel32 RaiseException() function can be used to force certain exceptions to occur, which includes exceptions that a debugger would normally consume.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr10 != BADADDR){
		Message("[*] Kernel32 WriteProcessMemory at address, breakpoint set %x\n", addr10);
		AddBpt(addr10);
		SetBptAttr(addr10, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr10, "Message(\"[!] ANTI-DBG TRIGGERED - kernel32_WriteProcessMemory: The kernel32 WriteProcessMemory() function can be used to perform self-modification of the code stream, by reading file content to a location after the call to the function.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr11 != BADADDR){
		Message("[*] Kernel32 CloseHandle at address, breakpoint set %x\n", addr11);
		AddBpt(addr11);
		SetBptAttr(addr11, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr11, "Message(\"[!] ANTI-DBG TRIGGERED - kernel32_CloseHandle: One well-known technique for detecting a debugger involves the kernel32 CloseHandle() function. If an invalid handle is passed to the kernel32 CloseHandle() function and a debugger is present, then an EXCEPTION_INVALID_HANDLE (0xC0000008) exception will be raised.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr12 != BADADDR){
		Message("[*] Kernel32 LoadLibraryA at address, breakpoint set %x\n", addr12);
		AddBpt(addr12);
		SetBptAttr(addr12, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr12, "Message(\"[!] ANTI-DBG TRIGGERED - kernel32_LoadLibraryA: The kernel32 LoadLibrary() function is a surprisingly simple and effective way to detect a debugger. When a file is loaded in the presence of a debugger, using the kernel32 LoadLibrary() function, a handle to the file is opened. This allows the debugger to read the debug information from the file (assuming that it is present).\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr13 != BADADDR){
		Message("[*] Kernel32 LoadLibraryExA at address, breakpoint set %x\n", addr13);
		AddBpt(addr13);
		SetBptAttr(addr13, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr13, "Message(\"[!] ANTI-DBG TRIGGERED - kernel32_LoadLibraryExA: The kernel32 LoadLibraryExA() function is a surprisingly simple and effective way to detect a debugger. When a file is loaded in the presence of a debugger, using the kernel32 LoadLibrary() function, a handle to the file is opened. This allows the debugger to read the debug information from the file (assuming that it is present).\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr14 != BADADDR){
		Message("[*] Kernel32 ReadFile at address, breakpoint set %x\n", addr14);
		AddBpt(addr14);
		SetBptAttr(addr14, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr14, "Message(\"[!] ANTI-DBG TRIGGERED - kernel32_ReadFile: The kernel32 ReadFile() function can be used to perform self-modification of the code stream, by reading file content to a location after the call to the function.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr15 != BADADDR){
		Message("[*] Kernel32 GetLocalTime at address, breakpoint set %x\n", addr15);
		AddBpt(addr15);
		SetBptAttr(addr15, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr15, "Message(\"[!] ANTI-DBG TRIGGERED - kernel32_GetLocalTime: When a debugger is present, and used to single-step through the code, there is a significant delay between the executions of the individual instructions, when compared to native execution. This delay can be measured using one of several possible time sources.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr16 != BADADDR){
		Message("[*] Kernel32 GetSystemTime at address, breakpoint set %x\n", addr16);
		AddBpt(addr16);
		SetBptAttr(addr16, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr16, "Message(\"[!] ANTI-DBG TRIGGERED - kernel32_GetSystemTime: When a debugger is present, and used to single-step through the code, there is a significant delay between the executions of the individual instructions, when compared to native execution. This delay can be measured using one of several possible time sources.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr17 != BADADDR){
		Message("[*] Kernel32 GetTickCount at address, breakpoint set %x\n", addr17);
		AddBpt(addr17);
		SetBptAttr(addr17, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr17, "Message(\"[!] ANTI-DBG TRIGGERED - kernel32_GetTickCount: When a debugger is present, and used to single-step through the code, there is a significant delay between the executions of the individual instructions, when compared to native execution. This delay can be measured using one of several possible time sources.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr18 != BADADDR){
		Message("[*] Kernel32 timeGetTime at address, breakpoint set %x\n", addr18);
		AddBpt(addr18);
		SetBptAttr(addr18, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr18, "Message(\"[!] ANTI-DBG TRIGGERED - kernel32_timeGetTime: When a debugger is present, and used to single-step through the code, there is a significant delay between the executions of the individual instructions, when compared to native execution. This delay can be measured using one of several possible time sources.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr19 != BADADDR){
		Message("[*] Kernel32 QueryPerformanceCounter at address, breakpoint set %x\n", addr19);
		AddBpt(addr19);
		SetBptAttr(addr19, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr19, "Message(\"[!] ANTI-DBG TRIGGERED - kernel32_QueryPerformanceCounter: When a debugger is present, and used to single-step through the code, there is a significant delay between the executions of the individual instructions, when compared to native execution. This delay can be measured using one of several possible time sources.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr20 != BADADDR){
		Message("[*] Kernel32 SwitchToThread at address, breakpoint set %x\n", addr20);
		AddBpt(addr20);
		SetBptAttr(addr20, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr20, "Message(\"[!] ANTI-DBG TRIGGERED - kernel32_SwitchToThread: The kernel32 SwitchToThread() function allows the current thread to offer to give up the rest of its time slice. When an application is being debugged, the act of single-stepping through the code causes debug events and often results in no yield being allowed.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr21 != BADADDR){
		Message("[*] Kernel32 Toolhelp32ReadProcessMemory at address, breakpoint set %x\n", addr21);
		AddBpt(addr21);
		SetBptAttr(addr21, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr21, "Message(\"[!] ANTI-DBG TRIGGERED - kernel32_Toolhelp32ReadProcessMemory: The kernel32 Toolhelp32ReadProcessMemory() allows one process to open and read the memory of another process.  This function can be used as another way to detect a step-over condition, by checking for a breakpoint after the function call.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr22 != BADADDR){
		Message("[*] Kernel32 UnhandledExceptionFilter at address, breakpoint set %x\n", addr22);
		AddBpt(addr22);
		SetBptAttr(addr22, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr22, "Message(\"[!] ANTI-DBG TRIGGERED - kernel32_UnhandledExceptionFilter: When an exception occurs, and no registered Exception Handlers exist (neither Structured nor Vectored), or if none of the registered handlers handles the exception, then the kernel32 UnhandledExceptionFilter() function will be called as a last resort. If a debugger is present, then that call will not be reached.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr23 != BADADDR){
		Message("[*] Kernel32 VirtualProtect at address, breakpoint set %x\n", addr23);
		AddBpt(addr23);
		SetBptAttr(addr23, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr23, "Message(\"[!] ANTI-DBG TRIGGERED - kernel32_VirtualProtect: The kernel32 VirtualProtect() can be used to allocate guard pages. Guard pages are pages that trigger an exception the first time that they are accessed. Guard pages can also be used to detect a debugger. \\n\")");

		// Add runtime patching here if necessary
	}

	if (addr24 != BADADDR){
		Message("[*] Kernel32 VirtualProtectEx at address, breakpoint set %x\n", addr24);
		AddBpt(addr24);
		SetBptAttr(addr24, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr24, "Message(\"[!] ANTI-DBG TRIGGERED - kernel32_Vkernel32_VirtualProtectEx: The kernel32 VirtualProtectEx() can be used to allocate guard pages. Guard pages are pages that trigger an exception the first time that they are accessed. Guard pages can also be used to detect a debugger.\\n\")");

		// Add runtime patching here if necessary
	}
}

static ntdll_brk()
{
    // NTDLL
    auto addr25 = LocByName("ntdll_NtQueryInformationProcess");
    auto addr26 = LocByName("ntdll_RtlQueryProcessHeapInformation");
    auto addr27 = LocByName("ntdll_RtlQueryProcessDebugInformation");
    auto addr28 = LocByName("ntdll_NtYieldExecution");
    auto addr29 = LocByName("ntdll_NtProtectVirtualMemory");
    auto addr30 = LocByName("ntdll_NtSetInformationThread");
    auto addr31 = LocByName("ntdll_DbgUiDebugActiveProcess");
    auto addr32 = LocByName("ntdll_NtDebugActiveProcess");
    auto addr33 = LocByName("ntdll_NtSetInformationProcess");
    auto addr34 = LocByName("ntdll_NtQueryObject");
    auto addr35 = LocByName("ntdll_NtQuerySystemInformation");
    auto addr36 = LocByName("ntdll_NtSetLdtEntries");
    auto addr37 = LocByName("ntdll_NtQueueApcThread");
    auto addr38 = LocByName("ntdll_NtRaiseException");
    auto addr39 = LocByName("ntdll_RtlRaiseException");
    auto addr40 = LocByName("ntdll_RtlProcessFlsData");
    auto addr41 = LocByName("ntdll_DbgPrint");
    auto addr42 = LocByName("ntdll_DbgSetDebugFilterState");
    auto addr43 = LocByName("ntdll_DbgBreakPoint");
    auto addr44 = LocByName("ntdll_NtSuspendThread");
    auto addr45 = LocByName("ntdll_NtWriteVirtualMemory");
    auto addr46 = LocByName("ntdll_NtClose");
    auto addr47 = LocByName("ntdll_LdrLoadDll");
    
	if (addr25 != BADADDR){
		Message("[*] NTDLL NtQueryInformationProcess at address, breakpoint set %x\n", addr25);
		AddBpt(addr25);
		SetBptAttr(addr25, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr25, "Message(\"[!] ANTI-DBG TRIGGERED - ntdll_NtQueryInformationProcess: The ntdll NtQueryInformationProcess() function accepts a parameter which is the class of information to query. The return value is 0xffffffff if the process is being debugged. \\n\")");

		// Add runtime patching here if necessary
	}

	if (addr26 != BADADDR){
		Message("[*] NTDLL RtlQueryProcessHeapInformation at address, breakpoint set %x\n", addr26);
		AddBpt(addr26);
		SetBptAttr(addr26, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr26, "Message(\"[!] ANTI-DBG TRIGGERED - ntdll_RtlQueryProcessHeapInformation: The ntdll RtlQueryProcessHeapInformation() function can be used to read the heap flags from the process memory of the current process.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr27 != BADADDR){
		Message("[*] NTDLL RtlQueryProcessDebugInformation at address, breakpoint set %x\n", addr27);
		AddBpt(addr27);
		SetBptAttr(addr27, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr27, "Message(\"[!] ANTI-DBG TRIGGERED - ntdll_RtlQueryProcessDebugInformation: The ntdll RtlQueryProcessDebugInformation() function can be used to read certain fields from the process memory of the requested process, including the heap flags. \\n\")");

		// Add runtime patching here if necessary
	}

	if (addr28 != BADADDR){
		Message("[*] NTDLL NtYieldExecution at address, breakpoint set %x\n", addr28);
		AddBpt(addr28);
		SetBptAttr(addr28, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr28, "Message(\"[!] ANTI-DBG TRIGGERED - ntdll_NtYieldExecution: The NTDLL NtYieldExecution() function allows the current thread to offer to give up the rest of its time slice. When an application is being debugged, the act of single-stepping through the code causes debug events and often results in no yield being allowed.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr29 != BADADDR){
		Message("[*] NTDLL NtProtectVirtualMemory at address, breakpoint set %x\n", addr29);
		AddBpt(addr29);
		SetBptAttr(addr29, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr29, "Message(\"[!] ANTI-DBG TRIGGERED - ntdll_NtProtectVirtualMemory: The kernel32 NtProtectVirtualMemory() can be used to allocate guard pages. Guard pages are pages that trigger an exception the first time that they are accessed. Guard pages can also be used to detect a debugger.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr30 != BADADDR){
		Message("[*] NTDLL NtSetInformationThread at address, breakpoint set %x\n", addr30);
		AddBpt(addr30);
		SetBptAttr(addr30, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr30, "Message(\"[!] ANTI-DBG TRIGGERED - ntdll_NtSetInformationThread: Windows 2000 introduced a function extension which, at first glance, might appear to exist only for anti-debugging purposes. It is the ThreadHideFromDebugger (0x11) member of the ThreadInformationClass class. It can be set on a per-thread basis by calling the ntdll NtSetInformationThread() function.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr31 != BADADDR){
		Message("[*] NTDLL DbgUiDebugActiveProcess at address, breakpoint set %x\n", addr31);
		AddBpt(addr31);
		SetBptAttr(addr31, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr31, "Message(\"[!] ANTI-DBG TRIGGERED - ntdll_DbgUiDebugActiveProcess: The kernel32 DbgUiDebugActiveProcess() can be used to attach as a debugger to an already running process. Since only one debugger can be attached to a process at a time, a failure to attach to the process might indicate the presence of anotherdebugger. \\n\")");

		// Add runtime patching here if necessary
	}

	if (addr32 != BADADDR){
		Message("[*] NTDLL NtDebugActiveProcess at address, breakpoint set %x\n", addr32);
		AddBpt(addr32);
		SetBptAttr(addr32, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr32, "Message(\"[!] ANTI-DBG TRIGGERED - ntdll_NtDebugActiveProcess: The kernel32 NtDebugActiveProcess() can be used to attach as a debugger to an already running process. Since only one debugger can be attached to a process at a time, a failure to attach to the process might indicate the presence of anotherdebugger. \\n\")");

		// Add runtime patching here if necessary
	}

	if (addr33 != BADADDR){
		Message("[*] NTDLL NtSetInformationProcess at address, breakpoint set %x\n", addr33);
		AddBpt(addr33);
		SetBptAttr(addr33, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr33, "Message(\"[!] ANTI-DBG TRIGGERED - ntdll_NtSetInformationProcess: Perhaps because the value of the Local Descriptor Table (LDT) register is zero in user-mode in a physical (as opposed to a virtual) Windows environment, it is generally not supported properly (or at all) by debuggers. As a result, it can be used as a simple anti-debugger technique.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr34 != BADADDR){
		Message("[*] NTDLL NtQueryObject at address, breakpoint set %x\n", addr34);
		AddBpt(addr34);
		SetBptAttr(addr34, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr34, "Message(\"[!] ANTI-DBG TRIGGERED - ntdll_NtQueryObject: Windows XP introduced a debug object. When a debugging session begins, a debug object is created, and a handle is associated with it. Using the ntdll NtQueryObject() function, it is possible to query for the list of existing objects, and check the number of handles associated with any debug objectthat exists.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr35 != BADADDR){
		Message("[*] NTDLL NtQuerySystemInformation at address, breakpoint set %x\n", addr35);
		AddBpt(addr35);
		SetBptAttr(addr35, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr35, "Message(\"[!] ANTI-DBG TRIGGERED - ntdll_NtQuerySystemInformation: The ntdll NtQuerySystemInformation() function accepts a parameter which is the class of information to query. Most of the classes are not documented. This includes the SystemKernelDebuggerInformation (0x23) class, which has existed since Windows NT. The SystemKernelDebuggerInformation class returns the value of two flags: KdDebuggerEnabled in al, and KdDebuggerNotPresent in ah. Thus, the return value in ah is zero if a debugger is present. \\n\")");

		// Add runtime patching here if necessary
	}

	if (addr36 != BADADDR){
		Message("[*] NTDLL NtSetLdtEntries at address, breakpoint set %x\n", addr36);
		AddBpt(addr36);
		SetBptAttr(addr36, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr36, "Message(\"[!] ANTI-DBG TRIGGERED - ntdll_NtSetLdtEntries: The ntdll NtSetLdtEntries() function also allows setting the Local Descriptor Table values directly, but only for the current process. It is an entirely separate function with a slightly different parameter format compared to the ProcessLdtInformation technique.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr37 != BADADDR){
		Message("[*] NTDLL NtQueueApcThread at address, breakpoint set %x\n", addr37);
		AddBpt(addr37);
		SetBptAttr(addr37, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr37, "Message(\"[!] ANTI-DBG TRIGGERED - ntdll_NtQueueApcThread: The ntdll NtQueueApcThread() function can be used to register Asynchronous Procedure Calls (APCs). Asynchronous Procedure Calls are functions that are called when the associated thread enters an alertable state, such as by calling the kernel32 Sleep() function. \\n\")");

		// Add runtime patching here if necessary
	}

	if (addr38 != BADADDR){
		Message("[*] NTDLL NtRaiseException at address, breakpoint set %x\n", addr38);
		AddBpt(addr38);
		SetBptAttr(addr38, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr38, "Message(\"[!] ANTI-DBG TRIGGERED - ntdll_NtRaiseException: The ntdll NtRaiseException() function can be used to force certain exceptions to occur, which includes exceptions that a debugger would normally consume. \\n\")");

		// Add runtime patching here if necessary
	}

	if (addr39 != BADADDR){
		Message("[*] NTDLL RtlRaiseException at address, breakpoint set %x\n", addr39);
		AddBpt(addr39);
		SetBptAttr(addr39, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr39, "Message(\"[!] ANTI-DBG TRIGGERED - ntdll_RtlRaiseException: The ntdll RtlRaiseException() function can be used to force certain exceptions to occur, which includes exceptions that a debugger would normally consume. \\n\")");

		// Add runtime patching here if necessary
	}

	if (addr40 != BADADDR){
		Message("[*] NTDLL RtlProcessFlsData at address, breakpoint set %x\n", addr40);
		AddBpt(addr40);
		SetBptAttr(addr40, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr40, "Message(\"[!] ANTI-DBG TRIGGERED - ntdll_RtlProcessFlsData: The ntdll RtlProcessFlsData() function is an undocumented function When called with the appropriate parameter and memory values, the function will execute code at a user-specified pointer in memory. If a debugger is unaware of this fact, then execution control might be lost.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr41 != BADADDR){
		Message("[*] Ntdll DbgPrint at address, breakpoint set %x\n", addr41);
		AddBpt(addr41);
		SetBptAttr(addr41, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr41, "Message(\"[!] ANTI-DBG TRIGGERED - ntdll_DbgPrint: Normally, the ntdll DbgPrint() function raises an exception, but a registered Structured Exception Handler will not see it.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr42 != BADADDR){
		Message("[*] Ntdll DbgSetDebugFilterState at address, breakpoint set %x\n", addr42);
		AddBpt(addr42);
		SetBptAttr(addr42, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr42, "Message(\"[!] ANTI-DBG TRIGGERED - ntdll_DbgSetDebugFilterState: The ntdll DbgSetDebugFilterState() function (or the ntdll NtSetDebugFilterState() function, both introduced in Windows XP) cannot be used to detect the presence of a debugger.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr43 != BADADDR){
		Message("[*] Ntdll DbgBreakPoint at address, breakpoint set %x\n", addr43);
		AddBpt(addr43);
		SetBptAttr(addr43, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr43, "Message(\"[!] ANTI-DBG TRIGGERED - ntdll_DbgBreakPoint: The ntdll DbgBreakPoint() function is called when a debugger attaches to an already-running process. The function allows the debugger to gain control because an exception is raised that the debugger can intercept.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr44 != BADADDR){
		Message("[*] NTDLL NtSuspendThread at address, breakpoint set %x\n", addr44);
		AddBpt(addr44);
		SetBptAttr(addr44, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr44, "Message(\"[!] ANTI-DBG TRIGGERED - ntdll_NtSuspendThread:  The ntdll NtSuspendThread() function can be another very effective way to disable user-mode debuggers. This can be achieved by enumerating the threads of a given process, or searching for a named window and opening its owner thread, and then suspending that thread.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr45 != BADADDR){
		Message("[*] NTDLL NtWriteVirtualMemory at address, breakpoint set %x\n", addr45);
		AddBpt(addr45);
		SetBptAttr(addr45, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr45, "Message(\"[!] ANTI-DBG TRIGGERED - ntdll_NtWriteVirtualMemory: The ntdll NtWriteVirtualMemory() function can be used to perform self-modification of the code stream, by reading file content to a location after the call to the function.\\n\")");

		// Add runtime patching here if necessary
	}

	if (addr46 != BADADDR){
		Message("[*] NTDLL NtClose at address, breakpoint set %x\n", addr46);
		AddBpt(addr46);
		SetBptAttr(addr46, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr46, "Message(\"[!] ANTI-DBG TRIGGERED - ntdll_NtClose: If an invalid handle is passed to the CloseHandle() function and a debugger is present, then an EXCEPTION_INVALID_HANDLE (0xC0000008) exception will be raised. \\n\")");

		// Add runtime patching here if necessary
	}

	if (addr47 != BADADDR){
		Message("[*] NTDLL LdrLoadDll at address, breakpoint set %x\n", addr47);
		AddBpt(addr47);
		SetBptAttr(addr47, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr47, "Message(\"[!] ANTI-DBG TRIGGERED - ntdll_LdrLoadDll: The ntdll LdrLoadDll() function is a surprisingly simple and effective way to detect a debugger. When a file is loaded in the presence of a debugger, using the kernel32 LoadLibrary() function, a handle to the file is opened. This allows the debugger to read the debug information from the file (assuming that it is present).\\n\")");

		// Add runtime patching here if necessary
	}
}

static user32_brk()
{
    // USER32
    auto addr48 = LocByName("user32_FindWindowA");
    auto addr49 = LocByName("user32_BlockInput");

	if (addr48 != BADADDR){
		Message("[*] Kernel32 FindWindowA at address, breakpoint set %x\n", addr48);
		AddBpt(addr48);
		SetBptAttr(addr48, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr48, "Message(\"[!] ANTI-DBG TRIGGERED - user32_FindWindowA: The user32 FindWindow() function can be used to search for windows by name or class. This is an easy way to detect the presence of a debugger, if the debugger has a graphical user interface. \\n\")");

		// Add runtime patching here if necessary
	}

	if (addr49 != BADADDR){
		Message("[*] Kernel32 BlockInput at address, breakpoint set %x\n", addr49);
		AddBpt(addr49);
		SetBptAttr(addr49, BPTATTR_FLAGS, BPT_TRACEON | BPT_TRACE | BPT_ENABLED);
		SetBptCnd(addr49, "Message(\"[!] ANTI-DBG TRIGGERED - user32_BlockInput: The user32 BlockInput() function can block or unblock all mouse and keyboard events (apart from the ctrl-alt-delete key sequence). The effect remains until either the process exits or the function is called again with the opposite parameter. It is a very effective way to disable debuggers.\\n\")");

		// Add runtime patching here if necessary
	}
}