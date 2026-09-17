# Test Plan
For reasons called "We keep forgetting to solder the debug headers somehow", this test utilizes only a single Raspberry Pi Pico W.

## Setup
- Set up a new repository using the specified template in the Lab 2 manual.
- From the root of the repo, run the following sequence of commands to initialize CMake:
    1. ``mkdir build``
    2. ``cmake -B build``
- Then, to build the project and flash it to the pico, use the following command:
    - ``cmake --build build --target flash_test``
    - If need be, reboot the pico using picotool with ``picotool reboot -f``
- Utilizing the Serial Monitor in VSCode, connect to the pico using a baud rate of 115200. The COM port that the pico shows as will be some variation on /dev/ttyACMx, where x is a positive integer.

# Expected behavior
- When connected to the serial monitor, the Pi Pico should print out debug messages showing the execution of code on a functional step-by-step basis. At current however, the act of even toggling the onboard LED appears to result in a hard crash of our tests.