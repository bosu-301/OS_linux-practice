#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
int main()
{
	int I = syscall(335);
	printf("SYSCALL::SYS_HELLO::RETVAL=%ld\n",I);
	return 0;
}

