/****************************************************************************************************/
/**

\file       Mem_Cfg.h
\brief      Dynamic memory allocation configuration
\author     Gerardo Valdovinos
\version    1.0
\date       02/12/2014
*/
/****************************************************************************************************/

/****************************************************************************************************/

#ifndef __MEM_CFG_H
#define __MEM_CFG_H


/*****************************************************************************************************
* Include files
*****************************************************************************************************/
#include <hidef.h>          /* common defines and macros */
#include "derivative.h"     /* derivative-specific definitions */
#include "Typedefs.h"
/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs
*****************************************************************************************************/
typedef enum 
{
    RAM_F0,
    RAM_F1,
    RAM_F2,
    RAM_F3,
    RAM_F4,
    RAM_F5,
    RAM_F6,
    RAM_F7,
    RAM_F8,
    RAM_F9,
    RAM_FA,
    RAM_FB,
    RAM_FC,
    RAM_FD,
    RAM_FE,
    RAM_FF,
    RAM_NULL
}teRamPage;

typedef struct 
{
    teRamPage           eRamPageID;   // Ram page ID
    u8*                 pu8Start;     // Start address    
    u8*                 pu8End;       // End address
}tstRamPage;

typedef struct 
{
    u8                  u8RamPages;   // Number of Ram pages
    const tstRamPage*   pstRamPage;   // Pointer to Ram page array
}tstMemAlloc;

/*-- Macros ------------------------------------------------------------------*/


/*-- Function Prototypes -----------------------------------------------------*/
extern const tstMemAlloc stMemAlloc;

#endif /* __MEM_CFG_H */

/*******************************************************************************/