 /****************************************************************************************************/
/**

\file       Gpt.h
\brief      General Purpose Timer functions
\author     Gerardo Valdovinos
\version    1.0
\date       08/10/2014
*/
/****************************************************************************************************/

/****************************************************************************************************/

#ifndef __GPT_H
#define __GPT_H


/*****************************************************************************************************
* Include files
*****************************************************************************************************/
#include "Typedefs.h"
#include "Gpt_Cfg.h"
/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/
extern u32 u32BusFreq;
/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs
*****************************************************************************************************/
typedef unsigned char Gpt_ChannelType;
typedef unsigned char Gpt_ValueType;

/*-- Macros ------------------------------------------------------------------*/

#define PITLD_BASE                      (0x0348)
#define PITLD_SET(channel,value)        (*( (u16*) (PITLD_BASE + (channel * 4)) ) ) = (u16)value

#define _EN(reg,channel)                reg=(reg|(1<<channel))
#define _DIS(reg,channel)               reg=(reg^(1<<channel))

#define PITCE_EN(channel)               PITCE=(PITCE|(1<<channel))
#define PITCE_DIS(channel)              PITCE=(PITCE&(~(1<<channel)))

#define PITINTE_EN(channel)             PITINTE=(PITINTE|(1<<channel))
#define PITINTE_DIS(channel)            PITINTE=(PITINTE&(~(1<<channel)))

#define PITMUX_MT(channel,microTim)     PITMUX=(PITMUX|(microTim<<channel))

#define PITTF_CLEAR(channel)            PITTF=(PITTF|(1<<channel))

#define PITFLT_EN(channel)              PITFLT=(PITFLT|(1<<channel))
#define PITFLT_DIS(channel)             PITFLT=(PITFLT&(~(1<<channel)))

/*-- Function Prototypes -----------------------------------------------------*/

//extern const tstGpt_DriverConfig* ptrConfigType;

/*-- Function Prototypes -----------------------------------------------------*/
void Gpt_Init( const tstGpt_DriverCfg* );
void Gpt_StartTimer( Gpt_ChannelType Channel ) ;
void Gpt_StopTimer( Gpt_ChannelType Channel ) ;
void Gpt_EnableNotification( Gpt_ChannelType Channel ) ;
void Gpt_DisableNotification( Gpt_ChannelType Channel ) ;

/** PIT Channel 0 ISR --> Main CPU  */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
	void interrupt  vfnPIT_Channel0_Isr(void);

	void interrupt  vfnPIT_Channel1_Isr( void  );

	void interrupt  vfnPIT_Channel2_Isr( void  );

	void interrupt  vfnPIT_Channel3_Isr( void  );

	void interrupt  vfnPIT_Channel4_Isr( void  );

	void interrupt  vfnPIT_Channel5_Isr( void  );

	void interrupt  vfnPIT_Channel6_Isr( void  );

	void interrupt  vfnPIT_Channel7_Isr( void  );
#pragma CODE_SEG DEFAULT 

#endif /* __GPT_H */

/*******************************************************************************/