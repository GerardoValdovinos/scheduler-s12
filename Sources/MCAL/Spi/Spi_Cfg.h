/****************************************************************************************************/
/**

\file       Spi_Cfg.h
\brief      Serial Peripheral Interface configuration
\author     Gerardo Valdovinos
\version    1.0
\date       18/11/2014
*/
/****************************************************************************************************/

/****************************************************************************************************/
#ifndef __SPI_CFG_H
#define __SPI_CFG_H
/*****************************************************************************************************
* Include files
*****************************************************************************************************/
//#include <hidef.h>          /* common defines and macros */
//#include "derivative.h"     /* derivative-specific definitions */
//#include "Typedefs.h"
/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/
#define SPI_6MHZ                1u
#define SPI_8MHZ                2u
#define SPI_12MHZ               3u
#define SPI_24MHZ               4u

#define SPI_8BITS               1u
#define SPI_16BITS              2u

#define SPI_CPOL_LOW            1u
#define SPI_CPOL_HIGH           3u
/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs
*****************************************************************************************************/

/*-- Macros ------------------------------------------------------------------*/
/*
typedef enum
{
    SPI_CH0 = 0,
    SPI_CH1,
    SPI_CH2,
}teSpiCh;

typedef struct
{
    teSpiCh                     eChannel;
    u8                          u8Speed;
    u8                          u8Bits;
    u8                          u8Cpol;  
}tstSpiChannelCfg;

typedef struct
{
    u8                          u8Channels;
    const tstSpiChannelCfg*     pstChannelCfg;    
}tstSpiDriverCfg;
*/
/*-- Function Prototypes -----------------------------------------------------*/
//extern const tstEctDriverCfg stEctDriverCfg;

#endif /* __SPI_CFG_H */

/*******************************************************************************/