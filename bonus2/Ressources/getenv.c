#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int ac, char *av[])
{
	if (ac != 2) {
		printf("Usage: %s [env_var]\n", av[0]);
	} else {
		char *val = getenv(av[1]);
		char hex[sizeof(void*)*2 + 3] = {0};
		sprintf(hex, "%p", val);
		char embedable[sizeof(void*)*4 + 1] = {0};
		if (val)
		{
			char *p = embedable;
			char *end = strchr(hex, 0);
			while (end > &hex[2]) {
				end -= 2;
				p[0] = '\\';
				p[1] = 'x';
				p[2] = end[0];
				p[3] = end[1];
				p += 4;
			}
		}
		printf("%s @ %s -> %s\n", av[1], hex, embedable);
	}
}
