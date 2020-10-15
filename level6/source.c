#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef void(*code)(void);

void m(void *p1, int p2, char *p3, int p4, int p5)
{
	puts("Nope");
	return;
}

void n(void) {
	system("/bin/cat /home/user/level7/.pass");
	return;
}

void main(int ac, char *av[])
{
	char *str;
	code *fn;

	str = malloc(0x40);
	fn = malloc(4);
	*fn = (void*)m;
	strcpy(str, av[1]);
	(**fn)();
	return;
}
