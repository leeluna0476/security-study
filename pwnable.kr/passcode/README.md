# the key solution
- gdb 내에서 zero flag를 1로 설정하여 jne를 통과하도록 한다?
  - 갑자기 broken pipe 문제가 생겨서 서버에서 튕겨나왔다. 아직 성공하지 못함.

- 정상적인 입력을 줄 수 있는 통로가 welcome의 name변수 뿐이다. 이걸 가지고 login의 passcode1, passcode2에 값을 줄 수 있을까?
  - 서로 다른 함수인데... 어카누
  - welcome이 반환되고 나서 원래 name이었던 메모리 영역에 passcode1, passcode2가 정의된다. name의 값들이 쓰레기값으로 남아있다.
  - name 메모리 영역 내에서 passcode1, passcode2가 어디에 위치할지 계산하고 그 위치에 123456, 13371337을 쓰면 된다.

**executable format**
- ELF32
- 참고: SYSTEM V APPLICATION BINARY INTERFACE - Intel386 Architecture Processor Supplement
```
passcode@ubuntu:~$ readelf -h passcode
ELF Header:
  Magic:   7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00
  Class:                             ELF32
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              EXEC (Executable file)
  Machine:                           Intel 80386
  Version:                           0x1
  Entry point address:               0x80490e0
  Start of program headers:          52 (bytes into file)
  Start of section headers:          14072 (bytes into file)
  Flags:                             0x0
  Size of this header:               52 (bytes)
  Size of program headers:           32 (bytes)
  Number of program headers:         11
  Size of section headers:           40 (bytes)
  Number of section headers:         29
  Section header string table index: 28
```

**welcome dump**
```asm
pwndbg> disassemble welcome
Dump of assembler code for function welcome:
   0x080492f2 <+0>:	push   ebp
   0x080492f3 <+1>:	mov    ebp,esp
   0x080492f5 <+3>:	push   ebx
   0x080492f6 <+4>:	sub    esp,0x74
   0x080492f9 <+7>:	call   0x8049130 <__x86.get_pc_thunk.bx>
   0x080492fe <+12>:	add    ebx,0x2d02
   0x08049304 <+18>:	mov    eax,gs:0x14
   0x0804930a <+24>:	mov    DWORD PTR [ebp-0xc],eax
   0x0804930d <+27>:	xor    eax,eax
   0x0804930f <+29>:	sub    esp,0xc
   0x08049312 <+32>:	lea    eax,[ebx-0x1f9d]
   0x08049318 <+38>:	push   eax
   0x08049319 <+39>:	call   0x8049050 <printf@plt>
   ; esp = ebp - 0x74 + 0x10 = ebp - 0x64 = ebp - 100
   0x0804931e <+44>:	add    esp,0x10
   ; esp - 0x8 = ebp - 100 - 8 = ebp - 108
   ; 8B 공간 더 마련함.
   ; name(주소, 8B)을 저장할 공간인가, 아니 주소는 4B.
   ; 놉. 그냥 align용인 듯. 아래 줄에서 4바이트 push하니까.
   ; word align (word=4B, 굳이 필요없어 보이는데..)
   0x08049321 <+47>:	sub    esp,0x8
   ; ebp - 0x70에서 4B 읽어 스택에 푸시한다.
   ; esp = ebp - 100, push -> esp = ebp - 108 - 4 = ebp - 112
   ; -> esp = ebp - 0x70
   ; 에에 그냥 그 자리에 똑같은 거 push한 거네
   0x08049324 <+50>:	lea    eax,[ebp-0x70]
   0x08049327 <+53>:	push   eax
   ; <abi386>
   ; ebx -> holds GOT(Global Offset Table) base address
   ; string literal과 같은 global data에 접근하기 위한 용도로 사용됨.
   0x08049328 <+54>:	lea    eax,[ebx-0x1f8b]
   0x0804932e <+60>:	push   eax
   ; argument words are pushed to stack
   ; the rightmost argument has the highest address
   ; 가장 최근에 push된 global data -> format string
   ; 그 전에 push된 [ebp - 0x70]
   0x0804932f <+61>:	call   0x80490d0 <__isoc99_scanf@plt>
   ;
   0x08049334 <+66>:	add    esp,0x10
   0x08049337 <+69>:	sub    esp,0x8
   0x0804933a <+72>:	lea    eax,[ebp-0x70]
   0x0804933d <+75>:	push   eax
   0x0804933e <+76>:	lea    eax,[ebx-0x1f85]
   0x08049344 <+82>:	push   eax
   0x08049345 <+83>:	call   0x8049050 <printf@plt>
   0x0804934a <+88>:	add    esp,0x10
   0x0804934d <+91>:	nop
   0x0804934e <+92>:	mov    eax,DWORD PTR [ebp-0xc]
   0x08049351 <+95>:	sub    eax,DWORD PTR gs:0x14
   0x08049358 <+102>:	je     0x804935f <welcome+109>
   0x0804935a <+104>:	call   0x80493c0 <__stack_chk_fail_local>
   0x0804935f <+109>:	mov    ebx,DWORD PTR [ebp-0x4]
   0x08049362 <+112>:	leave
   0x08049363 <+113>:	ret
End of assembler dump.
```
