 -- Q&A Section : 

1) What happens if you give BlinkAgent the highest priority?

If BlinkAgent calls vTaskDelay() the LED blinks normally and other tasks still run
If it does not, it monopolizes the CPU and makes all stop running

2) Why use vTaskDelay() instead of sleep_ms()?

vTaskDelay() gives control to the FreeRTOS scheduler. this allows multitasking. sleep_ms() blocks the entire CPU and impacts others

3) What determines stack size in BlinkAgent?

It’s controlled by getMaxStackSize(). this defines how much memory each task has for its function calls and variables. basically its memory management like in C

 -- Daily Modifications : 

Created Project and run. LED blinks
Changed task priority and observed a change in the LED blinking rates

 -- SOP :

Open VSCode with the Pico SDK extension

Build the project using compiler

Deploy to Pico by dragging the .uf2 file to the mounted drive (with boot and rst)

Monitor serial output via the VSCode terminal to observe the priority changes

Modify priorities in main.cpp and observe scheduler behavior.

UPDATE on 22/10/2025

Updated MultiBlink to add more leds and more workers with different priority.
