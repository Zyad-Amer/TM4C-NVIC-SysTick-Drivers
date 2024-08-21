# NVIC and SysTick Drivers

## Overview
This repository contains drivers for the Nested Vectored Interrupt Controller (NVIC) and SysTick Timer for the TM4C123GH6PM microcontroller. These drivers provide basic functionalities to manage interrupts and the system timer.

## NVIC Driver

### Features
- **Enable/Disable IRQs:** Control specific interrupts by enabling or disabling them.
- **Set IRQ Priority:** Configure the priority of specific interrupts.
- **Enable/Disable System Exceptions:** Manage system exceptions like memory faults, bus faults, and usage faults.
- **Set Exception Priority:** Adjust the priority for system exceptions.

### Functions
- `NVIC_EnableIRQ(IRQ_Num)`: Enables the specified IRQ.
- `NVIC_DisableIRQ(IRQ_Num)`: Disables the specified IRQ.
- `NVIC_SetPriorityIRQ(IRQ_Num, IRQ_Priority)`: Sets the priority for the specified IRQ.
- `NVIC_EnableException(Exception_Num)`: Enables the specified system exception.
- `NVIC_DisableException(Exception_Num)`: Disables the specified system exception.
- `NVIC_SetPriorityException(Exception_Num, Exception_Priority)`: Sets the priority for the specified system exception.

## SysTick Driver

### Features
- **Initialization:** Configure the SysTick timer to generate periodic interrupts.
- **Busy-Wait:** Set up the SysTick timer for delay using busy-waiting.
- **Callback Support:** Register a callback function to be executed on SysTick interrupt.
- **Start/Stop Timer:** Start, stop, or deinitialize the SysTick timer.

### Functions
- `SysTick_Init(a_TimeInMilliSeconds)`: Initializes the SysTick timer with the specified period.
- `SysTick_StartBusyWait(a_TimeInMilliSeconds)`: Starts the SysTick timer for a specified time using busy-wait.
- `SysTick_SetCallBack(Ptr2Func)`: Registers a callback function for SysTick interrupts.
- `SysTick_Handler()`: Default handler for the SysTick interrupt, calls the registered callback.
- `SysTick_Start()`: Starts or resumes the SysTick timer.
- `SysTick_Stop()`: Stops the SysTick timer.
- `SysTick_DeInit()`: Deinitializes the SysTick timer.

## Usage
- **NVIC:** Use the NVIC functions to manage hardware interrupts and exceptions by enabling, disabling, and setting priorities.
- **SysTick:** Initialize the SysTick timer for periodic tasks, use busy-wait for delays, and register callbacks for interrupt handling.

## Test Descriptions

### 1. GPIO and SysTick Test
This test demonstrates the use of GPIO interrupts and the SysTick timer. It is designed to alternate the state of three LEDs (Red, Blue, Green) on the TM4C123GH6PM microcontroller and respond to an external interrupt triggered by pressing the SW2 button.

- **SW2 Button (PF0):** Configured as an external interrupt source. When pressed, it triggers the `GPIOPortF_Handler()` interrupt service routine (ISR).
  - **ISR Functionality:**
    - Stops the SysTick timer.
    - Turns on all three LEDs (Red, Blue, Green) for 5 seconds.
    - Restarts the SysTick timer.
    - Clears the interrupt flag for PF0.
- **SysTick Timer:** Configured to generate an interrupt every 1 second.
  - **ISR Functionality:** Each second, the ISR changes the state of the LEDs to turn on one LED at a time in the sequence: Red → Blue → Green.

### 2. Exception Settings Test
This test validates the configuration of various system and fault exceptions on the TM4C123GH6PM microcontroller. The test ensures that exceptions like Memory Management Fault, Bus Fault, Usage Fault, and others can be enabled, disabled, and have their priorities correctly set.

- **Functionality:**
  - Enables and sets the priority for each of the following exceptions:
    - **Memory Management Fault**
    - **Bus Fault**
    - **Usage Fault**
    - **SVC (Supervisor Call) Exception**
    - **Debug Monitor Exception**
    - **PendSV (Pendable Service Call) Exception**
    - **SysTick Exception**
  - **Assertions:** After each operation, the code asserts the correct settings to ensure the exceptions are configured properly.
- **LED Indications:** The LEDs are also used to provide visual feedback, turning on and off as part of the test loop.
