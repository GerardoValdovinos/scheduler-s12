/****************************************************************************************************/
/**

\file       Ect_Cfg.h
\brief      Enhanced Capture Timer configuration
\author     Gerardo Valdovinos
\version    1.0
\date       18/11/2014
*/
/****************************************************************************************************/

/****************************************************************************************************/

#ifndef __ECT_CFG_H
#define __ECT_CFG_H


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
    ECT_CH0 = 0,
    ECT_CH1,
    ECT_CH2,
    ECT_CH3,
    ECT_CH4,
    ECT_CH5,
    ECT_CH6,
    ECT_CH7
}teEctCh;

typedef struct
{
    teEctCh                     eChannel;  
}tstEctChannelCfg;

typedef struct
{
    u8                          u8Channels;
    const tstEctChannelCfg*     pstChannelCfg;    
}tstEctDriverCfg;

/*-- Function Prototypes -----------------------------------------------------*/
extern const tstEctDriverCfg stEctDriverCfg;

#endif /* __ECT_CFG_H */

/*******************************************************************************/