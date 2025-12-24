#include "unity.h"
#include "unity_mock_input_evdev.h"
#include <qwiet/platform/testing/diode/input_evdev.h>

static struct pal_list_head __list;

static int
__verify_next_event(pal_input_evdev_t *dev,
                    unsigned int flags,
                    struct input_event *ev,
                    int ncalls)
{
  struct pal_list_head *node = NULL;
  struct evdev_expectation *expect = NULL;

  (void)dev;
  (void)flags;
  (void)ncalls;

  node = __list.next;
  TEST_ASSERT_NOT_NULL_MESSAGE(node,
                               "pal_input_evdev_next_event called but no "
                               "expectations queued");

  expect = pal_list_entry(node, struct evdev_expectation, node);

  /* Only populate ev if returning an event (not -EAGAIN or error) */
  if (expect->ret >= 0) {
    ev->type = expect->ev.type;
    ev->code = expect->ev.code;
    ev->value = expect->ev.value;
  }

  int ret = expect->ret;
  pal_list_del(&expect->node);
  pal_free(expect);
  return ret;
}

void
diode_evdev_init(void)
{
  pal_list_init(&__list);
  __wrap_pal_input_evdev_next_event_Stub(__verify_next_event);
}

void
diode_evdev_cleanup(void)
{
  struct pal_list_head *pos, *n;
  struct evdev_expectation *expect;

  pal_list_for_each_safe(pos, n, &__list)
  {
    pal_list_del(pos);
    expect = pal_list_entry(pos, struct evdev_expectation, node);
    pal_free(expect);
  }
}

void
diode_evdev_verify(void)
{
  TEST_ASSERT_TRUE_MESSAGE(
      pal_list_empty(&__list),
      "pal_input_evdev_next_event called fewer times than expected");
}

struct evdev_expectation *
diode_evdev_create_expectation(int ret, int type, int code, int value)
{
  struct evdev_expectation *e = pal_malloc(sizeof(*e));

  e->ret = ret;
  e->ev.type = type;
  e->ev.code = code;
  e->ev.value = value;
  e->ev.time.tv_sec = 0;
  e->ev.time.tv_usec = 0;

  pal_list_init(&e->node);
  pal_list_add_tail(&e->node, &__list);

  return e;
}
