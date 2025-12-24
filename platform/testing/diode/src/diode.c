#include "unity_mock_net.h"
#include <qwiet/platform/testing/diode/net_poll.h>

void
diode_init(void)
{
  unity_mock_net_Init();
  diode_poll_init();
}

void
diode_destroy(void)
{
  diode_poll_cleanup();
  unity_mock_net_Destroy();
}

void
diode_verify(void)
{
  unity_mock_net_Verify();
  diode_poll_verify();
}
