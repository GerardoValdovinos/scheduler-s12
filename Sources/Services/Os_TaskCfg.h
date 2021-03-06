/****************************************************************************************************/
/**

\file       Os_TaskCfg.h
\brief      Operative System Task Configuration 
\author     Gerardo Valdovinos
\version    1.0
\date       03/11/2014
*/
/****************************************************************************************************/

/****************************************************************************************************/

#ifndef __OS_TASK_CFG_H
#define __OS_TASK_CFG_H


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

typedef enum
{
    TASK0,
    TASK1,
    TASK2,
    TASK3,
    TASK4,
    TASK5,
    TASK6,
    TASK7,
    
    TASK_NULL    
}teTaskID;

#define TASK_EMPTY      (0xFFFF)

typedef enum
{
    PRIORITY0 = 0,
    PRIORITY1,
    PRIORITY2,
    PRIORITY3,
    PRIORITY4,
    PRIORITY5,
    PRIORITY6,
    PRIORITY7,
    PRIORITY8,
    
    PRIORITY_NULL
}tePriority;

#define MASK_1ms        (0b00000001)
#define MASK_2ms        (0b00000011)
#define MASK_4ms        (0b00000111)
#define MASK_8ms        (0b00001111)
#define MASK_16ms       (0b00011111)
#define MASK_32ms       (0b00111111)
#define MASK_64ms       (0b01111111)
#define MASK_128ms      (0b11111111)

#define OFFSET1         (0)
#define OFFSET2         (1)
#define OFFSET3         (3)
#define OFFSET4         (7)
#define OFFSET5        (15)
#define OFFSET6        (31)

/* Configuration typedefs */ 
typedef struct
{
    TaskType                tTaskID;            // Task ID
    tePriority              ePriority;          // Task priority
    u8                      u8Mask;             // Mask of task
    u8                      u8Offset;           // Offset of task
    vpfn                    vpCallback;         // Task Callback    
}tstOs_Task;

typedef struct
{
    u8                      u8NumberOfTasks;    // Number of tasks
    const tstOs_Task*       pstOs_Task;         // Pointer to a task configuration
}tstOs_TaskCfg;

/* Status typedefs */
typedef struct
{
    TaskType                tTCB_TaskID;            // Task ID
    tePriority              eTCB_Priority;          // Task priority
    TaskStateType           tTCB_State;             // Task state  
}tstTCB_Task;

typedef struct
{
    u8                      u8TCB_NumberOfTasks;    // Number of tasks
    tstTCB_Task*            pstTCB_Task;            // Pointer to task
}tstTCB;

/* Priority buffer typedefs */
typedef struct
{
    tePriority              ePriority;
    u8                      u8Index;
    TaskType                atTaskBuffer[5];  
}tstQueue;

typedef struct
{
    u8                      u8NumberOfQueues;
    tstQueue*               pstQueue;
}tstQueueBuffer;

/*-- Function Prototypes -----------------------------------------------------*/

extern const tstOs_TaskCfg stOs_TaskCfg[];

#endif /* __OS_TASK_CFG_H */

/*******************************************************************************/