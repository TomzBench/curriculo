#include <stdbool.h>
#include <unity.h>

#include "curriculo/platform/common/list.h"

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

/* Basic list operations */

void
test_list_head_init(void)
{
  PAL_LIST_HEAD(mylist);
  TEST_ASSERT_TRUE(pal_list_empty(&mylist));
  TEST_ASSERT_EQUAL_PTR(mylist.next, &mylist);
  TEST_ASSERT_EQUAL_PTR(mylist.prev, &mylist);
}

void
test_init_list_head(void)
{
  struct pal_list_head mylist;
  pal_list_init(&mylist);
  TEST_ASSERT_TRUE(pal_list_empty(&mylist));
}

void
test_list_add(void)
{
  struct test_item item1 = {.value = 1};
  struct test_item item2 = {.value = 2};

  pal_list_init(&item1.node);
  pal_list_init(&item2.node);

  pal_list_add(&item1.node, &test_list);
  TEST_ASSERT_FALSE(pal_list_empty(&test_list));
  TEST_ASSERT_TRUE(pal_list_is_singular(&test_list));

  pal_list_add(&item2.node, &test_list);
  TEST_ASSERT_FALSE(pal_list_is_singular(&test_list));

  /* item2 should be first (stack behavior) */
  struct test_item *first =
      pal_list_first_entry(&test_list, struct test_item, node);
  TEST_ASSERT_EQUAL_INT(2, first->value);
}

void
test_list_add_tail(void)
{
  struct test_item item1 = {.value = 1};
  struct test_item item2 = {.value = 2};

  pal_list_init(&item1.node);
  pal_list_init(&item2.node);

  pal_list_add_tail(&item1.node, &test_list);
  pal_list_add_tail(&item2.node, &test_list);

  /* item1 should be first (queue behavior) */
  struct test_item *first =
      pal_list_first_entry(&test_list, struct test_item, node);
  TEST_ASSERT_EQUAL_INT(1, first->value);

  struct test_item *last =
      pal_list_last_entry(&test_list, struct test_item, node);
  TEST_ASSERT_EQUAL_INT(2, last->value);
}

void
test_list_del(void)
{
  struct test_item item1 = {.value = 1};
  struct test_item item2 = {.value = 2};

  pal_list_init(&item1.node);
  pal_list_init(&item2.node);

  pal_list_add(&item1.node, &test_list);
  pal_list_add(&item2.node, &test_list);

  pal_list_del(&item2.node);
  TEST_ASSERT_TRUE(pal_list_is_singular(&test_list));

  struct test_item *first =
      pal_list_first_entry(&test_list, struct test_item, node);
  TEST_ASSERT_EQUAL_INT(1, first->value);
}

void
test_list_del_init(void)
{
  struct test_item item1 = {.value = 1};

  pal_list_init(&item1.node);
  pal_list_add(&item1.node, &test_list);

  pal_list_del_init(&item1.node);
  TEST_ASSERT_TRUE(pal_list_empty(&test_list));

  /* Node should be reinitialized (points to itself) */
  TEST_ASSERT_EQUAL_PTR(item1.node.next, &item1.node);
  TEST_ASSERT_EQUAL_PTR(item1.node.prev, &item1.node);
}

void
test_list_replace(void)
{
  struct test_item item1 = {.value = 1};
  struct test_item item2 = {.value = 2};

  pal_list_init(&item1.node);
  pal_list_init(&item2.node);

  pal_list_add(&item1.node, &test_list);
  pal_list_replace(&item1.node, &item2.node);

  struct test_item *first =
      pal_list_first_entry(&test_list, struct test_item, node);
  TEST_ASSERT_EQUAL_INT(2, first->value);
}

void
test_list_move(void)
{
  PAL_LIST_HEAD(other_list);
  struct test_item item1 = {.value = 1};

  pal_list_init(&item1.node);

  pal_list_add(&item1.node, &test_list);
  TEST_ASSERT_FALSE(pal_list_empty(&test_list));
  TEST_ASSERT_TRUE(pal_list_empty(&other_list));

  pal_list_move(&item1.node, &other_list);
  TEST_ASSERT_TRUE(pal_list_empty(&test_list));
  TEST_ASSERT_FALSE(pal_list_empty(&other_list));
}

void
test_list_move_tail(void)
{
  PAL_LIST_HEAD(other_list);
  struct test_item item1 = {.value = 1};
  struct test_item item2 = {.value = 2};

  pal_list_init(&item1.node);
  pal_list_init(&item2.node);

  pal_list_add(&item1.node, &other_list);
  pal_list_add(&item2.node, &test_list);

  pal_list_move_tail(&item2.node, &other_list);

  struct test_item *last =
      pal_list_last_entry(&other_list, struct test_item, node);
  TEST_ASSERT_EQUAL_INT(2, last->value);
}

