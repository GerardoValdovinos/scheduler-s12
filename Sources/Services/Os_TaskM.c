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
tstTCB* pstOs_TCB;
tstQueueBuffer* pstOs_QueueBuffer;
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
    pstOs_QueueBuffer = pQueueBuffer;   
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
    u8 u8Priority;
    u8 u8Index;
    u8 u8BufferSize;
    u8 i;
    
    if(taskID < pstOs_QueueBuffer->u8NumberOfQueues)
    {     
        /* Get priority of the task */
        u8Priority = (u8)pstOs_TCB->pstTCB_Task[taskID].eTCB_Priority;
        
        /* Get size of priority buffer */
        u8BufferSize = pstOs_QueueBuffer->pstQueue[u8Priority].u8Size;   
                     
        /* Inside a priority buffer get the actual index */
        u8Index = pstOs_QueueBuffer->pstQueue[u8Priority].u8Index;
        
        /* Search more than one activation of the task */
        for(i = 0; i <= u8Index; i++)
        {
            if(pstOs_QueueBuffer->pstQueue[u8Priority].au8Buffer[i] == taskID)
            {
                /* Task already activated */
                return E_OS_LIMIT;
            }
        }
        
        /*********************************************
         * Put task in corresponding priority buffer *
         *********************************************/
             
        /* Put task ID inside priority buffer and in corresponding index */
        pstOs_QueueBuffer->pstQueue[u8Priority].au8Buffer[u8Index] = (u8)taskID; 
    
        /* Change task state to Ready */
        pstOs_TCB->pstTCB_Task[taskID].u8TCB_State = READY;            
        
        /* Increment buffer index */
        if(u8Index < (u8BufferSize - 1))
        {
            pstOs_QueueBuffer->pstQueue[u8Priority].u8Index++;   
        }

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
void Os_TerminateTask(void)
{
    
}

/****************************************************************************************************/
/**
* \brief    Get Task ID
* \author   Gerardo Valdovinos
* \param    void
* \return   void   
*/
void Os_GetTaskID(void)
{
    
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
