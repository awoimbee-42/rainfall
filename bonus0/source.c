#include <string.h>
#include <unistd.h>
#include <stdio.h>

char header[6] = " - ";
char __[2] = " ";

void p(char *input, const char *separator)
{
	char tmp_read[4104];

	puts(separator);
	read(STDIN_FILENO, tmp_read, 4096); // no null-termination if input more than 4096 bytes
	*strchr(tmp_read, '\n') = '\0';
	strncpy(input, tmp_read, 20); // no null-termination if len(tmp_read) >= 20 bytes
	return;
}

void pp(char *buf)
{
	char new0[20];
	char new1[20];

	p(new0, header);
	p(new1, header);
	strcpy(buf, new0); // no overflow protection

	size_t len = strlen(buf);
	buf[len] = ' ';
	buf[len + 1] = '\0';

	strcat(buf, new1); // no overflow potection
	return;
}

int main(void)
{
	char buf[54];

	pp(buf);
	puts(buf);
	return 0;
}
