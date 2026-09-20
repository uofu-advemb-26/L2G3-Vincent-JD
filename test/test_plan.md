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

# Exercising the system
- All of the tests written are automated to minimize the chance of human error in interpreting test results. As such, the only "exercise" required to be performed is to plug the pico in over USB and observe the running tests.

# Expected behavior
- When connected to the serial monitor, the Pi Pico should print out debug messages showing the execution of code on a functional step-by-step basis. 

## Test plan steps
1. Document the functionality of code that isn't self-evident in function.
2. With the documentation complete, start writing helper functions that "clone" the functionality of the documented code alongside associated tests
3. Once the tests are confirmed passing, integrate the helper function code back into the main codebase and repeat with the next portion of undocumented code