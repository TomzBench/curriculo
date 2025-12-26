/**
 * @file libevdev.h
 * @brief Surgical mock declarations for libevdev functions
 *
 * This header declares only the libevdev functions we mock.
 * CMock parses this file instead of the full libevdev header.
 */

#ifndef DIODE_MOCKS_LIBEVDEV_H
#define DIODE_MOCKS_LIBEVDEV_H

#include <qwiet/platform/linux/input/evdev.h>

int
libevdev_new_from_fd(int fd, struct libevdev **dev);

int
libevdev_next_event(struct libevdev *dev,
                    unsigned int flags,
                    struct input_event *ev);

void
libevdev_free(struct libevdev *dev);

#endif
