#include <qwiet/platform/time.h>
#include <time.h>

int
pal_timeout_to_poll_ms(pal_timeout_t t)
{
  if (t.ns < 0) {
    return -1; /* poll() uses -1 for infinite */
  } else if (t.ns == 0) {
    return 0;
  } else {
    /* Convert ns to ms, rounding up to avoid busy-wait on small values */
    int64_t ms = (t.ns + 999999LL) / 1000000LL;
    /* Clamp to INT_MAX */
    if (ms > INT_MAX) {
      return INT_MAX;
    }
    return (int)ms;
  }
}

void
pal_timeout_to_abs_timespec(pal_timeout_t t, struct timespec *out)
{
  pal_assert(!pal_timeout_is_forever(t), "cannot convert forever to timespec");
  pal_assert(out != NULL, "out is NULL");

  struct timespec now;
  clock_gettime(CLOCK_REALTIME, &now);

  int64_t total_ns = now.tv_nsec + t.ns;
  out->tv_sec = now.tv_sec + (time_t)(total_ns / 1000000000LL);
  out->tv_nsec = (long)(total_ns % 1000000000LL);
}
