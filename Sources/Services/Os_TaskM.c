/*******************************************************************************/
/**
\file       Os_TaskM.c
\brief      Task manager services
\author     Gerardo Valdovinos
\version    1.0
\date       30/10/2014
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Own headers */
#include "Os_TaskM.h"

/** Used modules */
//#include "SchM.h"

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/
tstTCB*         pstOs_TCB;              // Pointer to Task Control Block
tstTCB_Task*    pstOs_TCBTask;          // Pointer to a Task

tstQueueBuffer* pstOs_QueueBuffer;      // Pointer to Queue buffer
tstQueue*       pstOs_Queue;            // Pointer to Queue

u8 gu8BUFFER_SIZE;                      // Variable of queue size

TaskType RunningTask;                   // Running task
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
* \brief    Operative system initialization
* \author   Gerardo Valdovinos
* \param    void
* \return   void     
*/
void Os_Init(tstTCB* pTCB, tstQueueBuffer* pQueueBuffer)
{
    /* Copy to a global pointers */
    pstOs_TCB = pTCB;
    pstOs_TCBTask = pTCB->pstTCB_Task; 
    
    pstOs_QueueBuffer = pQueueBuffer;
    pstOs_Queue = pQueueBuffer->pstQueue;   
} 

/****************************************************************************************************/
/**
* \brief    Activate Task
* \author   Gerardo Valdovinos
* \param    void
* \return   eOsStatus     
*/
eOsStatus Os_ActivateTask(TaskType taskID)
{   
    if(taskID < pstOs_TCB->u8TCB_NumberOfTasks)
    {            
        /*********************************************
         * Put task in corresponding priority buffer *
         *********************************************/
             
        /* Put task ID inside priority buffer and in corresponding index */
        PushToQueue(taskID, pstOs_TCBTask[taskID].eTCB_Priority); 
    
        /* Change task state to Ready */
        pstOs_TCBTask[taskID].tTCB_State = (TaskStateType)READY;            

        /* Service executed without error */
        return E_OK;            

    }
    else
    {
        /* Not valid task */
        return E_OS_ID;    
    }
       
}

/****************************************************************************************************/
/**
* \brief    Terminate Task
* \author   Gerardo Valdovinos
* \param    void
* \return   eOsStatus     
*/
eOsStatus Os_TerminateTask(void)
{
    /* Get running task */
    if(E_OK == (eOsStatus)Os_GetTaskID(&RunningTask))
    { 
        /* Change task state from Running to Suspended */
        pstOs_TCBTask[RunningTask].tTCB_State = (TaskStateType)SUSPENDED;
        
        /* Retrieve task from queue */
        RetrieveFromQueue(pstOs_TCBTask[RunningTask].eTCB_Priority);
        
        return E_OK;        
    }
    else
    {
        return E_OS_RESOURCE;
    }            
}

/****************************************************************************************************/
/**
* \brief    Get Task ID
* \author   Gerardo Valdovinos
* \param    void
* \return   eOsStatus   
*/
eOsStatus Os_GetTaskID(TaskRefType pTask)
{
    u8 u8Index;
    
    /* Search for the running task */
    for(u8Index = 0; u8Index < pstOs_TCB->u8TCB_NumberOfTasks; u8Index++)
    {
        if(pstOs_TCBTask[u8Index].tTCB_State == (TaskStateType)RUNNING)
        {
            /* Copy to local variables */           
            *pTask = pstOs_TCBTask[u8Index].tTCB_TaskID;

            return E_OK;
        }       
    }
    
    /* There isn't a running task */
    pTask = NULL;
    
    return E_OS_NOFUNC;           
}

/****************************************************************************************************/
/**
* \brief    Get Task state
* \author   Gerardo Valdovinos
* \param    void
* \return   eOsStatus    
*/
eOsStatus Os_GetTaskState(TaskType taskID, TaskStateRefType stateRef)
{
    if(taskID < pstOs_TCB->u8TCB_NumberOfTasks)
    {
        stateRef = (TaskStateRefType)&pstOs_TCBTask[taskID].tTCB_State;
        
        return E_OK;
    }
    else
    {
        return E_OS_ID;
    }
}

/****************************************************************************************************/
/**
* \brief    Push to queue
* \author   Gerardo Valdovinos
* \param    TaskType Task, tePriority ePriority
* \return   void    
*/
void PushToQueue(TaskType TaskID, tePriority ePriority)
{
    u8 i;   
    u8 index = pstOs_Queue[ePriority].u8Index;
    
    if(index < gu8BUFFER_SIZE)
    {
        for(i = 0; i <= index;i++)
        {
            if( pstOs_Queue[ePriority].atTaskBuffer[i] == TaskID)
            {
                break;
            }
            else if(pstOs_Queue[ePriority].atTaskBuffer[i] == TASK_EMPTY)
            {
                /* Push new Task ID */
                pstOs_Queue[ePriority].atTaskBuffer[index] = TaskID;
                
                /* Incremente index */
                pstOs_Queue[ePriority].u8Index++;                           
            }
        }
    }
}

/****************************************************************************************************/
/**
* \brief    Get Task state
* \author   Gerardo Valdovinos
* \param    tePriority ePriority
* \return   void    
*/
void RetrieveFromQueue(tePriority ePriority)
{  
    u8 i;
    u8 index = pstOs_Queue[ePriority].u8Index;
    
    if( (index != 0) && (index <= gu8BUFFER_SIZE) )
    {
        /* Shift to left priority buffer */    
        for(i = 0; i < index; i++)
        {
            pstOs_Queue[ePriority].atTaskBuffer[i] = pstOs_Queue[ePriority].atTaskBuffer[i+1];  
        }
        
        if(index == gu8BUFFER_SIZE)
        {
            pstOs_Queue[ePriority].atTaskBuffer[index - 1] = TASK_EMPTY;
        }
        
        pstOs_Queue[ePriority].u8Index--;
    }
}

/****************************************************************************************************/