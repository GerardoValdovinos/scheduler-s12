/*******************************************************************************/
/**
\file       Gpt.c
\brief      General Purpose Timer functions
\author     Gerardo Valdovinos
\version    1.0
\date       08/10/2014
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Own headers */
#include "Gpt.h"
/** Used modules */

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/
tstPIT_DeviceCfg* PIT_DeviceCfg;

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
* \brief    Initialize GPT
* \author   Gerardo Valdovinos
* \param    void 
* \return   void
*/
void Gpt_Init( const tstGpt_DriverCfg* Gpt_DriverCfg )
{
    u8 u8IndexChannel;
    static u32 u32Div;
    static u16 u16Div;
    tstPIT_ChannelCfg* Channel;
    
    /* Pointer to PIT device configuration */
    PIT_DeviceCfg = (tstPIT_DeviceCfg*) Gpt_DriverCfg[0].pstGpt_DevicesCfg[0].pstPIT_DeviceCfg;
    
    /* Check if there is at least one PIT channel to configure */
    if(PIT_DeviceCfg->u8PIT_Channels)
    {            
        /* PIT counter freeze while in Freeze mode */
        PITCFLMT_PITFRZ = 1u;
          
        /* Precalculated PIT microtimer (8-bit time base divider)*/
        PITMTLD0 = (u8)(PIT_DeviceCfg->u8PIT_uTimer0 - 1);
        PITMTLD1 = (u8)(PIT_DeviceCfg->u8PIT_uTimer1 - 1);
        
        for(u8IndexChannel = 0; u8IndexChannel < PIT_DeviceCfg->u8PIT_Channels; u8IndexChannel++)
        {     
            /* Save values in local for simplicity */
            Channel = (tstPIT_ChannelCfg*)&PIT_DeviceCfg->pstPIT_ChannelsCfg[u8IndexChannel];
            
            /* Calculates Timer value */               
            if(Channel->ePIT_uTimer == PIT_uTimer0)
            {                  
                u32Div = (u32)Channel->u16Freq_hz * (u32)PIT_DeviceCfg->u8PIT_uTimer0;     
                u16Div = (u16)(u32BusFreq / u32Div) - 1;
                PITLD_SET(u8IndexChannel,u16Div);
            }
            else
            {   
                u32Div = (u32)Channel->u16Freq_hz * (u32)PIT_DeviceCfg->u8PIT_uTimer1;     
                u16Div = (u16)(u32BusFreq / u32Div);
                PITLD_SET(u8IndexChannel,u16Div);                               
            }
            
            /* REGISTERS THAT ARE COMMON TO ALL PIT CHANNELS */
            /* Load 8-bit microtimer load register 0 into the 8-bit micro timer down-counter 0 */
            PITCFLMT_PFLMT0     = 1u;
            /* Load 8-bit microtimer load register 0 into the 8-bit micro timer down-counter 0 */
            PITCFLMT_PFLMT1     = 1u;
        } 
    }
}

/****************************************************************************************************/
/**
* \brief    Enable notifications
* \author   Gerardo Valdovinos
* \param    void 
* \return   void
*/
void Gpt_EnableNotification( Gpt_ChannelType Channel )
{
    /* Enable interrupt */
    PITINTE_EN(Channel);
    
    /* Clear interrupt flag */
    PITTF_CLEAR(Channel);   
}

/****************************************************************************************************/
/**
* \brief    Disable notifications
* \author   Gerardo Valdovinos
* \param    void 
* \return   void
*/
void Gpt_DisableNotification( Gpt_ChannelType Channel )
{
    /* Enable interrupt */
    PITINTE_DIS(Channel);
    
    /* Clear interrupt flag */
    PITTF_CLEAR(Channel);    
}

/****************************************************************************************************/
/**
* \brief    Start timer
* \author   Gerardo Valdovinos
* \param    void 
* \return   void
*/
void Gpt_StartTimer( Gpt_ChannelType Channel ) 
{
    tstPIT_ChannelCfg* ChannelCfg;

    /* Save values in local variable for simplicity */
    ChannelCfg = (tstPIT_ChannelCfg*)&PIT_DeviceCfg->pstPIT_ChannelsCfg[Channel];    
    
    /* Configure mux with corresponding uTimer */
    PITMUX_MT(Channel,ChannelCfg->ePIT_uTimer);
    
    /* Force load timer register */
    PITFLT_EN(Channel);
    
    /* Enable channel */    
    PITCE_EN(Channel);
    
    /* Enable Periodic Interrup Timer */
    PITCFLMT_PITE = 1u;   
}

