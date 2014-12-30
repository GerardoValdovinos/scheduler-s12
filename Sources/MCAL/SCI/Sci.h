/****************************************************************************************************/
/**

\file       Sci.h
\brief      Serial communication interface (UART)
\author     Gerardo Valdovinos
\version    1.0
\date       09/12/2014
*/
/****************************************************************************************************/

/****************************************************************************************************/

#ifndef __SCI_H
#define __SCI_H


/*****************************************************************************************************
* Include files
*****************************************************************************************************/
#include "Sci_Cfg.h"
#include "Mem.h"
/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/
extern u32 u32BusFreq;
/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs
*****************************************************************************************************/
#define SCI_OFF                         0u
#define SCI_ON                          1u
#define SCI_TX_BUSY                     2u
#define SCI_RX_OVERRUN                  3u

#define SCI_RE_MASK                     0x01
#define SCI_TE_MASK                     0x02
#define SCI_RIE_MASK                    0x04
#define SCI_TIE_MASK                    0x08

#define SCI_RE_OFFSET                   0
#define SCI_TE_OFFSET                   1
#define SCI_RIE_OFFSET                  2
#define SCI_TIE_OFFSET                  3

#define SCI_RE_BIT                      2
#define SCI_TE_BIT                      3
#define SCI_RIE_BIT                     5
#define SCI_TIE_BIT                     7

#define SCI_TDRE_BIT                    7
#define SCI_RDRF_BIT                    5

/*-- Macros ------------------------------------------------------------------*/

#define SCI_CHANNEL_OFFSET              8u
#define SCI_OFFSET(value)               (u8)(SCI_CHANNEL_OFFSET * value)

/* SCIBD Macro */
#define SCIBD(value)                    *( &SCI0BD + SCI_OFFSET(value) )                  
#define SCIBD_W(Channel, Bdr)           SCIBD(Channel) = (u16)((u32)(u32BusFreq) / (u32)(16 * Bdr))

/* SCICR2 Macro */
#define SCICR2(value)                   *( &SCI0CR2 + SCI_OFFSET(value) )
#define SCICR2_W(Channel, RE, TE, RIE, TIE)     SCICR2(Channel) |= (0x00)|(RE << 2)|(TE << 3)|(RIE << 5)|(TIE << 7)
#define SCICR2_SET(Channel, bit)        SCICR2(Channel) |= (1 << bit)
#define SCICR2_CLEAR(Channel, bit)      SCICR2(Channel) &= ~(1 << bit)

/* SCISR1 Macro */
#define SCISR1(value)                   *( &SCI0SR1 + SCI_OFFSET(value) )
#define SCISR1_R(Channel,bit)           (SCISR1(Channel) >> bit) & 0x01

/* SCIDRL Macro */
#define SCIDRL(value)                   *( &SCI0DRL + SCI_OFFSET(value) )
#define SCIDRL_W(Channel,value)         SCIDRL(Channel) = value 
#define SCIDRL_R(Channel)               SCIDRL(Channel) 

/*-- Typedefs-----------------------------------------------------------------*/
typedef struct 
{
    teSciChannel	    eChannel;           // Channel
    //u8                  u8ChannelCfg;       // Channel configuration
    u8                  u8Status;           // Status of channel
	u8			        u8TxBufferSize;     // Tx Buffer size
	u8			        u8RxBufferSize;     // Rx Buffer size 
	vpfn	            pfnTxCallback;      // Tx Callback function          
	vpfn	            pfnRxCallback;      // Rx Callback function
	                  
	u8*		            pu8TxBuffer;        // Pointer to Tx buffer
	u8*		            pu8RxBuffer;        // Pointer to Rx buffer
    u8*		            pu8TxBufferData;    // Pointer to Tx buffer data
	u8*		            pu8RxBufferData;    // Pointer to Rx buffer data
    u8                  u8TxBufferUsed;     // Tx buffer used
    u8                  u8RxBufferUsed;     // Rx buffer used
    
    u8                  u8TxEnable;         // Tx Enable
    u8                  u8RxEnable;         // Rx Enable
}tstSciChannel;

typedef struct 
{   
    u8                  u8ChannelsCount;    // Number of SCI channels
    tstSciChannel*      pstChannels;        // Pointer to SCI channesl 
}tstSciDriver;

/*-- Function Prototypes -----------------------------------------------------*/
void vfnSci_Init(const tstSciDriverCfg* SciDriverCfg);
void vfnSci_ON(teSciChannel Channel);
void vfnSci_OFF(teSciChannel Channel);
u8 u8fnSci_TxChar(teSciChannel Channel, u8 pu8Data);
void vfnSci_Tx(teSciChannel Channel, u8* pu8Data, u8 u8Length);

#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt  vfnSci0_TxRxIsr(void);
void interrupt  vfnSci1_TxRxIsr(void);
void vfnSci_IsrHandler(teSciChannel Channel);

#pragma CODE_SEG DEFAULT

#endif /* __SCI_H */

/*******************************************************************************/