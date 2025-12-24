#include <stdbool.h>
#include <unity.h>

#include <qwiet/platform/net.h>
#include <qwiet/platform/testing/diode.h>
#include <qwiet/platform/testing/diode/net_connect.h>

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
test_diode_connect_ok(void)
{
  EXPECT_NET_CONNECT(3, "127.0.0.1", 8080, 0);

  int ret = pal_net_connect(3, "127.0.0.1", 8080);
  TEST_ASSERT_EQUAL_INT(0, ret);
}

void
test_diode_connect_err(void)
{
  EXPECT_NET_CONNECT_ERR(3, "127.0.0.1", 8080);

  int ret = pal_net_connect(3, "127.0.0.1", 8080);
  TEST_ASSERT_EQUAL_INT(-1, ret);
}

extern int
unity_main(void);

int
main(void)
{
  return unity_main();
}
