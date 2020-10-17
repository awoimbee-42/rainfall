#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int ac,char *av[])
{
	char buf[40];
	int i;

	i = atoi(av[1]);
	if (i < 10) {
		memcpy(buf, av[2], (size_t)(i * 4));
		if (i == 0x574f4c46) {
			execl("/bin/sh", "sh", 0);
		}
		return 0;
	}
	return 1;
}
