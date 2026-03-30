import sys

def print_in_char(a):
    for i in range(0, 4):
        print(hex((a >> i * 8) & 0xff))
#        sys.stdout.buffer.write(
#                bytes([(a >> (i * 8)) & 0xff])
#                )

h = int("0x21DD09EC", 16)
a = h // 5 + 1
for _ in range(4):
    print_in_char(a)
print_in_char(h // 5)
