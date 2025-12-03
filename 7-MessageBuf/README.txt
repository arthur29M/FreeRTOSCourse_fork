1. Overview

This project shows the use of FreeRTOS on two Raspberry Pi Pico boards. We coordinate LED behavior, binary counting, and between board communication. Each board runs the same firmware and is connected via pin 16 on board A to pin 17 on board B).
The system uses multiple tasks to do blinking, counting, decoding, and handling. Runtime statistics are printed to monitor task behavior.

3. (SOP)
- Connect GPIO 16 board 1 to board 17 board b
- Connect external LEDs to LED pad
- Connect both boards to USB

- Compile the project using your CMake-based Pico SDK environment.
- Flash the “SerialCmds” firmware onto both boards with .uf2
- Open a serial monitor

- Upon power-up, each Pico initializes USB serial and starts FreeRTOS.
- Tasks are created and launched through the scheduler.
- LEDs will begin blinking and counting at the same time they are synced
- Inter-board signals shift the decoded binary values shown on the LED set.
---

4. FreeRTOS Concepts Demonstrated

This project highlights several FreeRTOS features:

- Task creation (`xTaskCreate`)
  Launches separate execution contexts for agents.
- Task prioritization
  IOAgent demonstrates raised priority to handle time-sensitive events.
- Scheduling (`vTaskStartScheduler`)
  give execution control to FreeRTOS.
- Dynamic memory and heap statistics
  Uses FreeRTOS heap API for diagnostics.
- Inter-task modular design
  Each logical function is encapsulated as an isolated task.
