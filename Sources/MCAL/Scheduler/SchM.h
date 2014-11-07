/****************************************************************************************************/
/**

\file       SchM.h
\brief      Scheduler Module
\author     Gerardo Valdovinos
\version    1.0
\date       22/10/2014
*/
/****************************************************************************************************/

/****************************************************************************************************/

#ifndef __SCH_M_H
#define __SCH_M_H


/*****************************************************************************************************
* Include files
*****************************************************************************************************/
#include "Gpt.h"
#include "Typedefs.h"
#include "string.h"

/* OS includes*/
#include "Os_TaskM.h"
#include "Os_TaskCfg.h"
#include "Os_Task.h"

/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs
*****************************************************************************************************/

/*-- Macros ------------------------------------------------------------------*/
/*
typedef struct
{
    teTaskID                eTCB_TaskID;            // Task ID
    tePriority              eTCB_Priority;          // Task priority
    u8                      u8TCB_State;            // Task state  
}tstTCB_Task;

typedef struct
{
    u8                      u8TCB_NumberOfTasks;    // Number of tasks
    tstTCB_Task*            pstTCB_Task;            // Pointer to task
}tstTCB;
*/
/*-- Function Prototypes -----------------------------------------------------*/
void SchM_Init(const tstOs_TaskCfg* Os_TaskCfg);
void SchM_DeInit(void);
void SchM_Start(void);
void SchM_OsTick(void);
void SchM_Dispatcher(void);

#endif /* __SCH_M_H */

/*******************************************************************************/