/*******************************************************************************/
/**
\file       Ect.c
\brief      Enhanced Capture Timer
\author     Gerardo Valdovinos
\version    1.0
\date       18/11/2014
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Own headers */
#include "Ect.h"

/** Used modules */

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/
u16 u16PulseTime;
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

/*****************************************************************************************************
* Code of module wide FUNCTIONS
****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    Input capture Initialization
* \author   Gerardo Valdovinos
* \param    void
* \return   void    
*/
void Ect_Init(void)
{
     ECT_TIOS   =   0x00;                       // Configure  all channels as input capture
     
     ECT_TSCR1  =   ECT_TSCR1_PRNT_MASK |       // Enable presicion timers           
                    ECT_TSCR1_TFFCA_MASK;       // Enable fast flag clear
                    
     ECT_TCTL4  =   ECT_TCTL4_EDG0B_MASK;       // Sets capture on falling edge on Ch0
     
     ECT_TIE    =   ECT_TIE_C0I_MASK;           // Enable interrupt on Ch0
     
     ECT_ICOVW  =   ECT_ICOVW_NOVW0_MASK;       // Erase a register until it is read
     
     ECT_ICSYS  =   ECT_ICSYS_TFMOD_MASK |      // Interrupt every two counter values
                    ECT_ICSYS_BUFEN_MASK;       // Enable holding register
         
     ECT_PTPSR  =   0xFF;                       // Prescaler to 256                
   
}

/****************************************************************************************************/
/**
* \brief    Input capture Initialization
* \author   Gerardo Valdovinos
* \param    void
* \return   void    
*/
void Ect_Start(void)
{
    /* Enable timer */
    ECT_TSCR1_TEN = 1;   
}


#pragma CODE_SEG __NEAR_SEG NON_BANKED
/****************************************************************************************************/
/**
* \brief    ECT channel 0 interrupt
* \author   Gerardo Valdovinos
* \param    void 
* \return   void
*/
void interrupt  vfnECT_Channel0_Isr( void )
{
    u16 u16TimeTC0;
    u16 u16TimeTC0H;

    u16TimeTC0 = ECT_TC0;
    u16TimeTC0H = ECT_TC0H;
    
    if(u16TimeTC0 > u16TimeTC0H)
    {
        u16PulseTime = u16TimeTC0 - u16TimeTC0H;     
    }
    else
    {
        
        u16PulseTime = (0xFFFF - u16TimeTC0H) + u16TimeTC0; 
    }
}

#pragma CODE_SEG DEFAULT
/****************************************************************************************************/