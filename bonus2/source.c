#include <inttypes.h>
#include <string.h>
#include <stdio.h>

#include <stdlib.h>

enum LANGUAGE {
	EN = 0,
	FI = 1,
	NL = 2,
};

enum LANGUAGE language = EN;

char *lang_str_fi = "fi";
char *lang_str_nl = "nl";

typedef uint32_t int_t;
typedef uint16_t undefined2;
typedef uint8_t undefined;
typedef uint8_t byte;

void greetuser(char *name)
{
	char out[19];

	if (language == FI) {
		strcpy(out, "Hyvää päivää ");
	}
	else if (language == NL) {
		strcpy(out, "Goedemiddag! ");
	}
	else if (language == EN) {
		strcpy(out, "Hello ");
	}
	strcat(out, name);
	puts(out);
	return;
}

int_t main(int ac, char *av[])
{
	char buf0[40];
	char buf1[36];
	char *env_lang;

	if (ac != 3) {
		return 1;
	}

	memset(buf0, 0, 76);
	strncpy(buf0, av[1], 40); // not always null-terminated
	strncpy(buf1, av[2], 32); // not always null-terminated
	env_lang = getenv("LANG");
	if (env_lang != NULL) {
		if (memcmp(env_lang, lang_str_fi, 2) == 0) {
			language = FI;
		}
		else if (memcmp(env_lang, lang_str_nl, 2) == 0) {
			language = NL;
		}
	}
	// memmove(stack0xffffff50, buf0, 76);
	greetuser(buf0);

	return 0;
}