/* List query operations */

void
test_list_is_first(void)
{
  struct test_item item1 = {.value = 1};
  struct test_item item2 = {.value = 2};

  pal_list_init(&item1.node);
  pal_list_init(&item2.node);

  pal_list_add_tail(&item1.node, &test_list);
  pal_list_add_tail(&item2.node, &test_list);

  TEST_ASSERT_TRUE(pal_list_is_first(&item1.node, &test_list));
  TEST_ASSERT_FALSE(pal_list_is_first(&item2.node, &test_list));
}

void
test_list_is_last(void)
{
  struct test_item item1 = {.value = 1};
  struct test_item item2 = {.value = 2};

  pal_list_init(&item1.node);
  pal_list_init(&item2.node);

  pal_list_add_tail(&item1.node, &test_list);
  pal_list_add_tail(&item2.node, &test_list);

  TEST_ASSERT_FALSE(pal_list_is_last(&item1.node, &test_list));
  TEST_ASSERT_TRUE(pal_list_is_last(&item2.node, &test_list));
}

void
test_list_empty(void)
{
  struct test_item item1 = {.value = 1};

  pal_list_init(&item1.node);

  TEST_ASSERT_TRUE(pal_list_empty(&test_list));

  pal_list_add(&item1.node, &test_list);
  TEST_ASSERT_FALSE(pal_list_empty(&test_list));
}

void
test_list_is_singular(void)
{
  struct test_item item1 = {.value = 1};
  struct test_item item2 = {.value = 2};

  pal_list_init(&item1.node);
  pal_list_init(&item2.node);

  TEST_ASSERT_FALSE(pal_list_is_singular(&test_list));

  pal_list_add(&item1.node, &test_list);
  TEST_ASSERT_TRUE(pal_list_is_singular(&test_list));

  pal_list_add(&item2.node, &test_list);
  TEST_ASSERT_FALSE(pal_list_is_singular(&test_list));
}

void
test_list_count_nodes(void)
{
  struct test_item items[5];

  TEST_ASSERT_EQUAL_size_t(0, pal_list_count_nodes(&test_list));

  for (int i = 0; i < 5; i++) {
    items[i].value = i;
    pal_list_init(&items[i].node);
    pal_list_add_tail(&items[i].node, &test_list);
  }

  TEST_ASSERT_EQUAL_size_t(5, pal_list_count_nodes(&test_list));
}

/* List entry macros */

void
test_list_entry(void)
{
  struct test_item item1 = {.value = 42};

  pal_list_init(&item1.node);
  pal_list_add(&item1.node, &test_list);

  struct pal_list_head *ptr = test_list.next;
  struct test_item *entry = pal_list_entry(ptr, struct test_item, node);

  TEST_ASSERT_EQUAL_INT(42, entry->value);
}

void
test_list_first_entry_or_null(void)
{
  struct test_item item1 = {.value = 42};

  /* Empty list should return NULL */
  struct test_item *entry =
      pal_list_first_entry_or_null(&test_list, struct test_item, node);
  TEST_ASSERT_NULL(entry);

  pal_list_init(&item1.node);
  pal_list_add(&item1.node, &test_list);

  entry = pal_list_first_entry_or_null(&test_list, struct test_item, node);
  TEST_ASSERT_NOT_NULL(entry);
  TEST_ASSERT_EQUAL_INT(42, entry->value);
}

void
test_list_last_entry_or_null(void)
{
  struct test_item item1 = {.value = 1};
  struct test_item item2 = {.value = 2};

  /* Empty list should return NULL */
  struct test_item *entry =
      pal_list_last_entry_or_null(&test_list, struct test_item, node);
  TEST_ASSERT_NULL(entry);

  pal_list_init(&item1.node);
  pal_list_init(&item2.node);
  pal_list_add_tail(&item1.node, &test_list);
  pal_list_add_tail(&item2.node, &test_list);

  entry = pal_list_last_entry_or_null(&test_list, struct test_item, node);
  TEST_ASSERT_NOT_NULL(entry);
  TEST_ASSERT_EQUAL_INT(2, entry->value);
}

/* Iteration macros */

void
test_list_for_each(void)
{
  struct test_item items[3];
  struct pal_list_head *pos;
  int count = 0;

  for (int i = 0; i < 3; i++) {
    items[i].value = i;
    pal_list_init(&items[i].node);
    pal_list_add_tail(&items[i].node, &test_list);
  }

  pal_list_for_each(pos, &test_list) { count++; }

  TEST_ASSERT_EQUAL_INT(3, count);
}

