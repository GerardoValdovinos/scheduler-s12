/****************************************************************************************************/
/**

\file       Os_TaskM.h
\brief      Task manager services
\author     Gerardo Valdovinos
\version    1.0
\date       30/10/2014
*/
/****************************************************************************************************/

/****************************************************************************************************/

#ifndef __OS_TASKM_H
#define __OS_TASKM_H


/*****************************************************************************************************
* Include files
*****************************************************************************************************/
#include "Os_TaskCfg.h"

/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/
extern u8 gu8BUFFER_SIZE;                      // Variable of queue size
/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs
*****************************************************************************************************/

/*-- Macros ------------------------------------------------------------------*/


/*-- Function Prototypes -----------------------------------------------------*/
void Os_Init(tstTCB* pTCB, tstQueueBuffer* pQueueBuffer);
// Principal function
eOsStatus Os_ActivateTask(TaskType taskID);
eOsStatus Os_TerminateTask(void);
eOsStatus Os_GetTaskID(TaskRefType Task);
void Os_GetTaskState(void);

// Internal function prototypes
void PushToQueue(TaskType Task, tePriority ePriority);
TaskType RetrieveFromQueue(tePriority ePriority);

#endif /* __OS_TASKM_H */

/*******************************************************************************/