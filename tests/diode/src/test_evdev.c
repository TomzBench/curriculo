#include <stdbool.h>
#include <unity.h>

#include <qwiet/platform/testing/diode.h>
#include <qwiet/platform/testing/diode/input/evdev.h>

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
test_diode_evdev_single_event(void)
{
  struct input_event ev;
  int ret;

  EXPECT_EVDEV_EVENT(EV_ABS, ABS_X, 500);

  ret = libevdev_next_event(NULL, LIBEVDEV_READ_FLAG_NORMAL, &ev);

  TEST_ASSERT_EQUAL_INT(LIBEVDEV_READ_STATUS_SUCCESS, ret);
  TEST_ASSERT_EQUAL_INT(EV_ABS, ev.type);
  TEST_ASSERT_EQUAL_INT(ABS_X, ev.code);
  TEST_ASSERT_EQUAL_INT(500, ev.value);
}

void
test_diode_evdev_touch_down(void)
{
  struct input_event ev;
  int ret;

  EXPECT_TOUCH_DOWN(100, 200);

  /* Event 1: ABS_X */
  ret = libevdev_next_event(NULL, LIBEVDEV_READ_FLAG_NORMAL, &ev);
  TEST_ASSERT_EQUAL_INT(LIBEVDEV_READ_STATUS_SUCCESS, ret);
  TEST_ASSERT_EQUAL_INT(EV_ABS, ev.type);
  TEST_ASSERT_EQUAL_INT(ABS_X, ev.code);
  TEST_ASSERT_EQUAL_INT(100, ev.value);

  /* Event 2: ABS_Y */
  ret = libevdev_next_event(NULL, LIBEVDEV_READ_FLAG_NORMAL, &ev);
  TEST_ASSERT_EQUAL_INT(LIBEVDEV_READ_STATUS_SUCCESS, ret);
  TEST_ASSERT_EQUAL_INT(EV_ABS, ev.type);
  TEST_ASSERT_EQUAL_INT(ABS_Y, ev.code);
  TEST_ASSERT_EQUAL_INT(200, ev.value);

  /* Event 3: BTN_TOUCH down */
  ret = libevdev_next_event(NULL, LIBEVDEV_READ_FLAG_NORMAL, &ev);
  TEST_ASSERT_EQUAL_INT(LIBEVDEV_READ_STATUS_SUCCESS, ret);
  TEST_ASSERT_EQUAL_INT(EV_KEY, ev.type);
  TEST_ASSERT_EQUAL_INT(BTN_TOUCH, ev.code);
  TEST_ASSERT_EQUAL_INT(1, ev.value);

  /* Event 4: SYN_REPORT */
  ret = libevdev_next_event(NULL, LIBEVDEV_READ_FLAG_NORMAL, &ev);
  TEST_ASSERT_EQUAL_INT(LIBEVDEV_READ_STATUS_SUCCESS, ret);
  TEST_ASSERT_EQUAL_INT(EV_SYN, ev.type);
  TEST_ASSERT_EQUAL_INT(SYN_REPORT, ev.code);
  TEST_ASSERT_EQUAL_INT(0, ev.value);
}

void
test_diode_evdev_eagain(void)
{
  struct input_event ev;
  int ret;

  EXPECT_EVDEV_EAGAIN();

  ret = libevdev_next_event(NULL, LIBEVDEV_READ_FLAG_NORMAL, &ev);

  TEST_ASSERT_EQUAL_INT(-1, ret);
}

void
test_diode_evdev_stylus_stroke(void)
{
  struct input_event ev;
  int ret;

  EXPECT_STYLUS_DOWN(500, 300, 2000);
  EXPECT_STYLUS_MOVE(510, 310, 2100);
  EXPECT_STYLUS_UP();

  /* Consume stylus down events (6 events) */
  for (int i = 0; i < 6; i++) {
    ret = libevdev_next_event(NULL, LIBEVDEV_READ_FLAG_NORMAL, &ev);
    TEST_ASSERT_EQUAL_INT(LIBEVDEV_READ_STATUS_SUCCESS, ret);
  }

  /* Consume stylus move events (4 events) */
  for (int i = 0; i < 4; i++) {
    ret = libevdev_next_event(NULL, LIBEVDEV_READ_FLAG_NORMAL, &ev);
    TEST_ASSERT_EQUAL_INT(LIBEVDEV_READ_STATUS_SUCCESS, ret);
  }

  /* Consume stylus up events (3 events) */
  for (int i = 0; i < 3; i++) {
    ret = libevdev_next_event(NULL, LIBEVDEV_READ_FLAG_NORMAL, &ev);
    TEST_ASSERT_EQUAL_INT(LIBEVDEV_READ_STATUS_SUCCESS, ret);
  }
}

extern int
unity_main(void);

int
main(void)
{
  return unity_main();
}
