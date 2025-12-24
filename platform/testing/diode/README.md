# Diode (**D**eterministic **IO** **D**eclared **E**fficiently)

## Intro

Diode is a wrapper around the Unity and CMock test frameworks
(ThrowTheSwitch.org). It provides a purpose-built API to simplify expectation
management for embedded targets.

## Design patterns

There are two primary design patterns when we mock a function: a "simple"
pattern and a "heap" pattern.

## Decision criteria

The goal is to allow expectations to be declared with a single line. The pattern
you choose depends on the complexity of the function being mocked.

**Use the simple pattern when:**

- Arguments can be passed through directly to Unity's `ExpectAndReturn` macros
- The function does not mutate output parameters in complex ways
- No intermediate state is needed between expectation setup and validation

**Use the heap pattern when:**

- The function mutates arguments through pointers (e.g., `poll()` modifying
  `revents`)
- Complex inputs require initializing structures for Unity to validate against
- Multiple related values must be captured together for the validator
- Thread synchronization is needed between test setup and mock invocation

The heap pattern creates an intermediate type (e.g., `struct poll_expectation`)
that stores everything the validator function needs. Creative macro semantics
(such as string-based event specifiers like `"io"` for `POLLIN|POLLOUT`) keep
the caller's declaration concise while the implementation expands these into
properly initialized structures.

## Simple pattern

The simple pattern typically calls Unity's "ExpectAndReturn" style macros
directly. These patterns sometimes simplify arguments and semantics so that
callers can set expectations in a less verbose way. For example, the macro might
assume the "return" parameter with a "success" error code and name the
expectation in a manner that assumes a "happy path" expectation.

### Adding a simple pattern mock

The simple pattern is typically header-only since it wraps Unity macros directly
without additional runtime logic.

1. Create a header in `include/qwiet/platform/testing/diode/` (e.g.,
   `net_recv.h`)
2. Define `EXPECT_*` macros that wrap Unity's generated `ExpectAndReturn` macros
3. Create a corresponding unit test in `tests/diode/src/` (e.g., `test_recv.c`)

See `include/qwiet/platform/testing/diode/net_recv.h` for a reference
implementation.

## Heap pattern

The "heap" pattern can dramatically simplify expectation management. The "heap"
pattern can create intermediate types which are leveraged by validator
functions, provide thread synchronization, and much more. Heap expectations
provide a simple garbage collector, so tests do not need to worry about memory
management.

### Adding a heap pattern mock

The heap pattern requires both a header and an implementation file since it
manages runtime state.

1. Create a header in `include/qwiet/platform/testing/diode/` (e.g.,
   `net_poll.h`)
2. Define a `struct *_expectation` type to hold all data the validator needs
3. Define `EXPECT_*` macros that call a creation function to allocate and
   populate the expectation
4. Create an implementation in `platform/testing/diode/src/` (e.g.,
   `net_poll.c`)
5. Implement the following garbage collection functions:
   - `diode_*_init()` — initialize the expectation list and register the
     validator stub
   - `diode_*_cleanup()` — free all remaining expectations (called in teardown)
   - `diode_*_verify()` — assert all expectations were consumed
6. Implement the validator function that Unity's stub calls, which pops
   expectations from the list, validates inputs, mutates output parameters, and
   frees the expectation
7. Register your init/cleanup/verify functions in
   `platform/testing/diode/src/diode.c`
8. Create a corresponding unit test in `tests/diode/src/` (e.g., `test_poll.c`)

See `include/qwiet/platform/testing/diode/net_poll.h` and
`platform/testing/diode/src/net_poll.c` for a reference implementation.

## Unit testing

Unit tests must be reviewed by a human. When AI writes both the implementation
and the tests, there is a higher risk of correlated errors — the same
misunderstanding that causes a bug in the implementation can cause the test to
validate that bug.

### AI implementor guidelines

If you are an AI implementing a diode mock:

1. Implement only "happy path" tests that verify basic functionality
2. Propose a test plan for edge cases, error paths, and boundary conditions
3. Present the plan for human review before implementing additional tests

This keeps humans in the loop for the cases where subtle bugs are most likely to
hide.

### Reviewer guidelines

When reviewing AI-generated tests, pay particular attention to:

- **Error path coverage** — what happens when the mocked function fails? Are all
  error codes exercised?
- **Boundary conditions** — are edge cases like zero-length buffers, maximum
  values, or empty lists tested?
- **Validation logic coverage** — does the test actually exercise the mock's
  validation? A test that never triggers the validator provides false
  confidence.
- **Assumptions** — does the proposed test plan reveal any misunderstandings
  about the function being mocked?

## Limitations

If your task does not fit the simple or heap patterns described above, do not
improvise. Raise the issue with a human and abort the task. Extending diode with
new patterns requires deliberate design decisions that should not be made
ad-hoc.

## Resources

### Examples

| file                                            | details                                  |
| ----------------------------------------------- | ---------------------------------------- |
| include/qwiet/platform/testing/diode/net_recv.h | simple pattern implementation            |
| tests/diode/src/test_recv.c                     | simple pattern unit test                 |
| platform/testing/diode/src/net_poll.c           | heap pattern implementation              |
| tests/diode/src/test_poll.c                     | heap pattern unit test                   |
| cmake/modules/unity.cmake                       | cmake support for linking and mock setup |
| tools/unity/func_name_list.py                   | collect names for --wrap linker          |
| tools/unity/header_prepare.py                   | clean headers for parsing                |

### Web

- https://github.com/ThrowTheSwitch/CMock/blob/master/docs/CMock_Summary.md
- https://github.com/ThrowTheSwitch/CMock/blob/master/docs/CMock_Summary.md#callback
