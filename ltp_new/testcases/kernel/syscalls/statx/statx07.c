/*
 * [Description]
 * Check that lookup_dcookie return EINVAL when kernel has no registered cookie/directory entry 
 * mappings at the time of lookup.
 */

#include <stdint.h>
#include "tst_test.h"

#include <sys/syscall.h>      /* Definition of SYS_* constants */
#include <unistd.h>
#include <limits.h>

//int syscall(SYS_lookup_dcookie, uint64_t cookie, char *buffer, size_t len);

static void run(void)
{
	enum { BUF_SIZE = 4096 };

	uint64_t cookie = (uint64_t) NULL;
	char *buffer = tst_alloc(BUF_SIZE);
	size_t len = (__kernel_ulong_t) NULL;

	TEST(syscall(SYS_lookup_dcookie, cookie, buffer, len));


	if (TST_RET > 0)
		tst_res(TFAIL, "lookup_dcookie not working as expected");
	else if (TST_RET == -1)
		tst_res(TPASS | TERRNO, "lookup_dcookie set errno as expected");
	else
		tst_res(TFAIL | TERRNO, "lookup_dcookie set errno to some unexpected value");
}

static struct tst_test test = {
	.test_all = run,
	.min_kver = "4.11",
};
