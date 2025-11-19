1. Overview
This project demonstrates how to use tasks and queues on the Raspberry Pi Pico to control LED behavior.

BlinkAgent controls a single LED blinking
CounterAgent controls four LEDs as a binary value
CounterAgent has been extended to support blinking through a pattern

The objective of the assignment is to understand queues and how tasks communicate using message passing instead of shared variables.

What are queues : 

Queues allow tasks to exchange messages in a thread-safe way.
Key characteristics:

A queue acts as a buffer that stores messages sent by one task and received by another.
Messages can be structured data types.
Writing to a queue and reading from it are non-blocking unless configured otherwise.
Tasks do not need to share variables or use locks.

Benefits are :
Tasks remain completely independent
No race conditions or unsafe shared memory access
Commands can be stored and processed in the order
Commands continue being executed even if the sender becomes busy

2. Project and how queues are used here
The main task does not access LED pins directly.
Instead, it sends commands to the CounterAgent through a queue
This single call places a message in the queue
CounterAgent will later read the message and act on it

A queue is created inside CounterAgent during construction

3. SOP

Open VSCode.
Confirm the Raspberry Pi Pico Extension is installed.
Run the build command.
Flash the program to the Pico.
Open the Serial Monitor to observe runtime output.

4. Conclusion
We learned : 
How to use FreeRTOS queues for inter-task communication.
How to build modular task-based architectures.
How to extend an existing queue-driven LED example into a pattern-driven controller.
How to keep tasks independent and cleanly separated.
