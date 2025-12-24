# Qwiet

Platform abstraction layer for embedded Linux and e-ink devices.

## Build

```bash
cmake -B build [options]
cmake --build build
```

## Build Options

| Option              | Values              | Default | Description                        |
| ------------------- | ------------------- | ------- | ---------------------------------- |
| `PLATFORM`          | `linux`, `pinenote` | `linux` | Target platform                    |
| `BUILD_TESTING`     | `ON`, `OFF`         | `OFF`   | Build test support (diode + Unity) |
| `BUILD_SHARED_LIBS` | `ON`, `OFF`         | `OFF`   | Build shared libraries             |

## Build Permutations

| Command                                                 | Targets                                                 |
| ------------------------------------------------------- | ------------------------------------------------------- |
| `cmake -B build -DPLATFORM=linux`                       | `qwiet_pal`, `libevdev`                             |
| `cmake -B build -DPLATFORM=linux -DBUILD_TESTING=ON`    | `qwiet_pal`, `libevdev`, `qwiet_diode`, `unity` |
| `cmake -B build -DPLATFORM=pinenote`                    | `qwiet_pal`, `libevdev`                             |
| `cmake -B build -DPLATFORM=pinenote -DBUILD_TESTING=ON` | `qwiet_pal`, `libevdev`, `qwiet_diode`, `unity` |
