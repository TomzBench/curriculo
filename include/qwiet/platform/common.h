#ifndef QWIET_COMMON_H
#define QWIET_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef PLATFORM_LINUX
#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h> /* IWYU pragma: keep (pal_assert) */
#include <stdlib.h>
#include <stdlib.h> /* IWYU pragma: keep (pal_assert) */
#include <string.h> /* IWYU pragma: keep (or add an include guard for testing */
#include <sys/poll.h>

#define pal_malloc(x) malloc(x)
#define pal_free(x) free(x)
#define pal_assert(cond, fmt, ...)                                             \
  do {                                                                         \
    if (!(cond)) {                                                             \
      fprintf(stderr,                                                          \
              "ASSERT FAILED: %s:%d (%s): " fmt "\n",                          \
              __FILE__,                                                        \
              __LINE__,                                                        \
              __func__,                                                        \
              ##__VA_ARGS__);                                                  \
      abort();                                                                 \
    }                                                                          \
  } while (0)

#endif /* PLATFORM_LINUX */

#ifdef __cplusplus
}
#endif

#endif
