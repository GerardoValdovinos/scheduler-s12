/****************************************************************************************************/
/**

\file       Ect.h
\brief      Enhanced Capture Timer
\author     Gerardo Valdovinos
\version    1.0
\date       18/11/2014
*/
/****************************************************************************************************/

/****************************************************************************************************/

#ifndef __ECT_H
#define __ECT_H


/*****************************************************************************************************
* Include files
*****************************************************************************************************/
#include "Ect_Cfg.h"
#include "Mem.h"    
/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs
*****************************************************************************************************/
/* ICOVW Macro */
#define ICOVW_SET(Channel)                  ECT_ICOVW |= (1 << Channel)   

/* TIE Macro */
#define TIE_SET(Channel)                    ECT_TIE |= (1 << Channel) 
#define TIE_CLEAR(Channel)                  ECT_TIE &= ~(1 << Channel)

/* TCTL Macro */
#define TCTL4_SET(Channel)                  ECT_TCTL4 |= (2 << (Channel * 2))
#define TCTL3_SET(Channel)                  ECT_TCTL3 |= (2 << ((Channel - 4) * 2)) 

#define TCTL4_CLEAR(Channel)                ECT_TCTL4 &= ~(2 << (Channel * 2))
#define TCTL3_CLEAR(Channel)                ECT_TCTL3 &= ~(2 << ((Channel - 4) * 2)) 
 
/*-- Macros ------------------------------------------------------------------*/
typedef struct
{
    teEctCh                     eChannel;
    u16                         u16PulseTime;  
}tstEctChannel;

typedef struct
{
    u8                          u8Channels;
    const tstEctChannel*        pstChannel;    
}tstEctDriver;

/*-- Function Prototypes -----------------------------------------------------*/
void Ect_Init(const tstEctDriverCfg* EctDriverCfg);
void Ect_Enable(teEctCh Channel);
void Ect_Disable(teEctCh Channel);

/** ECT Channel 0 ISR --> Main CPU  */
#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt  vfnECT_Channel0_Isr(void);

#pragma CODE_SEG DEFAULT 

#endif /* __ECT_H */

/*******************************************************************************/