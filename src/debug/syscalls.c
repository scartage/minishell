#define _GNU_SOURCE
#include <dlfcn.h>
#include <execinfo.h>
#include <unistd.h>

#include "../../inc/minishell.h"

int close(int fd)
{
	int (*libc_close)(int) = (int (*)(int))dlsym(RTLD_NEXT, "close");
	DEBUG("pid: %i: close: Closing fd: %i\n", getpid(), fd);
	return libc_close(fd);
}

int	 pipe(int fds[2])
{
	int (*libc_pipe)(int[2]) = (int (*)(int[2]))dlsym(RTLD_NEXT, "pipe");
	int res = libc_pipe(fds);
	DEBUG("pid: %i: pipe: Opening pipe: [%i, %i]\n", getpid(), fds[0], fds[1]);
	return res;
}