/*
 * am2320_test.c
 *
 *  Created on: Feb 15, 2024
 *      Author: andrew.purves
 */

#include <stdio.h>
#include <string.h>
#include "stm32l07xx.h"
#include "am2320.h"

int main(void)
{
	RCC_SetSysClk(SYS_CLK_HSI);
	AM2320_Init(AM2320_TEMPERATURE_AND_HUMIDITY);
	delay(100);

	while (1)
	{
		AM2320_RequestData();
		delay(100);
	}
}

void I2C1_IRQHandler(void)
{
	AM2320_IrqHandling();
}

void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle, uint8_t appEv)
{
	static float temperature = 0.f;
	static float humidity = 0.f;
	if (AM2320_HandleInterruptEvent(pI2CHandle, appEv) == AM2320_DATA_READY)
	{
		temperature = AM2320_GetTemperature();
		humidity = AM2320_GetHumidity();
	}
}