void
test_list_for_each_safe(void)
{
  struct test_item items[3];
  struct pal_list_head *pos, *n;
  int count = 0;

  for (int i = 0; i < 3; i++) {
    items[i].value = i;
    pal_list_init(&items[i].node);
    pal_list_add_tail(&items[i].node, &test_list);
  }

  /* Safe iteration allows removal during iteration */
  pal_list_for_each_safe(pos, n, &test_list)
  {
    pal_list_del(pos);
    count++;
  }

  TEST_ASSERT_EQUAL_INT(3, count);
  TEST_ASSERT_TRUE(pal_list_empty(&test_list));
}

void
test_list_for_each_entry(void)
{
  struct test_item items[3];
  struct test_item *pos;
  int sum = 0;

  for (int i = 0; i < 3; i++) {
    items[i].value = i + 1; /* 1, 2, 3 */
    pal_list_init(&items[i].node);
    pal_list_add_tail(&items[i].node, &test_list);
  }

  pal_list_for_each_entry(pos, &test_list, node) { sum += pos->value; }

  TEST_ASSERT_EQUAL_INT(6, sum); /* 1 + 2 + 3 = 6 */
}

void
test_list_for_each_entry_reverse(void)
{
  struct test_item items[3];
  struct test_item *pos;
  int values[3];
  int idx = 0;

  for (int i = 0; i < 3; i++) {
    items[i].value = i + 1; /* 1, 2, 3 */
    pal_list_init(&items[i].node);
    pal_list_add_tail(&items[i].node, &test_list);
  }

  pal_list_for_each_entry_reverse(pos, &test_list, node)
  {
    values[idx++] = pos->value;
  }

  TEST_ASSERT_EQUAL_INT(3, values[0]);
  TEST_ASSERT_EQUAL_INT(2, values[1]);
  TEST_ASSERT_EQUAL_INT(1, values[2]);
}

void
test_list_for_each_entry_safe(void)
{
  struct test_item items[3];
  struct test_item *pos, *n;

  for (int i = 0; i < 3; i++) {
    items[i].value = i;
    pal_list_init(&items[i].node);
    pal_list_add_tail(&items[i].node, &test_list);
  }

  /* Remove all even-valued entries */
  pal_list_for_each_entry_safe(pos, n, &test_list, node)
  {
    if (pos->value % 2 == 0) {
      pal_list_del(&pos->node);
    }
  }

  /* Only item with value 1 should remain */
  TEST_ASSERT_TRUE(pal_list_is_singular(&test_list));
  struct test_item *remaining =
      pal_list_first_entry(&test_list, struct test_item, node);
  TEST_ASSERT_EQUAL_INT(1, remaining->value);
}

/* Splice operations */

void
test_list_splice(void)
{
  PAL_LIST_HEAD(other_list);
  struct test_item item1 = {.value = 1};
  struct test_item item2 = {.value = 2};
  struct test_item item3 = {.value = 3};

  pal_list_init(&item1.node);
  pal_list_init(&item2.node);
  pal_list_init(&item3.node);

  pal_list_add_tail(&item1.node, &test_list);
  pal_list_add_tail(&item2.node, &other_list);
  pal_list_add_tail(&item3.node, &other_list);

  pal_list_splice(&other_list, &test_list);

  TEST_ASSERT_EQUAL_size_t(3, pal_list_count_nodes(&test_list));

  /* Order should be: item2, item3, item1 (splice adds after head) */
  struct test_item *first =
      pal_list_first_entry(&test_list, struct test_item, node);
  TEST_ASSERT_EQUAL_INT(2, first->value);
}

void
test_list_splice_tail(void)
{
  PAL_LIST_HEAD(other_list);
  struct test_item item1 = {.value = 1};
  struct test_item item2 = {.value = 2};

  pal_list_init(&item1.node);
  pal_list_init(&item2.node);

  pal_list_add_tail(&item1.node, &test_list);
  pal_list_add_tail(&item2.node, &other_list);

  pal_list_splice_tail(&other_list, &test_list);

  struct test_item *last =
      pal_list_last_entry(&test_list, struct test_item, node);
  TEST_ASSERT_EQUAL_INT(2, last->value);
}

void
test_list_splice_init(void)
{
  PAL_LIST_HEAD(other_list);
  struct test_item item1 = {.value = 1};

  pal_list_init(&item1.node);
  pal_list_add(&item1.node, &other_list);

  pal_list_splice_init(&other_list, &test_list);

  TEST_ASSERT_FALSE(pal_list_empty(&test_list));
  TEST_ASSERT_TRUE(pal_list_empty(&other_list)); /* other_list reinitialized */
}

extern int
unity_main(void);

int
main(void)
{
  return unity_main();
}
