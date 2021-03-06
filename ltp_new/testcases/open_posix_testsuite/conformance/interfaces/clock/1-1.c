/*
 * Copyright (c) 2002, Intel Corporation. All rights reserved.
 * Created by:  julie.n.fleischer REMOVE-THIS AT intel DOT com
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.
 *
 * Test that clock() returns a clock_t containing the processor time
 * since a specific point in time.
 * Dividing the return value by CLOCKS_PER_SEC gives time in seconds.
 *
 * 12/17/02 - Checking in correction made by
 *            jim.houston REMOVE-THIS AT attbi DOT com
 *            Test needed to do something as opposed to idle sleep to
 *            get the CPU time to increase.
 */
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "posixtest.h"

#define MAX_RUNTIME_SECONDS 15

int main(void)
{
	clock_t c1, c2;
	double sec1, sec2;
	time_t end = time(NULL) + MAX_RUNTIME_SECONDS;

	c1 = clock();
	if (c1 == (clock_t)-1) {
		printf("processor time not available\n");
		return PTS_UNRESOLVED;
	}
	sec1 = (double) c1 / CLOCKS_PER_SEC;

	do {
		c2 = clock();
		sec2 = (double) c2 / CLOCKS_PER_SEC;
		if (sec2 - sec1 > 1) {
			printf("Times T1=%.2lf, T2=%.2lf\n", sec1, sec2);
			printf("Test PASSED\n");
			return PTS_PASS;
		}
	} while (end >= time(NULL));

	printf("Error with processor times T1=%.2lf, T2=%.2lf\n",
	       sec1, sec2);
	return PTS_FAIL;
}
