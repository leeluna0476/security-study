# the key solution
```asm
pwndbg> ni
0x080492c4 in login ()
LEGEND: STACK | HEAP | CODE | DATA | WX | RODATA
────────────────────────────────────────────[ REGISTERS / show-flags off / show-compact-regs off ]─────────────────────────────────────────────
 EAX  0x804a047 ◂— '/bin/cat flag'
 EBX  0x804c000 (_GLOBAL_OFFSET_TABLE_) —▸ 0x804bf10 (_DYNAMIC) ◂— 1
 ECX  0x3f2
 EDX  0
 EDI  0xf7f11b80 (_rtld_global_ro) ◂— 0
 ESI  0x3f2
 EBP  0xffc7e908 —▸ 0xffc7e918 —▸ 0xf7f12020 (_rtld_global) —▸ 0xf7f12a40 ◂— 0
*ESP  0xffc7e8e0 —▸ 0x804a047 ◂— '/bin/cat flag'
*EIP  0x80492c4 (login+206) ◂— call system@plt
──────────────────────────────────────────────────────[ DISASM / i386 / set emulate off ]──────────────────────────────────────────────────────
   0x80492b2 <login+188>    call   setregid@plt                <setregid@plt>

   0x80492b7 <login+193>    add    esp, 0x10               ESP => 0xffc7e8e0 + 0x10
   0x80492ba <login+196>    sub    esp, 0xc                ESP => 0xffc7e8f0 - 0xc
   0x80492bd <login+199>    lea    eax, [ebx - 0x1fb9]     EAX => 0x804a047 ◂— '/bin/cat flag'
   0x80492c3 <login+205>    push   eax
 ► 0x80492c4 <login+206>    call   system@plt                  <system@plt>
        command: 0x804a047 ◂— '/bin/cat flag'

   0x80492c9 <login+211>    add    esp, 0x10
   0x80492cc <login+214>    jmp    login+244                   <login+244>
    ↓
   0x80492ea <login+244>    nop
   0x80492eb <login+245>    lea    esp, [ebp - 8]
   0x80492ee <login+248>    pop    ebx
───────────────────────────────────────────────────────────────────[ STACK ]───────────────────────────────────────────────────────────────────
00:0000│ esp 0xffc7e8e0 —▸ 0x804a047 ◂— '/bin/cat flag'
01:0004│-024 0xffc7e8e4 ◂— 0x3f2
02:0008│-020 0xffc7e8e8 —▸ 0xf7d71370 (getegid+16) ◂— ret
03:000c│-01c 0xffc7e8ec —▸ 0x80492ad (login+183) ◂— sub esp, 8
04:0010│-018 0xffc7e8f0 —▸ 0xffc7e9e4 —▸ 0xffc7fd35 ◂— '/home/passcode/passcode'
05:0014│-014 0xffc7e8f4 —▸ 0xf7f11b80 (_rtld_global_ro) ◂— 0
06:0018│-010 0xffc7e8f8 —▸ 0xffc7e918 —▸ 0xf7f12020 (_rtld_global) —▸ 0xf7f12a40 ◂— 0
07:001c│-00c 0xffc7e8fc ◂— 0x2138e00
─────────────────────────────────────────────────────────────────[ BACKTRACE ]─────────────────────────────────────────────────────────────────
 ► 0 0x80492c4 login+206
   1 0x804939a main+54
   2 0xf7cb3519 __libc_start_call_main+121
   3 0xf7cb35f3 __libc_start_main+147
   4 0x804910c _start+44
───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
pwndbg> ni
[Attaching after Thread 0xf7ed4500 (LWP 1013837) vfork to child process 1095308]
[New inferior 2 (process 1095308)]
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
[Detaching vfork parent process 1013837 after child exec]
[Inferior 1 (process 1013837) detached]
process 1095308 is executing new program: /usr/bin/dash
Error in re-setting breakpoint 1: Function "login" not defined.
Error in re-setting breakpoint 2: Function "login" not defined.
Warning:
Cannot insert breakpoint 3.
Cannot access memory at address 0x804927d

pwndbg>
```
