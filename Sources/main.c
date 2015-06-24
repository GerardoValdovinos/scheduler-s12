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
void vfnSPIInit(void)
{
    SPI0CR1 =   SPI0CR1_SPE_MASK | //SPI0CR1_SPTIE_MASK |               
                SPI0CR1_MSTR_MASK |
                SPI0CR1_SSOE_MASK;
                
    SPI0CR2 =   SPI0CR2_XFRW_MASK | SPI0CR2_MODFEN_MASK;
    //SPI0CR2_MODFEN = 1;            
                
    SPI0BR_SPPR = 0;
    SPI0BR_SPR = 1;                                
}

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
    //vfnPwm_Init(&stPwmDriverCfg);
      
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

    vfnSPIInit();
    
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


/****************************************************************************************************/



