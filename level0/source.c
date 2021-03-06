#define _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int ac, char *av[])
{
	char *exec_args[2];
	gid_t gid;
	uid_t uid;

	if (atoi(av[1]) == 423) {
		exec_args[0] = strdup("/bin/sh");
		exec_args[1] = NULL;
		gid = getegid();
		uid = geteuid();
		setresgid(gid, gid, gid);
		setresuid(uid, uid, uid);
		execv("/bin/sh", exec_args);
	} else {
		fwrite("No !\n", 1, 5, stderr);
	}
}
