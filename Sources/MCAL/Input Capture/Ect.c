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
//volatile u16 u16PulseTime;

/* Channel status pointer */
tstEctChannel* pstEctChannel;

/* Driver status */
tstEctDriver stEctDriver;

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
* \param    const tstEctDriverCfg* EctDriverCfg
* \return   void    
*/
void Ect_Init(const tstEctDriverCfg* EctDriverCfg)
{
    u8 u8Index;
    
    if(EctDriverCfg->u8Channels)
    {
        /* Allocate memory for channels status */
        pstEctChannel = (tstEctChannel*)pu8fnMem_Reserve(EctDriverCfg->u8Channels * sizeof(tstEctChannel));
        
        /* Fill Ect driver */
        stEctDriver.u8Channels = EctDriverCfg->u8Channels;
        stEctDriver.pstChannel = pstEctChannel;
        
        /* Configure  all channels as input capture */
        ECT_TIOS   =    0x00;                       
        
        /* Enable presicion timers and Enable fast flag clear */ 
        ECT_TSCR1  =    ECT_TSCR1_PRNT_MASK |                  
                        ECT_TSCR1_TFFCA_MASK;
        
        /* Interrupt every two counter values and Enable holding register */               
        ECT_ICSYS  =    ECT_ICSYS_TFMOD_MASK |       
                        ECT_ICSYS_BUFEN_MASK;         
        
        /* Bus prescaler to 256 */                            
        ECT_PTPSR  =   0xFF;                       // 
                        
        for(u8Index = 0;u8Index < EctDriverCfg->u8Channels;u8Index++)
        {
            /* Copy channel to status struct */
            pstEctChannel[u8Index].eChannel = EctDriverCfg->pstChannelCfg[u8Index].eChannel;
            
            /* Set pulse time to 0 */
            pstEctChannel[u8Index].u16PulseTime = 0;
            
            /* Erase a register until it is read */  
            ICOVW_SET(pstEctChannel[u8Index].eChannel);       
        }
    }

     /*
     ECT_TIOS   =   0x00;                       // Configure  all channels as input capture
     
     ECT_TSCR1  =   ECT_TSCR1_PRNT_MASK |       // Enable presicion timers           
                    ECT_TSCR1_TFFCA_MASK;       // Enable fast flag clear
                    
     ECT_TCTL4  =   ECT_TCTL4_EDG0B_MASK;       // Sets capture on falling edge on Ch0
     
     ECT_TIE    =   ECT_TIE_C0I_MASK;           // Enable interrupt on Ch0 
     
     ECT_ICOVW  =   ECT_ICOVW_NOVW0_MASK;       // Erase a register until it is read
     
     ECT_ICSYS  =   ECT_ICSYS_TFMOD_MASK |      // Interrupt every two counter values
                    ECT_ICSYS_BUFEN_MASK;       // Enable holding register
         
     ECT_PTPSR  =   0xFF;                       // Prescaler to 256                
     */
}

/****************************************************************************************************/
/**
* \brief    Input capture channel enable
* \author   Gerardo Valdovinos
* \param    void
* \return   void    
*/
void Ect_Enable(teEctCh Channel)
{
    /* Sets capture on falling edge */
    if(Channel <= 3)
    {        
        TCTL4_SET(Channel);
    }
    else
    {
        TCTL3_SET(Channel); 
    }

    
    /* Enable interrupt */
    TIE_SET(Channel);           
    
    /* Enable timer */
    ECT_TSCR1_TEN = 1;     
}

/****************************************************************************************************/
/**
* \brief    Input capture channel disable
* \author   Gerardo Valdovinos
* \param    void
* \return   void    
*/
void Ect_Disable(teEctCh Channel)
{
    /* Sets capture on falling edge */
    if(Channel <= 3)
    {        
        TCTL4_CLEAR(Channel);
    }
    else
    {
        TCTL3_CLEAR(Channel); 
    }

    
    /* Enable interrupt */
    TIE_CLEAR(Channel);               
}

/****************************************************************************************************/
/**
* \brief    ECT channel 0 interrupt
* \author   Gerardo Valdovinos
* \param    void 
* \return   void
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt  vfnECT_Channel0_Isr( void )
{
/*
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
    */
}

#pragma CODE_SEG DEFAULT
/****************************************************************************************************/