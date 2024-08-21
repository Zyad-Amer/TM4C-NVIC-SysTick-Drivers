/*
 * NVIC.c
 *
 *  Created on: Jul 26, 2024
 *      Author: Zyad Montaser
 */

#include "NVIC.h"
#include "Common_Macros.h"
#include "tm4c123gh6pm_registers.h"

/* Access the correct priority register by adding (IRQ_Num/4) to the address of the first priority register */
#define NVIC_PRI_REG(irq_num) (*((volatile uint32 *)(0xE000E400 + (irq_num / 4))))

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num)
{
    /* The first 32 interrupts controlled by Enable register number 0 */
    if (IRQ_Num <= 31)
        SET_BIT(NVIC_EN0_REG, IRQ_Num);

    /* The second 32 interrupts controlled by Enable register number 1 */
    else if (IRQ_Num <= 63)
        SET_BIT(NVIC_EN1_REG, (IRQ_Num - 32));

    /* The third 32 interrupts controlled by Enable register number 2 */
    else if (IRQ_Num <= 95)
        SET_BIT(NVIC_EN2_REG, (IRQ_Num - 64));

    /* The fourth 32 interrupts controlled by Enable register number 3 */
    else if (IRQ_Num <= 127)
        SET_BIT(NVIC_EN3_REG, (IRQ_Num - 96));

    /* The fifth 32 interrupts controlled by Enable register number 4 */
    else if (IRQ_Num <= 159)
        SET_BIT(NVIC_EN4_REG, (IRQ_Num - 128));
}

void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num)
{
    /* The first 32 interrupts controlled by Enable register number 0 */
    if (IRQ_Num <= 31)
        SET_BIT(NVIC_DIS0_REG, IRQ_Num);

    /* The second 32 interrupts controlled by Enable register number 1 */
    else if (IRQ_Num <= 63)
        SET_BIT(NVIC_DIS1_REG, (IRQ_Num - 32));

    /* The third 32 interrupts controlled by Enable register number 2 */
    else if (IRQ_Num <= 95)
        SET_BIT(NVIC_DIS2_REG, (IRQ_Num - 64));

    /* The fourth 32 interrupts controlled by Enable register number 3 */
    else if (IRQ_Num <= 127)
        SET_BIT(NVIC_DIS3_REG, (IRQ_Num - 96));

    /* The fifth 32 interrupts controlled by Enable register number 4 */
    else if (IRQ_Num <= 159)
        SET_BIT(NVIC_DIS4_REG, (IRQ_Num - 128));
}

void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority)
{
    uint32 pri_reg;

    /* Access the correct priority register by adding (IRQ_Num/4) to the address of the first priority register */
    pri_reg = NVIC_PRI_REG(IRQ_Num);

    if (IRQ_Num % 4 == 0)
    {
        /* Insert the given priority number to bits number 5, 6, and 7 */
        pri_reg = (pri_reg & 0xFFFFFF1F) | (IRQ_Priority << 5);
    }
    else if (IRQ_Num % 4 == 1)
    {
        /* Insert the given priority number to bits number 13, 14, and 15 */
        pri_reg = (pri_reg & 0xFFFF1FFF) | (IRQ_Priority << 13);
    }
    else if (IRQ_Num % 4 == 2)
    {
        /* Insert the given priority number to bits number 21, 22, and 23 */
        pri_reg = (pri_reg & 0xFF1FFFFF) | (IRQ_Priority << 21);
    }
    else if (IRQ_Num % 4 == 3)
    {
        /* Insert the given priority number to bits number 29, 30, and 31 */
        pri_reg = (pri_reg & 0x1FFFFFFF) | (IRQ_Priority << 29);
    }
}

void NVIC_EnableException(NVIC_ExceptionType Exception_Num)
{
    switch (Exception_Num)
    {
        case EXCEPTION_MEM_FAULT_TYPE:
            SET_BIT(NVIC_SYSTEM_SYSHNDCTRL, 16); /* Enable the memory management fault */
            break;

        case EXCEPTION_BUS_FAULT_TYPE:
            SET_BIT(NVIC_SYSTEM_SYSHNDCTRL, 17); /* Enable the Bus fault */
            break;

        case EXCEPTION_USAGE_FAULT_TYPE:
            SET_BIT(NVIC_SYSTEM_SYSHNDCTRL, 18); /* Enable the Usage fault */
            break;

        default:
            break;
    }
}

void NVIC_DisableException(NVIC_ExceptionType Exception_Num)
{
    switch (Exception_Num)
    {
        case EXCEPTION_MEM_FAULT_TYPE:
            CLEAR_BIT(NVIC_SYSTEM_SYSHNDCTRL, 16); /* Disable the memory management fault */
            break;

        case EXCEPTION_BUS_FAULT_TYPE:
            CLEAR_BIT(NVIC_SYSTEM_SYSHNDCTRL, 17); /* Disable the Bus fault */
            break;

        case EXCEPTION_USAGE_FAULT_TYPE:
            CLEAR_BIT(NVIC_SYSTEM_SYSHNDCTRL, 18); /* Disable the Usage fault */
            break;

        default:
            break;
    }
}

void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority)
{
    switch (Exception_Num)
    {
        case EXCEPTION_MEM_FAULT_TYPE:
            /* Insert the memory management fault priority to bits number 5, 6, and 7 of SYSPRI1 register */
            NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & 0xFFFFFF1F) | (Exception_Priority << 5);
            break;

        case EXCEPTION_BUS_FAULT_TYPE:
            /* Insert the Bus fault priority to bits number 13, 14, and 15 of SYSPRI1 register */
            NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & 0xFFFF1FFF) | (Exception_Priority << 13);
            break;

        case EXCEPTION_USAGE_FAULT_TYPE:
            /* Insert the Usage fault priority to bits number 21, 22, and 23 of SYSPRI1 register */
            NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & 0xFF1FFFFF) | (Exception_Priority << 21);
            break;

        case EXCEPTION_SVC_TYPE:
            /* Insert the SVC priority to bits number 29, 30, and 31 of SYSPRI2 register */
            NVIC_SYSTEM_PRI2_REG = (NVIC_SYSTEM_PRI2_REG & 0x1FFFFFFF) | (Exception_Priority << 29);
            break;

        case EXCEPTION_DEBUG_MONITOR_TYPE:
            /* Insert the DEBUG_MONITOR_TYPE priority to bits number 5, 6, and 7 of SYSPRI3 register */
            NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & 0xFFFFFF1F) | (Exception_Priority << 5);
            break;

        case EXCEPTION_PEND_SV_TYPE:
            /* Insert the PendSV priority to bits number 21, 22, and 23 of SYSPRI3 register */
            NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & 0xFF1FFFFF) | (Exception_Priority << 21);
            break;

        case EXCEPTION_SYSTICK_TYPE:
            /* Insert the SysTick timer interrupt priority to bits number 29, 30, and 31 of SYSPRI3 register */
            NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & 0x1FFFFFFF) | (Exception_Priority << 29);
            break;

        default:
            break;
    }
}
