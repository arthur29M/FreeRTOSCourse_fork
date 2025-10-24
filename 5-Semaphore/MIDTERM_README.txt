MIDTERM_Chapter5_README

1.Counting Sempahore Question :

This line :
SemaphoreHandle_t sem = xSemaphoreCreateCounting(3, 2);
creates a counting semaphore with 3 max tokens 
Initial count 2 available at start
Then we assign this same semaphore to 4 workers.

Scenario: 4 workers but only 2 tokens initially. Only 2 workers can acquire the semaphore at a time.
The other 2 workers will block until one of the first 2 releases a token.
The semaphore ensures that at most 2 workers are active at a time the others will wait.

Try it:
You would see in the output/logs that only two workers are blinking at once.
Once one finishes and releases the token, the next blocked worker will acquire it and start blinking.
This demonstrates resource limiting with counting semaphores.

2. Overview

This project demonstrates the use of FreeRTOS tasks and semaphores on the Raspberry Pi Pico.
It controls multiple LEDs using separate tasks and manages access to a shared resource 
(using a counting semaphore). The objectives are:
- Create multiple concurrent tasks using FreeRTOS.
- Use a counting semaphore to limit the number of active tasks simultaneously.
- Monitor task statistics and heap usage in real-time.

3. SOP

Connect LEDs to the GPIO pads defined in main.cpp.
Compile and upload the code to the Raspberry Pi Pico.
Monitor the serial console for task startup messages and runtime stats.
Observe LED blinking patterns.

Testing Counting Semaphore Limits : 
To test limiting workers with a counting semaphore:

1. Initialize the counting semaphore with a smaller number than the number of workers :
   SemaphoreHandle_t sem = xSemaphoreCreateCounting(4, 2); // 2 tokens, 4 workers

Assign the semaphore to all worker tasks.

Run the program.
Observe that only 2 workers can acquire the semaphore at a time; the other 2 wait.
