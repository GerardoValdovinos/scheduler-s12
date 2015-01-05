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
    
    /* Pwm Initialization */
    vfnPwm_Init(&stPwmDriverCfg);
      
    /* Memory allocation Initialization */
    vfnMem_Init(&stMemAlloc);
    
    /* Ect Initialization */
    Ect_Init(&stEctDriverCfg);
        
    /* Serial Communication interface Initialization */
    vfnSci_Init(&stSciDriverCfg);
 
    /* Scheduler Initialization */
    SchM_Init(&stOs_TaskCfg[0]);
    
    /* Enable Interrupts */   
    EnableInterrupts;

    /************************ 
     * Peripherals start    *
     ************************/
    /* Input capture start */
    //Ect_Enable(ECT_CH0);
    
    /* Pwm start */
    //vfnPwm_Start(PWM_CH01);
    
    /* SCI channel 0 start */
    vfnSci_ON(SCI_CH0);
    
    
    /***********************************
     * Scheduler start. Never get back *
     ***********************************/
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
    
    // Solo para pruebas. Activacion del pull-up del puerto T
    DDRT = 0x00;
    PERT_PERT0 = 1;  
}






