
#include <esp_log.h>
#include <string>

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

static char tag[] = "cpp_helloworld";

extern "C"
{
	void app_main(void);
}

class Blink
{
  public:
	Blink(gpio_num_t blinkPin)
	{
		this->blinkPin = blinkPin;
		gpio_pad_select_gpio(blinkPin);
		gpio_set_direction(blinkPin, GPIO_MODE_OUTPUT);
	}

	void blinkTimes(int x)
	{
		ESP_LOGD(tag, "Blink Times %d", x);

		int delayMs = 50;
		int level = gpio_get_level(blinkPin);
		gpio_set_level(blinkPin, 0);
		vTaskDelay(1000 / delayMs);
		for (int i = 0; i < x; i++)
		{
			gpio_set_level(blinkPin, 1);
			vTaskDelay(1000 / delayMs);
			gpio_set_level(blinkPin, 0);
			vTaskDelay(1000 / delayMs);
		}
		gpio_set_level(blinkPin, level);
	}

  private:
	gpio_num_t blinkPin = GPIO_NUM_2;
};

void app_main(void)
{
	vTaskDelay(1);
	Blink blink(GPIO_NUM_2);
	blink.blinkTimes(5);
}

