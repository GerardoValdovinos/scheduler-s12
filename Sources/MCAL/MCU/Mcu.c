/*******************************************************************************/
/**
\file       Mcu.c
\brief      Microcontroller functions.
\author     Gerardo Valdovinos
\version    1.0
\date       08/10/2014
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Own headers */
#include "Mcu.h"
/** Used modules */

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/
/* Global Frequency Bus */
u32 u32BusFreq;
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
* \brief    Mcu init. Initialize PLL
* \author   Gerardo Valdovinos
* \param    void 
* \return   void
*/
void Mcu_Init( void )
{
    Mcu_InitClock();
    Mcu_DistributePllClock();
    u32BusFreq = BUS_FREQ_MHZ * (u32)1000000;
}

/****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    Initialize Clock
* \author   Gerardo Valdovinos
* \param    void 
* \return   void
*/
void Mcu_InitClock( void )
{   
    u8 Syndiv, VcoFrq, Refdiv, RefFrq;
    
    Syndiv = SYNDIV_REG - 1;
    VcoFrq = VCOFRQ;
    Refdiv = REFDIV_REG - 1;
    RefFrq = REFFRQ;
    
    // **** S12XE PLL_init ****

    PLLCTL = 0B00000001;            // CME=0,PLLON=0,FM1=0,FM2=0,FSTWKP=0,PRE=0,PCE=0,SCME=1
    CLKSEL = 0B00000011;            // PLLSEL=0,PSTP=0,PLLWAI=0,RTIWAI=1,COPWAI=1
    SYNR = (u8)(VcoFrq | Syndiv);   // Set the multiplier register
    REFDV = (u8)(RefFrq | Refdiv);  // Set the divider register
    POSTDIV = POSTDIV_REG;          // Set the post divider register

}

/****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    Distribute PLL clock
* \author   Gerardo Valdovinos
* \param    void 
* \return   void
*/
void Mcu_DistributePllClock( void )
{
    PLLCTL_PLLON = 1;       // Enable the Phase Lock Loop
    while(!CRGFLG_LOCK);    // Wait till the PLL VCO is within tolerance

    CLKSEL_PLLSEL = 1;      // Select clock source from PLLCLK
    //ECLKCTL_NECLK=0;      // Enable the BusClk output at ECLK pin
}

/****************************************************************************************************/