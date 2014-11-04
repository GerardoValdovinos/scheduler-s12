/****************************************************************************************************/
/**

\file       Os_Types.h
\brief      Operative System Types
\author     Gerardo Valdovinos
\version    1.0
\date       03/11/2014
*/
/****************************************************************************************************/

/****************************************************************************************************/

#ifndef __OS_TYPES_H
#define __OS_TYPES_H


/*****************************************************************************************************
* Include files
*****************************************************************************************************/
#include <hidef.h>          /* common defines and macros */
#include "derivative.h"     /* derivative-specific definitions */
#include "Typedefs.h"

/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs
*****************************************************************************************************/
typedef u16 TaskType;
typedef TaskType* TaskRefType;
typedef u8 TaskStateType;
typedef TaskStateType* TaskStateRefType;

#ifndef TASK
#define TASK(taskID)        void taskID(void)
#endif

#define DeclareTask(taskID) extern TASK(taskID)
/*-- Macros ------------------------------------------------------------------*/
typedef enum
{
    E_OK = 0,
    E_OS_ACCESS,
    E_OS_CALLEVEL,
    E_OS_ID,
    E_OS_LIMIT,
    E_OS_NOFUNC,
    E_OS_RESOURCE,
    E_OS_STATE,
    E_OS_VALUE
}eOsStatus;

/*-- Function Prototypes -----------------------------------------------------*/

#endif /* __OS_TYPES_H */

/*******************************************************************************/