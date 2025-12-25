#ifndef QWIET_EVENT_H
#define QWIET_EVENT_H

#include <qwiet/platform/common.h>

#ifdef __cplusplus
extern "C" {
#endif

int
pal_event_fd();

int
pal_event_write(int sock, uint64_t val);

int
pal_event_read(int sock, uint64_t *val);

#ifdef __cplusplus
}
#endif

#endif
