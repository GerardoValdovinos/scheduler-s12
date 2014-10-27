/*******************************************************************************/
/**
\file       Gpt_Cfg.c
\brief      General Purpose Timer Configuration
\author     Gerardo Valdovinos
\version    1.0
\date       08/10/2014
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Own headers */
#include "Gpt_Cfg.h"
/** Used modules */

/*****************************************************************************************************
* Definition of module wide EXTERNs 
*****************************************************************************************************/
extern void SchM_OsTick(void);

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/
const tstPIT_ChannelCfg stPIT_ChannelCfg[] =
{
    {
        PIT_uTimer0,    //uTimer selected
        500,            //Time in microseconds
        2000,           //Frequency in hertz
        SchM_OsTick     //Callback function  
    }
/*    {
        PIT_uTimer0     //uTimer selected
        500,            //Time in microseconds
        2000,           //Frequency in hertz
        vpfn            //Callback function  
    }, 
    {
        PIT_uTimer0     //uTimer selected
        500,            //Time in microseconds
        2000,           //Frequency in hertz
        vpfn            //Callback function  
    },
    {
        PIT_uTimer0     //uTimer selected
        500,            //Time in microseconds
        2000,           //Frequency in hertz
        vpfn            //Callback function  
    },
    {
        PIT_uTimer0     //uTimer selected
        500,            //Time in microseconds
        2000,           //Frequency in hertz
        vpfn            //Callback function  
    },
    {
        PIT_uTimer0     //uTimer selected
        500,            //Time in microseconds
        2000,           //Frequency in hertz
        vpfn            //Callback function  
    },
    {
        PIT_uTimer0     //uTimer selected
        500,            //Time in microseconds
        2000,           //Frequency in hertz
        vpfn            //Callback function  
    },
    {
        PIT_uTimer0     //uTimer selected
        500,            //Time in microseconds
        2000,           //Frequency in hertz
        vpfn            //Callback function  
    },*/     
};

const tstPIT_DeviceCfg stPIT_DeviceCfg[] =
{
    sizeof(stPIT_ChannelCfg)/sizeof(stPIT_ChannelCfg[0]),   //Number of PIT channels activated
    100,                //uTimer0 value
    100,                //uTimer1 value   
    &stPIT_ChannelCfg[0]                                    //Pointer to PIT Channel structure
};

const tstGpt_DeviceCfg stGpt_DeviceCfg[] = 
{
    &stPIT_DeviceCfg[0]                                     //Pointer to PIT device
};

const tstGpt_DriverCfg stGpt_DriverCfg[] =
{
    sizeof(stGpt_DeviceCfg)/sizeof(stGpt_DeviceCfg[0]),     //Number of GPT devices
    &stGpt_DeviceCfg[0]                                     //Pointer to GPT device structure
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

/*****************************************************************************************************
* Code of module wide FUNCTIONS
****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    Initialize scheduler function
* \author   Gerardo Valdovinos
* \param    void 
* \return   void
*/

/****************************************************************************************************/