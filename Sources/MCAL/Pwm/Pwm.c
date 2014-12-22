/*******************************************************************************/
/**
\file       Pwm.c
\brief      Pulse width modulation driver
\author     Gerardo Valdovinos
\version    1.0
\date       17/12/2014
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Own headers */
#include "Pwm.h"
/** Used modules */

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/

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
* \brief    Pwm driver initialization
* \author   Gerardo Valdovinos
* \param    const tstPwmDriverCfg* PwmDriverCfg
* \return   void    
*/
void vfnPwm_Init(const tstPwmDriverCfg* PwmDriverCfg)
{
    u8 bIndex;
    u8 u8Channel16;
    u16 u16DutyCycle;
    u16 u16Frequency;

    if(PwmDriverCfg->u8Channels)
    {
        /* Concatenate all channels */
        PWMCTL = PWMCTL_CON01_MASK | PWMCTL_CON23_MASK | PWMCTL_CON45_MASK | PWMCTL_CON67_MASK;
        
        /* High level in start in all channels */
        PWMPOL = 0xFF;
        
        /* All channels left alligned */         
        PWMCAE = 0x00;          
        
        /* A and B clock selected */   
        PWMCLK = 0x00; 
        
        /* Bus clock divided by 4 in clock A and B */        
        PWMPRCLK = PWMPRCLK_PCKA1_MASK | PWMPRCLK_PCKB1_MASK;                     
        
        /* For every channel set period and DC */
        for(bIndex = 0;bIndex < PwmDriverCfg->u8Channels; bIndex++)
        {     
            /* Save in local variables */       
            u8Channel16 = PwmDriverCfg->stChannelCfg[bIndex].u8Channel16;
            u16DutyCycle = PwmDriverCfg->stChannelCfg[bIndex].u16DutyCycle;
            u16Frequency = PwmDriverCfg->stChannelCfg[bIndex].u16Frequency;
            
            /* Set period */
            PWMPER_W(u8Channel16, u16Frequency);
            
            /* Set duty cycle */
            PWMDTY_W(u8Channel16, u16DutyCycle);    
        } 
    }

    /*
    PWMCTL = PWMCTL_CON01_MASK;         // Concatenate channel 0 and 1
    PWMPOL = PWMPOL_PPOL1_MASK;         // High level in start
    PWMCAE = PWMCAE_CAE1_MASK;          // Left aligned   
    PWMCLK = PWMCLK_PCLK1_MASK;         // SA is selected as clock
    PWMPRCLK = PWMPRCLK_PCKA_MASK;      // Prescaler to A clock = Bus/2                
    PWMSCLA = 180;                     // Prescaler to 91 * 2 = 182
    
    PWMPER01 = 1000;      // Period
    PWMDTY01 = PWMPER01/2;      // Duty clycle 
    
    PWME = PWME_PWME1_MASK;             // Enable channel 1 
    */   
}

/****************************************************************************************************/
/**
* \brief    Pwm channel start
* \author   Gerardo Valdovinos
* \param    void
* \return   void    
*/
void vfnPwm_Start(u8 u8Channel)
{
    /* Enable channel */
    PWME_W(u8Channel, TRUE);                    
}

/****************************************************************************************************/
/**
* \brief    Pwm channel end
* \author   Gerardo Valdovinos
* \param    void
* \return   void    
*/
void vfnPwm_End(u8 u8Channel)
{
    /* Enable channel */
    PWME_W(u8Channel, FALSE);                    
}

/****************************************************************************************************/