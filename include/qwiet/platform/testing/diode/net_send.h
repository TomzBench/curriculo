#ifndef DIODE_SEND_H
#define DIODE_SEND_H

#include "unity_mock_net.h"
#include <qwiet/platform/posix/net.h>

// NOTE: The PAL abstraction layer does not currently expose error types.
// All failures return -1. When error type support is added, expand this
// interface with specific error expectations (e.g., EXPECT_NET_SEND_EAGAIN).

#define EXPECT_NET_SEND(__socket, __buf, __len, __flags, __ret)                \
  do {                                                                         \
    __wrap_pal_net_send_ExpectWithArrayAndReturn(                              \
        __socket, __buf, __len, __len, __flags, __ret);                        \
  } while (0)

#define EXPECT_NET_SEND_ERR(__socket, __len, __flags)                          \
  do {                                                                         \
    __wrap_pal_net_send_ExpectAnyArgsAndReturn(-1);                            \
  } while (0)

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif
