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
* \return   void     
*/
eOsStatus Os_ActivateTask(TaskType taskID)
{   
    if(taskID < pstOs_QueueBuffer->u8NumberOfQueues)
    {            
        /*********************************************
         * Put task in corresponding priority buffer *
         *********************************************/
             
        /* Put task ID inside priority buffer and in corresponding index */
        PushToQueue(taskID, pstOs_TCBTask[taskID].eTCB_Priority); 
    
        /* Change task state to Ready */
        pstOs_TCBTask[taskID].u8TCB_State = READY;            

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
* \return   void     
*/
eOsStatus Os_TerminateTask(void)
{
    TaskRefType RunningTask = NULL;

    /* Get running task */
    if(E_OK == (eOsStatus)Os_GetTaskID(RunningTask))
    { 
        /* Change task state from Running to Suspended */
        pstOs_TCBTask[*RunningTask].u8TCB_State = SUSPENDED;
        
        /* Retrieve task from queue */
        (void)RetrieveFromQueue(pstOs_TCBTask[*RunningTask].eTCB_Priority);
        
        return E_OK; 
        
    }
    return E_OS_RESOURCE;        
}

/****************************************************************************************************/
/**
* \brief    Get Task ID
* \author   Gerardo Valdovinos
* \param    void
* \return   void   
*/
eOsStatus Os_GetTaskID(TaskRefType Task)
{
    Task = NULL;
    
    return E_OK;    
}

/****************************************************************************************************/
/**
* \brief    Get Task state
* \author   Gerardo Valdovinos
* \param    void
* \return   void    
*/
void Os_GetTaskState(void)
{
    
}

/****************************************************************************************************/
/**
* \brief    Push to queue
* \author   Gerardo Valdovinos
* \param    TaskType Task, tePriority ePriority
* \return   void    
*/
void PushToQueue(TaskType Task, tePriority ePriority)
{
    u8 start = pstOs_Queue[ePriority].u8Start;
    u8 end = pstOs_Queue[ePriority].u8End;
    u8 active = pstOs_Queue[ePriority].u8Active;

    /* Push new Task ID */
    pstOs_Queue[ePriority].aeTaskBuffer[end] = Task;
    
    /* Increment end index */
    end = (end + 1) % gu8BUFFER_SIZE;
    pstOs_Queue[ePriority].u8End = end;

    if (active < gu8BUFFER_SIZE)
    {
        active++;
        pstOs_Queue[ePriority].u8Active = active;
    } 
    else 
    {
        /* Overwriting the oldest. Move start to next-oldest */
        //start = (start + 1) % gu8BUFFER_SIZE;        
        //pstOs_Queue[ePriority].u8Start = start;
    }
}

/****************************************************************************************************/
/**
* \brief    Get Task state
* \author   Gerardo Valdovinos
* \param    tePriority ePriority
* \return   TaskType    
*/
TaskType RetrieveFromQueue(tePriority ePriority)
{
    TaskType Task;
    
    u8 start = pstOs_Queue[ePriority].u8Start;
    u8 end = pstOs_Queue[ePriority].u8End;
    u8 active = pstOs_Queue[ePriority].u8Active;  

    if (!active)
    {
        return TASK_NULL;
    }

    Task = pstOs_Queue[ePriority].aeTaskBuffer[start];
    
    /* Increment start index */
    start = (start + 1) % gu8BUFFER_SIZE;
    pstOs_Queue[ePriority].u8Start = start;
    
    active--;
    pstOs_Queue[ePriority].u8Active = active;
    
    return Task;
}

/****************************************************************************************************/