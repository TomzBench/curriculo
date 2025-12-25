#include <unity.h>

#include <qwiet/platform/common/macros.h>

void
setUp(void)
{
}

void
tearDown(void)
{
}

/*
 * Test PAL_CONTAINER_OF with member at non-zero offset.
 *
 * Verifies pointer arithmetic and offsetof() work correctly, which could
 * vary on embedded platforms with different pointer sizes or alignment.
 */
void
test_container_of_nonzero_offset(void)
{
  struct test_struct {
    int before;
    char member;
    int after;
  };

  struct test_struct obj = {.before = 0xDEAD, .member = 'X', .after = 0xBEEF};

  char *member_ptr = &obj.member;
  struct test_struct *recovered =
      PAL_CONTAINER_OF(member_ptr, struct test_struct, member);

  TEST_ASSERT_EQUAL_PTR(&obj, recovered);
  TEST_ASSERT_EQUAL_INT(0xDEAD, recovered->before);
  TEST_ASSERT_EQUAL_CHAR('X', recovered->member);
  TEST_ASSERT_EQUAL_INT(0xBEEF, recovered->after);
}

/*
 * Test PAL_CONTAINER_OF with member at offset zero.
 *
 * Edge case where offsetof() returns 0, ensuring the subtraction
 * doesn't cause issues.
 */
void
test_container_of_zero_offset(void)
{
  struct test_struct {
    int first;
    int second;
  };

  struct test_struct obj = {.first = 42, .second = 99};

  int *first_ptr = &obj.first;
  struct test_struct *recovered =
      PAL_CONTAINER_OF(first_ptr, struct test_struct, first);

  TEST_ASSERT_EQUAL_PTR(&obj, recovered);
  TEST_ASSERT_EQUAL_INT(42, recovered->first);
  TEST_ASSERT_EQUAL_INT(99, recovered->second);
}

/*
 * Test PAL_NUM_VA_ARGS counts arguments correctly.
 *
 * The macro supports 1-16 arguments. Test representative values.
 */
void
test_num_va_args(void)
{
  TEST_ASSERT_EQUAL_INT(1, PAL_NUM_VA_ARGS(a));
  TEST_ASSERT_EQUAL_INT(2, PAL_NUM_VA_ARGS(a, b));
  TEST_ASSERT_EQUAL_INT(3, PAL_NUM_VA_ARGS(a, b, c));
  TEST_ASSERT_EQUAL_INT(4, PAL_NUM_VA_ARGS(a, b, c, d));
  TEST_ASSERT_EQUAL_INT(5, PAL_NUM_VA_ARGS(a, b, c, d, e));
  TEST_ASSERT_EQUAL_INT(8, PAL_NUM_VA_ARGS(1, 2, 3, 4, 5, 6, 7, 8));
  TEST_ASSERT_EQUAL_INT(
      16,
      PAL_NUM_VA_ARGS(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16));
}

extern int
unity_main(void);

int
main(void)
{
  return unity_main();
}
