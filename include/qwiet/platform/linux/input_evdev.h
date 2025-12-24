#ifndef QWIET_PLATFORM_LINUX_INPUT_EVDEV_H
#define QWIET_PLATFORM_LINUX_INPUT_EVDEV_H

#include <libevdev/libevdev.h>

#ifdef __cplusplus
extern "C" {
#endif

/* pal_input_evdev_t wraps libevdev's struct libevdev */
typedef struct libevdev pal_input_evdev_t;

/**
 * pal_input_evdev_new_from_fd - create evdev device from file descriptor
 * @fd: open file descriptor for /dev/input/eventX
 * @dev: pointer to store created device (caller frees via pal_input_evdev_free)
 *
 * Returns 0 on success, negative errno on failure.
 */
int
pal_input_evdev_new_from_fd(int fd, pal_input_evdev_t **dev);

/**
 * pal_input_evdev_next_event - read next input event from device
 * @dev: evdev device
 * @flags: read flags (PAL_INPUT_READ_FLAG_*)
 * @ev: output event structure
 *
 * Returns:
 *   PAL_INPUT_READ_STATUS_SUCCESS (0) - event available in ev
 *   PAL_INPUT_READ_STATUS_SYNC (1) - sync event, caller should continue reading
 *   -EAGAIN - no events available (non-blocking)
 *   other negative - error
 */
int
pal_input_evdev_next_event(pal_input_evdev_t *dev,
                           unsigned int flags,
                           struct input_event *ev);

/**
 * pal_input_evdev_free - free evdev device
 * @dev: device to free (may be NULL)
 */
void
pal_input_evdev_free(pal_input_evdev_t *dev);

/* Read flags (match libevdev values) */
#define PAL_INPUT_READ_FLAG_NORMAL 2
#define PAL_INPUT_READ_FLAG_SYNC 1

/* Read status (match libevdev values) */
#define PAL_INPUT_READ_STATUS_SUCCESS 0
#define PAL_INPUT_READ_STATUS_SYNC 1

#ifdef __cplusplus
}
#endif

#endif
