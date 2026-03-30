#include <stdio.h>
#include <string.h>

unsigned long hashcode = 0x21DD09EC;
unsigned long check_password(const char* p){
    int* ip = (int*)p;
    int i;
    int res=0;
    for (i=0; i<5; i++) {
        res += ip[i];
    }
    return res;
}

int main(void) {
	char *s = "\xc9\xce\xc5\x06\xc9\xce\xc5\x06\xc9\xce\xc5\x06\xc9\xce\xc5\x06\xc8\xce\xc5\x06";
	printf("%d\n", hashcode == check_password(s));
}
