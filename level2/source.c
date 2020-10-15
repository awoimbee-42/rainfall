#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void p(void)
{
	unsigned int check;
	char buf[76];

	fflush(stdout);
	gets(buf);
	if ((check & 0xb0000000) == 0xb0000000) {
		printf("(%p)\n", check);
		exit(1);
	}
	puts(buf);
	strdup(buf);
	return;
}

void main(void)
{
	p();
	return;
}
