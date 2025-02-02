# RCC Driver for STM32F103

## About

This RCC (Reset and Clock Control) driver is designed for the STM32F103 series of microcontrollers. It provides a set of functions to configure and manage the system clock source, enable/disable peripheral clocks, and trim the internal clock source.

## Features

- Supports various system clock sources:
  - HSE (High Speed External) Crystal
  - HSE (High Speed External) RC
  - HSI (High Speed Internal)
  - PLL (Phase-Locked Loop)
- Supports various PLL configuration options:
  - PLL input: HSI/2, HSE/2, or HSE
  - PLL multiplication value (2 to 16)
- Provides functions to enable and disable peripheral clocks
- Includes support for trimming the internal clock source

## Configuration Options

To configure the RCC driver, modify the `RCC_CONFIG_H` file. You can choose from the following options:

- `RCC_CLOCK_TYPE`: Select the system clock source (see below for options)
- `RCC_PLL_INPUT`: Select the PLL input clock source (only applicable if `RCC_PLL` is selected)
- `PLL_MUL_VALUE`: Select the PLL multiplication value (only applicable if `RCC_PLL` is selected)

### System Clock Source Options

- `RCC_HSE_CRYSTAL`: HSE (High Speed External) Crystal
- `RCC_HSE_RC`: HSE (High Speed External) RC
- `RCC_HSI`: HSI (High Speed Internal)
- `RCC_PLL`: PLL (Phase-Locked Loop)

### PLL Input Clock Source Options

- `RCC_PLL_IN_HSI_DIV_2`: HSI divided by 2
- `RCC_PLL_IN_HSE_DIV_2`: HSE divided by 2
- `RCC_PLL_IN_HSE`: HSE

### PLL Multiplication Value Options

- 2 to 16 (inclusive)

## Functions

- `RCC_voidInitSystemClock()`: Initializes the system clock source according to the chosen configuration.
- `RCC_voidEnableClock()`: Enables a peripheral clock for a specified bus and peripheral ID.
- `RCC_voidDisableClock()`: Disables a peripheral clock for a specified bus and peripheral ID.

## Example Usage

```c
#include "RCC_interface.h"
#include "RCC_config.h"

int main(void)
{
    RCC_voidInitSystemClock();
    RCC_voidEnableClock(RCC_AHB, GPIOA);
    RCC_voidDisableClock(RCC_APB1, TIM2);
    return 0;
}