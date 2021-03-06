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
        LED_OFF,
        LED_LOW_FREQ,
        0,
        0,
        0,        
    },
    {
        PORTA_PA1_MASK,
        LED_OFF,
        LED_LOW_FREQ,
        0,
        0,
        0,        
    },
    {
        PORTA_PA2_MASK,
        LED_OFF,
        LED_LOW_FREQ,
        0,
        0,
        0,         
    },
    {
        PORTA_PA3_MASK,
        LED_OFF,
        LED_LOW_FREQ,
        0,
        0,
        0,         
    },        
};

u8 u8Button0;
u8 u8Button1;
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
    //static u16 time = 0;

    /* Call to Control of pendubot function */
    //vfnCtrl_Pendubot();
    
    //PORTA_PA0 ^= 1;
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
* \brief    Task 2 - 1ms Period
* \author   Gerardo Valdovinos
* \param    void
* \return   void   
*/
TASK(Task_2ms)
{

    (void)Os_TerminateTask();     
}
/****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    Task 3 - 4ms Period
* \author   Gerardo Valdovinos
* \param    void
* \return   void   
*/
TASK(Task_4ms)
{
    /*/(void)u8fnSci_TxChar(SCI_CH0, 31);
        vfnSci_Tx(SCI_CH0, (u8*)&au8Temp[0], sizeof(au8Temp));
    } 
    
    // Escribir un byte por SPI
    if(SPI0SR_SPTEF == 1)
    {
        SPI0DRL = 0xAA;
    }   */
    (void)Os_TerminateTask();    
}

/**
* \brief    Task 4 - 64ms Period
* \author   Gerardo Valdovinos
* \param    void
* \return   void   
*/
TASK(Task_64ms)
{   
    /* This task controls the leds */
    vfnLedManager(&astLed[0]);
    vfnLedManager(&astLed[1]);
    vfnLedManager(&astLed[2]);
    vfnLedManager(&astLed[3]);
      
    (void)Os_TerminateTask();     
}

/**
* \brief    Task 5 - 128ms Period
* \author   Gerardo Valdovinos
* \param    void
* \return   void   
*/
TASK(Task_128ms)
{
    static u8 u8B1, u8B0;
    
    /* This task controls Button */
    if(PTP_PTP0 == 1)
    {
        u8B0++;        
    }
    else if( (PTP_PTP0 == 0) && (u8B0 != 0))
    {
        /* Reset debounce counter */
        u8B0 = 0;
        
        if(u8B0 > 15)
            u8Button0 = BUTTON_0_LONG;
        else
            u8Button0 = BUTTON_0;
    }
    
    if(PTP_PTP1 == 1)
    {
        u8B1++;        
    }
    else if( (PTP_PTP1 == 0) && (u8B1 != 0))
    {
        /* Reset debounce counter */
        u8B1 = 0;
        
        if(u8B1 > 15)
            u8Button1 = BUTTON_1_LONG;
        else
            u8Button1 = BUTTON_1;
    } 
    
    (void)Os_TerminateTask();    
}

/**
* \brief    Manager of leds. It permit a led to turn on, turn off and toggle.
* \author   Gerardo Valdovinos
* \param    void
* \return   void   
*/
void vfnLedManager(tstLed *pstLed)
{  
    switch(pstLed->u8Status)
    {
    case LED_ON:
        PORTA |= (1 << pstLed->u8LedMask);
        break;
    case LED_OFF:
        PORTA &= ~(1 << pstLed->u8LedMask);
        break;
    case LED_TOGGLE:
        pstLed->u8FreqCnt++;
        if(pstLed->u8FreqCnt >= pstLed->u8Freq )
        {
            pstLed->u8FreqCnt = 0;
            PORTA ^= (1 << pstLed->u8LedMask);
            
            if( (pstLed->u8Cnt != 0xFF) && (pstLed->u8Cnt >= (pstLed->u8Times * 2)))
            {
                pstLed->u8Status = LED_OFF;
            }
        }
        break;
    default:
        break;
    }
}
/****************************************************************************************************/


