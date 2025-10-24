/***
 * Demo program to flash an LED attached to GPIO PAD 0.
 * Uses FreeRTOS Task
 * Jon Durrant
 * 15-Aug-2022
 */


#include "pico/stdlib.h"

#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

#include "BlinkAgent.h"
#include "BlinkWorker.h"
#include "BlinkHeavy.h"


//Standard Task priority
#define TASK_PRIORITY		( tskIDLE_PRIORITY + 1UL )

//LED PAD to use
#define LED_PAD				0
#define LED1_PAD			1
#define LED2_PAD			2

#define LED3_PAD			3
#define LED4_PAD			4
#define LED5_PAD			5
#define LED6_PAD			6
#define LED7_PAD			7

#define ONBOARD_PAD			25


void runTimeStats(   ){
	TaskStatus_t *pxTaskStatusArray;
	volatile UBaseType_t uxArraySize, x;
	unsigned long ulTotalRunTime;


   // Get number of takss
   uxArraySize = uxTaskGetNumberOfTasks();
   printf("Number of tasks %d\n", uxArraySize);

   //Allocate a TaskStatus_t structure for each task.
   pxTaskStatusArray = (TaskStatus_t *)pvPortMalloc( uxArraySize * sizeof( TaskStatus_t ) );

   if( pxTaskStatusArray != NULL ){
      // Generate raw status information about each task.
      uxArraySize = uxTaskGetSystemState( pxTaskStatusArray,
                                 uxArraySize,
                                 &ulTotalRunTime );

	 // Print stats
	 for( x = 0; x < uxArraySize; x++ )
	 {
		 printf("Task: %d \t cPri:%d \t bPri:%d \t hw:%d \t%s\n",
				pxTaskStatusArray[ x ].xTaskNumber ,
				pxTaskStatusArray[ x ].uxCurrentPriority ,
				pxTaskStatusArray[ x ].uxBasePriority ,
				pxTaskStatusArray[ x ].usStackHighWaterMark ,
				pxTaskStatusArray[ x ].pcTaskName
				);
	 }


      // Free array
      vPortFree( pxTaskStatusArray );
   } else {
	   printf("Failed to allocate space for stats\n");
   }

   //Get heap allocation information
   HeapStats_t heapStats;
   vPortGetHeapStats(&heapStats);
   printf("HEAP avl: %d, blocks %d, alloc: %d, free: %d\n",
		   heapStats.xAvailableHeapSpaceInBytes,
		   heapStats.xNumberOfFreeBlocks,
		   heapStats.xNumberOfSuccessfulAllocations,
		   heapStats.xNumberOfSuccessfulFrees
		   );
}

//dummy task to hit memory limit
void cpuTask(void *params){
    int id = (int)params;
    while (true){
        // Simulate CPU work
        volatile int sum = 0;
        for (int i = 0; i < 10000; i++) sum += i;
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}


/***
 * Main task to blink external LED
 * @param params - unused
 */
void mainTask(void *params){
	BlinkAgent blink(LED_PAD);
	BlinkWorker worker1(LED1_PAD);
	BlinkHeavy worker2(LED2_PAD);

	BlinkAgent worker3(LED3_PAD);
	BlinkWorker worker4(LED4_PAD);
	BlinkHeavy worker5(LED5_PAD);
	BlinkAgent worker6(LED6_PAD);
	BlinkWorker worker7(LED7_PAD);

	BlinkWorker onboard(ONBOARD_PAD);

	printf("Main task started\n");

	blink.start("Blink", TASK_PRIORITY+1);
	worker1.start("Worker 1", TASK_PRIORITY+ 1);
	worker2.start("Worker 2", TASK_PRIORITY + 2);

	worker3.start("Worker 3", TASK_PRIORITY + 3);
	worker4.start("Worker 4", TASK_PRIORITY + 4);
	worker5.start("Worker 5", TASK_PRIORITY + 5);
	worker6.start("Worker 6", TASK_PRIORITY + 6);
	worker7.start("Worker 7", TASK_PRIORITY + 7);

	onboard.start("Onboard LED Blinking", TASK_PRIORITY + 1);


	while (true) { // Loop forever
		runTimeStats();
		vTaskDelay(2000);
	}
}




/***
 * Launch the tasks and scheduler
 */
void vLaunch( void) {

	//Start blink task
    TaskHandle_t task;
    xTaskCreate(mainTask, "MainThread", 500, NULL, TASK_PRIORITY, &task);

	//to add some load
	for (int i = 0; i < 20; i++){
    	char name[16];
    	sprintf(name, "CPUTask%d", i);
    	xTaskCreate(cpuTask, name, 256, (void*)i, TASK_PRIORITY + (i % 3), NULL);
	}

    /* Start the tasks and timer running. */
    vTaskStartScheduler();
}

/***
 * Main
 * @return
 */
int main( void )
{
	//Setup serial over USB and give a few seconds to settle before we start
    stdio_init_all();
    sleep_ms(3000);
    printf("GO\n");

    //Start tasks and scheduler
    const char *rtos_name = "FreeRTOS";
    printf("Starting %s on core 0:\n", rtos_name);
    printf("KHUOY Théo F14158805\n");

    vLaunch();


    return 0;
}
