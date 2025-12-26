#ifndef DIODE_INPUT_EVDEV_H
#define DIODE_INPUT_EVDEV_H

#include <qwiet/platform/common.h>
#include <qwiet/platform/common/list.h>
#include <qwiet/platform/linux/input/evdev.h>

struct evdev_expectation {
  struct pal_list_head node;
  int ret;
  struct input_event ev;
};

/*
 * Low-level event expectations
 */

#define EXPECT_EVDEV_EVENT(__type, __code, __value)                            \
  diode_evdev_create_expectation(                                              \
      LIBEVDEV_READ_STATUS_SUCCESS, (__type), (__code), (__value))

#define EXPECT_EVDEV_EAGAIN() diode_evdev_create_expectation(-1, 0, 0, 0)

#define EXPECT_EVDEV_SYNC(__type, __code, __value)                             \
  diode_evdev_create_expectation(                                              \
      LIBEVDEV_READ_STATUS_SYNC, (__type), (__code), (__value))

/*
 * High-level touch expectations
 *
 * These queue multiple events that together form a touch gesture.
 * Events are consumed in order by successive libevdev_next_event calls.
 */

#define EXPECT_TOUCH_DOWN(__x, __y)                                            \
  do {                                                                         \
    EXPECT_EVDEV_EVENT(EV_ABS, ABS_X, (__x));                                  \
    EXPECT_EVDEV_EVENT(EV_ABS, ABS_Y, (__y));                                  \
    EXPECT_EVDEV_EVENT(EV_KEY, BTN_TOUCH, 1);                                  \
    EXPECT_EVDEV_EVENT(EV_SYN, SYN_REPORT, 0);                                 \
  } while (0)

#define EXPECT_TOUCH_MOVE(__x, __y)                                            \
  do {                                                                         \
    EXPECT_EVDEV_EVENT(EV_ABS, ABS_X, (__x));                                  \
    EXPECT_EVDEV_EVENT(EV_ABS, ABS_Y, (__y));                                  \
    EXPECT_EVDEV_EVENT(EV_SYN, SYN_REPORT, 0);                                 \
  } while (0)

#define EXPECT_TOUCH_UP()                                                      \
  do {                                                                         \
    EXPECT_EVDEV_EVENT(EV_KEY, BTN_TOUCH, 0);                                  \
    EXPECT_EVDEV_EVENT(EV_SYN, SYN_REPORT, 0);                                 \
  } while (0)

/*
 * Stylus expectations (with pressure)
 */

#define EXPECT_STYLUS_DOWN(__x, __y, __pressure)                               \
  do {                                                                         \
    EXPECT_EVDEV_EVENT(EV_ABS, ABS_X, (__x));                                  \
    EXPECT_EVDEV_EVENT(EV_ABS, ABS_Y, (__y));                                  \
    EXPECT_EVDEV_EVENT(EV_ABS, ABS_PRESSURE, (__pressure));                    \
    EXPECT_EVDEV_EVENT(EV_KEY, BTN_TOOL_PEN, 1);                               \
    EXPECT_EVDEV_EVENT(EV_KEY, BTN_TOUCH, 1);                                  \
    EXPECT_EVDEV_EVENT(EV_SYN, SYN_REPORT, 0);                                 \
  } while (0)

#define EXPECT_STYLUS_MOVE(__x, __y, __pressure)                               \
  do {                                                                         \
    EXPECT_EVDEV_EVENT(EV_ABS, ABS_X, (__x));                                  \
    EXPECT_EVDEV_EVENT(EV_ABS, ABS_Y, (__y));                                  \
    EXPECT_EVDEV_EVENT(EV_ABS, ABS_PRESSURE, (__pressure));                    \
    EXPECT_EVDEV_EVENT(EV_SYN, SYN_REPORT, 0);                                 \
  } while (0)

#define EXPECT_STYLUS_UP()                                                     \
  do {                                                                         \
    EXPECT_EVDEV_EVENT(EV_KEY, BTN_TOUCH, 0);                                  \
    EXPECT_EVDEV_EVENT(EV_KEY, BTN_TOOL_PEN, 0);                               \
    EXPECT_EVDEV_EVENT(EV_SYN, SYN_REPORT, 0);                                 \
  } while (0)

#ifdef __cplusplus
extern "C" {
#endif

void
diode_evdev_init(void);

void
diode_evdev_cleanup(void);

void
diode_evdev_verify(void);

struct evdev_expectation *
diode_evdev_create_expectation(int ret, int type, int code, int value);

#ifdef __cplusplus
}
#endif

#endif /* DIODE_INPUT_EVDEV_H */
