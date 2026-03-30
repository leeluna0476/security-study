# Control flow
- main keywords: `cmp`, `jmp`, `call`

```asm
(gdb) disassemble main
Dump of assembler code for function main:
   0x0000555555555189 <+0>:	endbr64
   0x000055555555518d <+4>:	push   rbp
   0x000055555555518e <+5>:	mov    rbp,rsp
   0x0000555555555191 <+8>:	sub    rsp,0x10
   0x0000555555555195 <+12>:	mov    DWORD PTR [rbp-0x4],edi
   0x0000555555555198 <+15>:	mov    QWORD PTR [rbp-0x10],rsi
   0x000055555555519c <+19>:	cmp    DWORD PTR [rbp-0x4],0x2
   0x00005555555551a0 <+23>:	jne    0x555555555207 <main+126>
   0x00005555555551a2 <+25>:	mov    rax,QWORD PTR [rbp-0x10]
   0x00005555555551a6 <+29>:	add    rax,0x8
   0x00005555555551aa <+33>:	mov    rax,QWORD PTR [rax]
   0x00005555555551ad <+36>:	mov    rsi,rax
   0x00005555555551b0 <+39>:	lea    rax,[rip+0xe4d]        # 0x555555556004
   0x00005555555551b7 <+46>:	mov    rdi,rax
   0x00005555555551ba <+49>:	mov    eax,0x0
   0x00005555555551bf <+54>:	call   0x555555555080 <printf@plt>
   0x00005555555551c4 <+59>:	mov    rax,QWORD PTR [rbp-0x10]
   0x00005555555551c8 <+63>:	add    rax,0x8
   0x00005555555551cc <+67>:	mov    rax,QWORD PTR [rax]
   0x00005555555551cf <+70>:	lea    rdx,[rip+0xe44]        # 0x55555555601a
   0x00005555555551d6 <+77>:	mov    rsi,rdx
   0x00005555555551d9 <+80>:	mov    rdi,rax
   0x00005555555551dc <+83>:	call   0x555555555090 <strcmp@plt>
   ; change eax value before test (bitwise AND)
   ; a zero flag is set after test
   0x00005555555551e1 <+88>:	test   eax,eax
   0x00005555555551e3 <+90>:	jne    0x5555555551f6 <main+109>
   0x00005555555551e5 <+92>:	lea    rax,[rip+0xe3e]        # 0x55555555602a
   0x00005555555551ec <+99>:	mov    rdi,rax
   0x00005555555551ef <+102>:	call   0x555555555070 <puts@plt>
=> 0x00005555555551f4 <+107>:	jmp    0x555555555216 <main+141>
   0x00005555555551f6 <+109>:	lea    rax,[rip+0xe3d]        # 0x55555555603a
   0x00005555555551fd <+116>:	mov    rdi,rax
   0x0000555555555200 <+119>:	call   0x555555555070 <puts@plt>
   0x0000555555555205 <+124>:	jmp    0x555555555216 <main+141>
   0x0000555555555207 <+126>:	lea    rax,[rip+0xe33]        # 0x555555556041
   0x000055555555520e <+133>:	mov    rdi,rax
   0x0000555555555211 <+136>:	call   0x555555555070 <puts@plt>
   0x0000555555555216 <+141>:	mov    eax,0x0
   0x000055555555521b <+146>:	leave
   0x000055555555521c <+147>:	ret
End of assembler dump.
```

## after strcmp
- "AAAA-key-1234" vs "AAAA-Z10N-42-OK"
```
0x00005555555551f6 in main ()
(gdb) info registers
[[[[rax            0x11                17]]]]
rbx            0x7fffffffe2b8      140737488347832
rcx            0x5a                90
rdx            0x5                 5
rsi            0x55555555601a      93824992239642
rdi            0x7fffffffe577      140737488348535
rbp            0x7fffffffe190      0x7fffffffe190
rsp            0x7fffffffe180      0x7fffffffe180
r8             0x0                 0
r9             0x1f                31
r10            0x7ffff7cc0b30      140737350732592
r11            0x202               514
r12            0x2                 2
r13            0x0                 0
r14            0x555555557db0      93824992247216
r15            0x7ffff7ffd000      140737354125312
rip            0x5555555551f6      0x5555555551f6 <main+109>
eflags         0x206               [ PF IF ]
cs             0x33                51
ss             0x2b                43
ds             0x0                 0
es             0x0                 0
fs             0x0                 0
gs             0x0                 0
fs_base        0x7ffff7fb4740      140737353828160
gs_base        0x0                 0
```

