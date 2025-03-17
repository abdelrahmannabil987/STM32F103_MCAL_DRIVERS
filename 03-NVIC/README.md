# STM32F103 NVIC Driver (Bare-Metal)

A fully manual, register-level **NVIC (Nested Vector Interrupt Controller)** driver for the **STM32F103** microcontroller, built from scratch for fine-tuned interrupt control.

> Ideal for low-level embedded systems projects where **CMSIS** or **HAL** libraries are not used.

---

## 📌 Overview

- 📅 **Date**: 31 OCT 2024  
- 🔢 **Version**: V01  
- 🧑‍💻 **Author**: Abdelrahman Nabil

This driver allows precise control over **interrupt enabling, disabling, pending flags, active flags, and priority configuration** — all through **direct memory access** to NVIC registers.

---

## 🗂️ File Summary

| File               | Description                                                  |
|--------------------|--------------------------------------------------------------|
| `NVIC_interface.h` | Public APIs, IRQ numbers, user-callable functions            |
| `NVIC_private.h`   | Register definitions and internal macros                     |
| `NVIC_config.h`    | User configuration for priority grouping                     |
| `NVIC_program.c`   | Function definitions with register-level manipulations       |

---

## ✨ Features

- Enable/disable **external interrupts** (0 to 59)
- Set/clear **pending flags** for software-triggered IRQs
- Read **active flags** to check real-time IRQ status
- Configure **priority grouping** (group vs sub-priority bits)
- Set **interrupt priority** per peripheral/IRQ
- Lightweight: No dependencies on CMSIS or STM32 HAL

---

## 🔧 Configuration (Priority Grouping)

Located in `NVIC_config.h`:

| Macro                  | Group Priority Bits | Sub-Priority Bits |
|-----------------------|---------------------|-------------------|
| `MNVIC_4_GROUPS_0_SUB` | 4                   | 0                 |
| `MNVIC_3_GROUPS_1_SUB` | 3                   | 1                 |
| `MNVIC_2_GROUPS_2_SUB` | 2                   | 2                 |
| `MNVIC_1_GROUPS_3_SUB` | 1                   | 3                 |
| `MNVIC_0_GROUPS_4_SUB` | 0                   | 4                 |

### Example
```c
#define MNVIC_GROUP_SUB_DISTRIBUTION MNVIC_2_GROUPS_2_SUB
```

In `MNVIC_voidInit()`, this value is written to **SCB_AIRCR** to configure how the priority bits are split.

---

## 🧩 API Functions – Detailed

### 1. Initialize NVIC
```c
void MNVIC_voidInit(void);
```
> Sets up the **priority grouping** for group vs sub-priority division.

---

### 2. Enable Interrupt
```c
void MNVIC_voidEnableInterrupt(u8 interruptNumber);
```
> Enables IRQs 0–59 by writing to `NVIC_ISERx`.

---

### 3. Disable Interrupt
```c
void MNVIC_voidDisableInterrupt(u8 interruptNumber);
```
> Disables IRQs by writing to `NVIC_ICERx`.

---

### 4. Set Pending Flag
```c
void MNVIC_voidSetPendingFlag(u8 interruptNumber);
```
> Software-trigger an interrupt using **pending flag**.

---

### 5. Clear Pending Flag
```c
void MNVIC_voidDisablePendingFlag(u8 interruptNumber);
```
> Clears software-triggered pending status.

---

### 6. Get Active Flag
```c
u8 MNVIC_u8GetActiveFlag(u8 interruptNumber);
```
> Returns 1 if IRQ is active, 0 if not.

---

### 7. Set Priority
```c
void MNVIC_voidSetPriority(u8 interruptNumber, u8 priority);
```
> Sets **8-bit priority** value to `NVIC_IPRx`.  
*Note: Only upper 4 bits are effective (Cortex-M3).*

---

## 🧠 How Priorities Work (Cortex-M3)

- Each IRQ priority is stored in an 8-bit slot at `NVIC_IPRx`.
- **Only upper 4 bits are implemented** → Priority values: 0–15.
- Lower value = **higher priority** (0 is highest).

---

## 🧱 Register Mapping

| Register         | Address       | Bits Covered              |
|------------------|---------------|---------------------------|
| `NVIC_ISER0`     | 0xE000E100    | Enable IRQ 0–31           |
| `NVIC_ISER1`     | 0xE000E104    | Enable IRQ 32–59          |
| `NVIC_ICER0`     | 0xE000E180    | Disable IRQ 0–31          |
| `NVIC_ICER1`     | 0xE000E184    | Disable IRQ 32–59         |
| `NVIC_ISPR0`     | 0xE000E200    | Set pending IRQ 0–31      |
| `NVIC_ISPR1`     | 0xE000E204    | Set pending IRQ 32–59     |
| `NVIC_ICPR0`     | 0xE000E280    | Clear pending IRQ 0–31    |
| `NVIC_ICPR1`     | 0xE000E284    | Clear pending IRQ 32–59   |
| `NVIC_IABR0`     | 0xE000E300    | Active status IRQ 0–31    |
| `NVIC_IABR1`     | 0xE000E304    | Active status IRQ 32–59   |
| `NVIC_IPR`       | 0xE000E400    | Priority registers        |
| `SCB_AIRCR`      | 0xE000ED0C    | Priority grouping control |

---

## 🗃️ Interrupt Numbers (Macros)

| Peripheral       | Macro Name         | IRQ Number |
|------------------|--------------------|------------|
| EXTI0            | `EXTI0`            | 6          |
| TIM2             | `TIM2`             | 28         |
| USART1           | `USART1`           | 37         |
| SPI1             | `SPI1`             | 35         |
| UART5            | `UART5`            | 53         |
| DMA2_Channel4_5  | `DMA2_Channel4_5`  | 59         |
| ...              | ...                | ...        |

---

## 🧪 Example

```c
#include "NVIC_interface.h"

int main(void) {
    MNVIC_voidInit();  // Set priority grouping

    MNVIC_voidEnableInterrupt(USART1);    // Enable USART1 IRQ
    MNVIC_voidSetPriority(USART1, 2);     // Set priority to 2

    while (1) {
        // Application loop
        if (MNVIC_u8GetActiveFlag(USART1)) {
            // USART1 is active
        }
    }
}
```