/*******************************************************************************/
/**
\file       Os_Task.c
\brief      Operative System Module Tasks
\author     Gerardo Valdovinos
\version    1.0
\date       03/11/2014
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Own headers */
#include "Os_Task.h"
/** Used modules */

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/
tstLed astLed[] =
{
    {
        PORTA_PA0_MASK,
        LED_OFF;
        LED_LOW_FREQ;
        0;
        0;
        0;        
    },
    {
        PORTA_PA1_MASK,
        LED_OFF;
        LED_LOW_FREQ;
        0;
        0;
        0;        
    },
    {
        PORTA_PA2_MASK,
        LED_OFF;
        LED_LOW_FREQ;
        0;
        0;
        0;        
    },
    {
        PORTA_PA3_MASK,
        LED_OFF;
        LED_LOW_FREQ;
        0;
        0;
        0;        
    },
        
};
/*****************************************************************************************************
* Declaration of module wide FUNCTIONs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/
u8 au8Temp[] = "Que onda";
/*****************************************************************************************************
* Code of module wide FUNCTIONS
****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    Task 1 - 1ms Period
* \author   Gerardo Valdovinos
* \param    void
* \return   void   
*/
TASK(Task_1ms)
{
    static u16 time = 0;

    /* Call to Control of pendubot function */
    vfnCtrl_Pendubot();
    
    PORTA_PA0 ^= 1;
    /*
    time++;
    if(time >= 400)
    {
        PORTA_PA0 ^= 1; 
        time = 0;
    } 
    */
    (void)Os_TerminateTask();     
}
/****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    Task 1 - 1ms Period
* \author   Gerardo Valdovinos
* \param    void
* \return   void   
*/
TASK(Task_2ms)
{
    static u16 time = 0;

    /* Call to Control of pendubot function */
    
    
    
    /*
    time++;
    if(time >= 400)
    {
        PORTA_PA0 ^= 1; 
        time = 0;
    } 
    */
    (void)Os_TerminateTask();     
}
/****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    Task 2 - 4ms Period
* \author   Gerardo Valdovinos
* \param    void
* \return   void   
*/
TASK(Task_4ms)
{
    static u16 time = 0;
    
    time++;
    if(time >= 200)
    {
        PORTA_PA1 ^= 1; 
        time = 0;
    } 
    
    (void)Os_TerminateTask();    
}
/****************************************************************************************************/
/****************************************************************************************************/
/**
* \brief    Task 3 - 8ms Period
* \author   Gerardo Valdovinos
* \param    void
* \return   void   
*/
TASK(Task_8ms)
{
    static u16 time = 0;
    
    time++;
    if(time >= 200)
    {
        PORTA_PA2 ^= 1; 
        time = 0;
    } 
    
    (void)Os_TerminateTask();     
}
/****************************************************************************************************/
/****************************************************************************************************/
/**
* \brief    Task 4 - 16ms Period
* \author   Gerardo Valdovinos
* \param    void
* \return   void   
*/
TASK(Task_16ms)
{
    static u16 time = 0;
    
    /* This task controls the leds */
    vfnLedManager(tstLed *pstLed)
    
    
    time++;
    if(time >= 200)
    {
        PORTA_PA3 ^= 1; 
        time = 0;
        
        //(void)u8fnSci_TxChar(SCI_CH0, 31);
        vfnSci_Tx(SCI_CH0, (u8*)&au8Temp[0], sizeof(au8Temp));
    } 
    
    // Escribir un byte por SPI
    if(SPI0SR_SPTEF == 1)
    {
        SPI0DRL = 0xAA;
    }
      
    (void)Os_TerminateTask();     
}
/****************************************************************************************************/
/****************************************************************************************************/
/**
* \brief    Task 5 - 32ms Period
* \author   Gerardo Valdovinos
* \param    void
* \return   void   
*/
TASK(Task_32ms)
{
    ;    
}
/****************************************************************************************************/
/****************************************************************************************************/
/**
* \brief    Task 6 - 64ms Period
* \author   Gerardo Valdovinos
* \param    void
* \return   void   
*/
TASK(Task_64ms)
{
    ;    
}

/**
* \brief    Manager of leds. It permit a led to turn on, turn off and toggle.
* \author   Gerardo Valdovinos
* \param    void
* \return   void   
*/
void vfnLedManager(tstLed *pstLed)
{  
    switch(stLed->u8Status)
    {
    case LED_ON:
        PORTA |= (1 << stLed->u8LedMask);
        break;
    case LED_OFF:
        PORTA &= ~(1 << stLed->u8LedMask);
        break;
    case LED_TOGGLE:
        stLed.u8FreqCnt++;
        if(stLed->u8FreqCnt >= stLed->u8Freq )
        {
            stLed->u8FreqCnt = 0;
            PORTA ^= (1 << stLed->u8LedMask);
            
            if( (stLed->u8Cnt != 0xFF) && (stLed->u8Cnt >= (stLed->u8Times * 2)))
            {
                stLed->u8Status = LED_OFF;
            }
        }
        break;
    default:
        break;
    }
}
/****************************************************************************************************/


