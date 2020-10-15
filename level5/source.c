#include <stdio.h>
#include <stdlib.h>

void n(void)
{
	char buf [520];

	fgets(buf, 512, stdin);
	printf(buf);
	exit(1);
}

void o(void)
{
	system("/bin/sh");
	exit(1);
}

void main(void)
{
	n();
	return;
}
