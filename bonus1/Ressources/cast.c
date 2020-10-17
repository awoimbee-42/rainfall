// #include <string.h>
// #include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int ac, char *av[])
{
	if (ac < 2) {
		printf("Usage: %s [number]", av[0]);
		return 0;
	}
	int nb = atoi(av[1]);
	printf("%d -> %u\n", nb, (size_t)(nb * 4));
	return 0;
}
