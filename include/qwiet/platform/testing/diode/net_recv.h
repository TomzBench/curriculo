#ifndef DIODE_RECV_H
#define DIODE_RECV_H

#include <qwiet/platform/net.h>
#include "unity_mock_net.h"

#define EXPECT_NET_RECV(__socket, __length, __buff, __flags, __ret)            \
  do {                                                                         \
    __wrap_pal_net_recv_ExpectAndReturn(                                       \
        __socket, __buff, __length, __flags, __ret);                           \
    if (__ret > 0) {                                                           \
      __wrap_pal_net_recv_ReturnMemThruPtr_buf(__buff, __ret);                 \
    }                                                                          \
    __wrap_pal_net_recv_IgnoreArg_buf();                                       \
  } while (0)

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif
