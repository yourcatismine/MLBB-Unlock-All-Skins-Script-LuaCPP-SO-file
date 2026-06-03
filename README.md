# MLBB Unlock All Skins Script

A native C++ shared library that unlocks all skins in Mobile Legends: Bang Bang (MLBB) by hooking game functions using il2cpp runtime modification.

## Overview

This project provides a method to unlock all available skins in Mobile Legends: Bang Bang without restricting access based on ownership or gameplay conditions. It works by intercepting and modifying the behavior of game functions that validate skin eligibility.

## How It Works

The script uses **il2cpp hooking** to intercept key game functions:

- `CanSelectSkin()` - Checks if a skin can be selected
- `CanEquipSkin()` - Checks if a skin can be equipped
- `IsCanSelectSkin()` - Alternative check for skin selection eligibility
- `IsCanEquipSkin()` - Alternative check for skin equipment eligibility

Each hooked function is redirected to return `1` (true), bypassing the game's ownership and eligibility checks.

### Technical Details

- **Language**: C++ (C++17)
- **Architecture**: ARM native library (.so file)
- **Runtime**: il2cpp (Intermediate Language 2 C++)
- **Build System**: CMake
- **Logging**: Android logging framework

## Requirements

- CMake 3.10 or higher
- C++17 compatible compiler (Android NDK for cross-compilation)
- Standard Android build tools

## Building

### From Source

1. Ensure you have CMake installed:
   ```bash
   cmake --version
   ```

2. Clone the repository:
   ```bash
   git clone https://github.com/yourcatismine/MLBB-Unlock-All-Skins-Script-LuaCPP-SO-file.git
   cd MLBB-Unlock-All-Skins-Script-LuaCPP-SO-file
   ```

3. Create a build directory and compile:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

4. The compiled shared library will be located in the `build/` directory.

### Using Android NDK

For Android cross-compilation:

```bash
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=$NDK_PATH/build/cmake/android.toolchain.cmake \
      -DANDROID_ABI=arm64-v8a \
      -DANDROID_PLATFORM=android-21 \
      ..
make
```

## Installation & Usage

### Prerequisites

- Rooted Android device or emulator
- Mobile Legends: Bang Bang installed
- A framework supporting native library injection (e.g., Xposed, Frida, or similar)

### Steps

1. **Build or obtain the compiled `.so` file** (See Building section)

2. **Inject the library** into the MLBB game process using your preferred hooking framework

3. **Launch MLBB** - the hooked functions will automatically intercept skin eligibility checks

4. **Access all skins** - All skins should now be available for selection and equipment regardless of ownership status

## File Structure

```
.
├── CMakeLists.txt           # CMake build configuration
├── src/
│   ├── main.cpp            # Primary implementation with full hooks
│   └── main.cpp.new        # Alternative/updated implementation
└── README.md               # This file
```

## Compilation Flags

- **Release Build**: Optimized with `-Os` flag and `NDEBUG` enabled for smaller binary size
- **Debug Build**: Full debugging symbols and logging

## Important Notes & Warnings

### ⚠️ Disclaimer

- **Educational Purpose Only**: This project is intended for educational and research purposes only.
- **Terms of Service**: Using this modification violates Mobile Legends: Bang Bang's Terms of Service.
- **Account Risk**: Using this script may result in:
  - Account suspension or permanent ban
  - Loss of in-game progress and cosmetics
  - Restriction from official game events
- **Legal Considerations**: Unauthorized modification of software may violate local laws in your jurisdiction.
- **Use at Own Risk**: The author assumes no responsibility for any consequences resulting from the use of this script.

### Recommendations

- **Test Environment**: Only use on test/secondary accounts
- **Legal Compliance**: Check your local laws regarding software modification
- **Community Guidelines**: Review the official MLBB community guidelines before use
- **Detection Risk**: The game may have anti-cheat systems that detect this modification

## Logging

The library includes Android logging support. To view logs:

```bash
adb logcat | grep "HOOK"
```

## Contributing

For improvements, bug reports, or suggestions:
1. Fork the repository
2. Create a feature branch
3. Submit a pull request with detailed changes

## License

This project is provided as-is without any warranty or liability.

## Disclaimer

The author is not responsible for any misuse, legal consequences, or account penalties resulting from the use of this script. Users are solely responsible for their actions and must comply with applicable laws and the game's Terms of Service.

---

**Last Updated**: June 2026
