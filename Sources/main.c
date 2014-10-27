/*******************************************************************************/
/**
\file       main.c
\brief      Main function.
\author     Gerardo Valdovinos
\version    1.0
\date       8/10/2014
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Own headers */
#include "main.h"
/** Used modules */

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/

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
* \brief    Main function
* \author   Gerardo Valdovinos
* \param    void 
* \return   void
*/
void main(void) 
{
    /* Port Initialization */
    Gpio_Init();
       
    /* Mcu Initialization */
    Mcu_Init();
    
    /* Gpt Initialization */
    Gpt_Init(&stGpt_DriverCfg[0]);
 
    /* Scheduler Initialization */
    SchM_Init(&stSchM_TaskCfg[0]);
       
    EnableInterrupts;

    /* Scheduler start. Never get back */
    SchM_Start();

}
/****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    Gpio Initialization
* \author   Gerardo Valdovinos
* \param    void 
* \return   void
*/
void Gpio_Init(void)
{
    /* Data Port A initialization */
    PORTA = 0x00u;
    /* Data Direction Register Setup */
    DDRA =  0xFFu;
    /* Data Direction Register Setup for Port P */
    DDRP =  0x00;    
}






