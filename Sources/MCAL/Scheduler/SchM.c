/*******************************************************************************/
/**
\file       SchM.c
\brief      Shceduler Module
\author     Gerardo Valdovinos
\version    1.0
\date       22/10/2014
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Own headers */
#include "SchM.h"
/** Used modules */

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/

const tstOs_TaskCfg* pstOs_TaskCfg;     // Pointer to task array configuration
const tstOs_Task* pstOs_Task;           // Pointer to task configuration

/* This TCB should be created dinamically in Memory */
tstTCB_Task astTCB_Task[4];             // Number of tasks defined in astOs_Task[]
tstTCB stTCB;                           // Task Control Block

/* This Queue buffer should be created dinamically in Memory */
tstQueue astQueue[2];                   // Diferent priorities of tasks
tstQueueBuffer stQueueBuffer;           // Queue Buffer 

/*****************************************************************************************************
* Declaration of module wide FUNCTIONs 
*****************************************************************************************************/
void SchM_Background(void);

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
* \brief    Scheduler initialization
* \author   Gerardo Valdovinos
* \param    void
* \return   void     
*/
void SchM_Init(const tstOs_TaskCfg* Os_TaskCfg)
{
    u8 u8Index;
    u8 PriorityIndex = 0;
    
    /* Copy tasks configuration pointer */
    pstOs_TaskCfg = Os_TaskCfg;
    
    if(pstOs_TaskCfg->u8NumberOfTasks)
    {
        /* Copy task pointer */
        pstOs_Task = (tstOs_Task*)pstOs_TaskCfg->pstOs_Task;
        
        /* Copy configuration to a TCB pointer (status struct) */
        stTCB.pstTCB_Task = (tstTCB_Task*) &astTCB_Task[0];
        stTCB.u8TCB_NumberOfTasks = pstOs_TaskCfg->u8NumberOfTasks;        
    
        /* Fill task control block */
        for(u8Index = 0; u8Index < pstOs_TaskCfg->u8NumberOfTasks; u8Index++)
        {
            /* Initialize Task Control Block */
            astTCB_Task[u8Index].eTCB_Priority = pstOs_Task[u8Index].ePriority;
            astTCB_Task[u8Index].tTCB_TaskID = pstOs_Task[u8Index].tTaskID;
            astTCB_Task[u8Index].tTCB_State = (TaskStateType)SUSPENDED;            
       
        } 
         
        /* Initialize priority buffers */
        /* HARCODED. Se debieran revisar las prioridades que existen
         * y luego crear los buffers */
        for(u8Index = 0; u8Index < 2; u8Index++)  
        {
            astQueue[u8Index].ePriority = (tePriority)u8Index;
            astQueue[u8Index].u8Index = 0;
            (void)memset(&astQueue[u8Index].atTaskBuffer[0],0xFF,10);    
        }    
    }
   
    /* Copy to extern global variable */
    gu8BUFFER_SIZE = sizeof(astQueue[u8Index].atTaskBuffer)/2;
     
    /* Copy configuration to a Queue buffer pointer */
    stQueueBuffer.pstQueue = (tstQueue*) &astQueue[0];
    stQueueBuffer.u8NumberOfQueues = 2; // HARCODED. Solo hay dos prioridades 
    
    /* Operative system initialization */
    Os_Init(&stTCB, &stQueueBuffer);
    
}
/****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    Scheduler De-initialization
* \author   Gerardo Valdovinos
* \param    void
* \return   void     
*/
void SchM_DeInit(void)
{
    pstOs_TaskCfg = NULL;
    
    /* De-initialize OsTick timer */
    Gpt_DisableNotification(0);
    Gpt_StopTimer(0);    
}
/****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    Scheduler start
* \author   Gerardo Valdovinos
* \param    void
* \return   void     
*/
void SchM_Start(void)
{
    /* Initialize OsTick timer */
    Gpt_EnableNotification(0);
    Gpt_StartTimer(0);
    
    /* Go to a background task */
    SchM_Background();
}
/****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    Scheduler OsTick callback 
* \author   Gerardo Valdovinos
* \param    void
* \return   void     
*/
void SchM_OsTick(void)
{
    u8 u8IndexTable;
    u8 u8Mask;
    u8 u8Offset;
    u8 u8MaskOffset;
    static u8 u8OsTick = 0;
    
    /********************
     * Increment OsTick *
     ********************/
    u8OsTick++;
    
    /* Search an available task to execute */
    for(u8IndexTable = 0; u8IndexTable < pstOs_TaskCfg->u8NumberOfTasks; u8IndexTable++)
    {
        /* Copy to local variables */
        u8Mask = pstOs_TaskCfg->pstOs_Task[u8IndexTable].u8Mask;
        u8Offset = pstOs_TaskCfg->pstOs_Task[u8IndexTable].u8Offset;
        
        /* Form the real mask (Mask + Offset) */
        u8MaskOffset = (u8Mask + u8Offset) & u8Mask;
        
        /* Verify match */
        if( (u8OsTick & u8Mask) == u8MaskOffset )
        {       
            /*****************
             * Activate task *
             *****************/
            (void)Os_ActivateTask(astTCB_Task[u8IndexTable].tTCB_TaskID);     
            break;
        }
    }
           
}
/****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    Scheduler Background task
* \author   Gerardo Valdovinos
* \param    void
* \return   void     
*/
void SchM_Background(void)
{
    /* Loop forever */
    for(;;) 
    {
        //PORTA_PA4 = 1;
        
        /* Call Dispatcher */
        SchM_Dispatcher();
         
        _FEED_COP();    /* feeds the dog */
    }                   /* loop forever */    
}
/****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    Scheduler dispatcher. Priority 0 is higher. 
* \author   Gerardo Valdovinos
* \param    void
* \return   void     
*/
void SchM_Dispatcher(void)
{
    u8 u8QueueIndex;
    TaskType TaskID;
    
    for(u8QueueIndex = 0; u8QueueIndex < stQueueBuffer.u8NumberOfQueues; u8QueueIndex++)
    {
        if(astQueue[u8QueueIndex].u8Index)
        {
            /* Copy taskID from priority buffer */
            TaskID = (TaskType)astQueue[u8QueueIndex].atTaskBuffer[0];
            
            /* Set task state to running */
            astTCB_Task[TaskID].tTCB_State = (TaskStateType)RUNNING;
            
            /****************
             * Execute Task *
             ****************/
            pstOs_Task[TaskID].vpCallback();
            
            break;
        }
    }
}

