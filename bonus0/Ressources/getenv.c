#include <stdio.h>
#include <stdlib.h>

void main(int ac, char *av[])
{
	if (ac != 2) {
		printf("Usage: %s [env_var]\n", av[0]);
	} else {
		printf("%s @ %p\n", av[1], getenv(av[1]));
	}
}
