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

void main(void)
{
	RCC_voidInitSystemClock();
	RCC_voidEnableClock(RCC_APB2,2);

	MGPIO_voidSetPinDirection(GPIOA , PIN1 , 0b0010);
	GPIOA_ODR=0x00000002;

	while(1)
	{}
}


