#ifndef DIODE_H
#define DIODE_H

#include <qwiet/platform/testing/diode/net_connect.h>
#include <qwiet/platform/testing/diode/net_listen.h>
#include <qwiet/platform/testing/diode/net_poll.h>
#include <qwiet/platform/testing/diode/net_send.h>

#ifdef __cplusplus
extern "C" {
#endif

//! brief run unity init routines
void
diode_init(void);

//! brief run unity destroy routines
void
diode_destroy(void);

//! brief run unity verification routines
void
diode_verify(void);

#ifdef __cplusplus
}
#endif
#endif
