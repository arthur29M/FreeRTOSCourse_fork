/***
 * Demo program to light 4 LEDs as binary random value
 * Uses FreeRTOS Task
 * Jon Durrant
 * 15-Aug-2022
 */


#include "pico/stdlib.h"
#include "pico/multicore.h"

#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <math.h>

#include "BlinkAgent.h"
#include "CounterAgent.h"
#include "LedArrayAgent.h"


//Standard Task priority
#define TASK_PRIORITY		( tskIDLE_PRIORITY + 1UL )

//LED PAD to use
#define LED_PAD				25
#define LED1_PAD			0
#define LED2_PAD			1
#define LED3_PAD			2
#define LED4_PAD			3
#define LED5_PAD			4
#define LED6_PAD			5
#define LED7_PAD			6
#define LED8_PAD			7

#define BUFFER_SIZE 16
uint8_t patternBuffer[BUFFER_SIZE];
volatile int head = 0;
volatile int tail = 0;

bool bufferPush(uint8_t v) {
    int next = (head + 1) % BUFFER_SIZE;
    if (next == tail) return false;
    patternBuffer[head] = v;
    head = next;
    return true;
}

bool bufferPop(uint8_t &v) {
    if (head == tail) return false;
    v = patternBuffer[tail];
    tail = (tail + 1) % BUFFER_SIZE;
    return true;
}

void producerTask(void *param) {
	while (true) {
		uint8_t value = rand() & 0xFF;
		bufferPush(value);
		printf("Produced: 0x%02X\n", value);
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}

void consumerTask(void *param) {
    LedArrayAgent leds;
    leds.start("LEDArray", TASK_PRIORITY);

    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    uint8_t v;

    while (true) {
        if (bufferPop(v)) {
            leds.send(v);
            gpio_put(25, 1);   // onboard LED (GPIO 25)
            sleep_ms(50);
            gpio_put(25, 0);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}


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


/***
 * Main task to blink external LED
 * @param params - unused
 */
void mainTask(void *params){
	BlinkAgent blink(LED_PAD);
	CounterAgent counter(LED1_PAD, LED2_PAD, LED3_PAD, LED4_PAD, LED5_PAD, LED6_PAD, LED7_PAD, LED8_PAD);

	printf("Main task started\n");

	blink.start("Blink", TASK_PRIORITY);
	counter.start("Counter", TASK_PRIORITY);

	while (true) { // Loop forever
		runTimeStats();
		uint8_t r = rand() & 0x0F;
		counter.blink(r);
		printf("Blinking R=0x%X\n", r);
		vTaskDelay(3000);
	}
}




/***
 * Launch the tasks and scheduler
 */
void vLaunch( void) {

	//Start blink task
    TaskHandle_t task;
    xTaskCreate(mainTask, "MainThread", 500, NULL, TASK_PRIORITY, &task);

    /* Start the tasks and timer running. */
    vTaskStartScheduler();
}

/***
 * Main
 * @return
 */
int main(void) {
	stdio_init_all();
	sleep_ms(2000);
	printf("Multicore LED Queue Demo\n");

	xTaskCreate(producerTask, "Producer", 300, NULL, TASK_PRIORITY, NULL);

	multicore_launch_core1([] {
		xTaskCreate(consumerTask, "Consumer", 400, NULL, TASK_PRIORITY, NULL);
		vTaskStartScheduler();
	});

	vTaskStartScheduler();
	while (true);
}

