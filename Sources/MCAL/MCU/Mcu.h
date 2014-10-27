 /****************************************************************************************************/
/**

\file       Mcu.h
\brief      Microcontroller functions.
\author     Gerardo Valdovinos
\version    1.0
\date       09/10/2014
*/
/****************************************************************************************************/

/****************************************************************************************************/

#ifndef __MCU_H
#define __MCU_H


/*****************************************************************************************************
* Include files
*****************************************************************************************************/
#include "Mcu_Cfg.h"
#include "Typedefs.h"

/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/
//extern u32 u32BusFreq;

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs
*****************************************************************************************************/

/*-- Macros ------------------------------------------------------------------*/

/** ~~~~~~~~~~~~ System configuration definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//If POSTDIV_REG = 0, then F_pll = F_vco
#define POSTDIV_REG         0u  

//Only SYNDIV_REG need to be calculated                 
#define REFDIV_REG          1u 
   
//Desired frequency for VCO               
#define FREQ_VCO_MHZ        (BUS_FREQ_MHZ * 2)

//SYNDIV_REG value        
#define SYNDIV_REG          ((FREQ_VCO_MHZ * REFDIV_REG)/(2 * XTAL_FREQ_MHZ))

/* VCO frequency Selection */
#if ((32 <= FREQ_VCO_MHZ) & (FREQ_VCO_MHZ <= 48))
    #define VCOFRQ         (0 << 6)    
#elif ((48 < FREQ_VCO_MHZ) & (FREQ_VCO_MHZ <= 80))
    #define VCOFRQ         (1 << 6)
#elif ((80 < FREQ_VCO_MHZ) & (FREQ_VCO_MHZ <= 120))
    #define VCOFRQ         (3 << 6)
#else
    #error "Not valid Bus frequency"
#endif
 
/* Reference clock frequency Selection */ 
#if ((1 <= XTAL_FREQ_MHZ) & (XTAL_FREQ_MHZ <= 2))
    #define REFFRQ         (0 << 6)    
#elif ((2 < XTAL_FREQ_MHZ) & (XTAL_FREQ_MHZ <= 6))
    #define REFFRQ         (1 << 6)
#elif ((6 < XTAL_FREQ_MHZ) & (XTAL_FREQ_MHZ <= 12))
    #define REFFRQ         (2 << 6)
#elif (XTAL_FREQ_MHZ < 12)
    #define REFFRQ         (3 << 6)
#else
    #error "Not valid Xtal frequency"
#endif   
    

      
/*-- Function Prototypes -----------------------------------------------------*/
extern void Mcu_Init( void );
void Mcu_InitClock( void );
void Mcu_DistributePllClock( void );

#endif /* __MCU_H */

/*******************************************************************************/