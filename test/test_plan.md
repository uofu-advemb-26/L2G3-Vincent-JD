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

## Steps 

1. Observe the Pico's onboard LED.
    - Expected Result: it turns on and off following the pattern `SHORT_OFF, SHORT_ON, SHORT_OFF, SHORT_ON, SHORT_OFF, SHORT_ON, SHORT_OFF, SHORT_ON, SHORT_OFF, SHORT_ON, LONG_OFF, SHORT_ON, ...`
2. Starting right after a `LONG_OFF`, use a stopwatch to time the 10 `SHORT_OFF`/`SHORT_ON` transitions up to (but not including) the next `LONG_OFF`, then divide the total by 10. (A single 0.5 second interval is too fast to time by hand reliably; averaging over 10 cycles cancels out reaction-time error.)
    - Expected Result: the average duration per transition is approximately 0.5 seconds.
3. Time the duration from the start of one `LONG_OFF` to the start of the next.
    - Expected Result: approximately 5.5 seconds (10 short transitions plus one `LONG_OFF`).
4. Compare the length of `LONG_OFF` to a single `SHORT_OFF`/`SHORT_ON` by eye.
    - Expected Result: `LONG_OFF` is noticeably longer than a single short interval — roughly twice its length.
5. Type characters in the terminal connection to the Pico.
    - Expected Result: The LED continues to flash with the same pattern at the same rate.
6. Type a lowercase letter, e.g. `a`, in the terminal.
    - Expected Result: The corresponding uppercase letter, `A`, is echoed back.
7. Type an uppercase letter, e.g. `A`, in the terminal.
    - Expected Result: The corresponding lowercase letter, `a`, is echoed back.
8. Type the boundary letters `a`, `z`, `A`, and `Z` one at a time.
    - Expected Result: Each is echoed back case-swapped (`A`, `Z`, `a`, `z` respectively) with no off-by-one errors at the ends of the alphabet.
9. Type a non-alphabetic character, e.g. `1`, `!`, or a space, in the terminal.
    - Expected Result: The same character is echoed back unchanged.
10. Type several characters in a row without pausing.
    - Expected Result: Each character is echoed individually as it is typed; the program does not wait for Enter/newline before responding.
