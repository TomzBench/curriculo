#ifndef DIODE_LISTEN_H
#define DIODE_LISTEN_H

#include "unity_mock_net.h"
#include <qwiet/platform/posix/net.h>

// NOTE: The PAL abstraction layer does not currently expose error types.
// All failures return -1. When error type support is added, expand this
// interface with specific error expectations (e.g.,
// EXPECT_NET_LISTEN_EADDRINUSE).

#define EXPECT_NET_LISTEN(__socket, __port, __backlog, __ret)                  \
  do {                                                                         \
    __wrap_pal_net_listen_ExpectAndReturn(__socket, __port, __backlog, __ret); \
  } while (0)

#define EXPECT_NET_LISTEN_ERR(__socket, __port, __backlog)                     \
  do {                                                                         \
    __wrap_pal_net_listen_ExpectAndReturn(__socket, __port, __backlog, -1);    \
  } while (0)

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif
