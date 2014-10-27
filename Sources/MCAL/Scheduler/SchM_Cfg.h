/****************************************************************************************************/
/**

\file       SchM_Cfg.h
\brief      Scheduler Module Configuration 
\author     Gerardo Valdovinos
\version    1.0
\date       22/10/2014
*/
/****************************************************************************************************/

/****************************************************************************************************/

#ifndef __SCH_M_CFG_H
#define __SCH_M_CFG_H


/*****************************************************************************************************
* Include files
*****************************************************************************************************/
#include <hidef.h>          /* common defines and macros */
#include "derivative.h"     /* derivative-specific definitions */
#include "Typedefs.h"

#include "SchM_Tasks.h"
/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs
*****************************************************************************************************/

/*-- Macros ------------------------------------------------------------------*/
/*
typedef enum
{
    TASK0,
    TASK1,
    TASK2,
    TASK3,
    TASK4,
    TASK5,
    TASK6    
}teTask;
 */
#define MASK_1ms        (0b00000001)
#define MASK_2ms        (0b00000011)
#define MASK_4ms        (0b00000111)
#define MASK_8ms        (0b00001111)
#define MASK_16ms       (0b00011111)
#define MASK_32ms       (0b00111111)
#define MASK_64ms       (0b01111111)
#define MASK_128ms      (0b11111111)

#define OFFSET0         (0)
#define OFFSET1         (1)
#define OFFSET2         (2)
#define OFFSET3         (3)
#define OFFSET4         (4)
#define OFFSET5         (5)
#define OFFSET6         (6)
#define OFFSET7         (7)
#define OFFSET8         (8)
 
typedef struct
{
    //teTask                  eTask;              // Task ID
    u8                      u8Mask;             // Mask of task
    u8                      u8Offset;           // Offset of task
    vpfn                    vpCallback;         // Task Callback    
}tstSchM_Task;

typedef struct
{
    u8                      u8NumberOfTasks;    // Number of tasks
    const tstSchM_Task*     pstSchM_Task;       // Pointer to a task configuration
}tstSchM_TaskCfg;

/*-- Function Prototypes -----------------------------------------------------*/

extern const tstSchM_TaskCfg stSchM_TaskCfg[];

#endif /* __SCH_M_CFG_H */

/*******************************************************************************/