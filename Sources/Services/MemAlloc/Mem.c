/*******************************************************************************/
/**
\file       Mem.c
\brief      Dinamic memory allocation
\author     Gerardo Valdovinos
\version    1.0
\date       02/12/2014
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Own headers */
#include "Mem.h"

/** Used modules */

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/
tstMemAllocStatus stMemAllocStatus;
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
* \brief    
* \author   Gerardo Valdovinos
* \param    void
* \return   void     
*/
void vfnMem_Init(const tstMemAlloc* MemAlloc)
{
    u8* pu8Start;
    u8* pu8End;
    u8 u8PageIndex;
    
    /* Verify if there are at least one Ram page */
    if(MemAlloc->u8RamPages != 0)
    {
        /* Copy number of pages to status struct */
        stMemAllocStatus.u8RamPages = MemAlloc->u8RamPages;
        
        for(u8PageIndex = 0;u8PageIndex < MemAlloc->u8RamPages; u8PageIndex++)
        {
            /* Copy to locar variables */
            pu8Start = MemAlloc->pstRamPage[u8PageIndex].pu8Start;
            pu8End = MemAlloc->pstRamPage[u8PageIndex].pu8End;
            
            /* Update all entries in status struct */
            stMemAllocStatus.pstRamPageStatus[u8PageIndex].eRamPageID = MemAlloc->pstRamPage[u8PageIndex].eRamPageID;    
            stMemAllocStatus.pstRamPageStatus[u8PageIndex].pu8Current = pu8Start;         
            stMemAllocStatus.pstRamPageStatus[u8PageIndex].pu8End = pu8End;               
            stMemAllocStatus.pstRamPageStatus[u8PageIndex].u16FreeBytes = (u16)(pu8End - pu8Start + 1); 
            
            /* Erase Ram in order to assure all entries are ready to be used */
            vfnMem_Erase(pu8Start, stMemAllocStatus.pstRamPageStatus[u8PageIndex].u16FreeBytes)  
        }
    }
}

/****************************************************************************************************/