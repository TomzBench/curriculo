# Qwiet

Platform abstraction layer for embedded Linux and e-ink devices.

## Build

```bash
cmake -B build
cmake --build build
```

## Configuration

Build configuration is managed via Kconfig. See `configs/README.md` for details.

| Option         | Description                                         |
| -------------- | --------------------------------------------------- |
| `CONFIG`       | Config files (semicolon-separated, merged in order) |
| `CONFIG_EXTRA` | Extra config fragments to append                    |

### Available Configs

| File                    | Description                |
| ----------------------- | -------------------------- |
| `configs/linux.conf`    | Linux desktop platform     |
| `configs/pinenote.conf` | PineNote hardware platform |
| `configs/testing.conf`  | Testing overlay            |

### Examples

```bash
# Default (linux, no tests)
cmake -B build

# PineNote platform
cmake -B build -DCONFIG=configs/pinenote.conf

# Linux with tests (merged configs)
cmake -B build -DCONFIG="configs/linux.conf;configs/testing.conf"

# Or using overlay
cmake -B build -DCONFIG=configs/linux.conf -DCONFIG_EXTRA=configs/testing.conf
```

## Running Tests

```bash
cmake -B build -DCONFIG="configs/linux.conf;configs/testing.conf"
cmake --build build
ctest --test-dir build
```
