/*******************************************************************************/
/**
\file       Control.c
\brief      Control of Pendubot
\author     Gerardo Valdovinos
\version    1.0
\date       25/11/2014
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Own headers */
#include "Control.h"
#include "fixmath.h"
/** Used modules */

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/
fix16_t fxPWM;

//volatile extern u16 u16PulseTime;
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
* \brief    Control of pendubot
* \author   Gerardo Valdovinos
* \param    void
* \return   void    
*/
void vfnCtrl_Pendubot(void)
{
    //fxPWM = fix16_from_float(3.16);
    //fxPWM += u16PulseTime;    
}
/****************************************************************************************************/