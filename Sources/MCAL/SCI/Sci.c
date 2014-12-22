/*******************************************************************************/
/**
\file       Sci.c
\brief      Serial communication interface (UART)
\author     Gerardo Valdovinos
\version    1.0
\date       09/12/2014
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Own headers */
#include "Sci.h"
/** Used modules */

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/
/* Pointer to driver configuration */
//const tstSciDriverCfg* pstSciDriverCfg;

/* Pointer to channels (Memory allocation) */
tstSciChannel* pstSciChannel;

/* SCI diver status */
tstSciDriver stSciDriver;

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
* \brief    SCI initialization
* \author   Gerardo Valdovinos
* \param    void
* \return   void     
*/
void vfnSci_Init(const tstSciDriverCfg* SciDriverCfg)
{
    u8 u8Index;
    
    /* Is there at least one channel configuration? */
    if(SciDriverCfg->u8ChannelsCount)
    {
        /* Allocate memory for channels */
        pstSciChannel = (tstSciChannel*)pu8fnMem_Reserve(SciDriverCfg->u8ChannelsCount * sizeof(tstSciChannel));
        
        /* Fill SCI driver */
        stSciDriver.u8ChannelsCount = SciDriverCfg->u8ChannelsCount;
        stSciDriver.pstChannels = pstSciChannel;
        
        for(u8Index = 0; u8Index < SciDriverCfg->u8ChannelsCount; u8Index++)
        {
            /* Copy channel ID to status struct */
            pstSciChannel[u8Index].eChannel = SciDriverCfg->pstChannelsCfg[u8Index].eChannel;
          
            /* Copy buffer size and callbacks to status struct */
        	pstSciChannel[u8Index].u8TxBufferSize = SciDriverCfg->pstChannelsCfg[u8Index].u8TxBufferSize;     
        	pstSciChannel[u8Index].u8RxBufferSize = SciDriverCfg->pstChannelsCfg[u8Index].u8RxBufferSize;      
        	pstSciChannel[u8Index].pfnTxCallback = SciDriverCfg->pstChannelsCfg[u8Index].pfnTxCallback;                
        	pstSciChannel[u8Index].pfnRxCallback = SciDriverCfg->pstChannelsCfg[u8Index].pfnRxCallback;
        	
        	/* Memory allocation for buffers */                        
        	pstSciChannel[u8Index].pu8TxBuffer = (u8*)pu8fnMem_Reserve(pstSciChannel[u8Index].u8TxBufferSize);        
        	pstSciChannel[u8Index].pu8RxBuffer = (u8*)pu8fnMem_Reserve(pstSciChannel[u8Index].u8RxBufferSize); 
        	
        	/* Buffers used */       
            pstSciChannel[u8Index].u8TxBufferUsed = 0;     
            pstSciChannel[u8Index].u8RxBufferUsed = 0;   
            
            /* Set baud rate */
            SCIBD_W(u8Index, SciDriverCfg->pstChannelsCfg[u8Index].u32Baudrate);
            
            /* Copy configurations for the channel */
            pstSciChannel[u8Index].u8ChannelCfg |=  
            (0x00)|
            (SciDriverCfg->pstChannelsCfg[u8Index].u8RxEnable << SCI_RE_OFFSET)|
            (SciDriverCfg->pstChannelsCfg[u8Index].u8TxEnable << SCI_TE_OFFSET)|
            (SciDriverCfg->pstChannelsCfg[u8Index].u8RxIntEnable << SCI_RIE_OFFSET)|
            (SciDriverCfg->pstChannelsCfg[u8Index].u8TxIntEnable << SCI_TIE_OFFSET);
               
            /* Set status of channel to SCI_OFF */
            pstSciChannel[u8Index].u8Status = SCI_OFF;                      
        }    
    }
}

/****************************************************************************************************/
/**
* \brief    Turn SCI port ON. Enable transmission and reception
* \author   Gerardo Valdovinos
* \param    void
* \return   void     
*/
void vfnSci_ON(teSciChannel Channel)
{
    /* Configuration for the channel */
    SCICR2_W(   Channel,
                ((pstSciChannel[Channel].u8ChannelCfg & SCI_RE_MASK) >> SCI_RE_OFFSET),
                ((pstSciChannel[Channel].u8ChannelCfg & SCI_TE_MASK) >> SCI_TE_OFFSET),
                ((pstSciChannel[Channel].u8ChannelCfg & SCI_RIE_MASK) >> SCI_RIE_OFFSET),
                ((pstSciChannel[Channel].u8ChannelCfg & SCI_TIE_MASK) >> SCI_TIE_OFFSET));
                
    /*SCICR2_W(   Channel,
            (0x0F & SCI_RE_MASK),
            (0x0F & SCI_TE_MASK),
            (0x0F & SCI_RIE_MASK),
            (0x0F & SCI_TIE_MASK)); */           
                
    /* Set status of channel to SCI_ON */
    pstSciChannel[Channel].u8Status = SCI_ON;                  
}

/****************************************************************************************************/
/**
* \brief    Turn SCI port OFF. Disable transmission and reception
* \author   Gerardo Valdovinos
* \param    void
* \return   void     
*/
void vfnSci_OFF(teSciChannel Channel)
{
    /* Configuration for the channel. Turn off RE and TE */
    SCICR2_W(   Channel,
                0,
                0,
                (pstSciChannel[Channel].u8ChannelCfg & SCI_RIE_MASK),
                (pstSciChannel[Channel].u8ChannelCfg & SCI_TIE_MASK));
                
    /* Set status of channel to SCI_OFF */
    pstSciChannel[Channel].u8Status = SCI_OFF;      
}

/****************************************************************************************************/
/**
* \brief    Send a byte to Tx.
* \author   Gerardo Valdovinos
* \param    void
* \return   void     
*/
u8 u8fnSci_TxChar(teSciChannel Channel, u8 u8Data)
{
    /* Review if channel is active */
    if(pstSciChannel[Channel].u8Status == SCI_ON)
    {
        /* Review if transmit buffer is empty */
        if( SCISR1_R(Channel,SCI_TDRE_BIT) )
        {
            /* Send byte */
            SCIDRL_W(Channel, u8Data); 
            
            /* Change status of driver */
            //pstSciChannel[Channel].u8Status = SCI_TX_BUSY;
            
            return TRUE;                 
        }                   
    } 
    return FALSE;  
}

/****************************************************************************************************/