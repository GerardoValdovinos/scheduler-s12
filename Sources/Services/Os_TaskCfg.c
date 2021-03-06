/*******************************************************************************/
/**
\file       Os_TaskCfg.c
\brief      Operative System Task Configuration
\author     Gerardo Valdovinos
\version    1.0
\date       03/11/2014
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Own headers */
#include "Os_TaskCfg.h"
#include "Os_Task.h"
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

/* WARNING: Tasks have to be ordered by priority, from low to high */
const tstOs_Task astOs_Task[] =
{
    {
        (TaskType)TASK0,    // Task ID
        PRIORITY0,          // Priority
        MASK_1ms,           // Mask
        OFFSET1,            // Offset
        Task_1ms            // Callback
    },
    {
        (TaskType)TASK1,    // Task ID
        PRIORITY0,          // Priority
        MASK_2ms,           // Mask
        OFFSET2,            // Offset
        Task_2ms            // Callback
    },
    {
        (TaskType)TASK2,    // Task ID
        PRIORITY1,          // Priority
        MASK_4ms,           // Mask
        OFFSET3,            // Offset
        Task_4ms            // Callback
    },  
    {
        (TaskType)TASK3,    // Task ID
        PRIORITY1,          // Priority
        MASK_64ms,          // Mask
        OFFSET4,            // Offset
        Task_64ms           // Callback
    },
    {
        (TaskType)TASK4,    // Task ID
        PRIORITY1,          // Priority
        MASK_128ms,         // Mask
        OFFSET5,            // Offset
        Task_128ms          // Callback
    }      
};

const tstOs_TaskCfg stOs_TaskCfg[] =
{
    sizeof(astOs_Task)/sizeof(astOs_Task[0]),
    &astOs_Task[0]
};

/*****************************************************************************************************
* Code of module wide FUNCTIONS
****************************************************************************************************/
