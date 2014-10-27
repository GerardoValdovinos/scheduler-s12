/****************************************************************************************************/
/**

\file       SchM_Tasks.h
\brief      Scheduler Module Tasks
\author     Gerardo Valdovinos
\version    1.0
\date       22/10/2014
*/
/****************************************************************************************************/

/****************************************************************************************************/

#ifndef __SCH_M_TASKS_H
#define __SCH_M_TASKS_H


/*****************************************************************************************************
* Include files
*****************************************************************************************************/
#include "Typedefs.h"
/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs
*****************************************************************************************************/

/*-- Macros ------------------------------------------------------------------*/


/*-- Function Prototypes -----------------------------------------------------*/
void SchM_Task_1ms(void);
void SchM_Task_4ms(void);
void SchM_Task_8ms(void);
void SchM_Task_16ms(void);
void SchM_Task_32ms(void);
void SchM_Task_64ms(void);
void SchM_Background(void);

#endif /* __SCH_M_TASKS_H */

/*******************************************************************************/