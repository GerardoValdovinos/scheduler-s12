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
const tstMemAlloc* pstMemAlloc;

tstMemAllocStatus stMemAllocStatus;

tstRamPageStatus stRamPageStatus[] =
{
    {
        RAM_NULL,
        NULL,
        NULL,
        0
    }
};

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
* \brief    Memory allocation initialization
* \author   Gerardo Valdovinos
* \param    const tstMemAlloc* MemAlloc
* \return   void     
*/
void vfnMem_Init(const tstMemAlloc* MemAlloc)
{
    u8* pu8Start;
    u8* pu8End;
    u8 u8PageIndex;
    
    /* Copy pointer for future use */
    pstMemAlloc = MemAlloc;
    
    /* Verify if there are at least one Ram page */
    if(pstMemAlloc->u8RamPages != 0)
    {
        /* Copy number of pages to status struct */
        stMemAllocStatus.u8RamPages = pstMemAlloc->u8RamPages;
        
        /* Copy pointer to pages to status struct */
        stMemAllocStatus.pstRamPageStatus = (tstRamPageStatus*)&stRamPageStatus[0];
        
        for(u8PageIndex = 0;u8PageIndex < pstMemAlloc->u8RamPages; u8PageIndex++)
        {
            /* Copy to locar variables */
            pu8Start = pstMemAlloc->pstRamPage[u8PageIndex].pu8Start;
            pu8End = pstMemAlloc->pstRamPage[u8PageIndex].pu8End;
            
            /* Update all entries in status struct */
            stMemAllocStatus.pstRamPageStatus[u8PageIndex].eRamPageID = pstMemAlloc->pstRamPage[u8PageIndex].eRamPageID;    
            stMemAllocStatus.pstRamPageStatus[u8PageIndex].pu8Current = pu8Start;         
            stMemAllocStatus.pstRamPageStatus[u8PageIndex].pu8End = pu8End;               
            stMemAllocStatus.pstRamPageStatus[u8PageIndex].u16FreeBytes = (u16)(pu8End - pu8Start + 1); 
            
            /* Erase Ram in order to assure all entries are ready to be used */
            vfnMem_Erase(pu8Start, stMemAllocStatus.pstRamPageStatus[u8PageIndex].u16FreeBytes);  
        }
    }
}

/****************************************************************************************************/
/**
* \brief    Reserve a Ram memory space
* \author   Gerardo Valdovinos
* \param    u16 u16Size
* \return   u8*     
*/
u8* pu8fnMem_Reserve(u16 u16Size)
{
    u8 u8PageIndex;
    u8* pu8AllocatedBuffer = NULL;
    u8* pu8StartAddress;
    u8* pu8EndAddress;

    /* Search through Ram pages */
    for(u8PageIndex = 0; u8PageIndex < stMemAllocStatus.u8RamPages; u8PageIndex++)
    {
        pu8StartAddress = stMemAllocStatus.pstRamPageStatus[u8PageIndex].pu8Current;
        pu8EndAddress = stMemAllocStatus.pstRamPageStatus[u8PageIndex].pu8End;
        
        /* Apply alignment of 4 bytes. Start addres always starts in a 4 bytes alingned address */
        pu8StartAddress = (u8*)( ((u16)(pu8StartAddress) + 3) & 0xFFFC );
        
        /* Verify if enough memory is free in Ram page */
        if((u16)(pu8EndAddress - pu8StartAddress + 1) >= u16Size)
        {
            /* Memory space available, return pointer to start address */
            pu8AllocatedBuffer = pu8StartAddress;
            stMemAllocStatus.pstRamPageStatus[u8PageIndex].pu8Current = pu8StartAddress + u16Size;
            stMemAllocStatus.pstRamPageStatus[u8PageIndex].u16FreeBytes = (u16)(pu8EndAddress - pu8StartAddress - u16Size + 1);
            
            /* Stop searching through pages */
            break; 
        }
    }

    return pu8AllocatedBuffer;      
}
/****************************************************************************************************/
/**
* \brief    Erase Ram memory
* \author   Gerardo Valdovinos
* \param    u8* u8StartAddress, u16 u16Size
* \return   void     
*/
void vfnMem_Erase(u8* u8StartAddress, u16 u16Size)
{
    u16 u16Bytes;

    for(u16Bytes = 0;u16Bytes < u16Size; u16Bytes++)
    {                
        *u8StartAddress++ = 0;
    }
}

/****************************************************************************************************/