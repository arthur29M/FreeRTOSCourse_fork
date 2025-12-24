1. Overview

This project demonstrates a simple FreeRTOS-based application running on a Raspberry Pi Pico.
It showcases:

basic logging framework using multiple logging agents
system monitoring (task statistics and heap usage)
multitasking using FreeRTOS delays

The application runs entirely on core 0 of the RP2040.

The system consists of one main task that initializes and starts three agent tasks:
BlinkAgent : Controls the onboard LED (GPIO 25) and blinks it at a fixed rate.
LogAgentA : A logging task that periodically outputs log messages.
LogAgentB : A second logging task demonstrating multiple concurrent log producers.

Additionally, the main task periodically prints runtime statistics, including:

Number of active FreeRTOS tasks
Per-task priority and stack usage (high-water mark)
Heap usage and allocation statistics


2. Key Concepts Demonstrated

FreeRTOS Task Creation : Tasks are created using `xTaskCreate()` and started once the scheduler is running.
Object-Oriented Task Abstraction : Each functional task is implemented as a C++ class (“Agent”) with a `start()` method.
Runtime Introspection : FreeRTOS APIs such as `uxTaskGetSystemState()` and `vPortGetHeapStats()` are used to monitor system health.
Cooperative Scheduling : Tasks yield CPU time using `vTaskDelay()` rather than busy waiting.
Embedded Diagnostics : Stack high-water marks help identify stack sizing issues early.


3. Files and code
main.cpp

* Initializes USB serial I/O
* Creates the main FreeRTOS task
* Starts the FreeRTOS scheduler
* Periodically prints task and heap statistics

LogAgentA.h / .cpp
* Implements a logging task (Agent A)

LogAgentB.h / .cpp
* Implements a second logging task (Agent B)

4. Standard Operating Procedure (SOP)

Connect Pico via usb
Build and compile project
Flash uf2 on pico : Open a USB serial terminal at the appropriate port
Verify Runtime Behavior
Confirm all three tasks are listed in runtime statistics.
Check stack high-water marks for adequate margins.
Monitor heap availability to ensure no memory leaks.
