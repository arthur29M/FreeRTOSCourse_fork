#include "LedArrayAgent.h"
#include <stdio.h>

LedArrayAgent::LedArrayAgent() {
	for (int i = 0; i < LED_COUNT; i++) {
		ledPins[i] = i; // GPIO 0–7
		gpio_init(i);
		gpio_set_dir(i, GPIO_OUT);
		gpio_put(i, 0);
	}
	xQueue = xQueueCreate(LED_QUEUE_LEN, sizeof(LedCmd));
}

void LedArrayAgent::start(const char *name, UBaseType_t priority) {
	xTaskCreate(task, name, 300, this, priority, NULL);
}

void LedArrayAgent::send(uint8_t pattern) {
	LedCmd cmd{pattern};
	xQueueSendToBack(xQueue, &cmd, 0);
}

void LedArrayAgent::task(void *param) {
	auto *self = static_cast<LedArrayAgent *>(param);
	LedCmd cmd;

	while (true) {
		if (xQueueReceive(self->xQueue, &cmd, portMAX_DELAY)) {
			for (int i = 0; i < LED_COUNT; i++) {
				gpio_put(self->ledPins[i], (cmd.pattern >> i) & 1);
			}
			vTaskDelay(pdMS_TO_TICKS(300));
		}
	}
}
