/*
 * [Description]
 * Check that restart_syscall return success when execute
 */

#include <stdint.h>
#include "tst_test.h"
#include <sys/syscall.h>      /* Definition of SYS_* constants */
#include <unistd.h>
#include <limits.h>

//long restart_syscall(void);

static void run(void)
{

	//TEST(syscall(SYS_lookup_dcookie, cookie, buffer, len));
	
	TEST(SYS_restart_syscall);


	if (TST_RET > 0)
		tst_res(TPASS | TERRNO, "restart_syscall retrun value");
	else if (TST_RET == -1)
		tst_res(TPASS | TERRNO, "lookup_dcookie set errno as expected");
	else
		tst_res(TFAIL | TERRNO, "lookup_dcookie set errno to some unexpected value");
}

static struct tst_test test = {
	.test_all = run,
	.min_kver = "4.11",
};
