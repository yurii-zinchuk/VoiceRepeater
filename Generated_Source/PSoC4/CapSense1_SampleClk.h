/*******************************************************************************
* File Name: CapSense1_SampleClk.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_CapSense1_SampleClk_H)
#define CY_CLOCK_CapSense1_SampleClk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void CapSense1_SampleClk_StartEx(uint32 alignClkDiv);
#define CapSense1_SampleClk_Start() \
    CapSense1_SampleClk_StartEx(CapSense1_SampleClk__PA_DIV_ID)

#else

void CapSense1_SampleClk_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void CapSense1_SampleClk_Stop(void);

void CapSense1_SampleClk_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 CapSense1_SampleClk_GetDividerRegister(void);
uint8  CapSense1_SampleClk_GetFractionalDividerRegister(void);

#define CapSense1_SampleClk_Enable()                         CapSense1_SampleClk_Start()
#define CapSense1_SampleClk_Disable()                        CapSense1_SampleClk_Stop()
#define CapSense1_SampleClk_SetDividerRegister(clkDivider, reset)  \
    CapSense1_SampleClk_SetFractionalDividerRegister((clkDivider), 0u)
#define CapSense1_SampleClk_SetDivider(clkDivider)           CapSense1_SampleClk_SetDividerRegister((clkDivider), 1u)
#define CapSense1_SampleClk_SetDividerValue(clkDivider)      CapSense1_SampleClk_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define CapSense1_SampleClk_DIV_ID     CapSense1_SampleClk__DIV_ID

#define CapSense1_SampleClk_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define CapSense1_SampleClk_CTRL_REG   (*(reg32 *)CapSense1_SampleClk__CTRL_REGISTER)
#define CapSense1_SampleClk_DIV_REG    (*(reg32 *)CapSense1_SampleClk__DIV_REGISTER)

#define CapSense1_SampleClk_CMD_DIV_SHIFT          (0u)
#define CapSense1_SampleClk_CMD_PA_DIV_SHIFT       (8u)
#define CapSense1_SampleClk_CMD_DISABLE_SHIFT      (30u)
#define CapSense1_SampleClk_CMD_ENABLE_SHIFT       (31u)

#define CapSense1_SampleClk_CMD_DISABLE_MASK       ((uint32)((uint32)1u << CapSense1_SampleClk_CMD_DISABLE_SHIFT))
#define CapSense1_SampleClk_CMD_ENABLE_MASK        ((uint32)((uint32)1u << CapSense1_SampleClk_CMD_ENABLE_SHIFT))

#define CapSense1_SampleClk_DIV_FRAC_MASK  (0x000000F8u)
#define CapSense1_SampleClk_DIV_FRAC_SHIFT (3u)
#define CapSense1_SampleClk_DIV_INT_MASK   (0xFFFFFF00u)
#define CapSense1_SampleClk_DIV_INT_SHIFT  (8u)

#else 

#define CapSense1_SampleClk_DIV_REG        (*(reg32 *)CapSense1_SampleClk__REGISTER)
#define CapSense1_SampleClk_ENABLE_REG     CapSense1_SampleClk_DIV_REG
#define CapSense1_SampleClk_DIV_FRAC_MASK  CapSense1_SampleClk__FRAC_MASK
#define CapSense1_SampleClk_DIV_FRAC_SHIFT (16u)
#define CapSense1_SampleClk_DIV_INT_MASK   CapSense1_SampleClk__DIVIDER_MASK
#define CapSense1_SampleClk_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_CapSense1_SampleClk_H) */

/* [] END OF FILE */
