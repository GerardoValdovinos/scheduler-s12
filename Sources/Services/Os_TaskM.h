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
#include "Os_Types.h"

/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs
*****************************************************************************************************/

/*-- Macros ------------------------------------------------------------------*/


/*-- Function Prototypes -----------------------------------------------------*/
void Os_ActivateTask(void);
void Os_TerminateTask(void);
void Os_GetTaskID(void);
void Os_GetTaskState(void);

#endif /* __OS_TASKM_H */

/*******************************************************************************/