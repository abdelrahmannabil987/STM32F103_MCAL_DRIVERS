# STM32F103 GPIO Driver

A **bare-metal GPIO driver** for the STM32F103 microcontroller, offering precise control over pin modes, values, and ports using direct register access. Designed for performance and educational purposes.

---

## 🧑‍💻 Author
**Abdelrahman Nabil**  
📅 **Date**: 24 OCT 2024  
📄 **Version**: V01  

---

## 📂 Project Structure

```
GPIO_Driver/
├── GPIO_interface.h   // Public API and macros
├── GPIO_private.h     // Register addresses and internal definitions
├── GPIO_config.h      // Configuration header (reserved for future use)
└── GPIO_program.c     // Function implementations
```

---

## 🚀 Features

- Set pin **direction and mode** (Input, Output, Analog, Alternate Function).
- Write **HIGH/LOW** to individual pins or full ports.
- Read **input pin states**.
- Lightweight and **no external libraries** (HAL/LL) required.
- Ideal for **learning embedded systems** and low-level programming.

---

## 📚 Supported Modes

### Input Modes:
| Macro                  | Description                |
|------------------------|----------------------------|
| `INPUT_ANALOG`         | Analog input               |
| `INPUT_FLOATING`       | Floating input             |
| `INPUT_PULL_UP_DOWN`   | Input with pull-up/down    |

### Output Modes:
| Macro                        | Mode                                 |
|-----------------------------|--------------------------------------|
| `OUTPUT_SPEED_10MHZ_PP`     | Output Push-Pull @ 10MHz             |
| `OUTPUT_SPEED_10MHZ_OD`     | Output Open-Drain @ 10MHz            |
| `OUTPUT_SPEED_10MHZ_AF_PP`  | Alt Func Push-Pull @ 10MHz           |
| `OUTPUT_SPEED_10MHZ_AF_OD`  | Alt Func Open-Drain @ 10MHz          |
| *Same for 2MHz and 50MHz variants* |

---

## 🛠️ API Functions

### 1. Set Pin Direction

```c
void MGPIO_voidSetPinDirection(u8 port, u8 pin, u8 mode);
```

**Example:**
```c
MGPIO_voidSetPinDirection(GPIOA, PIN0, OUTPUT_SPEED_2MHZ_PP);
```

---

### 2. Set Pin Value

```c
void MGPIO_voidSetPinValue(u8 port, u8 pin, u8 value);
```

- `value`: `GPIO_HIGH` or `GPIO_LOW`

**Example:**
```c
MGPIO_voidSetPinValue(GPIOA, PIN0, GPIO_HIGH);
```

---

### 3. Read Pin Value

```c
u8 MGPIO_voidGetPinValue(u8 port, u8 pin);
```

**Example:**
```c
u8 val = MGPIO_voidGetPinValue(GPIOB, PIN5);
if (val == GPIO_HIGH) {
    // Do something
}
```

---

### 4. Set Full Port Value

```c
void MGPIO_voidSetPortValue(u8 port, u8 value);
```

**Example:**
```c
MGPIO_voidSetPortValue(GPIOC, 0xFF); // Set first 8 pins high
```

---

## 📌 Pin and Port Definitions

### Ports:
| Macro  | Description     |
|--------|-----------------|
| GPIOA  | Port A          |
| GPIOB  | Port B          |
| GPIOC  | Port C          |

### Pins:
| Macro    | Value  |
|----------|--------|
| PIN0     | 0      |
| ...      | ...    |
| PIN15    | 15     |

---

## 🔧 Register Access

Registers are directly mapped using memory addresses:

| Register   | Offset | Description                      |
|------------|--------|----------------------------------|
| `CRL`      | 0x00   | Control low pins (0-7)           |
| `CRH`      | 0x04   | Control high pins (8-15)         |
| `IDR`      | 0x08   | Input Data Register              |
| `ODR`      | 0x0C   | Output Data Register             |
| `BSRR`     | 0x10   | Bit Set/Reset                    |
| `BRR`      | 0x14   | Bit Reset                        |
| `LCKR`     | 0x18   | Lock Register                    |

*(Defined in `GPIO_private.h`)*

---

## 💡 Example: Blinking LED on PA0

```c
#include "GPIO_interface.h"

int main(void) {
    MGPIO_voidSetPinDirection(GPIOA, PIN0, OUTPUT_SPEED_2MHZ_PP);

    while (1) {
        MGPIO_voidSetPinValue(GPIOA, PIN0, GPIO_HIGH);
        for (volatile int i = 0; i < 100000; i++);  // Delay
        MGPIO_voidSetPinValue(GPIOA, PIN0, GPIO_LOW);
        for (volatile int i = 0; i < 100000; i++);  // Delay
    }
}
```

---
