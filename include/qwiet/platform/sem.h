/* SPDX-License-Identifier: Apache-2.0 */
/*
 * Counting semaphore abstraction.
 */
#ifndef QWIET_SEM_H
#define QWIET_SEM_H

#include <qwiet/platform/common.h>
#include <qwiet/platform/time.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  sem_t sem;
} pal_sem_t;

void
pal_sem_init(pal_sem_t *sem, unsigned int value);

void
pal_sem_destroy(pal_sem_t *sem);

int
pal_sem_wait(pal_sem_t *sem, pal_timeout_t timeout);

void
pal_sem_post(pal_sem_t *sem);

#ifdef __cplusplus
}
#endif

#endif
