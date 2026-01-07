#pragma once
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "pico/stdlib.h"

#define LED_COUNT 8
#define LED_QUEUE_LEN 10

struct LedCmd {
	uint8_t pattern; //8bit led pattern
};

class LedArrayAgent {
public:
	LedArrayAgent();
	void start(const char *name, UBaseType_t priority);
	void send(uint8_t pattern);
	static void task(void *param);

private:
	QueueHandle_t xQueue;
	uint8_t ledPins[LED_COUNT];
};
