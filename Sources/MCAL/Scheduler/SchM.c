/*******************************************************************************/
/**
\file       SchM.c
\brief      Shceduler Module
\author     Gerardo Valdovinos
\version    1.0
\date       22/10/2014
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Own headers */
#include "SchM.h"
/** Used modules */

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/
//tstSchM_Task* pstSchM_Task;
const tstSchM_TaskCfg* pstSchM_TaskCfg;
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
* \brief    Scheduler initialization
* \author   Gerardo Valdovinos
* \param    void
* \return   void     
*/
void SchM_Init(const tstSchM_TaskCfg* SchM_TaskCfg)
{
    pstSchM_TaskCfg = SchM_TaskCfg;       
}
/****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    Scheduler De-initialization
* \author   Gerardo Valdovinos
* \param    void
* \return   void     
*/
void SchM_DeInit(void)
{
    pstSchM_TaskCfg = NULL;    
}
/****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    Scheduler start
* \author   Gerardo Valdovinos
* \param    void
* \return   void     
*/
void SchM_Start(void)
{
    /* Initialize OsTick timer */
    Gpt_EnableNotification(0);
    Gpt_StartTimer(0);
    
    /* Go to a background task */
    SchM_Background();
}
/****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    Scheduler OsTick callback 
* \author   Gerardo Valdovinos
* \param    void
* \return   void     
*/
void SchM_OsTick(void)
{
    u8 u8IndexTable;
    u8 u8Mask;
    u8 u8Offset;
    u8 u8MaskOffset;
    static u8 u8OsTick = 0;
    
    /********************
     * Increment OsTick *
     ********************/
    u8OsTick++;
    
    /* Search an available task to execute */
    for(u8IndexTable = 0; u8IndexTable < pstSchM_TaskCfg->u8NumberOfTasks; u8IndexTable++)
    {
        /* Copy to local variables */
        u8Mask = pstSchM_TaskCfg->pstSchM_Task[u8IndexTable].u8Mask;
        u8Offset = pstSchM_TaskCfg->pstSchM_Task[u8IndexTable].u8Offset;
        
        /* Form the real mask (Mask + Offset) */
        u8MaskOffset = (u8Mask + u8Offset) & u8Mask;
        
        /* Verify match */
        if( (u8OsTick & u8Mask) == u8MaskOffset )
        {
        
            /****************
             * Execute task *
             ****************/
            pstSchM_TaskCfg->pstSchM_Task[u8IndexTable].vpCallback();
            
            break;
        }
    }
           
}
/****************************************************************************************************/


