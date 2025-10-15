 -- Q&A Section : 

1) What happens if you give BlinkAgent the highest priority?

If BlinkAgent calls vTaskDelay() the LED blinks normally and other tasks still run.
If it does not, it monopolizes the CPU and makes all stop running.

2) Why use vTaskDelay() instead of sleep_ms()?

vTaskDelay() gives control to the FreeRTOS scheduler. this allows multitasking. sleep_ms() blocks the entire CPU and impacts others.

3) What determines stack size in BlinkAgent?

It’s controlled by getMaxStackSize(). this defines how much memory each task has for its function calls and variables. basically its memory management like in C.

 -- Daily Modifications : 

Created Project and run. LED blinks.
Changed task priority and observed a change in the LED blinking rates.

 -- SOP :

