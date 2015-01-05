/****************************************************************************************************/
/**

\file       Pwm_Cfg.h
\brief      Pulse width modulation configuration
\author     Gerardo Valdovinos
\version    1.0
\date       17/12/2014
*/
/****************************************************************************************************/

/****************************************************************************************************/

#ifndef __PWM_CFG_H
#define __PWM_CFG_H


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

typedef enum
{
    PWM_CH01 = 0,
    PWM_CH23,       
    PWM_CH45,      
    PWM_CH67          
}tePwmCh;
    
typedef struct
{
    u8                      u8Channel16;    // Pwm channel
    u16                     u16Frequency;   // Pwm frequency
    u16                     u16DutyCycle;   // Pwm Duty cycle initial
}tstPwmChannelCfg;

typedef struct
{
    u8                      u8Channels;     // Number of channels
    const tstPwmChannelCfg* stChannelCfg;   // Pointer to channels configuration
}tstPwmDriverCfg;
  
/*-- Function Prototypes -----------------------------------------------------*/
extern const tstPwmDriverCfg stPwmDriverCfg;

#endif /* __PWM_CFG_H */

/*******************************************************************************/