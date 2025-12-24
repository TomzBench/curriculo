#include <errno.h>
#include <qwiet/platform/sem.h>

void
pal_sem_init(pal_sem_t *sem, unsigned int value)
{
  int ret = sem_init(&sem->sem, 0, value);
  pal_assert(ret == 0, "sem_init failed");
}

void
pal_sem_destroy(pal_sem_t *sem)
{
  int ret = sem_destroy(&sem->sem);
  pal_assert(ret == 0, "sem_destroy failed");
}

int
pal_sem_wait(pal_sem_t *sem, pal_timeout_t timeout)
{
  if (pal_timeout_is_nowait(timeout)) {
    return sem_trywait(&sem->sem) == 0 ? 1 : errno == EAGAIN ? 0 : -1;
  } else if (pal_timeout_is_forever(timeout)) {
    return sem_wait(&sem->sem) == 0 ? 1 : -1;
  } else {
    struct timespec abs;
    pal_timeout_to_abs_timespec(timeout, &abs);
    int ret = sem_timedwait(&sem->sem, &abs);
    return ret == 0 ? 1 : errno == ETIMEDOUT ? 0 : -1;
  }
}

void
pal_sem_post(pal_sem_t *sem)
{
  int ret = sem_post(&sem->sem);
  pal_assert(ret == 0, "sem_post failed");
}
