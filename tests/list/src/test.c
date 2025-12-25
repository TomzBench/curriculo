#include <stdbool.h>
#include <unity.h>

#include <qwiet/platform/common/list.h>

struct test_item {
  int value;
  struct pal_list_head node;
};

static PAL_LIST_HEAD(test_list);

void
setUp(void)
{
  pal_list_init(&test_list);
}

void
tearDown(void)
{
}

/*
 * Sanity check for linked list operations.
 *
 * The list implementation is adapted from the Linux kernel with only
 * namespace changes. This test verifies add, iterate, and delete work
 * correctly as a basic smoke test.
 */
void
test_list_sanity_check(void)
{
  struct test_item items[3];
  struct test_item *pos, *n;
  int sum = 0;

  /* Add items */
  for (int i = 0; i < 3; i++) {
    items[i].value = i + 1;
    pal_list_init(&items[i].node);
    pal_list_add_tail(&items[i].node, &test_list);
  }

  TEST_ASSERT_EQUAL_size_t(3, pal_list_count_nodes(&test_list));

  /* Iterate and sum */
  pal_list_for_each_entry(pos, &test_list, node) { sum += pos->value; }
  TEST_ASSERT_EQUAL_INT(6, sum);

  /* Safe deletion */
  pal_list_for_each_entry_safe(pos, n, &test_list, node)
  {
    pal_list_del(&pos->node);
  }

  TEST_ASSERT_TRUE(pal_list_empty(&test_list));
}

extern int
unity_main(void);

int
main(void)
{
  return unity_main();
}