/****************************************************************************************************/
/**
* \brief    Stop timer
* \author   Gerardo Valdovinos
* \param    void 
* \return   void
*/
void Gpt_StopTimer( Gpt_ChannelType Channel ) 
{
    /* Force load timer register */
    PITFLT_DIS(Channel);
    
    /* Enable channel */    
    PITCE_DIS(Channel);    
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED
/****************************************************************************************************/
/**
* \brief    PIT channel 0 interrupt
* \author   Gerardo Valdovinos
* \param    void 
* \return   void
*/
void interrupt  vfnPIT_Channel0_Isr( void )
{
    /* Callback for PIT channel 0 */
    if(PIT_DeviceCfg->pstPIT_ChannelsCfg[0].vpCallBack != NULL)
    {
        PIT_DeviceCfg->pstPIT_ChannelsCfg[0].vpCallBack();    
    }
    
    /* Clear interrupt flag */
    PITTF_CLEAR(0);
}

/****************************************************************************************************/
/**
* \brief    PIT channel 1 interrupt
* \author   Gerardo Valdovinos
* \param    void 
* \return   void
*/
void interrupt  vfnPIT_Channel1_Isr( void )
{
    /* Callback for PIT channel 0 */
    if(PIT_DeviceCfg->pstPIT_ChannelsCfg[1].vpCallBack != NULL)
    {
        PIT_DeviceCfg->pstPIT_ChannelsCfg[1].vpCallBack();    
    }
    
    /* Clear interrupt flag */
    PITTF_CLEAR(1);
}

/****************************************************************************************************/
/**
* \brief    PIT channel 2 interrupt
* \author   Gerardo Valdovinos
* \param    void 
* \return   void
*/
void interrupt  vfnPIT_Channel2_Isr( void )
{
    /* Callback for PIT channel 0 */
    if(PIT_DeviceCfg->pstPIT_ChannelsCfg[2].vpCallBack != NULL)
    {
        PIT_DeviceCfg->pstPIT_ChannelsCfg[2].vpCallBack();    
    }
    
    /* Clear interrupt flag */
    PITTF_CLEAR(2);
}

/****************************************************************************************************/
/**
* \brief    PIT channel 3 interrupt
* \author   Gerardo Valdovinos
* \param    void 
* \return   void
*/
void interrupt  vfnPIT_Channel3_Isr( void )
{
    /* Callback for PIT channel 0 */
    if(PIT_DeviceCfg->pstPIT_ChannelsCfg[3].vpCallBack != NULL)
    {
        PIT_DeviceCfg->pstPIT_ChannelsCfg[3].vpCallBack();   
    }
    
    /* Clear interrupt flag */
    PITTF_CLEAR(3);
}

/****************************************************************************************************/
/**
* \brief    PIT channel 4 interrupt
* \author   Gerardo Valdovinos
* \param    void 
* \return   void
*/
void interrupt  vfnPIT_Channel4_Isr( void )
{
    /* Callback for PIT channel 0 */
    if(PIT_DeviceCfg->pstPIT_ChannelsCfg[4].vpCallBack != NULL)
    {
        PIT_DeviceCfg->pstPIT_ChannelsCfg[4].vpCallBack();   
    }
    
    /* Clear interrupt flag */
    PITTF_CLEAR(4);
}

/****************************************************************************************************/
/**
* \brief    PIT channel 5 interrupt
* \author   Gerardo Valdovinos
* \param    void 
* \return   void
*/
void interrupt  vfnPIT_Channel5_Isr( void )
{
    /* Callback for PIT channel 0 */
    if(PIT_DeviceCfg->pstPIT_ChannelsCfg[5].vpCallBack != NULL)
    {
        PIT_DeviceCfg->pstPIT_ChannelsCfg[5].vpCallBack();    
    }
    
    /* Clear interrupt flag */
    PITTF_CLEAR(5);
}

/****************************************************************************************************/
/**
* \brief    PIT channel 6 interrupt
* \author   Gerardo Valdovinos
* \param    void 
* \return   void
*/
void interrupt  vfnPIT_Channel6_Isr( void )
{
    /* Callback for PIT channel 0 */
    if(PIT_DeviceCfg->pstPIT_ChannelsCfg[6].vpCallBack != NULL)
    {
        PIT_DeviceCfg->pstPIT_ChannelsCfg[6].vpCallBack();  
    }
    
    /* Clear interrupt flag */
    PITTF_CLEAR(6);
}

/****************************************************************************************************/
/**
* \brief    PIT channel 7 interrupt
* \author   Gerardo Valdovinos
* \param    void 
* \return   void
*/
void interrupt  vfnPIT_Channel7_Isr( void )
{
    /* Callback for PIT channel 0 */
    if(PIT_DeviceCfg->pstPIT_ChannelsCfg[7].vpCallBack != NULL)
    {
        PIT_DeviceCfg->pstPIT_ChannelsCfg[7].vpCallBack();    
    }
    
    /* Clear interrupt flag */
    PITTF_CLEAR(7);
}

#pragma CODE_SEG DEFAULT 
