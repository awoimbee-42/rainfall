#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
**	The original assembly is quite unreadable, so this doesn't map 1 to 1.
**	Exemple:
**		{
**			bytes0 = buffer0;
**			bytes1 = (byte *)"auth ";
**			i = 5;
**			do {
**				if (i == 0) break;
**				i -= 1;
**				bool0 = *bytes0 < *bytes1;
**				bool2 = *bytes0 == *bytes1;
**				bytes0 += (unsigned int)bool3 * -2 + 1;
**				bytes1 += (unsigned int)bool3 * -2 + 1;
**			} while (bool2);
**			bool1 = false;
**			bool0 = (!bool0 && !bool2) == bool0;
**			if (bool0) {}
**		}
**		Is replaced by:
**		if (strncmp(buffer0, "auth ", 5) == 0) {}
*/

char *auth;
char *service;

struct buffer {
	char cmd[5];
	char auth[2];
	char service[125];
} __attribute__((packed));

int main(void)
{
	struct buffer buf;

	while (true) {
		printf("%p, %p \n", auth, service);
		if (fgets(buf.cmd, 128, stdin) == NULL) {
			return 0;
		}
		if (strncmp(buf.cmd, "auth ", 5) == 0) {
			auth = malloc(4);
			auth[0] = 0;
			if (strlen(buf.auth) < 32) {
				strcpy(auth, buf.auth);
			}
		}
		if (strncmp(buf.cmd, "reset", 5) == 0) {
			free(auth);
		}
		if (strncmp(buf.cmd, "service", 6) == 0) {
			service = strdup(buf.service);
		}
		if (strncmp(buf.cmd, "login", 5) == 0) {
			if (auth[32] == 0) {
				fwrite("Password:\n", 1, 10, stdout);
			} else {
				system("/bin/sh");
			}
		}
	}
}
