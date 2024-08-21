/*
 * SysTick.c
 *
 *  Created on: Jul 26, 2024
 *      Author: Zyad Montaser
 */

#include "SysTick.h"
#include "Common_Macros.h"
#include "tm4c123gh6pm_registers.h"

static volatile void (*g_callBackptr)(void)=NULL_PTR;


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void SysTick_Init(uint16 a_TimeInMilliSeconds)
{
    SYSTICK_CTRL_REG    = 0; /* Initially disable the SysTick Timer by Clear the ENABLE Bit */

    /* The count takes 62.5 nSec (1/16M), 24 bit timer =16777215 count therefore it overflows every 1048.5 msec */
    if(a_TimeInMilliSeconds <= 1048)
    {
        SYSTICK_RELOAD_REG  = (a_TimeInMilliSeconds*16000)-1;      /* Set the Reload value  */
    }

    SYSTICK_CURRENT_REG = 0;       /* Clear the Current Register value */

    /*Choose the clock source to be System Clock (CLK_SRC = 1)
     * enable SysTick Interrupt (INTEN = 1)
     * enable the systick timer by set the enable bit*/
    SYSTICK_CTRL_REG |=0x07;

}

void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds)
{
    SYSTICK_CTRL_REG    = 0;              /* Disable the SysTick Timer by Clear the ENABLE Bit */

    /* The count takes 62.5 nSec (1/16M), 24 bit timer =16777215 count therefore it overflows every 1048.5 msec */
    if(a_TimeInMilliSeconds <= 1048)
    {
        SYSTICK_RELOAD_REG  = (a_TimeInMilliSeconds*16000)-1;      /* Set the Reload value  */
    }

    SYSTICK_CURRENT_REG = 0;              /* Clear the Current Register value */

     /* Enable the SysTick Timer (ENABLE = 1)
     * Disable SysTick Interrupt (INTEN = 0)
     * Choose the clock source to be System Clock (CLK_SRC = 1) */
    SYSTICK_CTRL_REG   |= 0x05;

    /* wait until the COUNT flag = 1 which mean SysTick Timer reaches ZERO value
     * COUNT flag is cleared after read the CTRL register value */
    while(!(SYSTICK_CTRL_REG & (1<<16)));
}

void SysTick_Handler(void)
{
    if(g_callBackptr != NULL_PTR)
    {
        /*call the CallBack Function */
        (*g_callBackptr)();
    }

    /* Clear the COUNT flag by writing any value in the Current Register as mentioned in the datasheet*/
    SYSTICK_CURRENT_REG = 0;
}

void SysTick_SetCallBack(volatile void (*Ptr2Func) (void))
{
    /* Save the address of the Call back function in a global variable */
    g_callBackptr = Ptr2Func;
}

void SysTick_Stop(void)
{
    CLEAR_BIT(SYSTICK_CTRL_REG,0); /* Clear the ENABLE Bit to stop the timer */
}

void SysTick_Start(void)
{
    /* Enable the SysTick Timer by set the ENABLE Bit */
    SET_BIT(SYSTICK_CTRL_REG,0);
}

void SysTick_DeInit(void)
{
    /* Clear All the SysTick Registers */
    SYSTICK_CTRL_REG = 0;
    SYSTICK_RELOAD_REG = 0;
    SYSTICK_CURRENT_REG = 0;

    /* Reset the global pointer value */
    g_callBackptr = NULL_PTR;
}

