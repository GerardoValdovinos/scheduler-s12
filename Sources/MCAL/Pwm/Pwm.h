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
// Offset is 1 because we are using 16bit registers
//#define PWM_CHANNEL_OFFSET                  1u       
//#define PWM_OFFSET(a)                       (u8)(PWM_CHANNEL_OFFSET * a)

#define PWMPER(b)                           *( &PWMPER01 + b )
#define PWMPER_W(channel, frequency)        PWMPER(channel) = (u16)(u32BusFreq / (4 * frequency))

#define PWMDTY(b)                           *( &PWMDTY01 + b )
#define PWMDTY_W(channel, value)            PWMDTY(channel) = value

#define PWME_SET(channel)                   PWME |= (1 << ( (channel * 2) + 1) )
#define PWME_CLEAR(channel)                 PWME &= ~(1 << ( (channel * 2) + 1) )

/*-- Function Prototypes -----------------------------------------------------*/
void vfnPwm_Init(const tstPwmDriverCfg* PwmDriverCfg);
void vfnPwm_Start(u8 u8Channel);
void vfnPwm_End(u8 u8Channel);
void vfnPwm_DC(u8 u8Channel, u16 u16DutyCycle);

#endif /* __PWM_H */

/*******************************************************************************/