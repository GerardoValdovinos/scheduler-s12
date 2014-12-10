/****************************************************************************************************/
/**

\file       Mem.h
\brief      Dynamic memory allocation
\author     Gerardo Valdovinos
\version    1.0
\date       02/12/2014
*/
/****************************************************************************************************/

/****************************************************************************************************/

#ifndef __MEM_H
#define __MEM_H


/*****************************************************************************************************
* Include files
*****************************************************************************************************/
#include "Mem_Cfg.h"

/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/

/* Data type definitions for near memory */
typedef struct 
{
    teRamPage           eRamPageID;     // Ram page ID
    u8*                 pu8Current;     // Current address    
    u8*                 pu8End;         // End address       
    u16                 u16FreeBytes;   // Free bytes
}tstRamPageStatus;

typedef struct 
{      
    u8                  u8RamPages;         // Number of Ram pages
    tstRamPageStatus*   pstRamPageStatus;   // Pointer to Ram page array
}tstMemAllocStatus;

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs
*****************************************************************************************************/

/*-- Macros ------------------------------------------------------------------*/


/*-- Function Prototypes -----------------------------------------------------*/
void vfnMem_Init(const tstMemAlloc* MemAlloc);
u8* pu8fnMem_Reserve(u16 u16Size);
void vfnMem_Erase(u8* u8StartAddress, u16 u16Size);

#endif /* __MEM_H */

/*******************************************************************************/