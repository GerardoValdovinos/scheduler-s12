/****************************************************************************************************/
/**

\file       main.h
\brief      Header for main functions
\author     Gerardo Valdovinos
\version    1.0
\date       08/10/2014
*/
/****************************************************************************************************/

/****************************************************************************************************/

#ifndef __MAIN_H
#define __MAIN_H


/*****************************************************************************************************
* Include files
*****************************************************************************************************/
#include "Typedefs.h"
#include "Mcu.h"
#include "Gpt.h"
#include "SchM.h"
#include "Ect.h"

/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs
*****************************************************************************************************/

/*-- Macros ------------------------------------------------------------------*/


/*-- Function Prototypes -----------------------------------------------------*/
void main( void );
void Gpio_Init(void);

#endif /* __MAIN_H */

/*******************************************************************************/