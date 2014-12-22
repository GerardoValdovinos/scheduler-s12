/****************************************************************************************************/
/**

\file       Pwm.h
\brief      Pulse width modulation driver
\author     Gerardo Valdovinos
\version    1.0
\date       17/12/2014
*/
/****************************************************************************************************/

/****************************************************************************************************/

#ifndef __PWM_H
#define __PWM_H


/*****************************************************************************************************
* Include files
*****************************************************************************************************/
#include "Pwm_Cfg.h"
/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/
extern u32 u32BusFreq;
/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs
*****************************************************************************************************/

/*-- Macros ------------------------------------------------------------------*/
#define PWM_CHANNEL_OFFSET                  2u
#define PWM_OFFSET(value)                   (u8)(PWM_CHANNEL_OFFSET * value)

#define PWMPER(value)                       *(u16*)( &PWMPER0 + PWM_OFFSET(value - 1) )
#define PWMPER_W(channel, frequency)        PWMPER(channel) = (u16)(u32BusFreq / (4 * frequency))

#define PWMDTY(value)                       *(u16*)( &PWMDTY0 + PWM_OFFSET(value - 1) )
#define PWMDTY_W(channel, value)            PWMDTY(channel) = value

#define PWME_W(channel, status)             PWME |= (status << channel)

/*-- Function Prototypes -----------------------------------------------------*/
void vfnPwm_Init(const tstPwmDriverCfg* PwmDriverCfg);
void vfnPwm_Start(u8 u8Channel);
void vfnPwm_End(u8 u8Channel);

#endif /* __PWM_H */

/*******************************************************************************/