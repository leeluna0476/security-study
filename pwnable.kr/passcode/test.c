#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

// 이게 대체 왜 되냐고 왜 세그폴트 안 나냐고
int	main(void) {
	char buf[4];
	scanf("%4s", buf);
	fflush(stdin);

	printf("%d\n", *(int *)buf);
	long long int d;
	printf("d=%lld\n", d);
	if (scanf("%s", (char *)(d)) == -1) {
		printf("EOF\n");
	}
	printf("*d=%d\n", *(int *)(d));
	printf("d=%lld\n", d);
	return 0;
}
