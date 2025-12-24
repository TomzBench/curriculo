#include <stdbool.h>
#include <unity.h>

#include "qwiet/platform/testing/diode/poll.h"
#include "stubs.h"
#include "unity_mock_stubs.h"
#include <qwiet/platform/net.h>
#include <qwiet/platform/testing/diode.h>

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
test_diode_poll_expect_ok(void)
{
  struct pollfd pfds[4] = {
      {.fd = 1, .events = 0, .revents = 0},
      {.fd = 2, .events = 0, .revents = 0},
      {.fd = 3, .events = POLLIN, .revents = 0},
      {.fd = 4, .events = POLLOUT, .revents = 0},
  };
  int ret;

  // Create our expectation, validate the macros populate expectation correctly
  struct poll_expectation *e = EXPECT_POLL_OK(100, "xxio", "xxeo", 1, 2, 3, 4);
  TEST_ASSERT_EQUAL_INT(2, e->ret);
  TEST_ASSERT_EQUAL_INT(4, e->nfds);
  TEST_ASSERT_EQUAL_INT(100, e->timeout);
  TEST_ASSERT_EQUAL_INT(1, e->fds[0].fd);
  TEST_ASSERT_EQUAL_INT(2, e->fds[1].fd);
  TEST_ASSERT_EQUAL_INT(3, e->fds[2].fd);
  TEST_ASSERT_EQUAL_INT(4, e->fds[3].fd);
  TEST_ASSERT_EQUAL_INT(1, e->fds[4].fd);
  TEST_ASSERT_EQUAL_INT(2, e->fds[5].fd);
  TEST_ASSERT_EQUAL_INT(3, e->fds[6].fd);
  TEST_ASSERT_EQUAL_INT(4, e->fds[7].fd);
  TEST_ASSERT_EQUAL_INT(0, e->fds[0].events);
  TEST_ASSERT_EQUAL_INT(0, e->fds[1].events);
  TEST_ASSERT_EQUAL_INT(POLLIN, e->fds[2].events);
  TEST_ASSERT_EQUAL_INT(POLLOUT, e->fds[3].events);
  TEST_ASSERT_EQUAL_INT(0, e->fds[4].events);
  TEST_ASSERT_EQUAL_INT(0, e->fds[5].events);
  TEST_ASSERT_EQUAL_INT(POLLIN, e->fds[6].events);
  TEST_ASSERT_EQUAL_INT(POLLOUT, e->fds[7].events);
  TEST_ASSERT_EQUAL_INT(0, e->fds[0].revents);
  TEST_ASSERT_EQUAL_INT(0, e->fds[1].revents);
  TEST_ASSERT_EQUAL_INT(0, e->fds[2].revents);
  TEST_ASSERT_EQUAL_INT(0, e->fds[3].revents);
  TEST_ASSERT_EQUAL_INT(0, e->fds[4].revents);
  TEST_ASSERT_EQUAL_INT(0, e->fds[5].revents);
  TEST_ASSERT_EQUAL_INT(POLLERR, e->fds[6].revents);
  TEST_ASSERT_EQUAL_INT(POLLOUT, e->fds[7].revents);

  // Call our stub, verify return and return_thru_ptrs
  ret = pal_net_socket_poll(pfds, 4, 100);
  TEST_ASSERT_EQUAL_INT(2, ret);
  TEST_ASSERT_EQUAL_INT(0, pfds[0].revents);
  TEST_ASSERT_EQUAL_INT(0, pfds[1].revents);
  TEST_ASSERT_EQUAL_INT(POLLERR, pfds[2].revents);
  TEST_ASSERT_EQUAL_INT(POLLOUT, pfds[3].revents);
}

void
test_sanity_check(void)
{
  TEST_ASSERT_TRUE(true);
}

void
test_mock_get_value(void)
{
  /* Set expectation: stub_get_value() will return 42 */
  __wrap_stub_get_value_ExpectAndReturn(42);

  /* Call the mocked function */
  int result = stub_get_value();

  TEST_ASSERT_EQUAL_INT(42, result);
}

void
test_mock_add(void)
{
  /* Set expectation: stub_add(10, 20) will return 30 */
  __wrap_stub_add_ExpectAndReturn(10, 20, 30);

  /* Call the mocked function */
  int result = stub_add(10, 20);

  TEST_ASSERT_EQUAL_INT(30, result);
}

extern int
unity_main(void);

int
main(void)
{
  return unity_main();
}
