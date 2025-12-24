#include "unity_mock_net.h"
#include <qwiet/platform/testing/diode/net_poll.h>

#ifdef PLATFORM_LINUX
#include "unity_mock_input_evdev.h"
#include <qwiet/platform/testing/diode/input_evdev.h>
#endif

void
diode_init(void)
{
  unity_mock_net_Init();
  diode_poll_init();
#ifdef PLATFORM_LINUX
  unity_mock_input_evdev_Init();
  diode_evdev_init();
#endif
}

void
diode_destroy(void)
{
  diode_poll_cleanup();
  unity_mock_net_Destroy();
#ifdef PLATFORM_LINUX
  diode_evdev_cleanup();
  unity_mock_input_evdev_Destroy();
#endif
}

void
diode_verify(void)
{
  unity_mock_net_Verify();
  diode_poll_verify();
#ifdef PLATFORM_LINUX
  unity_mock_input_evdev_Verify();
  diode_evdev_verify();
#endif
}
