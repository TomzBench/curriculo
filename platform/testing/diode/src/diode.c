#include <curriculo/platform/testing/diode/poll.h>

void
diode_init(void)
{
  diode_poll_init();
}

void
diode_destroy(void)
{
  diode_poll_cleanup();
}

void
diode_verify(void)
{
  diode_poll_verify();
}
