#include <stdbool.h>
#include <unity.h>

#include <qwiet/platform/posix/net.h>
#include <qwiet/platform/testing/diode.h>
#include <qwiet/platform/testing/diode/net_recv.h>

void
setUp(void)
{
  diode_init();
}

void
tearDown(void)
{
  diode_verify();
  diode_destroy();
}

void
test_diode_recv_ok(void)
{
  uint8_t *expect = (uint8_t *)"hello";
  EXPECT_NET_RECV(3, 5, expect, 0, 5);

  uint8_t buf[5] = {0};
  int ret = pal_net_recv(3, buf, 5, 0);
  TEST_ASSERT_EQUAL_INT(5, ret);
  TEST_ASSERT_EQUAL_MEMORY("hello", buf, 5);
}

extern int
unity_main(void);

int
main(void)
{
  return unity_main();
}
