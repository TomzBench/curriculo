#include <stdbool.h>
#include <unity.h>

#include <qwiet/platform/posix/net.h>
#include <qwiet/platform/testing/diode.h>
#include <qwiet/platform/testing/diode/net_send.h>

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
test_diode_send_ok(void)
{
  const char *data = "hello";
  EXPECT_NET_SEND(3, data, 5, 0, 5);

  int ret = pal_net_send(3, data, 5, 0);
  TEST_ASSERT_EQUAL_INT(5, ret);
}

void
test_diode_send_err(void)
{
  const char *data = "hello";
  EXPECT_NET_SEND_ERR(3, 5, 0);

  int ret = pal_net_send(3, data, 5, 0);
  TEST_ASSERT_EQUAL_INT(-1, ret);
}

extern int
unity_main(void);

int
main(void)
{
  return unity_main();
}
