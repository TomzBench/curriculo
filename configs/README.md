# Kconfig Configuration Files

This directory contains Kconfig configuration files for different build targets.

## Available Configurations

| File            | Description                             |
| --------------- | --------------------------------------- |
| `linux.conf`    | Linux desktop platform                  |
| `pinenote.conf` | PineNote hardware platform              |
| `testing.conf`  | Testing overlay (adds CONFIG_TESTING=y) |

## Usage

```bash
# Default (linux.conf)
cmake -B build

# Explicit config
cmake -B build -DCONFIG=configs/pinenote.conf

# Merge configs (semicolon-separated, applied in order)
cmake -B build -DCONFIG="configs/linux.conf;configs/testing.conf"

# Or use CONFIG_EXTRA for overlays
cmake -B build -DCONFIG=configs/linux.conf -DCONFIG_EXTRA=configs/testing.conf
```

## Scaling to Per-App Configurations

If the project grows to multiple applications with different feature
requirements, consider a Zephyr-style per-app configuration model:

```
apps/
  drawing/
    prj.conf          # App-specific: CONFIG_PLATFORM_LINUX=y, CONFIG_DRAWING_FEATURE=y
    src/
  viewer/
    prj.conf          # App-specific: CONFIG_PLATFORM_LINUX=y, CONFIG_VIEWER_FEATURE=y
    src/
```

Each app would be built independently:

```bash
cmake -B build/drawing -DCONFIG=apps/drawing/prj.conf
cmake -B build/viewer -DCONFIG=apps/viewer/prj.conf
```

Tests would remain part of the main build system (enabled via
`CONFIG_TESTING=y`) to allow single-invocation test runs.
