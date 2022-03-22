#include "tst_test.h"
#include <errno.h>
       #include <stddef.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <unistd.h>
       #include <linux/audit.h>
       #include <linux/filter.h>
       #include <linux/seccomp.h>
       #include <sys/prctl.h>
#include "tst_test.h"
#include <stdint.h>
#include "lapi/syscalls.h"
#include <stdio.h>
#include "linux/types.h"

int seccomp(unsigned int operation, unsigned int flags, void *args)
{
return tst_syscall(__NR_seccomp, operation, flags, args);
}
static void run(void)
{  

   int *ptr = {0};

	TEST(seccomp(2, 0, &ptr));

	if (TST_RET == 0)
		tst_res(TPASS, "seccomp functin working as expected");
	else if (TST_ERR == EFAULT)
		tst_res(TFAIL, "seccomp set errno to EFAULT");
	else
		tst_res(TFAIL | TERRNO, "seccomp set errno to some unexpected value");
}

static struct tst_test test = {
	.test_all = run,
	.min_kver = "4.11",
};
