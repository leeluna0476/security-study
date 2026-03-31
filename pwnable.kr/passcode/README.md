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
   ; lea: 데이터가 저장된 위치의 주소 계산. c언어의 &연산과 동일.
   ; int *p = ebp - 0x70; int *eax = &(*p); 이것과 비슷하다.
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

**login dump**
```asm
pwndbg> disassemble login
Dump of assembler code for function login:
   0x080491f6 <+0>:	push   ebp
   0x080491f7 <+1>:	mov    ebp,esp
   0x080491f9 <+3>:	push   esi
   0x080491fa <+4>:	push   ebx
   0x080491fb <+5>:	sub    esp,0x10
   0x080491fe <+8>:	call   0x8049130 <__x86.get_pc_thunk.bx>
   0x08049203 <+13>:	add    ebx,0x2dfd
   0x08049209 <+19>:	sub    esp,0xc
   0x0804920c <+22>:	lea    eax,[ebx-0x1ff8]
   0x08049212 <+28>:	push   eax
   0x08049213 <+29>:	call   0x8049050 <printf@plt>
   0x08049218 <+34>:	add    esp,0x10
   0x0804921b <+37>:	sub    esp,0x8
   0x0804921e <+40>:	push   DWORD PTR [ebp-0x10]
   0x08049221 <+43>:	lea    eax,[ebx-0x1fe5]
   0x08049227 <+49>:	push   eax
   0x08049228 <+50>:	call   0x80490d0 <__isoc99_scanf@plt>
   0x0804922d <+55>:	add    esp,0x10
   0x08049230 <+58>:	mov    eax,DWORD PTR [ebx-0x4]
   0x08049236 <+64>:	mov    eax,DWORD PTR [eax]
   0x08049238 <+66>:	sub    esp,0xc
   0x0804923b <+69>:	push   eax
   0x0804923c <+70>:	call   0x8049060 <fflush@plt>
   0x08049241 <+75>:	add    esp,0x10
   0x08049244 <+78>:	sub    esp,0xc
   0x08049247 <+81>:	lea    eax,[ebx-0x1fe2]
   0x0804924d <+87>:	push   eax
   0x0804924e <+88>:	call   0x8049050 <printf@plt>
   0x08049253 <+93>:	add    esp,0x10
   0x08049256 <+96>:	sub    esp,0x8
   0x08049259 <+99>:	push   DWORD PTR [ebp-0xc]
   0x0804925c <+102>:	lea    eax,[ebx-0x1fe5]
   0x08049262 <+108>:	push   eax
   0x08049263 <+109>:	call   0x80490d0 <__isoc99_scanf@plt>
   0x08049268 <+114>:	add    esp,0x10
   0x0804926b <+117>:	sub    esp,0xc
   0x0804926e <+120>:	lea    eax,[ebx-0x1fcf]
   0x08049274 <+126>:	push   eax
   0x08049275 <+127>:	call   0x8049090 <puts@plt>
   0x0804927a <+132>:	add    esp,0x10
   0x0804927d <+135>:	cmp    DWORD PTR [ebp-0x10],0x1e240
   0x08049284 <+142>:	jne    0x80492ce <login+216>
   0x08049286 <+144>:	cmp    DWORD PTR [ebp-0xc],0xcc07c9
   0x0804928d <+151>:	jne    0x80492ce <login+216>
   0x0804928f <+153>:	sub    esp,0xc
   0x08049292 <+156>:	lea    eax,[ebx-0x1fc3]
   0x08049298 <+162>:	push   eax
   0x08049299 <+163>:	call   0x8049090 <puts@plt>
   0x0804929e <+168>:	add    esp,0x10
   0x080492a1 <+171>:	call   0x8049080 <getegid@plt>
   0x080492a6 <+176>:	mov    esi,eax
   0x080492a8 <+178>:	call   0x8049080 <getegid@plt>
   0x080492ad <+183>:	sub    esp,0x8
   0x080492b0 <+186>:	push   esi
   0x080492b1 <+187>:	push   eax
   0x080492b2 <+188>:	call   0x80490c0 <setregid@plt>
   0x080492b7 <+193>:	add    esp,0x10
   0x080492ba <+196>:	sub    esp,0xc
   0x080492bd <+199>:	lea    eax,[ebx-0x1fb9]
   0x080492c3 <+205>:	push   eax
   0x080492c4 <+206>:	call   0x80490a0 <system@plt>
   0x080492c9 <+211>:	add    esp,0x10
   0x080492cc <+214>:	jmp    0x80492ea <login+244>
   0x080492ce <+216>:	sub    esp,0xc
   0x080492d1 <+219>:	lea    eax,[ebx-0x1fab]
   0x080492d7 <+225>:	push   eax
   0x080492d8 <+226>:	call   0x8049090 <puts@plt>
   0x080492dd <+231>:	add    esp,0x10
   0x080492e0 <+234>:	sub    esp,0xc
   0x080492e3 <+237>:	push   0x0
   0x080492e5 <+239>:	call   0x80490b0 <exit@plt>
   0x080492ea <+244>:	nop
   0x080492eb <+245>:	lea    esp,[ebp-0x8]
   0x080492ee <+248>:	pop    ebx
   0x080492ef <+249>:	pop    esi
   0x080492f0 <+250>:	pop    ebp
   0x080492f1 <+251>:	ret
End of assembler dump.
```
## address of each variable
- 두 함수의 ebp는 모두 함수 호출 직후의 esp값이다.
- 두 함수 호출 직후에 esp 값이 같다면 두 ebp는 서로 같다.

**main에서 welcome, login을 호출하는 부분**
```asm
   0x08049390 <+44>:	call   0x80492f2 <welcome>
   0x08049395 <+49>:	call   0x80491f6 <login>
```
- welcome 반환 후에 스택에 변화를 주지 않는다. 두 함수의 호출 직후 esp값은 동일하다.

**func welcome:**
- name: ebp - 0x70

**func login:**
- passcode1: ebp - 0x10
- passcode2: ebp - 0x0c

**name을 기준으로 두고 passcode1, passcode2가 될 위치에 값 쓰기**
- passcode1: ebp - 0x10 = ebp - 0x70 + 0x60 = name + 96
- passcode2: ebp - 0x0c = ebp - 0x70 + 0x64 = name + 100

**welcome: scanf 호출 방식**
`scanf("%100s", name);`

**입력 데이터**
- 96B: 아무 값, 4B: 123456(passcode1), 4B: 1337133(passcode2).
- 100B는 먼저 scanf 내부 버퍼에 저장되고, name에 저장하면서 소비된다.
  - 123456 = 0x0001e240 -> 40 e2 01 00 (귀신같이 마지막에 \0로 끝난다...)
  - \0을 읽었으니 EOF? 놉. \0이랑 EOF랑 다르다. \0 포함해서 white-space 나오기 전까지 읽을 수 있다.
- 100B 처리하고 나서 파일 포인터는 passcode2 부분을 가리킨다.
- passcode2는 어떻게 쓰냐 하...
```asm
pwndbg> x $ebp - 0x10
0xff920078:	0x0001e240
pwndbg> x $ebp - 0xc
0xff92007c:	0x47906d00
```
- passcode2 안된다고 안된다고 ㅜㅜㅜ
