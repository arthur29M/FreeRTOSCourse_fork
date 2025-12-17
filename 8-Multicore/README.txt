1. PROJECT OVERVIEW

This project demonstrates the use of FreeRTOS Symmetric
Multiprocessing on the Raspberry Pi Pico utilizing both
CPU cores simultaneously.

The application creates multiple FreeRTOS tasks and explicitly binds
them to specific CPU cores using task core affinity. It also shows
runtime statistics, heap usage, and inter-task communication concepts.

The program controls:
- Two blinking LEDs on separate cores
- A 4-bit binary counter displayed on GPIO pins
- A main supervisory task that runs on Core 0

2. TASK DESCRIPTIONS

MainTask :
it Initializes and starts all agents
then Assigns core affinity
then periodically prints runtime statistics
sends random 4-bit values to CounterAgent

BlinkAgent:
toggles a GPIO pin at a fixed interval
demonstrates task execution on a specific core

CounterAgent:
displays a 4-bit value on four GPIO pins
receives commands from MainTask

3. KEY CONCEPTS DEMONSTRATED
- FreeRTOS SMP on RP2040
- Task creation and scheduling
- Core affinity binding
- Multi-core task isolation
- Heap and runtime monitoring
- Object-oriented task design in C++
- GPIO control from multiple cores

4. STANDARD OPERATING PROCEDURE (SOP)

- Connect LEDs to the specified GPIO pins with resistors.
- Connect Raspberry Pi Pico to the host PC via USB.

Build
- Open the project
- Ensure FreeRTOS is configured with pico support.
- Configure the project
- Build
- Compile

Flashing the Pico
- Hold the BOOTSEL button on the Pico.
- Plug in the USB cable.
- Release BOOTSEL.
- Copy the generated .uf2 file to the Pico drive.

Analyse : Use the Serial Monitor to verify the correct function of the program
