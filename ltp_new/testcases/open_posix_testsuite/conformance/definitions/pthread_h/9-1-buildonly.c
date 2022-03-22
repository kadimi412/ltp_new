  /*
   * Copyright (c) 2002, Intel Corporation. All rights reserved.
   * Created by:  rolla.n.selbak REMOVE-THIS AT intel DOT com
   * This file is licensed under the GPL license.  For the full content
   * of this license, see the COPYING file at the top level of this
   * source tree.

   Test this function is defined:

   int pthread_detach(pthread_t);
   */

#include <pthread.h>

static pthread_t a;

static void dummy_func()
{
	pthread_detach(a);
	return;
}
