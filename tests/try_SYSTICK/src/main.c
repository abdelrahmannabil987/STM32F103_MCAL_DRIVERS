/*
 * main.c
 *
 *  Created on: Mar 14, 2025
 *      Author: abdelrahman
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "STICK_interface.h"

void led(void);
void main(void)
{
	RCC_voidInitSystemClock();
	RCC_voidEnableClock(RCC_APB2,2);
	MSTICK_voidInit();
	MSTICK_voidSetIntervalPeriodic(8000000,&led);
	MGPIO_voidSetPinDirection(GPIOA , PIN1 , 0b0010);

	while(1)
	{

	}
}


void led(void)
{
	 GPIOA_ODR ^= (1 << 1);
}

