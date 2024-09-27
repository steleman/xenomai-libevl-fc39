/*
 * SPDX-License-Identifier: MIT
 *
 * Exercise recursive locking.
 */

#include <sys/types.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <evl/thread.h>
#include <evl/mutex.h>
#include <evl/clock.h>
#include "helpers.h"

static struct evl_mutex lock;

int main(int argc, char *argv[])
{
	struct sched_param param;
	int tfd, mfd;
	char *name;

	param.sched_priority = 1;
	__Texpr_assert(pthread_setschedparam(pthread_self(),
				SCHED_FIFO, &param) == 0);

	/* EVL inherits the inband scheduling params upon attachment. */
	__Tcall_assert(tfd, evl_attach_self("monitor-recursive:%d", getpid()));

	name = get_unique_name(EVL_MONITOR_DEV, 0);
	__Tcall_assert(mfd, evl_create_mutex(
			&lock, EVL_CLOCK_MONOTONIC,
			0, EVL_MUTEX_RECURSIVE|EVL_CLONE_PRIVATE, name));

	__Texpr_assert(evl_lock_mutex(&lock) == 0); /* +1 */
	__Texpr_assert(evl_unlock_mutex(&lock) == 0); /* free */
	__Texpr_assert(evl_lock_mutex(&lock) == 0);   /* +1 */
	__Texpr_assert(evl_trylock_mutex(&lock) == 0); /* +2 */
	__Texpr_assert(evl_unlock_mutex(&lock) == 0);  /* +1 */
	__Texpr_assert(evl_lock_mutex(&lock) == 0);    /* +2 */
	__Texpr_assert(evl_unlock_mutex(&lock) == 0);  /* +1 */
	__Texpr_assert(evl_unlock_mutex(&lock) == 0);  /* free */
	__Texpr_assert(evl_unlock_mutex(&lock) == -EPERM);

	evl_close_mutex(&lock);

	return 0;
}
