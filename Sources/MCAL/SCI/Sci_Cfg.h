/****************************************************************************************************/
/**

\file       Sci_Cfg.h
\brief      Serial communication interface (UART) configuration
\author     Gerardo Valdovinos
\version    1.0
\date       09/12/2014
*/
/****************************************************************************************************/

/****************************************************************************************************/

#ifndef __SCI_CFG_H
#define __SCI_CFG_H


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
#define ENABLE      1
#define DISABLE     0

/*-- Macros ------------------------------------------------------------------*/
typedef enum 
{
    SCI_CH0,
    SCI_CH1,
    SCI_NULL
}teSciChannel;

typedef struct 
{       
    teSciChannel	    eChannel;           // Channel
 	u32			        u32Baudrate;	    // Baudrate 
	u8			        u8TxBufferSize;     // Tx Buffer size
	u8			        u8RxBufferSize;     // Rx Buffer size 	
	vpfn	            pfnTxCallback;      // Tx Callback function          
	vpfn	            pfnRxCallback;      // Rx Callback function   	
    u8                  u8TxEnable;         // Tx Enable
    u8                  u8RxEnable;         // Rx Enable
    //u8                  u8TxIntEnable;      // Tx Interrupt enable
    //u8                  u8RxIntEnable;      // Rx Interrupt enable
}tstSciChannelCfg;


typedef struct 
{
    u8                      u8ChannelsCount;    // Number of SCI channels
    const tstSciChannelCfg* pstChannelsCfg;     // Pointer to SCI channesl configuration
}tstSciDriverCfg;

/*-- Function Prototypes -----------------------------------------------------*/

extern const tstSciDriverCfg stSciDriverCfg;


#endif /* __SCI_CFG_H */

/*******************************************************************************/