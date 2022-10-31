/*******************************************************************************
* File Name: Avoice.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Avoice_ALIASES_H) /* Pins Avoice_ALIASES_H */
#define CY_PINS_Avoice_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Avoice_0			(Avoice__0__PC)
#define Avoice_0_PS		(Avoice__0__PS)
#define Avoice_0_PC		(Avoice__0__PC)
#define Avoice_0_DR		(Avoice__0__DR)
#define Avoice_0_SHIFT	(Avoice__0__SHIFT)
#define Avoice_0_INTR	((uint16)((uint16)0x0003u << (Avoice__0__SHIFT*2u)))

#define Avoice_INTR_ALL	 ((uint16)(Avoice_0_INTR))


#endif /* End Pins Avoice_ALIASES_H */


/* [] END OF FILE */
