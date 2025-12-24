#include <qwiet/platform/linux/input_evdev.h>

int
pal_input_evdev_new_from_fd(int fd, pal_input_evdev_t **dev)
{
  return libevdev_new_from_fd(fd, (struct libevdev **)dev);
}

int
pal_input_evdev_next_event(pal_input_evdev_t *dev,
                           unsigned int flags,
                           struct input_event *ev)
{
  return libevdev_next_event((struct libevdev *)dev, flags, ev);
}

void
pal_input_evdev_free(pal_input_evdev_t *dev)
{
  libevdev_free((struct libevdev *)dev);
}
