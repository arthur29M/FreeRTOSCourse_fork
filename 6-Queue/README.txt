6 - Queues ; CountLED project ReadMe

This project demonstrates inter-task communication using queues
The system creates multiple  tasks that blink LEDs and display runtime information

A queue in FreeRTOS is used for communication between tasks or between an interrupt and a task.
- Producer tasks send data to a queue using xQueueSend() or xQueueSendFromISR().
- Consumer tasks receive data from a queue using xQueueReceive().
- Queues handle synchronization automatically and tasks block (wait) when a queue is full or empty.
- This avoids conflicts and allows clean separation between tasks.

2. SOP :
Open VS Code with the Raspberry Pi Pico extension installed.
Open the project folder
Click “Build” in the Pico extension menu to compile the project.
After build finishes, the .uf2 file will be created in the build folder.
Connect your Raspberry Pi Pico via USB while holding the BOOTSEL button.
Copy the generated .uf2 file onto the Pico’s USB drive.
The Pico will automatically reboot and run the FreeRTOS LED demo.

3. Code explanation

- runTimeStats()
It gather tasks and heap usage statistics using:
uxTaskGetSystemState() to list active tasks.
vPortGetHeapStats() to show heap allocation details.
Prints info to the console.

mainTask()
Starts two child tasks: BlinkAgent and CounterAgent.
Generates random 4-bit numbers to display on 4 LEDs.
Prints system stats and heap info.
Runs infinitely

main()
Initializes USB serial communication, waits briefly, and launches FreeRTOS:
stdio_init_all();
sleep_ms(2000);
printf("Starting FreeRTOS on core 0:\n");
vLaunch(); to launch everythign
