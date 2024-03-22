---
title: Homebrew Macropad Firmware
defaultPlatform: mac
defaultTool: cli
---
# macropad

firmware for the homebrew macro pad

## build and install instructions

### Install SDK Dependencies

The instructions below assume that you are either on a macOS or Linux-based system. You will need to install CMake, the Arm GCC toolchain, and `libusb-1.0`

#### macOS
```bash
brew install cmake libusb
brew install --cask gcc-arm-embedded
```

#### Linux
Use whatever package manager you want.
```bash
sudo apt install cmake build-essential libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib libusb-1.0.0
```

### Install the Pico C/C++ SDK

Clone the Pico C/C++ SDK:
```bash
git clone https://github.com/raspberrypi/pico-sdk.git --branch master
cd pico-sdk
git submodule update --init
```

> Recommended to store this somewhere that is remembered easily either in `/usr/bin/lib/` or in `$HOME/Libraries/`

### Install picotool
If you are on macOS, you will already know that Finder is like a baby. Some macOS users have reported issues with trying to flash `.UF2` files

###
Build project by running the following:
```bash
mkdir build
cd build
cmake ..
make -j4
```

Install firmware to macropad by doing the following:

- Press and hold `BOOTSEL` and hit reset button
- Inside the project build folder run the following command:
```bash
picotool load macropad_hid.uf2
```