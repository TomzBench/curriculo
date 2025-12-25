#ifndef DIODE_CONNECT_H
#define DIODE_CONNECT_H

#include "unity_mock_net.h"
#include <qwiet/platform/posix/net.h>

// NOTE: The PAL abstraction layer does not currently expose error types.
// All failures return -1. When error type support is added, expand this
// interface with specific error expectations (e.g.,
// EXPECT_NET_CONNECT_REFUSED).

#define EXPECT_NET_CONNECT(__socket, __ip, __port, __ret)                      \
  do {                                                                         \
    __wrap_pal_net_connect_ExpectAndReturn(__socket, __ip, __port, __ret);     \
  } while (0)

#define EXPECT_NET_CONNECT_ERR(__socket, __ip, __port)                         \
  do {                                                                         \
    __wrap_pal_net_connect_ExpectAndReturn(__socket, __ip, __port, -1);        \
  } while (0)

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif
