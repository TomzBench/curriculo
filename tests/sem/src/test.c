#include "unity.h"
#include <qwiet/platform/sem.h>
#include <qwiet/platform/time.h>

void
setUp(void)
{
}

void
tearDown(void)
{
}

void
test_sem_ok(void)
{
  int ret;
  pal_sem_t sem;
  pal_sem_init(&sem, 0);

  ret = pal_sem_wait(&sem, PAL_NO_WAIT);
  TEST_ASSERT_EQUAL_INT(0, ret);

  ret = pal_sem_wait(&sem, PAL_MSEC(10));
  TEST_ASSERT_EQUAL_INT(0, ret);

  pal_sem_post(&sem);

  ret = pal_sem_wait(&sem, PAL_FOREVER);
  TEST_ASSERT_EQUAL_INT(1, ret);

  pal_sem_destroy(&sem);
}

extern int
unity_main(void);

int
main(void)
{
  return unity_main();
}
