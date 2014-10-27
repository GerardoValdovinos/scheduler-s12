 /****************************************************************************************************/
/**

\file       Gpt_Cfg.h
\brief      General Purpose Timer Configuration
\author     Gerardo Valdovinos
\version    1.0
\date       08/10/2014
*/
/****************************************************************************************************/

/****************************************************************************************************/

#ifndef __GPT_CFG_H
#define __GPT_CFG_H


/*****************************************************************************************************
* Include files
*****************************************************************************************************/
#include <hidef.h>          /* common defines and macros */
#include "derivative.h"     /* derivative-specific definitions */
#include "Typedefs.h"
/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs
*****************************************************************************************************/

/*-- Macros ------------------------------------------------------------------*/
// uTimer enum
typedef enum
{
    PIT_uTimer0,
    PIT_uTimer1,
    PIT_Null  
}tePIT_uTimer;      

// PIT channel configuration
typedef struct
{
    tePIT_uTimer                ePIT_uTimer;        //uTimer selected
    u16                         u16Time_us;         //Time in microseconds
    u16                         u16Freq_hz;         //Frequency in hertz
    vpfn                        vpCallBack;         //Callback function      
}tstPIT_ChannelCfg;

// PIT device configuration
typedef struct
{
    u8                          u8PIT_Channels;     //Number of PIT channels activated
    u8                          u8PIT_uTimer0;      //uTimer0 value
    u8                          u8PIT_uTimer1;      //uTimer1 value
    const tstPIT_ChannelCfg*    pstPIT_ChannelsCfg; //Pointer to PIT Channel structure       
}tstPIT_DeviceCfg;

// GPT device configuration
typedef struct
{
    const tstPIT_DeviceCfg*     pstPIT_DeviceCfg;   //Pointer to PIT device
    //const tstTIM_DeviceCfg*   //Reserved for TIM
}tstGpt_DeviceCfg;

// GPT driver configuration
typedef struct
{
    u8                          u8Gpt_Devices;      //Number of GPT devices
    const tstGpt_DeviceCfg*     pstGpt_DevicesCfg;  //Pointer to GPT device structure   
}tstGpt_DriverCfg;

/*-- Function Prototypes -----------------------------------------------------*/

extern  const tstGpt_DriverCfg stGpt_DriverCfg[];

#endif /* __GPT_CFG_H */

/*******************************************************************************/