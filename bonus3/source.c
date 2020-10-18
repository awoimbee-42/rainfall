#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int ac, char *av[])
{
	char buf[83];
	FILE *f;

	f = fopen("/home/user/end/.pass", "r");
	memset(buf, 0, 33);
	if ((f == NULL) || (ac != 2)) {
		return 0xffffffff;
	}
	fread(buf, 1, 66, f);
	buf[16] = 0;
	buf[atoi(av[1])] = 0;
	fread(&buf[17], 1, 65, f); //
	fclose(f);
	if (strcmp(buf, av[1]) == 0) {
		execl("/bin/sh", "sh", 0);
	} else {
		puts(&buf[17]);
	}
	return 0;
}
