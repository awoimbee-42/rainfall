#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This code only works in 32bit mode
// gcc -m32

char c[79];

void m(void *p1, int p2 ,char *p3 ,int p4 ,int p5)
{
	time_t t;

	t = time((time_t *)0);
	printf("%s - %d\n", c, t);
	return;
}

int main(int ac, char *av[])
{
	unsigned int *p1;
	void *tmp;
	unsigned int *p2;
	FILE *f;

	p1 = malloc(8);
	p1[0] = 1;
	tmp = malloc(8);
	p1[1] = (unsigned int)tmp;
	p2 = malloc(8);
	p2[0] = 2;
	tmp = malloc(8);
	p2[1] = (unsigned int)tmp;
	strcpy((char *)p1[1], av[1]);
	strcpy((char *)p2[1], av[2]);
	f = fopen("/home/user/level8/.pass", "r");
	fgets(c, 68, f);
	puts("~~");
	return 0;
}
