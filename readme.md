# macropad

firmware for the homebrew macro pad

# build and install instructions

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