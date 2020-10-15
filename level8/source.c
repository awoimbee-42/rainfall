#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char byte;

char *auth;
char *service;


int main(void)

{
	char c;
	char *s;
	int i;
	unsigned int u;
	byte *bytes0;
	byte *bytes1;
	bool bool0;
	bool bool1;
	bool bool2;
	byte bool3;
	byte buffer0[5];
	char buffer1[2];
	char buffer3[125];

	bool3 = 0;
	while (true) {
		printf("%p, %p \n", auth, service);
		s = fgets((char *)buffer0, 128, stdin);
		bool0 = false;
		bool2 = s == NULL;
		if (bool2) {
			return 0;
		}
		i = 5;
		bytes0 = buffer0;
		bytes1 = (byte *)"auth ";
		do {
			if (i == 0) break;
			i = i + -1;
			bool0 = *bytes0 < *bytes1;
			bool2 = *bytes0 == *bytes1;
			bytes0 = bytes0 + (unsigned int)bool3 * -2 + 1;
			bytes1 = bytes1 + (unsigned int)bool3 * -2 + 1;
		} while (bool2);
		bool1 = false;
		bool0 = (!bool0 && !bool2) == bool0;
		if (bool0) {
			auth = (int *)malloc(4);
			*auth = 0;
			u = 0xffffffff;
			s = buffer1;
			do {
				if (u == 0) break;
				u = u - 1;
				c = *s;
				s = s + (unsigned int)bool3 * -2 + 1;
			} while (c != '\0');
			u = ~u - 1;
			bool1 = u < 0x1e;
			bool0 = u == 0x1e;
			if (u < 0x1f) {
				strcpy((char *)auth,buffer1);
			}
		}
		i = 5;
		bytes0 = buffer0;
		bytes1 = (byte *)"reset";
		do {
			if (i == 0) break;
			i -= 1;
			bool1 = *bytes0 < *bytes1;
			bool0 = *bytes0 == *bytes1;
			bytes0 += (unsigned int)bool3 * -2 + 1;
			bytes1 += (unsigned int)bool3 * -2 + 1;
		} while (bool0);
		bool2 = false;
		bool0 = (!bool1 && !bool0) == bool1;
		if (bool0) {
			free(auth);
		}
		i = 6;
		bytes0 = buffer0;
		bytes1 = (byte *)"service";
		do {
			if (i == 0) break;
			i -= 1;
			bool2 = *bytes0 < *bytes1;
			bool0 = *bytes0 == *bytes1;
			bytes0 += (unsigned int)bool3 * -2 + 1;
			bytes1 += (unsigned int)bool3 * -2 + 1;
		} while (bool0);
		bool1 = false;
		bool0 = (!bool2 && !bool0) == bool2;
		if (bool0) {
			bool1 = (byte *)0xfffffff8 < buffer0;
			bool0 = buffer3 == NULL;
			service = strdup(buffer3);
		}
		i = 5;
		bytes0 = buffer0;
		bytes1 = (byte *)"login";
		do {
			if (i == 0) break;
			i = i + -1;
			bool1 = *bytes0 < *bytes1;
			bool0 = *bytes0 == *bytes1;
			bytes0 += (unsigned int)bool3 * -2 + 1;
			bytes1 += (unsigned int)bool3 * -2 + 1;
		} while (bool0);
		if ((!bool1 && !bool0) == bool1) {
			if (auth[8] == 0) {
				fwrite("Password:\n", 1, 10, stdout);
			}
			else {
				system("/bin/sh");
			}
		}
	}
}
