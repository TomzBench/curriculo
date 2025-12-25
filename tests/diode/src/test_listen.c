#include <stdbool.h>
#include <unity.h>

#include <qwiet/platform/posix/net.h>
#include <qwiet/platform/testing/diode.h>
#include <qwiet/platform/testing/diode/net_listen.h>

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
test_diode_listen_ok(void)
{
  EXPECT_NET_LISTEN(3, 8080, 5, 0);

  int ret = pal_net_listen(3, 8080, 5);
  TEST_ASSERT_EQUAL_INT(0, ret);
}

void
test_diode_listen_err(void)
{
  EXPECT_NET_LISTEN_ERR(3, 8080, 5);

  int ret = pal_net_listen(3, 8080, 5);
  TEST_ASSERT_EQUAL_INT(-1, ret);
}

extern int
unity_main(void);

int
main(void)
{
  return unity_main();
}