## a little crack
- input: `AAAA` -> must jump to `printf("WRONG!\n");`
- changed the `rax (the result of strcmp stored originally)` value to `0`
- -> jumped to `printf("Access Granted!\n");`
```
(gdb) ni
0x00005555555551e1 in main ()
(gdb) info registers
rax            0xffffffd3          4294967251
rbx            0x7fffffffe2b8      140737488347832
rcx            0x2d                45
rdx            0x3                 3
rsi            0x55555555601b      93824992239643
rdi            0x7fffffffe580      140737488348544
rbp            0x7fffffffe190      0x7fffffffe190
rsp            0x7fffffffe180      0x7fffffffe180
r8             0xffff              65535
r9             0xb                 11
r10            0xfffffffffffff02b  -4053
r11            0x202               514
r12            0x2                 2
r13            0x0                 0
r14            0x555555557db0      93824992247216
r15            0x7ffff7ffd000      140737354125312
rip            0x5555555551e1      0x5555555551e1 <main+88>
eflags         0x293               [ CF AF SF IF ]
cs             0x33                51
ss             0x2b                43
ds             0x0                 0
es             0x0                 0
fs             0x0                 0
gs             0x0                 0
fs_base        0x7ffff7fb4740      140737353828160
gs_base        0x0                 0
(gdb) set $rax=0
(gdb) info registers
rax            0x0                 0
rbx            0x7fffffffe2b8      140737488347832
rcx            0x2d                45
rdx            0x3                 3
rsi            0x55555555601b      93824992239643
rdi            0x7fffffffe580      140737488348544
rbp            0x7fffffffe190      0x7fffffffe190
rsp            0x7fffffffe180      0x7fffffffe180
r8             0xffff              65535
r9             0xb                 11
r10            0xfffffffffffff02b  -4053
r11            0x202               514
r12            0x2                 2
r13            0x0                 0
r14            0x555555557db0      93824992247216
r15            0x7ffff7ffd000      140737354125312
rip            0x5555555551e1      0x5555555551e1 <main+88>
eflags         0x293               [ CF AF SF IF ]
cs             0x33                51
ss             0x2b                43
ds             0x0                 0
es             0x0                 0
fs             0x0                 0
gs             0x0                 0
fs_base        0x7ffff7fb4740      140737353828160
gs_base        0x0                 0
(gdb) ni
0x00005555555551e3 in main ()
(gdb) info registers
rax            0x0                 0
rbx            0x7fffffffe2b8      140737488347832
rcx            0x2d                45
rdx            0x3                 3
rsi            0x55555555601b      93824992239643
rdi            0x7fffffffe580      140737488348544
rbp            0x7fffffffe190      0x7fffffffe190
rsp            0x7fffffffe180      0x7fffffffe180
r8             0xffff              65535
r9             0xb                 11
r10            0xfffffffffffff02b  -4053
r11            0x202               514
r12            0x2                 2
r13            0x0                 0
r14            0x555555557db0      93824992247216
r15            0x7ffff7ffd000      140737354125312
rip            0x5555555551e3      0x5555555551e3 <main+90>
eflags         0x246               [ PF ZF IF ]
cs             0x33                51
ss             0x2b                43
ds             0x0                 0
es             0x0                 0
fs             0x0                 0
gs             0x0                 0
fs_base        0x7ffff7fb4740      140737353828160
gs_base        0x0                 0
(gdb) ni
0x00005555555551e5 in main ()
(gdb) info registers
rax            0x0                 0
rbx            0x7fffffffe2b8      140737488347832
rcx            0x2d                45
rdx            0x3                 3
rsi            0x55555555601b      93824992239643
rdi            0x7fffffffe580      140737488348544
rbp            0x7fffffffe190      0x7fffffffe190
rsp            0x7fffffffe180      0x7fffffffe180
r8             0xffff              65535
r9             0xb                 11
r10            0xfffffffffffff02b  -4053
r11            0x202               514
r12            0x2                 2
r13            0x0                 0
r14            0x555555557db0      93824992247216
r15            0x7ffff7ffd000      140737354125312
rip            0x5555555551e5      0x5555555551e5 <main+92>
eflags         0x246               [ PF ZF IF ]
cs             0x33                51
ss             0x2b                43
ds             0x0                 0
es             0x0                 0
fs             0x0                 0
gs             0x0                 0
fs_base        0x7ffff7fb4740      140737353828160
gs_base        0x0                 0
(gdb) ni
0x00005555555551ec in main ()
(gdb) ni
0x00005555555551ef in main ()
(gdb) ni
Access Granted!
0x00005555555551f4 in main ()
(gdb)
```
